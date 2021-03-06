#ifndef CLOCK_FREQUENCY_MANAGER_IMPLEMENTATION_BASE_H
#define CLOCK_FREQUENCY_MANAGER_IMPLEMENTATION_BASE_H

// See copyright notice in file Copyright in the root directory of this archive.

#include "warped.h"
#include "DVFSManager.h"
#include "controlkit/FIRFilter.h"
#include "StopWatch.h"

namespace warped {

class TimeWarpSimulationManager;
class CommunicationManager;

/** The DVFSManagerImplementationBase implementation base class.

    This contains the default implementations of DVFS functions
*/
class DVFSManagerImplementationBase : public DVFSManager {
public:
   
  /**@name Public Class Methods of DVFSManagerImplementationBase. */
  //@{

  /// Constructor
  DVFSManagerImplementationBase(TimeWarpSimulationManager*,int, int, Algorithm, bool,
                                UsefulWorkMetric, double);

  /// Destructor
  virtual ~DVFSManagerImplementationBase();

  /// to be called from the simulation manager's simulation loop
  virtual void poll();

  /// from Configurable
  virtual void configure(SimulationConfiguration &configuration);

  void resetMeasurementCounter() { myMeasurementCounter = 0;}

  virtual void delay(int) {}

  virtual string toString();

  //@} // End of Public Class Methods of DVFSManagerImplementationBase.

protected:
   
  /**@name Protected Class Methods of DVFSManagerImplementationBase. */
  //@{

  virtual bool checkMeasurementPeriod();
  virtual bool isMaster() { return mySimulationManagerID == 0; }
  virtual void writeCSVRow(int, double, int);
  int getPeriod() { return myMeasurementPeriod; }
  void populateAvailableFrequencies();
  void setCPUFrequency(int cpu_idx, int freq);
  bool updateFrequencyIdxs();
  void fillUsefulWork(vector<double>&);
  void initializeFrequencyIdxs(int maxfreq);
  bool isDummy() const { return myAlg == FIXED; }
  bool debugPrint() const { return myDebugPrint; }
  void setGovernorMode(int i, const char* governor);

  virtual bool doEffectiveUtilization() { 
    return myUWM == EFFECTIVE_UTILIZATION; 
  }

  //@} // End of Protected Class Methods of DVFSManagerImplementationBase.

  TimeWarpSimulationManager* mySimulationManager;
  CommunicationManager* myCommunicationManager;
  int mySimulationManagerID;
  int myNumSimulationManagers;
  int myCPU;
  int myFIRSize;
  std::vector<FIRFilter<double> > myUtilFilters;

  // begin() == fastest, end() == slowest
  std::vector<int> myAvailableFreqs;
  vector<int> myFrequencyIdxs;

private:

  int myMeasurementPeriod;
  StopWatch myStopwatch;
  int myMeasurementCounter;
  int myMaxFreqIdx;
  bool myDebugPrint;
  Algorithm myAlg;
  UsefulWorkMetric myUWM;
  int myLastRollbacks;
  int myLastEventsRolledBack;
  int myLastEventsExecuted;
  double myThreshold;

  double getRollbacksForPeriod();
  double getRollbackFractionForPeriod();

  static const char* algorithmStrings[];
  static const char* uwmStrings[];
};

}

#endif //CLOCK_FREQUENCY_MANAGER_IMPLEMENTATION_BASE_H
