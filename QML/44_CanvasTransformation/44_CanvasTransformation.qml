import QtQuick 2.12
import QtQuick.Window 2.12

Canvas {
    id: root
    width: 400
    height: 400

    onPaint: {
        var ctx = getContext("2d")
        ctx.lineWidth = 4
        ctx.strokeStyle = "blue"
        ctx.translate(root.width / 2, root.height / 2)  // 原点移动到中心

        ctx.beginPath()
//        ctx.save()
        ctx.scale(1.5, 1.5)  // 缩放，同时指定x,y的缩放值
        ctx.rect(-30, -30, 60 ,60)
        ctx.stroke()
//        ctx.restore()

//        ctx.resetTransform()  // 恢复所有变换，原点回到左上角
//        ctx.translate(root.width / 2, root.height / 2)  // 原点移动到中心

        ctx.beginPath()
        ctx.rotate(Math.PI / 4)
        ctx.strokeStyle = "red"
        ctx.rect(-30, -30, 60 ,60)
        ctx.stroke()

//        ctx.closePath()
    }
}
