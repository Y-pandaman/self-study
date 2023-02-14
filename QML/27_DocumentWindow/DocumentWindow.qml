import QtQuick 2.0
import QtQuick.Controls 2.12
import Qt.labs.platform 1.0 as Platform

ApplicationWindow {
    id: root
    width: 640; height: 480

    // 创建菜单
    menuBar: MenuBar {
        Menu {  // 菜单
            title: "&File"
            MenuItem {   // 子菜单
                text: "&New"
                icon.source: "images/new.png"
                onTriggered: root.newDocument()  // 点击
            }
            MenuItem {
                text: "&Open"
                icon.source: "images/open.png"
                onTriggered: root.openDocument()
            }
            MenuItem {
                text: "&Save"
                icon.source: "images/save.png"
                onTriggered: root.saveDocument()
            }
            MenuItem {
                text: "Save &As"
                icon.source: "images/save-as.png"
                onTriggered: root.saveAsDocument()
            }
        }
    }

    // 共享函数,新建窗口
    function createNewDocument() {
        var componet = Qt.createComponent("DocumentWindow.qml")
        var window = componet.createObject(/*root*/)
        return window
    }

    // 新建文档
    function newDocument() {
        var window = createNewDocument()
        window.show()
    }

    // 打开文档
    function openDocument() {
        openDialog.open()
    }

    // 调用自带的dialog
    property string fileName  // 文件名
    property bool isDirty: true   // 是否保存
    property bool tryingToClose: false  // 是否关闭
    Platform.FileDialog {
        id: openDialog
        title: "Open"
        onAccepted: {
            var window = root.createNewDocument()
            window.fileName = openDialog.file
            window.show()
        }
    }

    function saveAsDocument() {
        saveAsDialog.open()
    }

    function saveDocument() {
        if (fileName.length == 0) {
            root.saveAsDocument()
        }
        else {
            root.isDirty = false
            if (root.tryingToClose) {
                root.close()
            }
        }
    }

    Platform.FileDialog {
        id: saveAsDialog
        title: "Save As"
        onAccepted: {
            root.fileName = saveAsDialog.file
            saveDocument()
        }
        onRejected: {
            root.tryingToClose = false
        }
    }

    // 关闭事件
    onClosing: {
        if (root.isDirty) {
            closeWarningDialog.open()
            close.accepted = false
            console.log("onClosing")
        }
    }

    // 提示窗
    Platform.MessageDialog {
        id: closeWarningDialog
        title: "Close Document"
        text: "有更新没保存，是否需要保存？"
        buttons: Platform.MessageDialog.Yes | Platform.MessageDialog.No | Platform.MessageDialog.Cancel
        onYesClicked: {
            root.tryingToClose = true
            root.saveDocument()
        }
        onNoClicked: {
            root.isDirty = false
            root.close()
        }
        onRejected: {}
    }

    // 文件是否保存，添加*
    title: (fileName.length == 0 ? "Document" : fileName) + (isDirty ? "*" : "")
}
