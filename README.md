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
QCollectionJsonDocument errorDocument;
errorDocument.setHref(QUrl("http://example.com/friends"));
QCollectionJsonError error;
error.setTitle("File not found!");
error.setCode("404");
error.setMessage("The file could not be found.");
errorDocument.setError(error);

QVariant documentVariant = errorDocument.toVariant();
QJsonDocument jsonDoc = QJsonDocument::fromVariant(documentVariant);
qDebug() << jsonDoc.toJson(); // Write to some QTcpSocket etc...
````

Please have a look at the example for further details.


License
=======

QCollectionJson is licensed under the LGPLv3.0. See LICENSE for details.
