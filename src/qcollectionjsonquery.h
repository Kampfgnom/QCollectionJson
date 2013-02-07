#ifndef QJSONCOLLECTIONQUERY_H
#define QJSONCOLLECTIONQUERY_H

#include <QSharedDataPointer>

class QUrl;
class QVariant;
class QCollectionJsonData;

class QJsonCollectionQueryData;

class QCollectionJsonQuery
{
public:
    QCollectionJsonQuery();
    QCollectionJsonQuery(const QUrl &href, const QString &rel);
    QCollectionJsonQuery(const QCollectionJsonQuery &);
    QCollectionJsonQuery &operator=(const QCollectionJsonQuery &);
    ~QCollectionJsonQuery();

    bool isValid() const;

    QString rel() const;
    void setRel(const QString &rel);

    QUrl href() const;
    void setHref(const QUrl &href);

    QString prompt() const;
    void setPrompt(const QString &prompt);

    QString name() const;
    void setName(const QString &name);

    QList<QCollectionJsonData> data() const;
    void setData(const QList<QCollectionJsonData> &data);
    void addData(const QCollectionJsonData &data);

    QVariant toVariant() const;

    static QCollectionJsonQuery fromVariant(const QVariant &variant);


private:
    QSharedDataPointer<QJsonCollectionQueryData> d;
};

#endif // QJSONCOLLECTIONQUERY_H
