import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    width: 300
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

    // View
    ListView {
        id: listView
        anchors.fill: parent
        delegate: detailDelegate
        model: planets
    }

    // Model 数据源
    ListModel {
        id: planets
        ListElement {
            name: "地球"
            imageSource: "../image/planet/地球.png"
            facts: "地球是太阳系的第三行星"
        }
        ListElement {
            name: "火星"
            imageSource: "../image/planet/火星.png"
            facts: "火星是太阳系的第四行星"
        }
        ListElement {
            name: "土星"
            imageSource: "../image/planet/土星.png"
            facts: "土星是太阳系的第六行星"
        }
        ListElement {
            name: "木星"
            imageSource: "../image/planet/木星.png"
            facts: "木星是太阳系的第五行星"
        }
        ListElement {
            name: "海王星"
            imageSource: "../image/planet/海王星.png"
            facts: "海王星是太阳系的第八行星"
        }
    }

    // delegate
    Component {
        id: detailDelegate
        Item {
            id: wrapper
            width: listView.width
            height: 30

            // 显示左边的文字
            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 30

                color: "#333333"
                border.color: Qt.lighter(color, 1.2)
                Text {
                    id: text
                    color: "white"
                    text: model.name
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: parent.height - 4
                }
            }

            // 显示右边的图标
            Rectangle {
                id: image
                width: 26
                height: 26
                anchors.topMargin: 2
                anchors.rightMargin: 2
                anchors.right: parent.right
                anchors.top: parent.top
                Image {
                    source: model.imageSource
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: parent.state = "expanded"
            }

            // 返回按钮
            Rectangle {
                id: closeButton
                width: 26
                height: 26
                anchors.topMargin: 2
                anchors.rightMargin: 2
                anchors.right: parent.right
                anchors.top: parent.top
                color: "lightblue"
                border.color: Qt.lighter(color, 1.1)
                opacity: 0
                Text {
                    anchors.centerIn: parent
                    text: '\u25C0'  // 图标
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        wrapper.state = ""
                    }
                }
            }

            // 文本显示区域
            Item {
                id: factsView
                // 布局
                anchors.top: image.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                opacity: 0

                Rectangle {
                    anchors.fill: parent
                    color: "black"
                    Text {
                        anchors.margins: 5
                        anchors.fill: parent
                        font.pixelSize: 20
                        text: model.facts
                        wrapMode: Text.WordWrap  // 自动换行
                        color: "white"
                    }
                }
            }

            states: [
                State {
                    name: "expanded"
                    PropertyChanges {
                        target: wrapper
                        height: listView.height
                    }
                    PropertyChanges {
                        target: image
                        height: listView.width
                        width: listView.width
                        anchors.topMargin: 30
                        anchors.rightMargin: 0
                    }
                    PropertyChanges {
                        target: wrapper.ListView.view
                        contentY: wrapper.y  // 图像移到顶层
                        interactive: false  // 不能滑动
                    }
                    PropertyChanges {
                        target: closeButton
                        opacity: 1
                    }
                    PropertyChanges {
                        target: factsView
                        opacity: 1
                    }
                }
            ]

            // 显示动画
            transitions: [
                Transition {
                    NumberAnimation {
                        duration: 200
                        // 多个属性都有动画
                        properties: "height, width, anchors.rightMargin, anchors.topMargin, opacity"
                    }
                }
            ]
        }
    }
}
