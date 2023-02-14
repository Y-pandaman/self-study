import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: root
    width: 430
    height: 300

    Canvas {
        id: canvas
        x: 10
        y: 10
        width: 200
        height: 200

        onPaint: {
            var ctx = getContext("2d")
            var x = 10 + Math.random() * 180
            var y = 10 + Math.random() * 180

            ctx.globalAlpha = 0.7
            ctx.fillStyle = Qt.hsla(Math.random(), 0.5, 0.5, 1.0)
            ctx.beginPath()
            ctx.arc(x, y, x / 5, 0, 360)
            ctx.fill() // 绘制
            ctx.closePath()
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var url = canvas.toDataURL("image/png")  // 设置编码格式
                image.source = url
            }
        }
    }

    Image {
        id: image
        x: 210
        y: 10
        width: 200
        height: 200
    }

    // 定时器绘制
    Timer {
        interval: 500
        running: true
        repeat: true  // 一直运行
        onTriggered: canvas.requestPaint()
    }
}
