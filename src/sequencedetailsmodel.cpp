#include "sequencedetailsmodel.h"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static const int nbSequenceImagesToPlot = 10;

SequenceDetails::SequenceDetails(const QString &sequenceId)
{
    // Global Id
    seqId = sequenceId;

    // Extract camera infos
    FileStorage fileTraceCam("/home/etienne/__A__/Dev/Reidentification/Data/Traces/" + sequenceId.toStdString() + "_cam.yml", FileStorage::READ);
    if(!fileTraceCam.isOpened())
    {
        cout << "Error: Cannot open the additional information file for the sequence " << sequenceId.toStdString() << endl;
        exit(0);
    }

    // Cam id
    std::string valueStr = fileTraceCam["camId"];
    camId = QString(valueStr.c_str());

    // Date
    int value = fileTraceCam["beginDate"];
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(value) * 1000);
    date = dateTime.toString("dd/MM/yy - HH:mm");

    // Duration
    QTime durationTime(0,0, static_cast<int>(fileTraceCam["endDate"]) - value);
    if(durationTime.minute() > 0)
    {
        duration += durationTime.toString("m") + " min ";
    }
    duration += durationTime.toString("ss") + " sec";

    fileTraceCam.release();

    // Extract the sequence image list
    QFile imgListFile("/home/etienne/__A__/Dev/Reidentification/Data/Traces/" + sequenceId + "_list.txt");
    if(!imgListFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error: Cannot open the images list";
        return;
    }

    QTextStream textStream(&imgListFile);
    QStringList lines;
    while (!textStream.atEnd())
    {
        lines.append("/home/etienne/__A__/Dev/Reidentification/Data/Traces/" + textStream.readLine() + ".png");
    }

    for(int i = 0 ; i < lines.size() ; i += 1 + lines.size()/nbSequenceImagesToPlot) // We add +1 in case of the list size is <5
    {
        imgUrlList.append(lines.at(i));
    }
}

SequenceDetailsModel::SequenceDetailsModel() :
    QAbstractListModel(0)
{
}

int SequenceDetailsModel::rowCount(const QModelIndex &parent) const{
    return sequenceList.size();
}

QVariant SequenceDetailsModel::data(const QModelIndex &index, int role) const{
    if(role == NameRole)
    {
        return sequenceList.at(index.row()).seqId;
    }
    else if(role == DateRole)
    {
        return sequenceList.at(index.row()).date;
    }
    else if(role == DurationRole)
    {
        return sequenceList.at(index.row()).duration;
    }
    else if(role == CamIdRole)
    {
        return sequenceList.at(index.row()).camId;
    }
    else if(role == ImgUrlList)
    {
        return sequenceList.at(index.row()).imgUrlList;
    }
    return QVariant();
}

QHash<int, QByteArray> SequenceDetailsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DurationRole] = "duration";
    roles[CamIdRole] = "camId";
    roles[DateRole] = "date";
    roles[ImgUrlList] = "imgUrlList";
    return roles;
}

void SequenceDetailsModel::plotDetails(const QStringList &newData)
{
    sequenceList.clear();

    foreach (const QString &sequenceId, newData) {
        sequenceList.append(SequenceDetails(sequenceId));
    }

    emit layoutChanged();
}
