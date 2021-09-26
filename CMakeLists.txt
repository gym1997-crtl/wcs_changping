cmake_minimum_required(VERSION 2.8.3)
project(WCS_ADO)

set(BOOST_ROOT $ENV{BOOST_HOME})
set(BOOST_LIBRARYDIR $ENV{BOOST_HOME})
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.71.0 COMPONENTS thread date_time program_options filesystem system REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
else()
  message("boost not found")
endif()

cmake_policy(SET CMP0020 NEW)
#设置find_package的.cmake搜索路径
SET(CMAKE_PREFIX_PATH $ENV{QT_HOME}/lib/cmake)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5 QUIET COMPONENTS Core Xml OpenGL Gui Widgets REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)
#加入QWidgets包含目录
include_directories(${Qt5Widgets_INCLUDE_DIRS})
#加入Qt5Network包含目录
find_package(Qt5Network)
include_directories(${Qt5Network_INCLUDE_DIRS})
#加入Qt5Xml包含目录
find_package(Qt5Xml)
include_directories(${Qt5Xml_INCLUDE_DIRS})


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
include_directories(
  include
  include/ADODatabase
  include/Common
  include/Manage
  include/librabbitmq
)


IF(CMAKE_BUILD_TYPE MATCHES "release")
link_directories(${${PROJECT_NAME}_SOURCE_DIR}/lib/Release)
add_link_options("/DEBUG")
add_compile_options("/Zi") 
ELSE()
link_directories(${${PROJECT_NAME}_SOURCE_DIR}/lib/Debug)
ENDIF()

add_subdirectory(src)
