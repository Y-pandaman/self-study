import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window
    visible: true
    width: 320
    height: 480
    title: qsTr("Stack")

    header: ToolBar {
        ToolButton {
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"   //  \u25C0表示三角符号
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                }
                else {
                    drawer.open()
                }
            }
        }
        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: "Profile"
                width: parent.width
                onClicked: {
                    stackView.push("Profile.qml")  // 跳转方式1
                    drawer.close()
                }
            }

            ItemDelegate {
                text: "about"
                width: parent.width
                onClicked: {
                    stackView.push(aboutPage)   // 跳转方式2
                    drawer.close()
                }
            }
        }
    }

    StackView {  // 堆栈视图
        id: stackView
        anchors.fill: parent

        initialItem: Home {}  // 初始界面
    }

    Component {
        id: aboutPage
        About{}
    }
}
