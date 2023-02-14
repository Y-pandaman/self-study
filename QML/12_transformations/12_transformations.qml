import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Transformations")

    // 恢复默认状态
    MouseArea {
        anchors.fill: parent
        onClicked: {
            qq1.x = 50
            qq2.rotation = 0
            qq3.rotation = 0
            qq3.scale = 1
        }
    }

    // 平移
    ClickableImage {
        id: qq1
        x: 50; y: 50
        source: "../image/3.png"

        onClicked: {
            x += 10
        }
    }

    // 旋转
    ClickableImage {
        id: qq2
        x: 200; y: 50
        source: "../image/3.png"

        onClicked: {
            rotation += 10
        }
    }

    // 旋转 + 缩放
    ClickableImage {
        id: qq3
        x: 350; y: 50
        source: "../image/3.png"

        onClicked: {
            rotation += 10
            scale += 0.1
        }
    }
}
