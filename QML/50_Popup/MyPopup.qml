import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {
    id: popup
    x: 400
    y: 200
    width: 400
    height: 300
    modal: true  // 是否模态框，true: 只显示当前框，外部控件都点不了
    focus: true
    visible: true
    //    dim: true  // 是否需要设置非模态对话框的背景色

    // 关闭属性，默认esc键和框外部的键
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

    // 进入效果动画
    enter: Transition {
        NumberAnimation {
            property: "opacity"
            from: 0.0
            to: 1.0
            duration: 1000
        }
    }

    // 退出效果动画
    exit: Transition {
        NumberAnimation {
            property: "opacity"
            from: 1.0
            to: 0.0
            duration: 1000
        }
    }

    contentItem: Rectangle {
        color: "lightblue"
        anchors.fill: parent
        Text {
            id: text
            anchors.fill: parent
            text: qsTr("1234567 890qwefdgfdrtyui  oqasdfghjgdfsgfd sgdfsgdfsgdfs  gzxcvbn") + contentWidth
            font.pixelSize: 20
            wrapMode: Text.WordWrap
        }
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 30
        text: "Cancel"
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 230
        text: "Ok"
    }

    // 控制popup模态框框外部的属性
    Overlay.modal: Rectangle {
        anchors.fill: parent
        //        color: "red"  // 英语赋色
        //        color: "#00ff00"  // RGB赋色
        color: "#33ff0000"  // RGBA赋色   ARGB

        Popup { // 为了让其他的button有用，在popup中新建一个popup
            width: parent.width
            height: 70
            visible: true
            closePolicy: Popup.NoAutoClose  // popup框不消失
            background: Rectangle{
                color: "transparent"  // 透明色
//                color: "grey"
            }
            Button {
                width: 50
                height: 50
                anchors.right: parent.right
            }
        }
    }

    // 控制popup非模态框框外部的属性
    // 需要设置dim为true
    Overlay.modeless: Rectangle {
        anchors.fill: parent
        color: "green"
    }
}
