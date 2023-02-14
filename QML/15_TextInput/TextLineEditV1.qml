import QtQuick 2.0

FocusScope{   // 焦点作用域
    width: 300; height: 30
    Rectangle {
        anchors.fill: parent
        color: "lightsteelblue"
        border.color: "gray"
    }

    property alias text: input.text
    property alias input: input

//    TextInput {
//        id: input
//        anchors.fill: parent  // 填充进上面定义的Rectangle
//        anchors.margins: 2
//        focus: true
//    }

    // TextEdit
    TextEdit {
        id: input
        anchors.fill: parent  // 填充进上面定义的Rectangle
        anchors.margins: 2
        focus: true
        wrapMode: Text.WordWrap   // 自动换行
    }
}

