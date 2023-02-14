import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.platform 1.0
import "./common" as Com

Window {
    id: root
    visible: true
    width: 700
    height: 600

    Com.MyTextEdit{
        id: remote_ip
        y: 10
        input.text: "192.168.1.253"
        title: "远端 IP :"
    }

    Com.MyTextEdit{
        id: remote_port
        y: 50
        input.text: "1030"
        title: "远端端口:"
    }

    Com.MyTextEdit{
        id: local_port
        y: 90
        input.text: "8888"
        title: "本地端口:"
    }

    Com.MyTextEdit {
        id: file_name
        y: 130
        rect.width: 170
        input.text: "sdfsd"
        title: "保存文件名："
    }

    Com.MyButton {
        id: file_btn
        label.text: "打开目录"
        label.font.pixelSize: 20
        y: 160
        x: 20
        onClicked: {
            canInit.fileName = file_name.input.text
            folderDialog.open()
        }
    }

    Rectangle {
        x: 0
        y: 230
        width: parent.width
        height: 350

        Com.MyTextArea {
            id: text_area
            textSize: 20
            anchors.fill: parent
            anchors.centerIn: parent
            textArea.text:  ""
        }
    }


    Com.MyButton{
        id: receive_btn
        label.text: "开始接收"
        label.font.pixelSize: 20
        x: 150
        y: 160
        onClicked: {
            if(receive_btn.label.text === "开始接收"){
                receive_btn.label.text = "停止接收"
                canInit.setFlag(true)
                canInit.receiveData(remote_ip.input.text, remote_port.input.text, local_port.input.text)
                timer.start()
            }
            else {
                receive_btn.label.text = "开始接收"
                canInit.setFlag(false)
                timer.stop()
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "选择文件"
        folder: StandardPaths.standardLocations(StandardPaths.destroy())[0]
        nameFilters: ["csv文件", "*.csv"]
        onAccepted: {
            canInit.createFile(fileDialog.fileUrl)
        }
    }

    FolderDialog {
        id: folderDialog
        folder: StandardPaths.standardLocations(StandardPaths.destroy())[0]
        onAccepted: {
            canInit.createFile(folderDialog.currentFolder.toString())
        }
    }

    Connections {
        target: canInit
        function onSendData() {
            text_area.textArea.text += canInit.dataStr.toString()
        }
    }


    Timer {
        id: timer
        interval: 1
        running: true
        repeat: true
//        onTriggered: text_area.textArea.text += canInit.dataStr.toString()
    }

}
