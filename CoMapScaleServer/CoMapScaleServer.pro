#-------------------------------------------------
#
# Project created by QtCreator 2011-10-20T09:26:27
#
#-------------------------------------------------

CONFIG += mobility
MOBILITY += location

#INCLUEPATH += "C:\QtSDK\Desktop\Qt\4.7.1\mingw\include\QtMobility\"

#Linux
#INCLUDEPATH += "/opt/QtSDK/Desktop/Qt/474/gcc/include/QtMobility/" \

                #"/opt/QtSDK/Desktop/Qt/474/gcc/plugins/geoservices"
                #"/home/bens/Code/Geoservices_nokia/geoservices/nokia"

QT       += core gui\
            network

TARGET = CoMapOviServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpserver.cpp \
    clientconnection.cpp \
    mappingwidget.cpp \
    mapoverlay.cpp \
    mapmarker.cpp \
    geomap.cpp \
    zoombuttonitem.cpp \
    clientstate.cpp \
    datalogger.cpp

HEADERS  += mainwindow.h \
    tcpserver.h \
    clientconnection.h \
    mappingwidget.h \
    mapoverlay.h \
    mapmarker.h \
    geomap.h \
    zoombuttonitem.h \
    clientstate.h \
    datalogger.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog

RESOURCES += \
    Icons.qrc

maemo5 {
    target.path = /opt/CoMapScaleServer/bin
    INSTALLS += target
}
