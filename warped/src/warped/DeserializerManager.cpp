// See copyright notice in file Copyright in the root directory of this archive.

#include "DeserializerManager.h"

using namespace warped;

void 
DeserializerManager::registerDeserializer( const string &dataType, 
					   deserializeFunc functionPtr ){
  deserializerMap.insert( std::make_pair(dataType, functionPtr) );
}

deserializeFunc 
DeserializerManager::findDeserializer( const string &dataType ){
  unordered_map<string, deserializeFunc>::iterator it = deserializerMap.find(dataType);
  if( it != deserializerMap.end() ){
    return (*it).second;
  }
  else{
    return NULL;
  }
  //return (*(deserializerMap.find( dataType ))).second;
}


DeserializerManager *
DeserializerManager::instance(){
  static DeserializerManager *instance = new DeserializerManager();

  return instance;
}


