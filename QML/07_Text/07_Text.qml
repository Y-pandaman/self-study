import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
//    color: "blue"  // 背景

    // 使用Image元素设置背景图片
    Image {
        width: root.width
        height: root.height
        source: "../image/2e84792c799715258e071ce0c33e111a.gif"
    }

    Text {
        id: txt
        width: root.width
        height: root.height
//        text: "hello qml"  // 文本
        text: "<a href=\"http://www.baidu.com\">百度一下</a>"  // 富文本
        onLinkActivated: console.log(link + " link activated")
        font.bold: true  //粗体
        font.pixelSize: 24  //字体大小
        color: "red"  // 字体颜色
        horizontalAlignment: Text.AlignHCenter  // 水平居中
        verticalAlignment: Text.AlignVCenter  // 垂直居中
    }
}
