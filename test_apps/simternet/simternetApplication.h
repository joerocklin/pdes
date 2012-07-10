#ifndef SIMTERNET_APPLICATION
#define SIMTERNET_APPLICATION

#include <warped/Application.h>
#include <warped/IntVTime.h>
#include <warped/PartitionInfo.h>

#include <vector>

class SimternetApplication : public Application {
public:
  SimternetApplication();
  
  // The following are required methods in the warped system
  int finalize();
  int initialize( vector<string> &arguments );
  string getCommandLineParameters() const;
  int getNumberOfSimulationObjects( int mgrId ) const;
  void registerDeserializers();
  const PartitionInfo *getPartitionInfo( unsigned int numProcessorsAvailable );
  
  const VTime &getPositiveInfinity(){ return IntVTime::getIntVTimePositiveInfinity(); }
  const VTime &getZero(){ return IntVTime::getIntVTimeZero(); }
  const VTime &getTime(string &){ return IntVTime::getIntVTimeZero(); }
  
private:
  // And now methods which are called from the above
  vector<SimulationObject *> *getSimulationObjects();

  unsigned int numObjects;
};

#endif