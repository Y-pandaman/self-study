import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    visible: true
    width: 640
    height: 480

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#112233"
        }
        GradientStop {
            position: 1.0
            color: "#445566"
        }
    }

    // 添加动作
    ListModel {
        id: actionModel

        ListElement {
            name: "张三"
            hello: function(value){
                console.log(value + "张三在此")
            }
        }

        ListElement {
            name: "李四"
            hello: function(value){
                console.log(value + "李四在此")
            }
        }

        ListElement {
            name: "王五"
            hello: function(value){
                console.log(value + "王五在此")
            }
        }
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 10

        focus: true
        spacing: 5
        clip: true
        model: actionModel

        delegate: Rectangle {
            id: delegate

            width: ListView.view.width
            height: 30
            color: "lightblue"

            Text {
                anchors.centerIn: parent
                font.pixelSize: 10
                text: model.name
            }

            MouseArea {
                anchors.fill: parent
                onClicked: model.hello(model.index)
            }
        }
    }
}
