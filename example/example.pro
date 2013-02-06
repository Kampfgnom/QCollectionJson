### General config ###

TARGET          = QJsonCollectionExample
VERSION         = 0.1.0
TEMPLATE        = app
QT              +=
QT              -= gui
CONFIG          +=
QMAKE_CXXFLAGS  += -Wall -ansi -pedantic -Wno-long-long

### QCollectionJson ###

QCOLLECTIONJSON_PATH = ..
include($$QCOLLECTIONJSON_PATH/QCollectionJson.pri)
LIBS            += $$QCOLLECTIONJSON_LIBS
INCLUDEPATH     += $$QCOLLECTIONJSON_INCLUDEPATH


### Files ###

HEADERS += \

SOURCES += \
    main.cpp

RESOURCES += \
    exampleDocuments.qrc

OTHER_FILES += \
    collection.json \
    item.json \
    queries.json \
    template.json \
    error.json
