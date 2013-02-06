#ifndef QCOLLECTIONJSONITEM_H
#define QCOLLECTIONJSONITEM_H

#include <QSharedDataPointer>

class QUrl;
class QVariant;
class QCollectionJsonLink;
class QCollectionJsonData;

class QCollectionJsonItemData;

class QCollectionJsonItem
{
public:
    QCollectionJsonItem();
    QCollectionJsonItem(const QCollectionJsonItem &);
    QCollectionJsonItem &operator=(const QCollectionJsonItem &);
    ~QCollectionJsonItem();

    bool isValid() const;

    QUrl href() const;
    void setHref(const QUrl &href);

    QList<QCollectionJsonLink> links() const;
    void setLinks(const QList<QCollectionJsonLink> &links);
    void addLink(const QCollectionJsonLink &link);

    QList<QCollectionJsonData> data() const;
    void setData(const QList<QCollectionJsonData> &data);
    void addData(const QCollectionJsonData &data);

    QVariant toVariant() const;

    static QCollectionJsonItem fromVariant(const QVariant &variant);

private:
    QSharedDataPointer<QCollectionJsonItemData> d;
};

#endif // QCOLLECTIONJSONITEM_H
