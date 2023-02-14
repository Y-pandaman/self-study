import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: root
    visible: true
    width: 640
    height: 480
    color: "#4a4a4a"

    Image {
        id: image
        source: "../image/3.png"
        x: (root.width - width) / 2; y: 40
    }

    Text {
        color: "white"
//        x: (root.width - width) / 2;   // 居中
        width: root.width
        horizontalAlignment: Text.AlignHCenter  // 居中

        y: image.y + image.height + 20
        text: "企鹅"
    }
}
