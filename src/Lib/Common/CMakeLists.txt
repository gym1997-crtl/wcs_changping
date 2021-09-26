#PROJECT Lib 
AUX_SOURCE_DIRECTORY(./ PROJECT_SRC_LIS)

IF(CMAKE_BUILD_TYPE MATCHES "release")
	add_library(libCommon ${PROJECT_SRC_LIS})

ELSE()
	add_library(libCommond ${PROJECT_SRC_LIS})

ENDIF()
