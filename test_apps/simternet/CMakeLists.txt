cmake_minimum_required (VERSION 2.6)
project (Simternet)

include_directories("${PROJECT_SOURCE_DIR}/../../build/include")
FIND_LIBRARY(WARPED_LIBRARY warped "${PROJECT_SOURCE_DIR}/../../build/lib")

add_executable(simternet 
		simternet.cxx 
		simternetApplication.cxx 
)

target_link_libraries( simternet ${WARPED_LIBRARY} )
