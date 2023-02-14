import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 700
    height: 480
    color: "gray"
    title: qsTr("Hello World")

    ClickableImageV2 {
        id: qq1
        x: 40; y: root.height - height
        source: "../image/3.png"
        text: "animation on property"

        NumberAnimation on y{
            to: 40
            duration: 3000
        }
    }

    ClickableImageV2 {
        id: qq2
        x: qq1.x + qq1.width + 20; y: root.height - height
        source: "../image/3.png"
        text: "animation on property"

        Behavior on y{
            NumberAnimation{
                duration: 3000
            }
        }

        onClicked: y = 40
    }

    ClickableImageV2 {
        id: qq3
        x: qq2.x + qq1.width + 20; y: root.height - height
        source: "../image/3.png"
        text: "animation on property"

//        onClicked: anim.restart()  // 点击重启动画
        NumberAnimation {  // 执行动画需要主动调用
            id: anim
            target: qq3
            from: root.height - qq3.height
            to: 40
            duration: 3000
            property: "y"  // 针对的属性
            running: area.pressed  // 按压鼠标才执行动画
        }

        MouseArea {
            id: area
            anchors.fill: parent
        }
    }
}
