import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Soccer ball")
    property int duration: 2000

    Rectangle {
        id: sky
        width: root.width
        height: 300
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#0080ff"
            }
            GradientStop {
                position: 1.0
                color: "#66ccff"
            }
        }
    }

    Rectangle {
        id: ground
        anchors.top: sky.bottom
        width: root.width
        height: 180
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#00ff00"
            }
            GradientStop {
                position: 1.0
                color: "#00903f"
            }
        }
    }

    Image {
        id: ball
        source: "../image/ball.png"
        scale: 0.5
        x: 0
        y: root.height - height

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ball.x = 0
                ball.y = root.height - ball.height
                ball.rotation = 0
                animation.restart()
            }
        }
    }

    ParallelAnimation {
        id: animation
        SequentialAnimation {
            NumberAnimation {
                properties: "y"
                target: ball
                to: 150
                duration: root.duration * 0.4
                easing.type: Easing.OutCirc
            }
            NumberAnimation {
                properties: "y"
                target: ball
                to: root.height - ball.height
                duration: root.duration * 0.6
                easing.type: Easing.OutBounce
            }
        }
        NumberAnimation {
            properties: "x"
            target: ball
            to: 400
            duration: root.duration
        }
        RotationAnimation {
            properties: "rotation"
            target: ball
            to: 1800
            duration: root.duration
        }
    }
}
