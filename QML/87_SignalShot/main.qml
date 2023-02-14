import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    color: "white"

    Component {
        id: com
        Button {
            id: btn
            width: 100
            height: 50
            background: Rectangle{
                anchors.fill: parent
                border.color: btn.activeFocus ? "red" : "black"

            }
//            signal btnSig(int value)
//            onClicked: {
//                btnSig(10)
//            }

            signal leftBtnPressed()
            Keys.onLeftPressed: {
                leftBtnPressed()
            }
        }
    }

    MyComponent {
        com1: com
        com2: com
    }
}
