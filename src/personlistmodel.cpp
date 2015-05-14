#include "personlistmodel.h"


Person::Person(const QString &name) : name(name), nbOccurrence(0)
{
}

PersonListModel::PersonListModel() :
    QAbstractListModel(0)
{

}

int PersonListModel::rowCount(const QModelIndex &parent) const{
    return personList.size();
}

QVariant PersonListModel::data(const QModelIndex &index, int role) const{
    if(role == NameRole)
    {
        return personList.at(index.row()).name;
    }
    else if(role == OccurenceRole)
    {
        return personList.at(index.row()).nbOccurrence;
    }
    return QVariant();
}


QHash<int, QByteArray> PersonListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[OccurenceRole] = "occurence";
    return roles;
}

void PersonListModel::addPerson(const QString &stringName, const QString &seqId){

    // Format the name
    QString name = stringName;
    name.replace(QString("_"),QString(" "));

    // Add the
    bool find = false;

    for(Person &currentPers : personList) {
        if(currentPers.name == name)
        {
            find = true;

            currentPers.nbOccurrence++;
            currentPers.seqIdsList.append(seqId);
        }
    }

    if(!find)
    {
        personList.append(Person(name));
        personList.back().nbOccurrence++;
        personList.back().seqIdsList.append(seqId);
    }
}

void PersonListModel::plotDetails(int row) {
    emit personSelected(personList.at(row).seqIdsList);
}
