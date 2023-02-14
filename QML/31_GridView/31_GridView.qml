import QtQuick 2.12
import QtQuick.Window 2.12
import "../common"

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    GridView {
        anchors.fill: parent
        anchors.margins: 20
        clip: true

        model: 100   // 数据量
        cellWidth: 45
        cellHeight: 45
        flow: GridView.FlowTopToBottom  // 方向  从上到下
        delegate: GreenBox {
            width: 40
            height: 40
            text: index
        }
    }
}
