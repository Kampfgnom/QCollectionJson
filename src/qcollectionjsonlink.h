#ifndef QCOLLECTIONJSONLINK_H
#define QCOLLECTIONJSONLINK_H

#include <QSharedDataPointer>

class QUrl;
class QVariant;

class QCollectionJsonLinkData;

class QCollectionJsonLink
{
public:
    QCollectionJsonLink();
    QCollectionJsonLink(const QCollectionJsonLink &);
    QCollectionJsonLink &operator=(const QCollectionJsonLink &);
    ~QCollectionJsonLink();

    bool isValid() const;

    QString rel() const;
    void setRel(const QString &rel);

    QUrl href() const;
    void setHref(const QUrl &href);

    QString prompt() const;
    void setPrompt(const QString &prompt);

    QString name() const;
    void setName(const QString &name);

    QString render() const;
    void setRender(const QString &render);

    QVariant toVariant() const;

    static QCollectionJsonLink fromVariant(const QVariant &variant);

private:
    QSharedDataPointer<QCollectionJsonLinkData> data;
};

#endif // QCOLLECTIONJSONLINK_H
