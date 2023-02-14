import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    width: 640
    height: 480

    // 渐变色背景
    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#123456"
        }
        GradientStop {
            position: 1.0
            color: "#654321"
        }
    }

    // 按钮
    Rectangle {
        property int count: count = theModel.count - 1
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        height: 40
        color: "lightblue"
        border.color: Qt.lighter(color, 1.2)

        Text {
            id: text
            text: "Add Item"
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                theModel.append({"num": ++parent.count})
            }
        }
    }

    // Model
    ListModel {
        id: theModel
        ListElement {num: 0}
        ListElement {num: 1}
        ListElement {num: 2}
        ListElement {num: 3}
    }

    // View
    GridView {
        anchors.fill: parent
        anchors.margins: 20
        anchors.bottomMargin: 80
        clip: true
        cellHeight: 45
        cellWidth: 45
        model: theModel
        delegate: numberDelegate
    }

    // delegate
    Component {
        id: numberDelegate

        Rectangle {
            id: rect
            width: 40
            height: 40
            color: "yellow"

//            property int index
//            property int num

            Text {
                id: text
                anchors.centerIn: parent
                font.pixelSize: 15
                text: model.num  // 每个delegate都有自己的模型属性和相应的模型数据
            }

            GridView.onAdd: addAnimation.start()
            GridView.onRemove: removeAnimation.start()

            NumberAnimation {
                id: addAnimation
                target: rect
                property: "scale"
                from: 0
                to: 1
                duration: 250
                easing.type: Easing.InOutCirc
            }

            // 消失动画
            SequentialAnimation {
                id: removeAnimation
                PropertyAction {
                    target: rect
                    property: "GridView.delayRemove"
                    value: true
                }

                NumberAnimation {

                    target: rect
                    property: "scale"
                    to: 0
                    duration: 250
                    easing.type: Easing.InOutCirc
                }

                PropertyAction {
                    target: rect
                    properties: "GridView.delayRemove"
                    value: false
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    theModel.remove(index)
                }
            }
        }
    }
}
