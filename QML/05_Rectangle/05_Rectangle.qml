import QtQuick 2.12
import QtQuick.Window 2.12


Rectangle {
    id: root
    width: 200
//    height: 100
    height: root.width
    border.color: "#00ff00"
    border.width: 5  // 边框大小

    Rectangle {
        x: 50
        y: 50
        width: 100
        height: 100
//        border.color: "#ff0000"  // 边框颜色
//        border.width: 5  // 边框大小
        border {
            color: "#ff0000"
            width: 5
        }
        color: "#0000ff"  // 背景颜色
        radius: 50 // 倒角半径
    }
}


/*
Item {
    id: root
    width: 200; height: 200

    Rectangle {
        id: rect1
        x: 12; y: 12
        width: 76; height: 96
        color: "#ff0000"
    }
    // 下面的矩形框会覆盖上面的，可通过z值调整上下层关系
    Rectangle {
        id: rect2
        x: 50; y: 50
        width: 76; height: 96
        border.color: "#00ff00"
        color: "#0000ff"
        radius: 50
    }
}
*/
