import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("layout")

    GreenSquare {
//        BlueSquare {
//            text: "(1)"
//            anchors.fill: parent
//            anchors.margins: 10
//        }

//        BlueSquare {
//            text: "(2)"
//            anchors.left: parent.left
//            y: 10
//            anchors.margins: 10
//        }

//        BlueSquare {
//            text: "(3)"
//            anchors.left: parent.right
//        }

//        BlueSquare {
//            id: blue1
//            text: "(4-1)"
//            anchors.top: parent.top
//            anchors.margins: 10
//            anchors.horizontalCenter: parent.horizontalCenter
//            height: 25
//        }

//        BlueSquare {
//            text: "(4-2)"
//            anchors.margins: 10
//            anchors.top: blue1.bottom
//            anchors.horizontalCenter: parent.horizontalCenter
//            width: 75; height: 25
//        }

//        BlueSquare {
//            text: "(5)"
//            anchors.centerIn: parent
//            anchors.margins: 10
//        }

        BlueSquare {
            text: "(6)"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: -12  // 偏移
        }
    }
}
