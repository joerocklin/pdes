#ifndef DFF_APPLICATION
#define DFF_APPLICATION

#include <warped/Application.h>
#include <warped/IntVTime.h>

class DFFApplication : public Application{
public:

  DFFApplication();

  int initialize( vector<string> &arguments);

  int getNumberOfSimulationObjects(int mgrId) const;

  const PartitionInfo *getPartitionInfo( unsigned int numberOfProcessorsAvailable);

  int finalize();

  void registerDeserializers();

  string getCommandLineParameters() const {return "foo"; }

  const VTime &getPositiveInfinity(){return IntVTime::getIntVTimePositiveInfinity();}

  const VTime &getZero(){ return IntVTime::getIntVTimeZero();}

  const VTime &getTime(string &){return IntVTime::getIntVTimeZero();}

private:

  ArgumentParser &getArgumentParser();

  unsigned int numObjects;

  string inputFileName;

};

#endif

