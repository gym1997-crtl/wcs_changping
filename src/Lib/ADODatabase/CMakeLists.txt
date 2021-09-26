add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

#PROJECT Lib 
AUX_SOURCE_DIRECTORY(./ PROJECT_SRC_LIS)

SET(AOD_MOC
	#ADD QT OBJECT .h FILE HERE
 	../../../include/ADODatabase/ApiServer.h
 	../../../include/ADODatabase/ApiClient.h
)

set(APP_UIS
	#ADD UIS FILE HERE ##
 )

set(APP_QCCS 
	#ADD .qrc FILE HERE###
)

IF(CMAKE_BUILD_TYPE MATCHES "release")
	set(ADO_LIBS
	  #ADD LIB HERE###
	  ${QT_LIBRARIES}
	  ${Boost_LIBRARIES}
	)
ELSE()
	set(ADO_LIBS
	  #ADD LIB HERE###
	  ${QT_LIBRARIES}
	  ${Boost_LIBRARIES}
	)
ENDIF()

IF(CMAKE_BUILD_TYPE MATCHES "release")
	add_library(libADODatabase ${PROJECT_SRC_LIS} ${AOD_MOC})
	# target_link_libraries(libADODatabase ${ADO_LIBS} Qt5::Core Qt5::Network)
ELSE()
	add_library(libADODatabased ${PROJECT_SRC_LIS} ${AOD_MOC})
	# target_link_libraries(libADODatabase ${ADO_LIBS} Qt5::Core Qt5::Network)
ENDIF()
