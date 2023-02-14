import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Component")

    Button {
        text: "开始"
//        color: "yellow"   // color未开放属性，不可改变
        onClicked: {
            text1.text = "按钮被点击"
        }
    }

    Text {
        id: text1
        x: 12; y: 76
        width: 116; height: 26
        text: "waiting ... "
        horizontalAlignment: Text.AlignHCenter
    }
}
