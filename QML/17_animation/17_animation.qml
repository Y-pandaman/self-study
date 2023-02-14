import QtQuick 2.12
import QtQuick.Window 2.12

Image {
    id: root
    source: "../image/ChatFormBG.jpg"

    property int padding: 40
    property bool running: false
    Image {
        id: qq
        source: "../image/3.png"
        x: root.padding
        y: (root.height - height) / 2

        // x的值变化
//        PropertyAnimation on x {
        NumberAnimation on x {  // 效率更高
            to: root.width - qq.width - root.padding
            duration: 3000
            running: root.running
        }

        // 旋转值变化
//        PropertyAnimation on rotation {
//        RotationAnimator on rotation {
        RotationAnimation on rotation {
            to: 360
            duration: 3000
            running: root.running
        }

        // 尺度变化
        ScaleAnimator on scale {
            from: 1
            to: 0
            duration: 3000
            running: root.running
        }

        // 透明度变化
//        PropertyAnimation on opacity {
//        NumberAnimation on opacity {
        OpacityAnimator on opacity {  // 需要指定from
            from: 1
            to: 0
            duration: 3000
            running: root.running
        }
    }

//    // 透明度变化
//        OpacityAnimator on opacity {  // 需要指定from
//        target: qq  // 动画放到Image外面，需要指定target
//        from: 1
//        to: 0
//        duration: 3000
//        running: root.running
//    }

    // 鼠标点击启动
    MouseArea {
        anchors.fill: parent
        onClicked: root.running = true
    }
}
