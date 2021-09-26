add_definitions(-DBOOST_NO_MEMBER_TEMPLATE_FRIENDS)

IF(CMAKE_BUILD_TYPE MATCHES "release")
SET(QT_LIBRARIES
 #ADD QT OBJECT .h FILE HERE
 $ENV{QT_HOME}/lib/qtmain.lib
 $ENV{QT_HOME}/lib/Qt5OpenGL.lib
 $ENV{QT_HOME}/lib/Qt5Widgets.lib
 $ENV{QT_HOME}/lib/Qt5Gui.lib
 $ENV{QT_HOME}/lib/Qt5Core.lib
 $ENV{QT_HOME}/lib/Qt5Network.lib
 $ENV{QT_HOME}/lib/Qt5Xml.lib
)
ELSE()
SET(QT_LIBRARIES
 #ADD QT OBJECT .h FILE HERE
 $ENV{QT_HOME}/lib/qtmaind.lib
 $ENV{QT_HOME}/lib/Qt5OpenGLd.lib
 $ENV{QT_HOME}/lib/Qt5Widgetsd.lib
 $ENV{QT_HOME}/lib/Qt5Guid.lib
 $ENV{QT_HOME}/lib/Qt5Cored.lib
 $ENV{QT_HOME}/lib/Qt5Networkd.lib
 $ENV{QT_HOME}/lib/Qt5Xmld.lib
)
ENDIF()


SET(APP_MOC_SRCS
	#ADD QT OBJECT .h FILE HERE
	MainWnd.h
	DataModel.h
	OrderMonitor.h
	TaskMonitor.h
	AGVMonitor.h
	progressbardelegate.h
	DODMonitor.h
	StorageMonitor.h
	MyLabel.h
	skinitem.h
	skindialog.h
	SendOrderLabelWidget.h
	SendOrderConfirmLabel.h
	SendOrderParkingLabel.h
	SendOrderEquipmentLabel.h
	SendOrderBridgeLabel.h
	HttpAnalysisAndPackage.h
)


set(APP_SRCS
	main.cpp
	MainWnd.cpp
	DataModel.cpp
	DODMonitor.cpp
	OrderMonitor.cpp
	AGVMonitor.cpp
	progressbardelegate.cpp
	TaskMonitor.cpp
	StorageMonitor.cpp
	MyLabel.cpp
	skinitem.cpp
	skindialog.cpp
	SendOrderLabelWidget.cpp
	SendOrderConfirmLabel.cpp
	SendOrderParkingLabel.cpp
	SendOrderEquipmentLabel.cpp
	SendOrderBridgeLabel.cpp
)

set(APP_UIS
	#ADD UIS FILE HERE ##

 )

set(APP_QCCS 
	#ADD .qrc FILE HERE###

)
IF(CMAKE_BUILD_TYPE MATCHES "release")
if(WIN32)
set(APP_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  librabbitmq.4.lib
  setupapi.lib 
  libtransferdevice
  libcom
  libCore
  libManage
  libADODatabase
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)

else()

link_directories(/lib)

set(APP_LIBS
    libtransferdevice
    libcom 	
	libCore
	libManage
	libADODatabase
	
	rt 
	${Boost_LIBRARIES}
)
endif()

ELSE()
if(WIN32)
set(APP_LIBS
  #ADD LIB HERE###
  WS2_32.lib
  librabbitmq.4.lib
  setupapi.lib 
  libtransferdeviced
  libcomd 
  libCored
  libManaged
  libADODatabased
  ${QT_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
else()

link_directories(/lib)

set(APP_LIBS
	libtransferdeviced
	libcomd 
	libCored
	libManaged
	libADODatabased
	rt 
	${Boost_LIBRARIES}
)
endif()
ENDIF()

ADD_DEFINITIONS(-D_REENTRANT -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED )


IF(CMAKE_BUILD_TYPE MATCHES "release")
add_executable(wcs ${APP_SRCS} ${APP_MOC} ${APP_UIS_H} ${APP_QCCS_SRCS} )
message(${APP_LIBS})
target_link_libraries(wcs ${APP_LIBS} )
set_target_properties(wcs PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
ELSE()
add_executable(wcsd ${APP_SRCS} ${APP_MOC} ${APP_UIS_H} ${APP_QCCS_SRCS} )
message(${APP_LIBS})
target_link_libraries(wcsd ${APP_LIBS} )
set_target_properties(wcsd PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
ENDIF()