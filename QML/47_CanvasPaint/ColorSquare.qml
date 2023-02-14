import QtQuick 2.0
import QtQuick.Controls 2.12

Button {
    width: 100
    height: 100
    property alias color: bg.color
    Rectangle {
        id: bg
        width: 90
        height: 90
        opacity: 0.8
        anchors.centerIn: parent
    }
}
