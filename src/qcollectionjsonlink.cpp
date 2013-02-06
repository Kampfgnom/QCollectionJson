#include "qcollectionjsonlink.h"
#include <QSharedData>

#include <QUrl>
#include <QVariant>
#include <QString>

class QCollectionJsonLinkData : public QSharedData {
public:
    QString rel;
    QUrl href;
    QString prompt;
    QString name;
    QString render;
};

QCollectionJsonLink::QCollectionJsonLink() : data(new QCollectionJsonLinkData)
{
}

QCollectionJsonLink::QCollectionJsonLink(const QCollectionJsonLink &rhs) : data(rhs.data)
{
}

QCollectionJsonLink &QCollectionJsonLink::operator=(const QCollectionJsonLink &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QCollectionJsonLink::~QCollectionJsonLink()
{
}

bool QCollectionJsonLink::isValid() const
{
    return !data->rel.isEmpty() && !data->href.isEmpty();
}

QString QCollectionJsonLink::rel() const
{
    return data->rel;
}

void QCollectionJsonLink::setRel(const QString &rel)
{
    data->rel = rel;
}

QUrl QCollectionJsonLink::href() const
{
    return data->href;
}

void QCollectionJsonLink::setHref(const QUrl &href)
{
    data->href = href;
}

QString QCollectionJsonLink::prompt() const
{
    return data->prompt;
}

void QCollectionJsonLink::setPrompt(const QString &prompt)
{
    data->prompt = prompt;
}

QString QCollectionJsonLink::name() const
{
    return data->name;
}

void QCollectionJsonLink::setName(const QString &name)
{
    data->name = name;
}

QString QCollectionJsonLink::render() const
{
    return data->render;
}

void QCollectionJsonLink::setRender(const QString &render)
{
    data->render = render;
}

static const QString REL("rel");
static const QString HREF("href");
static const QString PROMPT("prompt");
static const QString NAME("name");
static const QString RENDER("render");

QVariant QCollectionJsonLink::toVariant() const
{
    QVariantMap result;
    result[REL] = rel();
    result[HREF] = href();
    result[PROMPT] = prompt();
    result[NAME] = name();
    result[RENDER] = render();
    return result;
}


QCollectionJsonLink QCollectionJsonLink::fromVariant(const QVariant &variant)
{
    QCollectionJsonLink result;
    if(!variant.canConvert<QVariantMap>()) {
        return result;
    }

    QVariantMap link = variant.toMap();
    result.setRel(link[REL].toString());
    result.setHref(link[HREF].toUrl());
    result.setPrompt(link[PROMPT].toString());
    result.setName(link[NAME].toString());
    result.setRender(link[RENDER].toString());

    return result;
}
