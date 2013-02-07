#include "qcollectionjsondata.h"
#include <QSharedData>

#include <QString>
#include <QVariant>

class QCollectionJsonDataData : public QSharedData {
public:
    QString name;
    QVariant value;
    QString prompt;
};

QCollectionJsonData::QCollectionJsonData() : data(new QCollectionJsonDataData)
{
}

QCollectionJsonData::QCollectionJsonData(const QString &name, const QVariant value) :
    data(new QCollectionJsonDataData)
{
    setName(name);
    setValue(value);
}

QCollectionJsonData::QCollectionJsonData(const QCollectionJsonData &rhs) : data(rhs.data)
{
}

QCollectionJsonData &QCollectionJsonData::operator=(const QCollectionJsonData &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QCollectionJsonData::~QCollectionJsonData()
{
}

bool QCollectionJsonData::isValid() const
{
    return !data->name.isEmpty();
}

QString QCollectionJsonData::name() const
{
    return data->name;
}

void QCollectionJsonData::setName(const QString &name)
{
    data->name = name;
}

QVariant QCollectionJsonData::value() const
{
    return data->value;
}

void QCollectionJsonData::setValue(const QVariant &value)
{
    data->value = value;
}

QString QCollectionJsonData::prompt() const
{
    return data->prompt;
}

void QCollectionJsonData::setPrompt(const QString &prompt)
{
    data->prompt = prompt;
}

static const QString PROMPT("prompt");
static const QString NAME("name");
static const QString VALUE("value");

QVariant QCollectionJsonData::toVariant() const
{
    QVariantMap result;
    result[NAME] = name();
    if(!value().isNull()) result[VALUE] = value();
    if(!prompt().isEmpty()) result[PROMPT] = prompt();
    return result;
}

QCollectionJsonData QCollectionJsonData::fromVariant(const QVariant &variant)
{
    QCollectionJsonData result;
    if(!variant.canConvert<QVariantMap>()) {
        return result;
    }

    QVariantMap data = variant.toMap();
    result.setPrompt(data[PROMPT].toString());
    result.setName(data[NAME].toString());
    result.setValue(data[VALUE]);

    return result;
}
