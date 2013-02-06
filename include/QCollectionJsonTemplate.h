#ifndef QCOLLECTIONJSONTEMPLATE_H
#define QCOLLECTIONJSONTEMPLATE_H

#include <QSharedDataPointer>

class QVariant;
class QCollectionJsonData;

class QCollectionJsonTemplateData;
class QCollectionJsonTemplate
{
public:
    QCollectionJsonTemplate();
    QCollectionJsonTemplate(const QCollectionJsonTemplate &);
    QCollectionJsonTemplate &operator=(const QCollectionJsonTemplate &);
    ~QCollectionJsonTemplate();

    bool isValid() const;

    QList<QCollectionJsonData> data() const;
    void setData(const QList<QCollectionJsonData> &data);
    void addData(const QCollectionJsonData &data);

    QVariant toVariant() const;

    static QCollectionJsonTemplate fromVariant(const QVariant &variant);

private:
    QSharedDataPointer<QCollectionJsonTemplateData> d;
};

#endif // QCOLLECTIONJSONTEMPLATE_H
