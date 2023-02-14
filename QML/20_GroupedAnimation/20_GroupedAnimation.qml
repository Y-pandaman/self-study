import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Grouped Animation")
    property int duration: 3000

    Image {
        source: "../image/ChatFormBG.jpg"
        anchors.fill: parent
    }

    ClickableImageV3 {
        id: qq
        x: 20; y: root.height - height
        source: "../image/3.png"
        text: "qq"
        onClicked: animation.restart()
    }

    // 容器
//    SequentialAnimation {  // 顺序动画
    ParallelAnimation {   // 并行动画
        id: animation
        NumberAnimation {
            target: qq
            properties: "y"
            from: root.height - qq.height
            to: 20
            duration: root.duration
        }

        NumberAnimation {
            target: qq
            properties: "x"
            from: 20
            to: 450
            duration: root.duration
        }
    }
}
