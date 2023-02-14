import QtQuick 2.0

Item {
    // 开放可改变的属性
    id: root
    property  alias text: label.text  // 设置别名，用于被调用时改变button的text属性
    signal clicked

    Rectangle {
        id: button
        x: 12; y: 12
        width: 116; height: 26
        color: "lightsteelblue"
        border.color: "slategrey"
        Text {
            id: label
            anchors.centerIn: parent
            text: "Start"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.clicked()
            }
        }
    }
}


