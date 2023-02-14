import QtQuick 2.12
import QtQuick.Window 2.12

Canvas {
    id: root

    width: 400
    height: 400

    onPaint: {
        var ctx = getContext("2d")

        // 显示图片，路径，显示位置（x,y)
//        ctx.drawImage("../image/3.png", 10, 10)  // 使用前需先加载

        ctx.save() // 保持裁剪状态
        ctx.strokeStyle = "red"
        ctx.beginPath()
        ctx.moveTo(210, 100)
        ctx.lineTo(310, 100)
        ctx.lineTo(260, 175)
        ctx.closePath()
        ctx.stroke()  // 显示
        ctx.clip()  // 进入裁剪状态
        ctx.drawImage("../image/3.png", 200, 10)  // 只显示裁剪区域的图像
        ctx.restore() // 结束裁剪状态，恢复正常状态

        ctx.drawImage("../image/3.png", 10, 10)
    }

    // 加载图片
    Component.onCompleted: {
        loadImage("../image/3.png")
    }
}
