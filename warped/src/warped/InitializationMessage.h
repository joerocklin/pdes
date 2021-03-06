#ifndef INITIALIZATION_MESSAGE_H
#define INITIALIZATION_MESSAGE_H

// See copyright notice in file Copyright in the root directory of this archive.

/**
   This is the class defining the termination token that gets passed
   around.  Essentially, it has a color and a terminator.  

   The color can be WHITE, which means it's on the first cycle,
   RED, which means it's on it's second cycle, or BLACK.
*/

#include "KernelMessage.h"

namespace warped {

/**
   This class represents the token that gets passed between
   communication managers at initialization time.
*/

class InitializationMessage : public KernelMessage {
public:
  InitializationMessage( unsigned int source,
			 unsigned int dest,
			 const vector<string> &initObjectNames,
			 unsigned int initNumSimulationManagers ) :
    KernelMessage( source, dest ),
    objectNames( initObjectNames ),
    numSimulationManagers( initNumSimulationManagers ){}
  
  void serialize( SerializedInstance * ) const;
  static Serializable *deserialize( SerializedInstance *data );

  static const string &getInitializationMessageType();

  const string &getDataType() const {
    return getInitializationMessageType();
  }

  static void registerDeserializer();
  
  const vector<string> &getObjectNames() const { return objectNames; }
  const unsigned &getNumSimulationManagers() const { return numSimulationManagers; }
  
private:
  static const vector<string> deserializeStringVector( SerializedInstance *data );

  const vector<string> objectNames;
  const unsigned numSimulationManagers;

};

}

#endif
