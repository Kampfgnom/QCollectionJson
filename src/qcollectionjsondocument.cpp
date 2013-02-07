#include "qcollectionjsondocument.h"
#include <QSharedData>

#include "qcollectionjsonerror.h"
#include "qcollectionjsontemplate.h"
#include "qcollectionjsonquery.h"
#include "qcollectionjsonlink.h"
#include "qcollectionjsonitem.h"

#include <QList>
#include <QString>
#include <QJsonDocument>
#include <QVariant>
#include <QDebug>

static const QString COLLECTION("collection");
static const QString VERSION("version");
static const QString HREF("href");
static const QString LINKS("links");
static const QString QUERIES("queries");
static const QString ITEMS("items");
static const QString ERROR("error");
static const QString TEMPLATE("template");

class QCollectionJsonDocumentData : public QSharedData {
public:
    QCollectionJsonDocumentData() :
        QSharedData(),
        version("1.0")
    {}

    QUrl href;
    QString version;
    QList<QCollectionJsonLink> links;
    QList<QCollectionJsonQuery> queries;
    QUrl queriesLink;
    QList<QCollectionJsonItem> items;
    QCollectionJsonTemplate templateData;
    QUrl templateLink;
    QCollectionJsonError error;
};

QCollectionJsonDocument::QCollectionJsonDocument() : data(new QCollectionJsonDocumentData)
{
}

QCollectionJsonDocument::QCollectionJsonDocument(const QUrl &href) : data(new QCollectionJsonDocumentData)
{
    setHref(href);
}

QCollectionJsonDocument::QCollectionJsonDocument(const QCollectionJsonDocument &rhs) : data(rhs.data)
{
}

