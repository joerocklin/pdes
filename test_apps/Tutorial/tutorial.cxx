#include <warped/WarpedMain.h>
#include "tutorialApplication.h"

int main(int argc, char** argv) {
  WarpedMain wm( new TutorialApplication() );
  
  return wm.main( argc, argv );
}