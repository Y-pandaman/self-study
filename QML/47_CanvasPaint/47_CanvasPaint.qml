import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    visible: true
    width: 640
    height: 480

    Row {
        id: colorTools
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 8
        }
        property color paintColor: "blue"
        Repeater {
            model: ["blue", "green", "yellow", "red"]
            ColorSquare {
                color: modelData
                down: parent.paintColor === color  // 按下
                onClicked: {
                    parent.paintColor = color  // 获取点击的颜色
                }
            }
        }
    }

    Canvas {
        id: canvas
        anchors {
            left: parent.left
            right: parent.right
            top: colorTools.bottom
            bottom: parent.bottom
            margins: 8
        }

        property real lastX
        property real lastY
        property color color: colorTools.paintColor
        onPaint: {
            var ctx = getContext("2d")
            ctx.lineWidth = 3
            ctx.strokeStyle = canvas.color
            ctx.beginPath()
            ctx.moveTo(lastX, lastY)
            lastX = area.mouseX
            lastY = area.mouseY
            ctx.lineTo(lastX, lastY)
            ctx.stroke()
        }

        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: {
                canvas.lastX = mouseX  // 获取鼠标坐标
                canvas.lastY = mouseY
            }
            onPositionChanged: {
                canvas.requestPaint()
            }
        }
    }
}
