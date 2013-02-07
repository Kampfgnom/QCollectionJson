#ifndef QCOLLECTIONJSONERROR_H
#define QCOLLECTIONJSONERROR_H

#include <QSharedDataPointer>

class QVariant;

class QCollectionJsonErrorData;

class QCollectionJsonError
{
public:
    QCollectionJsonError();
    QCollectionJsonError(const QString &title, const QString &code, const QString &message);
    QCollectionJsonError(const QCollectionJsonError &);
    QCollectionJsonError &operator=(const QCollectionJsonError &);
    ~QCollectionJsonError();

    bool isValid() const;

    QString title() const;
    void setTitle(const QString &title);

    QString code() const;
    void setCode(const QString &code);

    QString message() const;
    void setMessage(const QString &message);

    QVariant toVariant() const;

    static QCollectionJsonError fromVariant(const QVariant &variant);

private:
    QSharedDataPointer<QCollectionJsonErrorData> data;
};

#endif // QCOLLECTIONJSONERROR_H
