import QtQuick 2.12
import QtQuick.Window 2.12

Canvas {
    id: canvas
    width: 800
    height: 400

    onPaint: {
        var ctx = getContext("2d")
        ctx.fillStyle = "#333"
        ctx.fillRect(0, 0, canvas.width, canvas.height)

        // 阴影设置
        ctx.shadowColor = "red"  // 阴影颜色
        ctx.shadowOffsetX = 3  // x偏移
        ctx.shadowOffsetY = 3 // y偏移
        ctx.shadowBlur = 10  // 模糊处理

        // 渲染文字
        ctx.font = "bold 80px sans-serif"  // 粗体、大小、字体
        ctx.fillStyle = "lightgreen"  // 字体颜色
        ctx.fillText("I'm Coming !!!", 200, 200)  // 文字内容、位置
    }
}
