#include "qcollectionjsonerror.h"
#include <QSharedData>

#include <QVariantMap>
#include <QString>

class QCollectionJsonErrorData : public QSharedData {
public:
    QCollectionJsonErrorData() : QSharedData(),
        valid(false)
    {}

    QString title;
    QString code;
    QString message;
    bool valid;
};

QCollectionJsonError::QCollectionJsonError() : data(new QCollectionJsonErrorData)
{
}

QCollectionJsonError::QCollectionJsonError(const QCollectionJsonError &rhs) : data(rhs.data)
{
}

QCollectionJsonError &QCollectionJsonError::operator=(const QCollectionJsonError &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QCollectionJsonError::~QCollectionJsonError()
{
}

bool QCollectionJsonError::isValid() const
{
    return data->valid;
}

QString QCollectionJsonError::title() const
{
    return data->title;
}

void QCollectionJsonError::setTitle(const QString &title)
{
    data->valid = data->valid || !title.isEmpty();
    data->title = title;
}

QString QCollectionJsonError::code() const
{
    return data->code;
}

void QCollectionJsonError::setCode(const QString &code)
{
    data->valid = data->valid || !code.isEmpty();
    data->code = code;
}

QString QCollectionJsonError::message() const
{
    return data->message;
}

void QCollectionJsonError::setMessage(const QString &message)
{
    data->valid = data->valid || !message.isEmpty();
    data->message = message;
}

static const QString TITLE("title");
static const QString CODE("code");
static const QString MESSAGE("message");

QVariant QCollectionJsonError::toVariant() const
{
    QVariantMap result;
    result[TITLE] = title();
    result[CODE] = code();
    result[MESSAGE] = message();
    return result;
}

QCollectionJsonError QCollectionJsonError::fromVariant(const QVariant &variant)
{
    QCollectionJsonError result;
    if(!variant.canConvert<QVariantMap>()) {
        return result;
    }

    QVariantMap data = variant.toMap();
    result.setTitle(data[TITLE].toString());
    result.setCode(data[CODE].toString());
    result.setMessage(data[MESSAGE].toString());
    result.data->valid = !variant.isNull() && variant.isValid();

    return result;
}
