import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    width: 400
    height: 200
    border.color: "black"
    anchors.centerIn: parent
    ListView {
        id: listView
        width: 180; height: 200
        header: Rectangle {  // 顶部
            width: listView.width
            height: 20
            color: "blue"
        }
        footer: Rectangle {  // 尾部
            width: listView.width
            height: 20
            color: "green"
        }

        //    model: 3  // 数字 或者 list类型[] model控制了所有的数据
        //    model: ['apple', 'banana', 'pear']
        model: ListModel {
            ListElement {
                name: "Bill Smith"
                number: "555 3264"
                myValue: 111  // MyValue为自定义的变量
            }
            ListElement {
                name: "John Brown"
                number: "555 8426"
                myValue: 222
            }
            ListElement {
                name: "Sam Wise"
                number: "555 0473"
                myValue: 333
            }
        }
        spacing: 20  // 项之间的间隔
        highlight: Rectangle {
            color: "lightsteelblue"
            radius: 5
        }
        //    delegate: Button {  // delegate控制了每一项数据是如何绘制的
        ////        text: index
        ////        text: modelData
        //        text: name + "  " + number + " " + myValue  // ListModel直接访问变量
        //    }

        //    flickableDirection: Flickable.AutoFlickDirection  // 纵向拖拽回弹效果
        flickableDirection: Flickable.HorizontalFlick  // 横向拖拽回弹效果

        delegate: Rectangle {
            color: "transparent"
            width: 150
            height: 20
            Text {
                text: name+ " " + number + " " + myValue
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    currentIndex = index
                }
            }
        }
    }
}
