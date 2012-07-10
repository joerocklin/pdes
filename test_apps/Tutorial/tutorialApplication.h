#ifndef TUTORIAL_APPLICATION
#define TUTORIAL_APPLICATION

#include "tutorial.h"

#include <warped/Application.h>
#include <warped/IntVTime.h>
#include <warped/PartitionInfo.h>

#include <vector>

class TutorialApplication : public Application {
public:
  TutorialApplication();
  
  // The following are required methods in the warped system
  int finalize();
  int initialize( vector<string> &arguments );
  string getCommandLineParameters() const;
  int getNumberOfSimulationObjects( int mgrId ) const;
  void registerDeserializers();
  const PartitionInfo *getPartitionInfo( unsigned int numProcessorsAvailable );
  
  const VTime &getPositiveInfinity(){ enter_method; return IntVTime::getIntVTimePositiveInfinity(); }
  const VTime &getZero(){ enter_method; return IntVTime::getIntVTimeZero(); }
  const VTime &getTime(string &){ enter_method; return IntVTime::getIntVTimeZero(); }
  
private:
  // And now methods which are called from the above
  vector<SimulationObject *> *getSimulationObjects();

  unsigned int numObjects;
};

#endif