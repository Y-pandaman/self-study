import QtQuick 2.12
import QtQuick.Window 2.12

//DarkSquare {
//    id: root
//    width: 240; height: 240

//    // 列，竖着排
//    Column {
//        id: column
//        anchors.centerIn: parent   // 居中
//        spacing: 10

//        RedSquare {}
//        GreenSquare {
//            width: 96
//        }
//        BlueSquare {}
//    }

//    // 行，横着排
//    Row {
//        id: row
//        anchors.centerIn: parent   // 居中
//        spacing: 10

//        RedSquare {}
//        GreenSquare {
//            width: 96
//        }
//        BlueSquare {}
//    }
//}

//    网格排列
//DarkSquare {
//    id: root
//    width: 240; height: 240

//    Grid {
//        id: grid1
//        anchors.centerIn: parent  // 居中
//        spacing: 10
//        rows: 2          // 2行
//        columns: 3   //3列

//        RedSquare {}
//        GreenSquare {}
//        BlueSquare {}
//        RedSquare {}
//        GreenSquare {}
//        BlueSquare {}
//    }
//}


// 流排列
//DarkSquare {
//    id: root
//    width: 240; height: 240

//    Flow {
//        id: flow
//        anchors.fill: parent
//        anchors.margins: 20 // 边框距离
//        spacing: 10

//        RedSquare {}
//        GreenSquare {}
//        BlueSquare {}
//        RedSquare {}
//        GreenSquare {}
//        BlueSquare {}
//    }
//}


// grid
DarkSquare {
    id: root
    width: 300; height: 300

    Grid {
        id: grid2
        anchors.centerIn: parent
        anchors.margins: 8 // 边框距离
        spacing: 4
        property variant colorArray: ["#00bde3", "#67c111", "#ea7025"]

        columns: 5  // columns默认为4,下面的model只能为16
        Repeater {   // 循环
            model: grid2.columns * grid2.columns
//            RedSquare{}
            Rectangle {
                id: rect
//                required property int index   // 不可用
                property int colorIndex: Math.floor(Math.random() * 3)  // 随机值 0,1,2
                color: grid2.colorArray[colorIndex]
                width: 56; height: 56

                Text {
                    anchors.centerIn: parent
                    text: "Cell " + rect.Positioner.index
//                    text: "Cell " + parent.index   // 不可用
                    color: "white"
                }
            }
        }
    }
}
