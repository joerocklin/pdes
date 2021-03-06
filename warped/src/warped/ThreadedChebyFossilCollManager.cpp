// See copyright notice in file Copyright in the root directory of this archive.


#include "ThreadedChebyFossilCollManager.h"
#include "Event.h"
#include "ThreadedTimeWarpSimulationManager.h"
#include <math.h>

using std::cout;
using namespace warped;

ThreadedChebyFossilCollManager::ThreadedChebyFossilCollManager(ThreadedTimeWarpSimulationManager *sim,
                                               int checkPeriod,
                                               int minimumSamples,
                                               int maximumSamples,
                                               int defaultLen,
                                               double risk):
  ThreadedOptFossilCollManager(sim, checkPeriod, minimumSamples, maximumSamples, defaultLen, risk),
  errorTerm(2.576){

  for(int i = 0; i < sim->getNumberOfSimulationObjects(); i++){
    samples.push_back(vector<unsigned int>(maxSamples, 0));
    total.push_back(0);
    sampleIndex.push_back(0);
  }
}

ThreadedChebyFossilCollManager::~ThreadedChebyFossilCollManager(){
}

void
ThreadedChebyFossilCollManager::sampleRollback(SimulationObject *object, const VTime &rollVTime){
  int rollbackTime = rollVTime.getApproximateIntTime();
  int rollbackDistance = object->getSimulationTime().getApproximateIntTime() - rollbackTime;
  unsigned int objId = object->getObjectID()->getSimulationObjectID();

  if(numSamples[objId] < maxSamples){
    // Sample the rollback.
    total[objId] = total[objId] - samples[objId][sampleIndex[objId]];
    samples[objId][sampleIndex[objId]] = rollbackDistance;
    total[objId] = total[objId] + rollbackDistance;

    sampleIndex[objId]++;
    numSamples[objId]++;

    // If there are enough samples, then calculate the mean, variance
    // and new active history length.
    if(numSamples[objId] > minSamples){
      double sampleVariance = 0;
      double mean1, mean2;
      double variance1, variance2;
      mean1 = mean2 = variance1 = variance2 = 0;

      double sampleMean = total[objId] / double(numSamples[objId]);

      for(int i = 0; i < numSamples[objId]; i++) {
        sampleVariance += ((double(samples[objId][i]) - sampleMean) *
                           (double(samples[objId][i]) - sampleMean));
      }

      sampleVariance = sampleVariance / numSamples[objId];

      mean1 = sampleMean - 1.96*sqrt(sampleVariance/(double)numSamples[objId]);
      mean2 = sampleMean + 1.96*sqrt(sampleVariance/(double)numSamples[objId]);

      for(int i = 0; i < numSamples[objId]; i++) {
        variance1 += ((double(samples[objId][i]) - mean1) *
                      (double(samples[objId][i]) - mean1));
        variance2 += ((double(samples[objId][i]) - mean2) *
                      (double(samples[objId][i]) - mean2));
      }

      variance1 = variance1 / numSamples[objId];
      variance2 = variance2 / numSamples[objId];

      if(variance1 < variance2){
        sampleVariance = variance2;
      }
      else{
        sampleVariance = variance1;
      }

      activeHistoryLength[objId] = sampleMean + errorTerm * sqrt(sampleVariance/(1.0-riskFactor));
      utils::debug << objId << " - NEW LENGTH: " << activeHistoryLength[objId] << endl;
    }
  }

  if(lastCollectTimes[objId] >= 0 && !recovering && rollbackTime <= lastCollectTimes[objId]){
    utils::debug << mySimManager->getSimulationManagerID()
      << " - Catastrophic Rollback: Last collection time: " << lastCollectTimes[objId]
      << ", Rollback Time: " << rollbackTime << ", Starting Recovery." << endl;

    setRecovery(objId, rollbackTime);
  }
}
