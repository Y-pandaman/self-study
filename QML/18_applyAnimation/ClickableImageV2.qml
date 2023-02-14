
import QtQuick 2.0

Item {
    id: root
    width: container.childrenRect.width  // 所有子窗口的宽度
    height: container.childrenRect.height
    // 开放可修改属性
    property alias text: label.text
    property alias source: image.source

    signal clicked

    Column {
        id: container

        Image {
            id: image
        }

        Text {
            id: label
            width: image.width   // 宽度不超过图片的宽度
            wrapMode: Text.WordWrap   // 文本自动换行
            horizontalAlignment: Text.AlignHCenter  // 水平居中
            color: "#ececec"
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
