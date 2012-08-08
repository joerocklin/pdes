cmake_minimum_required (VERSION 2.6)
project (Tutorial)

include_directories("${PROJECT_SOURCE_DIR}/../../build/include")

FIND_LIBRARY(WARPED_LIBRARY warped "${PROJECT_SOURCE_DIR}/../../build/lib")
FIND_LIBRARY(UTILS_LIBRARY utils "${PROJECT_SOURCE_DIR}/../../build/lib")

add_executable(Tutorial 
		tutorial.cxx 
		tutorialApplication.cxx 
		tutorialObject.cxx 
		tutorialState.cxx
		tutorialMessage.cxx
)
target_link_libraries( Tutorial ${WARPED_LIBRARY} ${UTILS_LIBRARY})
