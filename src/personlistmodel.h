#ifndef PERSONLISTMODEL_H
#define PERSONLISTMODEL_H

#include <QAbstractListModel>

#include "sequencedetailsmodel.h"

class Person
{
public:
    Person(const QString &name);

    QString name;
    int nbOccurrence;

    QStringList seqIdsList;
};

class PersonListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PersonRoles {
        NameRole = Qt::UserRole,
        OccurenceRole
    };

    PersonListModel(SequenceDetailsModel &sm);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void addPerson(const QString &stringName, const QString &seqId);


public slots:
    void plotDetails(int row);

private:
    QList<Person> personList;
    SequenceDetailsModel *sm; // TODO: Replace by signal/slot (emit/receive the seqId) ?

};

#endif // PERSONLISTMODEL_H
