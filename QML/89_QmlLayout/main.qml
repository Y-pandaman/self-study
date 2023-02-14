import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

//    // flow 流式布局
//    Rectangle {
//        width: 400
//        height: 300
//        border.color: "red"

//        Flow {
//                  anchors.fill: parent
//                  anchors.margins: 4
//                  spacing: 10
//                  flow: Flow.TopToBottom

//                  Text { text: "Text"; font.pixelSize: 40 }
//                  Text { text: "items"; font.pixelSize: 40 }
//                  Text { text: "flowing"; font.pixelSize: 40 }
//                  Text { text: "inside"; font.pixelSize: 40 }
//                  Text { text: "a"; font.pixelSize: 40 }
//                  Text { text: "Flow"; font.pixelSize: 40 }
//                  Text { text: "item"; font.pixelSize: 40 }
//              }
//    }


////    Column {
//    Row {
//        id: col
//        spacing: 20
//        leftPadding: 30
//        topPadding: 30
////        layoutDirection: Qt.RightToLeft

//        Component.onCompleted: {
//            console.log(effectiveLayoutDirection)
//        }

//        Repeater {
//            id: rep
//            model: ListModel {}
//            Button {
//                width: 100
//                height: 50
//                text: index + " " + name

//            }
//        }
//        move: Transition {
//              NumberAnimation { properties: "x,y"; easing.type: Easing.OutBounce }
//          }
//        add: Transition {
//              NumberAnimation { properties: "x,y"; easing.type: Easing.OutBounce }
//          }
//        populate: Transition {
//              NumberAnimation { properties: "x,y"; from: 200; duration: 100; easing.type: Easing.OutBounce }
//          }
//    }

//    Button {
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        anchors.bottomMargin: 30
//        onClicked: {
//            rep.model.insert(0, {"name": rep.model.count})
//        }
//    }

//    Grid {
//        x: 400
////          columns: 3 // 默认为4列
//        rows: 3
//          spacing: 2
//          Rectangle { color: "red"; width: 50; height: 50 }
//          Rectangle { color: "green"; width: 20; height: 50 }
//          Rectangle { color: "blue"; width: 50; height: 20 }
//          Rectangle { color: "cyan"; width: 50; height: 50 }
//          Rectangle { color: "magenta"; width: 10; height: 10 }
//      }

    Rectangle {
        id: maskRect
        x: 200
        y: 100
        width: grid.width
        height: grid.height
        radius:10
        border.color: "black"
    }

    Rectangle {
        width: grid.width + 4
        height: grid.height + 4
       radius: 10
       border.width: 3
       OpacityMask {
            source: grid
            maskSource: maskRect
//            anchors.fill: maskRect
            anchors.fill: parent
            anchors.margins: 2
        }
    }



    Grid {
        id: grid
        width: 15
        height: 200
        columns: 3
        x: 300
        y: 100

        Repeater {
            model: grid.width / 5 * grid.height / 5
            Rectangle {
                width: 5
                height: 5
                color: index % 2 ?  "black" : "white"
            }
        }
    }
}
