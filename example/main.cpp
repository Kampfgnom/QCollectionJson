#include <QCoreApplication>

#include <QCollectionJson.h>

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QJsonDocument>

void inspectFile(const QString &fileName)
{
    QFile collectionFile(fileName);

    if (!collectionFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray data;
    while (!collectionFile.atEnd()) {
        QByteArray line = collectionFile.readLine();
        data += line;
    }

    qDebug() << "\n\nParsing " << fileName;

    QJsonDocument document = QJsonDocument::fromJson(data);
    QCollectionJsonDocument collectionDocument = QCollectionJsonDocument::fromQVariant(document.toVariant().toMap());

    qDebug() << "HREF: " << collectionDocument.href();
    qDebug() << "VERSION: " << collectionDocument.version();

    qDebug() << "LINKS:";
    foreach(QCollectionJsonLink link, collectionDocument.links()) {
        qDebug() << "href: " << link.href();
    }

    qDebug() << "ITEMS:";
    foreach(QCollectionJsonItem item, collectionDocument.items()) {
        qDebug() << "href: " << item.href();
    }

    qDebug() << "QUERIES:";
    foreach(QCollectionJsonQuery query, collectionDocument.queries()) {
        qDebug() << "href: " << query.href();
    }
    qDebug() << "queries link: " << collectionDocument.queriesLink();

    qDebug() << "TEMPLATE:";
    QCollectionJsonTemplate tpl = collectionDocument.templateData();
    foreach(QCollectionJsonData data, tpl.data()) {
        qDebug() << "name: " << data.name();
    }
    qDebug() << "template link: " << collectionDocument.templateLink();

    qDebug() << "ERROR:";
    qDebug() << "message: " << collectionDocument.error().message();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Read some examples
    inspectFile(QLatin1String(":/examples/collection.json"));
    inspectFile(QLatin1String(":/examples/error.json"));
    inspectFile(QLatin1String(":/examples/item.json"));
    inspectFile(QLatin1String(":/examples/queries.json"));
    inspectFile(QLatin1String(":/examples/template.json"));

    // Create a Collection+JSON
    QCollectionJsonDocument document(QUrl("http://example.com/friends"));


    QCollectionJsonItem item(QUrl("http://example.com/friends/Niklas"));

    QCollectionJsonData data("name", QVariant("Niklas"));
    data.setPrompt("First Name");
    item.addData(data);

    QCollectionJsonLink link(QUrl("http://example.com/blogs/Niklas"), "blog");
    item.addLink(link);

    document.addItem(item);
    document.addItem(item);

    QCollectionJsonTemplate tpl;
    tpl.addData(data);
    document.setTemplate(tpl);

    QCollectionJsonQuery query(QUrl("http://example.com/search"), "search");
    QCollectionJsonData queryData("searchString");
    queryData.setPrompt("Search");
    query.addData(queryData);
    document.addQuery(query);

    QVariant documentVariant = document.toVariant();
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(documentVariant);
    qDebug() << jsonDoc.toJson();

    // Create error Collection+JSON
    QCollectionJsonDocument errorDocument(QUrl("http://example.com/friends"));
    QCollectionJsonError error("File not found!", "404", "The file could not be found.");
    errorDocument.setError(error);

    documentVariant = errorDocument.toVariant();
    jsonDoc = QJsonDocument::fromVariant(documentVariant);
    qDebug() << jsonDoc.toJson();

    return a.exec();
}
