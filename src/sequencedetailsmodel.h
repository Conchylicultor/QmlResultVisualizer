#ifndef SEQUENCEDETAILSMODEL_H
#define SEQUENCEDETAILSMODEL_H

#include <QAbstractListModel>

class SequenceDetails
{
public:
    SequenceDetails(const QString &sequenceId);

    QString seqId;
    QString camId;
    QString date;
    QString duration;

    QStringList imgUrlList;
};

class SequenceDetailsModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum SeqRoles {
        NameRole = Qt::UserRole,
        CamIdRole,
        DateRole,
        DurationRole,
        ImgUrlList
    };

    SequenceDetailsModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void plotDetails(const QStringList &newData);

private:
    QList<SequenceDetails> sequenceList;
};

#endif // SEQUENCEDETAILSMODEL_H
