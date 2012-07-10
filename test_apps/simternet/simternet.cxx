#include <warped/WarpedMain.h>
#include "simternetApplication.h"

int main(int argc, char** argv) {
  WarpedMain wm( new SimternetApplication() );
  
  return wm.main( argc, argv );
}