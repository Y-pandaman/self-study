import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.0 as Platform

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    background: Rectangle {
        color: "gray"
    }

    Image {
        id: image
        source:"qrc:/images/bg.jpg"
        anchors.fill: parent
//        fillMode: Image.PreserveAspectFit  // 不改变比例
        asynchronous: true  // 打开异步，提高加载速度
    }

    header: ToolBar {
        Flow {
            anchors.fill: parent
            ToolButton {
                text: "打开"
                icon.source: "qrc:/images/folder.png"
                onClicked: fileOpenDialog.open()
            }
        }
    }

    Platform.FileDialog {
        id: fileOpenDialog
        title: "选择图片"
        nameFilters: [
            "Image files(*.png, *.jpg)",
            "all files(*.*)"
        ]
        onAccepted: {
            image.source = fileOpenDialog.file
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"   // &表示可以使用快捷键
            MenuItem {   // 子菜单
                text: "&Open"
                icon.source: "qrc:/images/folder.png"
                onTriggered: fileOpenDialog.open()
            }
        }
        Menu {
            title: "&Help"   // &表示可以使用快捷键
            MenuItem {   // 子菜单
                text: "&About"
                onTriggered: aboutDialog.open()
            }
        }
    }

    Dialog {
        id: aboutDialog
        width: 300; height: 150
        anchors.centerIn: parent
        title: "About"
        Label {
            anchors.fill: parent
            text: "there is about..."
            horizontalAlignment: Text.AlignHCenter
        }
        standardButtons: Platform.StandardButton.Ok
    }

}
