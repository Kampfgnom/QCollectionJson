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

    inspectFile(QLatin1String(":/examples/collection.json"));
    inspectFile(QLatin1String(":/examples/error.json"));
    inspectFile(QLatin1String(":/examples/item.json"));
    inspectFile(QLatin1String(":/examples/queries.json"));
    inspectFile(QLatin1String(":/examples/template.json"));

    return a.exec();
}
