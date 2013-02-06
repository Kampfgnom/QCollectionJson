#ifndef QCOLLECTIONJSONDATA_H
#define QCOLLECTIONJSONDATA_H

#include <QSharedDataPointer>

class QVariant;

class QCollectionJsonDataData;

class QCollectionJsonData
{
public:
    QCollectionJsonData();
    QCollectionJsonData(const QCollectionJsonData &);
    QCollectionJsonData &operator=(const QCollectionJsonData &);
    ~QCollectionJsonData();

    bool isValid() const;

    QString name() const;
    void setName(const QString &name);

    QVariant value() const;
    void setValue(const QVariant &value);

    QString prompt() const;
    void setPrompt(const QString &prompt);

    QVariant toVariant() const;

    static QCollectionJsonData fromVariant(const QVariant &variant);

private:
    QSharedDataPointer<QCollectionJsonDataData> data;
};

#endif // QCOLLECTIONJSONDATA_H
