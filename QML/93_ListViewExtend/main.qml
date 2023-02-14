import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml.Models 2.12
import QtQuick.XmlListModel 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    XmlListModel {
          id: xmlModel
          source: "/myXML.xml"
          query: "/rss/channel/item"

          XmlRole { name: "title"; query: "title/string()" }
          XmlRole { name: "pubDate"; query: "pubDate/string()" }
          XmlRole { name: "value"; query: "value/number()" }
      }

    ListView {
          width: 180; height: 300
          model: xmlModel
          delegate: Text { text: title + ": " + pubDate  + " " + value}
      }






//    Button {
//        id: btn
//        width: 200
//        height: 480
//    }

//    ObjectModel {
//        id: myModel
//        Rectangle {
//            width: 440
//            height: 480
//            color: "red"
//        }
//        Rectangle {
//            width: 440
//            height: 480
//            color: "yellow"
//        }
//        Rectangle {
//            width: 440
//            height: 480
//            color: "blue"
//        }
//    }

//    ListView {
//        anchors.left: btn.right
//        anchors.right: parent.right
//        height: 480
//        model: myModel
//        orientation: ListView.Horizontal  // 横向
//        snapMode: ListView.SnapOneItem  // 每次滑动一个item
//        clip: true  // 裁剪多余的部分，不会覆盖其他界面
//    }





//    SwipeView {  // 只能全屏填充滑动
//          id: view

//          currentIndex: 1
//          anchors.fill: parent

//          Item {
//              id: firstPage
//              Rectangle {
//                anchors.fill: parent
//                color: "blue"
//              }
//          }
//          Item {
//              id: secondPage
//              Rectangle {
//                anchors.fill: parent
//                color: "green"
//              }
//          }
//          Item {
//              id: thirdPage
//              Rectangle {
//                anchors.fill: parent
//                color: "red"
//              }
//          }
//      }

//      PageIndicator {
//          id: indicator

//          count: view.count
//          currentIndex: view.currentIndex

//          anchors.bottom: view.bottom
//          anchors.horizontalCenter: parent.horizontalCenter
//      }
}
