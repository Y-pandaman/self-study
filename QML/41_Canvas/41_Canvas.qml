
import QtQuick 2.12
import QtQuick.Window 2.12

Canvas {
    id: root

    width: 600
    height: 500

    onPaint: {
        var ctx = getContext("2d")
        ctx.lineWidth = 4   // 线宽
        ctx.strokeStyle = "blue"  // 画笔颜色
        ctx.fillStyle = "red"  // 填充色

        ctx.beginPath()  // 开始
        ctx.moveTo(50, 50)
        ctx.lineTo(200, 50)
        ctx.lineTo(200, 200)
        ctx.lineTo(50, 200)
        ctx.closePath()  // 结束,封闭图像
        ctx.fill()  // 填充
        ctx.stroke()  // 将图案渲染出来

        // 矩形  (起点x,起点y，宽，高）
        ctx.fillRect(250, 50, 50, 80)  // 填充的矩形
        ctx.clearRect(260, 60, 30, 60)  // 镂空矩形

        ctx.strokeRect(250, 200, 40, 40)  // 直接画矩形

        // 创建渐变色填充
        // 范围是整张画布
        var gradient = ctx.createLinearGradient(0, 0, 0, root.height)
        gradient.addColorStop(0, "blue")
        gradient.addColorStop(0.5, "red")  // 画布的一半

        ctx.fillStyle = gradient
        ctx.fillRect(300, 0, 50, 50)
        ctx.fillRect(350, 50, 50, 50)
        ctx.fillRect(400, 100, 50, 50)
        ctx.fillRect(450, 150, 50, 50)
        ctx.fillRect(500, 200, 50, 50)
        ctx.fillRect(550, 250, 50, 350)
    }
}
