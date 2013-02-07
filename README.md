QCollectionJson 0.1
===================

QCollectionJson is a Qt wrapper for [Collection+JSON](http://amundsen.com/media-types/collection/) documents.

It currently supports the complete specification of Collection+JSON version 1.0.


Project setup
=============

QCollectionJson comes with some helpers to include it in you project.

You can simply add the whole project to your qmake based project and add the following lines to your application's project file:

````
QCOLLECTIONJSON_PATH = relative/or/absolute/path/to/QCollectionJson
include($$QCOLLECTIONJSON_PATH/QCollectionJson.pri)
LIBS            += $$QCOLLECTIONJSON_LIBS
INCLUDEPATH     += $$QCOLLECTIONJSON_INCLUDEPATH
`````

You may of course setup everything as you like :wink:


Usage
=====

Parsing
-------

Include header, parse JSON, parse Collection+JSON:

```` C++
#include <QCollectionJson.h>
...

QByteArray data = "... some JSON data ...";

QJsonDocument document = QJsonDocument::fromJson(data);
QCollectionJsonDocument collectionDocument = QCollectionJsonDocument::fromQVariant(document.toVariant().toMap());
````

Writing
-------
```` C++
// Create error Collection+JSON
QCollectionJsonDocument errorDocument(QUrl("http://example.com/friends"));
QCollectionJsonError error("File not found!", "404", "The file could not be found.");
errorDocument.setError(error);

// Convert to JSON QByteArray
QVariant documentVariant = errorDocument.toVariant();
QJsonDocument jsonDoc = QJsonDocument::fromVariant(documentVariant);
qDebug() << jsonDoc.toJson(); // Write to some QTcpSocket etc...
````

Please have a look at the example for further details.


Requirements and building
=========================

QCollectionJson has been developed and tested only on Qt 5.0 on a Mac. The library itself should be compatible to older versions of Qt, but the example uses Qt 5's QJson* classes.

The project can be build in Qt Creator or by issuing the following commands.

````
qmake
make
````

Contributing
============

Since I wrote the library before I decided to switch to [HAL](http://stateless.co/hal_specification.html), this library is currently not in use and not well tested.

If you find errors, simply file an issue in GitHub, or even better:

If you want to contribute to QCollectionJson, you can do the usual Fork-Patch-FilePullRequest dance. I might even tranfser the project in someone else's hands!


License
=======

QCollectionJson is licensed under the LGPLv3.0. See LICENSE for details.
