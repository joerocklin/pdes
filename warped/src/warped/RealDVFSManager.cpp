// See copyright notice in file Copyright in the root directory of this archive.

#include "RealDVFSManager.h"
#include "TimeWarpSimulationManager.h"
#include "UsefulWorkMessage.h"
#include "CommunicationManager.h"
#include <utils/Debug.h>

using namespace std;

RealDVFSManager::RealDVFSManager(TimeWarpSimulationManager* simMgr,
                                 int measurementPeriod,
                                 int firsize,
                                 bool fixed,
                                 bool debug,
                                 OptimizationGoal og,
                                 UsefulWorkMetric uwm)
  :DVFSManagerImplementationBase(simMgr,
                                 measurementPeriod,
                                 firsize,
                                 fixed,
                                 debug,
                                 og,
                                 uwm)
{}

void
RealDVFSManager::poll() {
  if(checkMeasurementPeriod()) {
    // initiate the measurement cycle
    if(isMaster()) {
      int dest = (mySimulationManagerID + 1) % myNumSimulationManagers;
      UsefulWorkMessage* msg = new UsefulWorkMessage(mySimulationManagerID,
                                                       dest,
                                                       myNumSimulationManagers,
                                                       UsefulWorkMessage::COLLECT);
      myCommunicationManager->sendMessage(msg, dest);
    }
  }
}

void
RealDVFSManager::registerWithCommunicationManager() {
  myCommunicationManager->registerMessageType(UsefulWorkMessage::dataType(), this);
}

void
RealDVFSManager::configure(SimulationConfiguration &config) {
  // populate available frequencies and our CPU id, set userspace governor
  DVFSManagerImplementationBase::configure(config);

  // initialize the frequency index array now that we know how many
  // frequencies are available
  int maxidx = myAvailableFreqs.size() - 1;

  // maxidx - 1: only go down to 1.5 GHz
  initializeFrequencyIdxs(maxidx - 1);

  // initialize my frequency to the median frequency
  int freq = myAvailableFreqs[maxidx / 2];
  cout << "(" << mySimulationManagerID << "): bound to PE " << myCPU
       << "; initializing freq to " << freq << endl;
  setCPUFrequency(myCPU, freq);
}

void
RealDVFSManager::receiveKernelMessage(KernelMessage* kMsg) {
  resetMeasurementCounter();

  UsefulWorkMessage* msg = dynamic_cast<UsefulWorkMessage*>(kMsg);
  ASSERT(msg);

  std::vector<double> dat;
  msg->getData(dat);

  fillUsefulWork(dat);
  if(isMaster()) {

    for(int i = 0; i < dat.size(); ++i)
      myUtilFilters[i].update(dat[i]);

    bool changed = false;
    if(!isDummy())
      changed = updateFrequencyIdxs();

    if(changed && !isDummy()) {
      for(int i=0; i < myFrequencyIdxs.size(); i++)
        setCPUFrequency(i, myAvailableFreqs[myFrequencyIdxs[i]]);
    }

    if(debugPrint())
      for(int i=0; i < myFrequencyIdxs.size(); i++)
        writeCSVRow(i, 
                    myUtilFilters[i].getData(), 
                    myAvailableFreqs[myFrequencyIdxs[i]]);

  }
  else {

    int dest = (mySimulationManagerID + 1) % myNumSimulationManagers;
    UsefulWorkMessage* newMsg = new UsefulWorkMessage(mySimulationManagerID,
                                                        dest,
                                                        myNumSimulationManagers,
                                                        UsefulWorkMessage::COLLECT);
    newMsg->setData(dat);
    myCommunicationManager->sendMessage(newMsg, dest);
  }

  delete kMsg;
}

string
RealDVFSManager::toString() {
  return "Real DVFS, " + DVFSManagerImplementationBase::toString();
}