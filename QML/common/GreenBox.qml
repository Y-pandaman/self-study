import QtQuick 2.0

Rectangle {
    color: "lightgreen"
    property alias text: label.text
    Text {
        id: label
        color: "white"
        anchors.centerIn: parent
        text: ""
    }
}
