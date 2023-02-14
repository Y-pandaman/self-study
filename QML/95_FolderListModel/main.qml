import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.folderlistmodel 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    ListView {
          width: 200; height: 400

          FolderListModel {
              id: folderModel
              folder: "file:///G:\\BDCA\\workspace\\gitee\\self-study\\QML\\95_FolderListModel"
//              showDirs: false   // 是否显示文件夹
              showDirsFirst: true  // 先显示文件夹
              nameFilters: ["*"]
              Component.onCompleted: {
                console.log(folder)
              }
          }

          model: folderModel
          delegate: Text {
              id: txt
              text: filePath + "/" + fileName + ":" + fileSize
              font.pixelSize: 20
          }
      }

}
