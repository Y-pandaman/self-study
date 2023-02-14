import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import QtQuick.Controls.Imagine 2.12

ApplicationWindow {
    visible: true
    width: 640; height: 480
    title: "Imaging"

    Column {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        width: parent.width / 2
        spacing: 10

        Repeater {
            model: 5
            delegate: Button {
                width: parent.width
                height: 70
                text: "Cleck me !"
            }
        }
    }

    Grid {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        columns: 2
        spacing: 10

        Repeater {
            model: 10
            delegate: Button {
                height: 70
                text: "Check me !"
                checkable: true
            }
        }
    }
}
