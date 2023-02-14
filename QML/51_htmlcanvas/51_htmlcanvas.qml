import QtQuick 2.12
import QtQuick.Window 2.12

Canvas {
    id: canvas
    width: 800
    height: 450

    property real lastX: width * Math.random()
    property real lastY: height * Math.random()
    property real hue: 0

    property bool requestLine: false
    property bool requestBlank: false

    onPaint: {
        var ctx = getContext('2d')
        if(requestLine) {
            line(ctx)
            requestLine = false
        }
        if(requestBlank){
            blank(ctx)
            requestBlank = false
        }
    }

    function line(context) {
        context.save()

        context.translate(canvas.width / 2, canvas.height / 2)
        context.scale(0.9, 0.9)
        context.translate(-canvas.width / 2, -canvas.height /2)

        context.beginPath()
        context.lineWidth = 5 + Math.random() * 10

        context.moveTo(lastX, lastY)

        lastX = canvas.width * Math.random()
        lastY = canvas.height * Math.random()

        context.bezierCurveTo(
                    canvas.width * Math.random(),
                    canvas.height * Math.random(),
                    canvas.width * Math.random(),
                    canvas.height * Math.random(),
                    lastX,
                    lastY
                    )

        hue = hue + 0.1 * Math.random()
        if(hue > 1.0)
            hue -= 1
        context.strokeStyle = Qt.hsla(hue, 0.5, 0.5, 1.0)
        context.stroke()
        context.restore()
    }

    Component.onCompleted: {
        lineTimer.start()
        blankTimer.start()
    }

    Timer {
        id: lineTimer
        interval: 50
        repeat: true
        onTriggered: {
            canvas.requestPaint()
            requestLine = true
        }
    }

    // 背景逐渐变暗
    function blank(context) {
        context.fillStyle = Qt.rgba(0, 0, 0, 0.1)
        context.fillRect(0, 0, canvas.width, canvas.height)
    }

    Timer {
        id: blankTimer
        interval: 40
        repeat: true
        onTriggered: {
            canvas.requestPaint()
            requestBlank = true
        }
    }
}
