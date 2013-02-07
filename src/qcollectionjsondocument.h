#ifndef QCOLLECTIONJSONDOCUMENT_H
#define QCOLLECTIONJSONDOCUMENT_H

#include <QSharedDataPointer>

#include <QUrl>
#include <QVariantMap>

class QVariant;
class QJsonDocument;
class QCollectionJsonLink;
class QCollectionJsonItem;
class QCollectionJsonError;
class QCollectionJsonQuery;
class QCollectionJsonTemplate;

class QCollectionJsonDocumentData;

class QCollectionJsonDocument
{
public:
    QCollectionJsonDocument();
    QCollectionJsonDocument(const QUrl &href);
    QCollectionJsonDocument(const QCollectionJsonDocument &);
    QCollectionJsonDocument &operator=(const QCollectionJsonDocument &);
    ~QCollectionJsonDocument();

    bool isValid() const;

    QUrl href() const;
    void setHref(const QUrl &href);

    QString version() const;
    void setVersion(const QString &version);
    
    QList<QCollectionJsonLink> links() const;
    void setLinks(const QList<QCollectionJsonLink> &links);
    void addLink(const QCollectionJsonLink &link);

    QList<QCollectionJsonItem> items() const;
    void setItems(const QList<QCollectionJsonItem> &items);
    void addItem(const QCollectionJsonItem &item);

    QList<QCollectionJsonQuery> queries() const;
    void setQueries(const QList<QCollectionJsonQuery> &queries);
    void addQuery(const QCollectionJsonQuery &query);
    QUrl queriesLink() const;
    void setQueriesLink(const QUrl &url);

    QCollectionJsonTemplate templateData() const;
    void setTemplate(const QCollectionJsonTemplate &templateData);
    QUrl templateLink() const;
    void setTemplateLink(const QUrl &url);

    QCollectionJsonError error() const;
    void setError(const QCollectionJsonError &error);

    QVariant toVariant() const;

    static QCollectionJsonDocument fromQVariant(const QVariantMap &jsonDocument);

private:
    QSharedDataPointer<QCollectionJsonDocumentData> data;
};

#endif // QCOLLECTIONJSONDOCUMENT_H
