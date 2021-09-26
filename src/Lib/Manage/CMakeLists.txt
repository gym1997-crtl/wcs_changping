add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()


#PROJECT Lib 
AUX_SOURCE_DIRECTORY(./ MANAGE_SRC)


SET(MANAGE_MOC
	#ADD QT OBJECT .h FILE HERE
)

set(APP_UIS
	#ADD UIS FILE HERE ##

 )

set(APP_QCCS 
	#ADD .qrc FILE HERE###

)

IF(CMAKE_BUILD_TYPE MATCHES "release")
set(MANAGE_LIBS
  #ADD LIB HERE###
  ${QT_LIBRARIES}
  ${Boost_LIBRARIES}
)
ELSE()
set(MANAGE_LIBS
  #ADD LIB HERE###
  ${QT_LIBRARIES}
  ${Boost_LIBRARIES}
)
ENDIF()

IF(CMAKE_BUILD_TYPE MATCHES "release")
add_library(libManage ${MANAGE_SRC} ${MANAGE_MOC})
# target_link_libraries(libManage ${MANAGE_LIBS} Qt5::Core Qt5::Network)
ELSE()
add_library(libManaged ${MANAGE_SRC} ${MANAGE_MOC})
# target_link_libraries(libManaged ${MANAGE_LIBS} Qt5::Core Qt5::Network)
ENDIF()
