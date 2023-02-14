import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("input")

//    Rectangle {
//        width: 300; height: 80
//        color: "linen"
//        TextInput {
//            id: input1
//            x: 8; y: 8
//            width: 96; height: 20
//            focus: true
//            text: "Text input 1"

//            KeyNavigation.tab: input2  // 切换焦点
//        }

//        TextInput {
//            id: input2
//            x: 8; y: 36
//            width: 96; height: 20
////            focus: true
//            text: "Text input 2"

//            KeyNavigation.tab: input1   // 切换焦点
//        }
//    }

    TextLineEditV1 {
        id: text1
        text: "Text input 1"
        input.font.pixelSize: 16
        height: input.font.pixelSize +10
        input.color: "white"
        focus: true
        KeyNavigation.tab: text2
    }

    TextLineEditV1 {
        id: text2
        text: "Text input 2"
        input.font.pixelSize: 16
        y: text1.y + text1.height +12
        height: input.font.pixelSize +10
        input.color: "white"
        KeyNavigation.tab: text1
    }
}
