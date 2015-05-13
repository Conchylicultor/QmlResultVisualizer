#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "personlistmodel.h"
#include "sequencedetailsmodel.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Load the models
    SequenceDetailsModel sm;
    PersonListModel pm(sm);

    // Read all results from the text file
    QFile resultFile("/home/etienne/__A__/Dev/Reidentification/Data/Debug/network_save.net");
    if(!resultFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error: Cannot open the network file";
        return 0;
    }

    QTextStream textStream(&resultFile);
    QString line;
    while (!textStream.atEnd() || line.startsWith("*Edges"))
    {
        line = textStream.readLine();

        QRegExp nameRegex("pers:(\\S+)");
        QRegExp seqIdRegex("seq:(\\S+)");

        if(nameRegex.indexIn(line) != -1 && seqIdRegex.indexIn(line) != -1) // Correct sequence present
        {
            pm.addPerson(nameRegex.cap(1), seqIdRegex.cap(1));
        }
    }

    // Setup the engine
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("personListModel", &pm);
    engine.rootContext()->setContextProperty("sequenceDetailsModel", &sm);

    engine.load(QUrl(QStringLiteral("qrc:///qml/Main.qml")));

    QObject *personListTableView = engine.rootObjects().first()->findChild<QObject*>("personListTableView");
    if(personListTableView == 0)
    {
        qDebug() << "Error: No table view";
    }
    QObject::connect(personListTableView, SIGNAL(personSelected(int)),
                     &pm, SLOT(plotDetails(int)));
    //QObject::connect(pm, SIGNAL(personSelected(int)),
    //                 &sm, SLOT(plotDetails(int)));

    return app.exec();
}