QCollectionJsonDocument &QCollectionJsonDocument::operator=(const QCollectionJsonDocument &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QCollectionJsonDocument::~QCollectionJsonDocument()
{
}

bool QCollectionJsonDocument::isValid() const
{
    // According to docs version must be 1.0... I allow other versions...
    if(data->version.isEmpty())
        return false;

    // href must be empty or valid
    if(!data->href.isEmpty()
            && !data->href.isValid())
        return false;

    foreach(const QCollectionJsonLink link, links()) {
        if(!link.isValid())
            return false;
    }

    foreach(const QCollectionJsonItem item, items()) {
        if(!item.isValid())
            return false;
    }

    foreach(const QCollectionJsonQuery query, queries()) {
        if(!query.isValid())
            return false;
    }

    if(!templateData().isValid())
        return false;

    return true;
}

QUrl QCollectionJsonDocument::href() const
{
    return data->href;
}

void QCollectionJsonDocument::setHref(const QUrl &href)
{
    data->href = href;
}

QString QCollectionJsonDocument::version() const
{
    return data->version;
}

void QCollectionJsonDocument::setVersion(const QString &version)
{
    data->version = version;
}

QList<QCollectionJsonLink> QCollectionJsonDocument::links() const
{
    return data->links;
}

void QCollectionJsonDocument::setLinks(const QList<QCollectionJsonLink> &links)
{
    data->links = links;
}

void QCollectionJsonDocument::addLink(const QCollectionJsonLink &link)
{
    data->links.append(link);
}

QList<QCollectionJsonItem> QCollectionJsonDocument::items() const
{
    return data->items;
}

void QCollectionJsonDocument::setItems(const QList<QCollectionJsonItem> &items)
{
    data->items = items;
}

void QCollectionJsonDocument::addItem(const QCollectionJsonItem &item)
{
    data->items.append(item);
}

QList<QCollectionJsonQuery> QCollectionJsonDocument::queries() const
{
    return data->queries;
}

void QCollectionJsonDocument::setQueries(const QList<QCollectionJsonQuery> &queries)
{
    data->queries = queries;
}

void QCollectionJsonDocument::addQuery(const QCollectionJsonQuery &query)
{
    data->queries.append(query);
}

QUrl QCollectionJsonDocument::queriesLink() const
{
    return data->queriesLink;
}

void QCollectionJsonDocument::setQueriesLink(const QUrl &url)
{
    QCollectionJsonLink link;
    link.setHref(url);
    link.setRel(QUERIES);
    addLink(link);

    data->queriesLink = url;
}

QCollectionJsonTemplate QCollectionJsonDocument::templateData() const
{
    return data->templateData;
}

void QCollectionJsonDocument::setTemplate(const QCollectionJsonTemplate &templateData)
{
    data->templateData = templateData;
}

QUrl QCollectionJsonDocument::templateLink() const
{
    return data->templateLink;
}

void QCollectionJsonDocument::setTemplateLink(const QUrl &url)
{
    QCollectionJsonLink link;
    link.setHref(url);
    link.setRel(TEMPLATE);
    addLink(link);

    data->templateLink = url;
}

QCollectionJsonError QCollectionJsonDocument::error() const
{
    return data->error;
}

void QCollectionJsonDocument::setError(const QCollectionJsonError &error)
{
    data->error = error;
}

QVariant QCollectionJsonDocument::toVariant() const
{
    QVariantMap collectionDocument;
    QVariantMap collection;

    collection[VERSION] = version();
    collection[HREF] = href();

    // links
    if(!links().isEmpty()) {
        QVariantList list;
        foreach(const QCollectionJsonLink tmp, links()) {
            list.append(tmp.toVariant());
        }
        collection[LINKS] = list;
    }

    // items
    if(!items().isEmpty()) {
        QVariantList list;
        foreach(const QCollectionJsonItem tmp, items()) {
            list.append(tmp.toVariant());
        }
        collection[ITEMS] = list;
    }

    // Template
    if(templateLink().isEmpty()) {
        QVariantMap v = templateData().toVariant().toMap();
        if(!v.isEmpty())
            collection[TEMPLATE] = v;
    }

    // Queries
    if(queriesLink().isEmpty()
            && !queries().isEmpty()) {
        QVariantList list;
        foreach(const QCollectionJsonQuery tmp, queries()) {
            list.append(tmp.toVariant());
        }
        collection[QUERIES] = list;
    }

    // error
    if(error().isValid()) {
        collection[ERROR] = error().toVariant();
    }

    collectionDocument[COLLECTION] = collection;
    return collectionDocument;
}

QCollectionJsonDocument QCollectionJsonDocument::fromQVariant(const QVariantMap &jsonDocument)
{
    QCollectionJsonDocument result;

    if(!jsonDocument.contains(COLLECTION))
        return result;

    QVariantMap collection = jsonDocument.value(COLLECTION).toMap();

    // Version (default is 1.0, only overwrite, when existent)
    if(collection.contains(VERSION))
        result.setVersion(collection.value(VERSION).toString());

    // Href
    result.setHref(collection[HREF].toUrl());

    // Error
    result.setError(QCollectionJsonError::fromVariant(collection[ERROR]));

    // Template
    result.setTemplate(QCollectionJsonTemplate::fromVariant(collection[TEMPLATE]));

    // Links
    QVariant v = collection[LINKS];
    if(v.canConvert<QVariantList>()) {
        QVariantList list = v.toList();
        foreach(const QVariant variant, list) {
            QCollectionJsonLink thingy = QCollectionJsonLink::fromVariant(variant);

            if(thingy.rel() == QUERIES)
                result.setQueriesLink(thingy.href());
            else if(thingy.rel() == TEMPLATE)
                result.setTemplateLink(thingy.href());
            else
                result.addLink(thingy);
        }
    }

    // Queries
    v = collection[QUERIES];
    if(v.canConvert<QVariantList>()) {
        QVariantList list = v.toList();
        foreach(const QVariant variant, list) {
            QCollectionJsonQuery thingy = QCollectionJsonQuery::fromVariant(variant);
            result.addQuery(thingy);
        }
    }

    // Items
    v = collection[ITEMS];
    if(v.canConvert<QVariantList>()) {
        QVariantList list = v.toList();
        foreach(const QVariant variant, list) {
            QCollectionJsonItem thingy = QCollectionJsonItem::fromVariant(variant);
            result.addItem(thingy);
        }
    }

    return result;
}
