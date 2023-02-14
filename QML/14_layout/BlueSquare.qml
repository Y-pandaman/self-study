import QtQuick 2.0

Rectangle {
    width: 50
    height: 50
    color: "blue"
    border.color: Qt.lighter(color)

    // 开放Text
    property alias text: label.text
    Text {
        id: label
        text: "text"
        color: "white"
        anchors.centerIn: parent
    }
}
