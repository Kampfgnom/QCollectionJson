#include "qcollectionjsonitem.h"
#include <QSharedData>

#include "qcollectionjsonlink.h"
#include "qcollectionjsondata.h"

#include <QList>
#include <QVariantMap>
#include <QUrl>

class QCollectionJsonItemData : public QSharedData {
public:
    QUrl href;
    QList<QCollectionJsonLink> links;
    QList<QCollectionJsonData> data;
};

QCollectionJsonItem::QCollectionJsonItem() : d(new QCollectionJsonItemData)
{
}

QCollectionJsonItem::QCollectionJsonItem(const QCollectionJsonItem &rhs) : d(rhs.d)
{
}

QCollectionJsonItem &QCollectionJsonItem::operator=(const QCollectionJsonItem &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

QCollectionJsonItem::~QCollectionJsonItem()
{
}

bool QCollectionJsonItem::isValid() const
{
    return !d->href.isEmpty()
            && d->href.isValid();
}

QUrl QCollectionJsonItem::href() const
{
    return d->href;
}

void QCollectionJsonItem::setHref(const QUrl &href)
{
    d->href = href;
}

QList<QCollectionJsonLink> QCollectionJsonItem::links() const
{
    return d->links;
}

void QCollectionJsonItem::setLinks(const QList<QCollectionJsonLink> &links)
{
    d->links = links;
}

void QCollectionJsonItem::addLink(const QCollectionJsonLink &link)
{
    d->links.append(link);
}

QList<QCollectionJsonData> QCollectionJsonItem::data() const
{
    return d->data;
}

void QCollectionJsonItem::setData(const QList<QCollectionJsonData> &data)
{
    d->data = data;
}

void QCollectionJsonItem::addData(const QCollectionJsonData &data)
{
    d->data.append(data);
}

static const QString HREF("href");
static const QString DATA("data");
static const QString LINKS("links");

QVariant QCollectionJsonItem::toVariant() const
{
    QVariantMap result;
    result[HREF] = href();

    QVariantList list;
    foreach(const QCollectionJsonData data, d->data) {
        list.append(data.toVariant());
    }
    result[DATA] = list;

    list.clear();
    foreach(const QCollectionJsonLink link, d->links) {
        list.append(link.toVariant());
    }
    result[LINKS] = list;

    return result;
}

QCollectionJsonItem QCollectionJsonItem::fromVariant(const QVariant &variant)
{
    QCollectionJsonItem result;
    if(!variant.canConvert<QVariantMap>())
        return result;

    QVariantMap query = variant.toMap();
    result.setHref(query[HREF].toUrl());

    // Data
    if(query.contains(DATA)) {
        QVariant v = query.value(DATA);

        if(v.canConvert<QVariantList>()) {
            QVariantList list = v.toList();
            foreach(const QVariant data, list) {
                QCollectionJsonData thingy = QCollectionJsonData::fromVariant(data);
                result.addData(thingy);
            }
        }
    }

    // Links
    if(query.contains(LINKS)) {
        QVariant v = query.value(LINKS);

        if(v.canConvert<QVariantList>()) {
            QVariantList list = v.toList();
            foreach(const QVariant data, list) {
                QCollectionJsonLink thingy = QCollectionJsonLink::fromVariant(data);
                result.addLink(thingy);
            }
        }
    }

    return result;
}
