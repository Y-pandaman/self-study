import QtQuick 2.12
import "../common"

Column {
    height: childrenRect.height
    id: root
    spacing: 2  // 间隔
    //    Repeater {
    ////        model: 10  // 使用数字
    //        model: ["Enterprise", "Columbia", "Challenger", "Discover", "Endeavour", "Atlantis"] // 使用数组
    //        delegate: BlueBox {
    ////            required property int index
    //            width: 160; height: 30
    ////            text: index
    //            text: modelData + '(' + index + ')'  // modelData用于获取数组内的内容
    //        }
    ////        onItemAdded: console.log("item" + index + "added")
    //    }

    Repeater {
        id: list
        model: ListModel {
            ListElement {
                name: "Mercury"
                surfaceColor: "red"
            }
            ListElement {
                name: "Venus"
                surfaceColor: "yellow"
            }
            ListElement {
                name: "Earth"
                surfaceColor: "blue"
            }
            ListElement {
                name: "Mars"
                surfaceColor: "orange"
            }
            ListElement {
                name: "Jupiter"
                surfaceColor: "#123456"
            }
            ListElement {
                name: "Saturn"
                surfaceColor: "lightyellow"
            }
            ListElement {
                name: "Uranus"
                surfaceColor: "lightBlue"
            }
            ListElement {
                name: "Neptune"
                surfaceColor: "lightGreen"
            }
        }

//        delegate: BlueBox {
        BlueBox {  // delegate 为默认属性，可不写
            id: blueBox
            color: "gray"
            width: 160; height: 30
            text: name
            rect_color: surfaceColor
            radius: 3
        }
    }
}
