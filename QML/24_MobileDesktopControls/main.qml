import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform 1.0 as Platform
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: root
    visible: true
    width: 320
    height: 480
    title: qsTr("Hello World")
    background: Rectangle {
        color: "gray"
    }

    Image {
        id: image
        source:"qrc:/images/bg.jpg"
        anchors.fill: parent
//        fillMode: Image.PreserveAspectFit  // 不改变图片比例
        asynchronous: true  // 打开异步，提高加载速度
    }

    // PC端风格
//    header: ToolBar {
//        Flow {
//            anchors.fill: parent
//            ToolButton {
//                text: "打开"
//                icon.source: "qrc:/images/folder.png"
//                onClicked: fileOpenDialog.open()
//            }
//        }
//    }

    // 移动端风格
    header: ToolBar {
        Material.background: Material.Oriange
        ToolButton {
            icon.source: "qrc:/images/folder.png"
            onClicked: drawer.open()
        }
        Label {
            anchors.centerIn: parent
            text: "Image Viewer"
            font.pixelSize: 20
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

    // 侧滑菜单
    Drawer {
        id: drawer
        width: root.width * 2 / 3
        height: root.height

        ListView {
            anchors.fill: parent   // 防止view太小，显示不全
            model: ListModel {   // 列表
                ListElement {    // 列表项
                    text: "Open"
                    triggered: function() {
                        fileOpenDialog.open()
                    }
                }
                ListElement {
                    text: "About"
                    triggered: function() {
                        aboutDialog.open()
                    }
                }
            }

            // delegate使能显示出列表内容
            delegate: ItemDelegate {
                text: model.text
                highlighted: ListView.isCurrentItem
                onClicked: {
                    drawer.close()
                    model.triggered()
                }
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
