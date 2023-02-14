import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: mouse
        focus: true // 设置可获取焦点
        x: (parent.width - 100) / 2; y: (parent.height - 60) / 2
        width: 100; height: 60
        border.color: "#ff0000"
        radius: 10
    }

    // 鼠标区域元素
    MouseArea {
        // 设置区域
        x: mouse.x; y: mouse.y
        width: mouse.width; height:mouse.height
        onClicked: {
            console.log(mouseX, mouseY)
        }
    }
}
