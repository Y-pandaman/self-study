import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("turn round")

    Image {
        anchors.fill: parent  // 用当前元素填充parent，背景随窗口大小填充
        id: background
        source: "image/PersonalFormBG.jpg"

        Image {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            height: background.height / 2
            id: pole
            source: "image/BackgroundColor.bmp"
        }

        Image {
            anchors.centerIn: parent   // 放到parent的中间
            id: qq
            source: "image/3.png"

            // 动画，100ms完成
            Behavior on rotation {
                NumberAnimation {
                    duration: 100
                }
            }
        }

        // 点击企鹅，企鹅会旋转
        MouseArea {
            anchors.fill: parent
            onClicked: qq.rotation += 720
        }

    }
}
