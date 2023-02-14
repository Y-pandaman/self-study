import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property int time: 0

    Button {
        id: startButton
        text: "start"
        onClicked: {
            timer.start()
        }
    }

    Button {
        id: stopButton
        text: "stop"
        onClicked: {
            timer.stop()
        }
        anchors.left: startButton.right
        anchors.margins: 20
    }

    Timer {
        id: timer
        interval: 100
        running: true  // 启动，只触发一次
        repeat: true  // 不断触发
        triggeredOnStart: true  // 定时器running时触发
        onTriggered: {
            time += 1
        }
    }

    Text {
        id: txt
        text: time
        font.pixelSize: 60
        anchors.centerIn: parent
    }
}
