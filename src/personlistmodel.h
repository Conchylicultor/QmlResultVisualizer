#ifndef PERSONLISTMODEL_H
#define PERSONLISTMODEL_H

#include <QAbstractListModel>

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

    PersonListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void addPerson(const QString &stringName, const QString &seqId);

public slots:
    void plotDetails(int row);

signals:
    void personSelected(const QStringList &sequenceIdList);

private:
    QList<Person> personList;
};

#endif // PERSONLISTMODEL_H
