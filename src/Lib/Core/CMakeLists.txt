#PROJECT Lib 
AUX_SOURCE_DIRECTORY(./ PROJECT_SRC_LIS)

IF(CMAKE_BUILD_TYPE MATCHES "release")
	add_library(libCore ${PROJECT_SRC_LIS})
	target_link_libraries(libCore libCommon)

ELSE()
	add_library(libCored ${PROJECT_SRC_LIS})
	target_link_libraries(libCored libCommond)
ENDIF()
