#include "qcollectionjsonquery.h"
#include <QSharedData>

#include "qcollectionjsondata.h"

#include <QList>
#include <QString>
#include <QUrl>
#include <QVariant>

class QJsonCollectionQueryData : public QSharedData {
public:
    QString rel;
    QUrl href;
    QString prompt;
    QString name;
    QList<QCollectionJsonData> data;
};

QCollectionJsonQuery::QCollectionJsonQuery() : d(new QJsonCollectionQueryData)
{
}

QCollectionJsonQuery::QCollectionJsonQuery(const QCollectionJsonQuery &rhs) : d(rhs.d)
{
}

QCollectionJsonQuery &QCollectionJsonQuery::operator=(const QCollectionJsonQuery &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

QCollectionJsonQuery::~QCollectionJsonQuery()
{
}

bool QCollectionJsonQuery::isValid() const
{
    bool valid = !d->href.isEmpty() && !d->rel.isEmpty();
    foreach(const QCollectionJsonData data, d->data) {
        valid = valid && data.isValid();
    }
    return valid;
}

QString QCollectionJsonQuery::rel() const
{
    return d->rel;
}

void QCollectionJsonQuery::setRel(const QString &rel)
{
    d->rel = rel;
}

QUrl QCollectionJsonQuery::href() const
{
    return d->href;
}

void QCollectionJsonQuery::setHref(const QUrl &href)
{
    d->href = href;
}

QString QCollectionJsonQuery::prompt() const
{
    return d->prompt;
}

void QCollectionJsonQuery::setPrompt(const QString &prompt)
{
    d->prompt = prompt;
}

QString QCollectionJsonQuery::name() const
{
    return d->name;
}

void QCollectionJsonQuery::setName(const QString &name)
{
    d->name = name;
}

QList<QCollectionJsonData> QCollectionJsonQuery::data() const
{
    return d->data;
}

void QCollectionJsonQuery::setData(const QList<QCollectionJsonData> &data)
{
    d->data = data;
}

void QCollectionJsonQuery::addData(const QCollectionJsonData &data)
{
    d->data.append(data);
}

static const QString REL("rel");
static const QString HREF("href");
static const QString PROMPT("prompt");
static const QString NAME("name");
static const QString DATA("data");

QVariant QCollectionJsonQuery::toVariant() const
{
    QVariantMap result;
    result[REL] = rel();
    result[HREF] = href();
    if(!prompt().isEmpty()) result[PROMPT] = prompt();
    if(!prompt().isEmpty()) result[NAME] = name();

    QVariantList list;
    foreach(const QCollectionJsonData data, d->data) {
        list.append(data.toVariant());
    }
    if(!list.isEmpty()) result[DATA] = list;

    return result;
}

QCollectionJsonQuery QCollectionJsonQuery::fromVariant(const QVariant &variant)
{
    QCollectionJsonQuery result;
    if(!variant.canConvert<QVariantMap>())
        return result;

    QVariantMap query = variant.toMap();
    result.setRel(query[REL].toString());
    result.setHref(query[HREF].toUrl());
    result.setPrompt(query[PROMPT].toString());
    result.setName(query[NAME].toString());

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

    return result;
}
