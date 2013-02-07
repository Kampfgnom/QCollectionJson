#include "qcollectionjsontemplate.h"
#include <QSharedData>

#include "qcollectionjsondata.h"

#include <QList>
#include <QVariantMap>

class QCollectionJsonTemplateData : public QSharedData {
public:
    QList<QCollectionJsonData> data;
};

QCollectionJsonTemplate::QCollectionJsonTemplate() : d(new QCollectionJsonTemplateData)
{
}

QCollectionJsonTemplate::QCollectionJsonTemplate(const QCollectionJsonTemplate &rhs) : d(rhs.d)
{
}

QCollectionJsonTemplate &QCollectionJsonTemplate::operator=(const QCollectionJsonTemplate &rhs)
{
    if (this != &rhs)
        d.operator=(rhs.d);
    return *this;
}

QCollectionJsonTemplate::~QCollectionJsonTemplate()
{
}

bool QCollectionJsonTemplate::isValid() const
{
    bool valid = true;
    foreach(const QCollectionJsonData data, d->data) {
        valid = valid && data.isValid();
    }
    return valid;
}

QList<QCollectionJsonData> QCollectionJsonTemplate::data() const
{
    return d->data;
}

void QCollectionJsonTemplate::setData(const QList<QCollectionJsonData> &data)
{
    d->data = data;
}

void QCollectionJsonTemplate::addData(const QCollectionJsonData &data)
{
    d->data.append(data);
}

static const QString DATA("data");

QVariant QCollectionJsonTemplate::toVariant() const
{
    QVariantMap result;

    QVariantList list;
    foreach(const QCollectionJsonData data, d->data) {
        list.append(data.toVariant());
    }
    if(!list.isEmpty()) result[DATA] = list;

    return result;
}

QCollectionJsonTemplate QCollectionJsonTemplate::fromVariant(const QVariant &variant)
{
    QCollectionJsonTemplate result;
    if(!variant.canConvert<QVariantMap>())
        return result;

    QVariantMap temp = variant.toMap();

    if(temp.contains(DATA)) {
        QVariant v = temp.value(DATA);

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
