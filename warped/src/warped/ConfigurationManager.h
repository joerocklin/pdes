#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

// See copyright notice in file Copyright in the root directory of this archive.

#include "warped.h"
#include "Configurable.h"

namespace warped {
class SimulationManager;

/** The ConfigurationManager abstract base class.

    The ConfigurationManager abstract base class represents the base
    class from which all configuration managers should be derived
    from.
*/
class ConfigurationManager : virtual public Configurable {
public:
   
  /**@name Public Class Methods of ConfigurationManager */
  //@{
  
  /// Default destructor
  virtual ~ConfigurationManager(){};
  
  //@} // End of Public Class Methods of ConfigurationManager
  
  virtual SimulationManager *getSimulationManager() = 0;

protected:

   /**@name Protected Class Methods of ConfigurationManager */
   //@{

   /// Default constructor
   ConfigurationManager(){};
   
   //@} // End of Protected Class Methods of ConfigurationManager
   
};

}

#endif
