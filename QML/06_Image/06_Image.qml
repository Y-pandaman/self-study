import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Image {
        id: image1
        x: 0; y: (parent.height - 46) / 2
        width: 40; height: 46
        source: "../image/1.png"
        sourceSize.width: 20
    }

    Image {
        id: image2
        x: (parent.width - 199) / 2; y: (parent.height - 228) / 2
        width: 199; height: 228
        source: "../image/3.png"
    }

    Image {
        id: image3
        x: image2.x + image2.width + 20; y: (parent.height - 228) / 2
        width: image2.width / 3
        source: "../image/3.png"
//        fillMode: Image.Stretch                         // 拉伸
//        fillMode: Image.PreserveAspectCrop  // 裁剪
        fillMode: Image.PreserveAspectFit         // 自适应
    }
}
