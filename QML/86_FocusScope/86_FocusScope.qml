import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    Rectangle {
    FocusScope {
        id: rect1
        width: 300
        height: 200
        focus: true
        Text {
            id: txt1
            focus: true
            text: qsTr("focus " + txt1.focus + " activeFocus: " + txt1.activeFocus)  // 后获取先得true
            Component.onCompleted: {
                console.log("text1 complete")
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                txt1.focus = true  // 无用
                txt1.forceActiveFocus()  // 强制获取焦点
            }
        }
}

//    Rectangle {
    FocusScope {
        id: rect2
        width: 300
        height: 200
        y: 100
        Text {
            id: txt2
            focus: true
            text: qsTr("focus " + txt2.focus + " activeFocus: " + txt2.activeFocus)
            Component.onCompleted: {
                console.log("text2 complete")
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                txt2.focus = true  // 无用
                txt2.forceActiveFocus()
            }
        }
    }

    // focus
//    Button {
//        id: btn
//        width: 100
//        height: 50
//        focus: false
////        focusPolicy: Qt.NoFocus  // 按键焦点失效
//        background: Rectangle {
//            anchors.fill: parent
//            border.color: btn.focus ? "blue" : "red"
//        }
//        onFocusChanged: {
//            console.log("focus: ", focus)
//        }
//        onFocusReasonChanged: {
//            console.log("focusReason: ", focusReason)
//        }
//        Component.onCompleted: {
//            console.log("focusPolicy: ", focusPolicy)
//        }
//    }
}
