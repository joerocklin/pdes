// See copyright notice in file Copyright in the root directory of this archive.


#ifndef DTCHEBYFOSSILCOLLMANAGER_H_
#define DTCHEBYFOSSILCOLLMANAGER_H_

#include "DTOptFossilCollManager.h"

/** The ChebyFossilCollManager class.

    This class implements the decision function using the
    Chebyshev inequality.
*/
class DTChebyFossilCollManager : public DTOptFossilCollManager{
public:

  /**@name Public Class Methods of ChebyFossilCollManager. */
  //@{

  /** Constructor.

      @param simMgr Handle to the simulation manager.
      @param checkPeriod The checkpoint period.
      @param minimumSamples The minimum samples taken before calculation.
      @param maximumSamples The max samples taken before calculation stops.
      @param defaultLen The initial active history length of all objects.
      @param risk The probability of a catastrophic rollback.
  */
  DTChebyFossilCollManager(DTTimeWarpSimulationManager *simMgr,
                         int checkPeriod,
                         int minimumSamples,
                         int maximumSamples,
                         int defaultLen,
                         double risk);

  /// Desctructor
  virtual ~DTChebyFossilCollManager();

  /** This function samples the rollback time to determine the
      active history length of the simulation object.

      @param obj The simulation object rolled back.
      @param time The rollback time.
  */
  void sampleRollback(SimulationObject *obj, const VTime &time);

  //@} // End of Public Class Methods of ChebyFossilCollManager.

protected:

  /**@name protected Class Methods of ChebyFossilCollManager. */
  //@{

  /// The rollback times for all of the simulation objects on this
  /// simulation manager.
  vector< vector<unsigned int> > samples;

  /// The current index for the sample vector.
  vector<unsigned int> sampleIndex;

  /// The current total rollback time for each simulation object.
  vector<int> total;

  /// Used for calculating the active history length.
  double errorTerm;

  //@} // End of Protected Class Methods of ChebyFossilCollManager.
};




#endif /* DTCHEBYFOSSILCOLLMANAGER_H_ */