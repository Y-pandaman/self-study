import QtQuick 2.0

Rectangle {
    id: root
    signal clicked
    property alias label: label

    color: "lightgray"
    border.color: "black"
    width: 100
    height: 50

    Text {
        id: label
        anchors.centerIn: parent
        font.pixelSize: 10
        text: qsTr("text")
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
