import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text{
        x: 0; y: 0  // 起始位置,子元素从父元素上继承了坐标系统
        width: 640; height: 480  // 显示区域
        text: "Hello World!"   // 文本
        verticalAlignment: Text.AlignVCenter  // 水平居中
        horizontalAlignment: Text.AlignHCenter  // 垂直居中
        font.pixelSize: 48  //字体大小
        color: "blue"   // 字体颜色
    }
}
