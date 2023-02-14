import QtQuick 2.0

Rectangle {
    color: "blue"
    property alias text: label.text
    property alias rect_color: rect.color
    Text {
        id: label
        text: qsTr("text")
        color: "white"
        anchors.centerIn: parent
    }

    Rectangle {
        id: rect
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 4
        width: 16; height: 16
        radius: 8
        color: "yellow"
    }
}
