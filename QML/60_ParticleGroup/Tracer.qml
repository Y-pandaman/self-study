import QtQuick 2.0

Item {
    id: item
    anchors.fill: parent
    property color color
    Rectangle {
        id: rect
        border.color: item.color
        color: Qt.rgba(0, 0, 0, 0)
        anchors.fill: parent
    }
}
