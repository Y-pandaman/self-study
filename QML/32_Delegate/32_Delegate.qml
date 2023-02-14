import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    width: 120
    height: 300

    // 渐变色背景
    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#123456"
        }
        GradientStop {
            position: 1.0
            color: "#654321"
        }
    }

    ListView {
        anchors.fill: parent
        id: listView
        anchors.margins: 20
        focus: true
        clip: true
        spacing: 5
        model: 100
        delegate: numberDelegate
    }

    Component {
        id: numberDelegate

        Rectangle {
            width: ListView.view.width
            height: 40
            color: ListView.isCurrentItem ? "lightblue" : "lightgreen"
            border.color: Qt.lighter(color, 0.5)
            id: rect
            Text {
                id: text
                anchors.centerIn: parent
                text: index
                font.pixelSize: 15
            }
        }
    }
}
