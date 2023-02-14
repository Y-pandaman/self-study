import QtQuick 2.12

Rectangle {
    width: 640
    height: 480
    color: "#333"

    GenieEffect {
        source: Image {
            source: "../image/ball.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                parent.minimized = !parent.minimized
//                console.log(genieEffect.minimized)
            }
        }
    }
}
