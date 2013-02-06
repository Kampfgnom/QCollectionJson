QCOLLECTIONJSON_PATH = ..
include($$QCOLLECTIONJSON_PATH/QCollectionJson.pri)

### General config ###

TARGET          = $$QCOLLECTIONJSON_TARGET
VERSION         = $$QCOLLECTIONJSON_VERSION
TEMPLATE        = lib
QT              +=
QT              -= gui
CONFIG          += staticlib
QMAKE_CXXFLAGS  += -Wall -ansi -pedantic -Wno-long-long
INCLUDEPATH     += $$QCOLLECTIONJSON_INCLUDEPATH


### Files ###

HEADERS += \
    qcollectionjsondocument.h \
    qcollectionjsonlink.h \
    qcollectionjsonitem.h \
    qcollectionjsondata.h \
    qcollectionjsontemplate.h \
    qcollectionjsonerror.h \
    qcollectionjsonquery.h

SOURCES += \
    qcollectionjsondocument.cpp \
    qcollectionjsonlink.cpp \
    qcollectionjsonitem.cpp \
    qcollectionjsondata.cpp \
    qcollectionjsontemplate.cpp \
    qcollectionjsonerror.cpp \
    qcollectionjsonquery.cpp
