import QtQuick 2.0

FocusScope {
    id: root

    property alias title: title.text
    property alias rect: rect
    property alias input: textInput

    Text {
        id: title
        font. pixelSize: 20
        text: qsTr("text")
    }

    Rectangle {
        id: rect
        anchors.verticalCenter: title.verticalCenter
        anchors.left: title.right
        anchors.leftMargin: 5
        width: 200
        height: 30
        border.color: "black"
        border.width: 2
        color: "lightgray"
        TextInput{
            id: textInput
            anchors.fill: parent
            focus: true
            font.pixelSize: 20
            text: ""
            verticalAlignment: Qt.AlignVCenter
        }
    }
}
