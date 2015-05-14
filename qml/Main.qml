import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Sequence Visualizer")

    Dialog {
        id: helpDialog
        title: "Sequence Visualizer"

        standardButtons: StandardButton.Ok

        Text {
            text: "<b>Sequence Visualizer</b><br/>" +
                  "Based on Qt 5.3.0 and Qml<br/>" +
                  "Etienne Pot, 2015"
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Exit"
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: "Help"
            MenuItem {
                text: "About"
                onTriggered: helpDialog.open();
            }
        }
    }

    SplitView {
        anchors.fill: parent

        TableView {
            objectName: "personListTableView"

            Layout.minimumWidth: 200

            model: personListModel

            signal personSelected(int row)

            onClicked: {
                personSelected(row)
            }

            TableViewColumn {
                title: "Person Name"
                role: "name"
            }

            TableViewColumn {
                title: "Nb occurence"
                role: "occurence"
            }
        }



        TabView {
            Layout.minimumWidth: 200
            Layout.fillWidth:true

            Tab {
                title: "List appearance"

                Rectangle {
                    color: "#202020"

                    ScrollView {
                        anchors.fill: parent

                        ListView {
                            anchors.margins: 5

                            model: sequenceDetailsModel
                            delegate: SequenceDetailsDelegate {}

                            spacing: 5
                        }
                    }
                }
            }

            Tab {
                title: "General informations"
                Text{
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: "TODO ???"
                }
            }
        }
    }
}
