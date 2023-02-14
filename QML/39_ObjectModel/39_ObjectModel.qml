import QtQuick 2.12
import QtQuick.Window 2.12
import QtQml.Models 2.12

Rectangle {
    visible: true
    width: 640
    height: 480

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#112233"
        }
        GradientStop {
            position: 1.0
            color: "#445566"
        }
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        model: itemModel
    }

    // ObjectModel不用delegate,直接定义要显示的内容
    ObjectModel {
        id: itemModel

        Rectangle {
            height: 50
            width: 50
            color: "blue"
        }

        Rectangle {
            height: 50
            width: 100
            color: "yellow"
            Text {
                anchors.centerIn: parent
                text: qsTr("text")
            }
        }

        Rectangle {
            height: 50
            width: 50
            radius: 25
            color: "green"
        }
    }
}
