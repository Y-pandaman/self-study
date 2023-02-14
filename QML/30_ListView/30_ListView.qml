import QtQuick 2.12
import QtQuick.Window 2.12
import "../common"

Window {
    width: 80
    height: 300
    visible: true

    ListView {
        id: listView
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10
        clip: true  // true表示看不见list创建和销毁的过程,默认是false
        model: 100  //100个list
        cacheBuffer: 80   // 缓冲区大小
//        orientation: ListView.Horizontal  // 横向列表，使用时需修改width,height
//        layoutDirection: "RightToLeft"   // 从右向左，横向列表适用
        highlight: highlightComponent  // 高亮显示
        focus: true

        delegate: Item {
            id: wrapper
            width: listView.width
            height: 40
            Text {
                anchors.centerIn: parent
                text: index
            }

            // 打印信息
            Component.onCompleted: {
                console.log(index + " added")
            }
            Component.onDestruction: {
                console.log(index + " destroyed")
            }
        }
    }

    Component {
        id: highlightComponent

        GreenBox {
            id: greenBox
            width: ListView.width

            // 添加显示动画
            //  透明度先变成0，再恢复
            y:listView.currentItem.y
            Behavior on y {
                SequentialAnimation {
                    PropertyAnimation {
                        target: greenBox
                        property: "opacity"
                        to: 0
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 200
                    }
                    PropertyAnimation {
                        target: greenBox
                        property: "opacity"
                        to: 1
                        duration: 200
                    }
                }
            }
        }
    }
}
