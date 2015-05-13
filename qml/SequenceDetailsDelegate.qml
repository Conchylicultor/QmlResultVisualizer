import QtQuick 2.2
import QtQuick.Layouts 1.1


Component {
    id: sequencedetailsdelegate

    Rectangle {
        height: 120
        width: parent.width

        color: "#3C1900"
        border.width : 3
        border.color : "#AA6939"
        radius: 15.0

        Row {
            anchors.fill: parent;
            anchors.margins: 5;

            Item
            {
                height:parent.height
                width: 200
                Text
                {
                    anchors.left: parent.left
                    anchors.top: parent.top

                    anchors.margins: 15;
                    anchors.topMargin: 10;

                    color:"#FFD2B1"

                    text: '<b>Name:     </b> ' + model.name + '<br/>' +
                          '<b>Camera:   </b> ' + model.camId + '<br/>' +
                          '<b>Date:     </b> ' + model.date + '<br/>' +
                          '<b>Duration: </b> ' + model.duration
                }
            }

            Repeater {
                model: imgUrlList

                Image {
                    id: sequenceImage
                    source: "file://" + model.modelData
                    height: 110
                    fillMode: Image.PreserveAspectFit
                    scale:0.0 // Initial state

                    PropertyAnimation {
                        id:apparitionAnimation
                        target: sequenceImage;
                        property: "scale";
                        easing.type: Easing.OutQuart
                        from: 0.0;
                        to: 1.0;
                        duration: 500
                        loops: 1;
                    }

                    Timer {
                        interval: (index+1)*50
                        running: true
                        repeat: false
                        onTriggered: {
                            apparitionAnimation.start()
                        }
                    }
                }
            }
        }
    }
}
