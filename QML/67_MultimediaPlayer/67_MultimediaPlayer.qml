import QtQuick 2.12
import QtMultimedia 5.12
import QtQuick.Controls 2.12

// -----------------------------------
// -----------------------------------
Rectangle {
    id: root
    width: 640
    height: 480

    MediaPlayer {
        id: player
        source: "../image/2446.mp4"
        volume: volumeSlider.value
    }

    VideoOutput {
        anchors.fill: parent
        source: player
    }

    Rectangle {
        color: "black"
        width: 40
        height: 220
        anchors.top: root.top
        anchors.right: root.right
        Column {
            Text {
                color: "white"
                text: qsTr("音量")
            }
            Slider {
                id: volumeSlider
                orientation: Qt.Vertical
                value: 0.5
                anchors.margins: 20
            }
        }
    }

    Row {
        height: 50
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        spacing: 20
        Button {
            width: 50
            anchors.verticalCenter: parent.verticalCenter
            text: player.playbackState === MediaPlayer.PlayingState ? "Pause" : "Play"
            onClicked: {
                switch(player.playbackState) {
                case MediaPlayer.PlayingState:
                    player.pause()
                    break
                case MediaPlayer.PausedState:
                    player.play()
                    break
                case MediaPlayer.StoppedState:
                    player.play()
                    break
                }
            }
        }
        Slider {
            id: progressSlider
            width: parent.width - 80
            anchors.verticalCenter: parent.verticalCenter
            value: player.duration>0?player.position/player.duration:0

            background: Rectangle {
                implicitHeight: 8
                radius: 3
                color: "lightgreen"

                Rectangle {
                    width: progressSlider.value * parent.width
                    height: parent.height
                    color: "blue"
                    radius: 3
                }
            }

            onMoved: function() {
                console.log(player.position)
                player.position = player.duration * progressSlider.value
            }
        }
    }

    Component.onCompleted: {
        player.play()
    }

    Connections {
        target: player
        onMediaObjectChanged: {
            if (player.mediaObject)
                player.mediaObject.notifyInterval = 50;
        }
    }
}

// ------------------------------------------------------
// -----------------------------------------------------------

//Item {
//    width: 1024
//    height: 600
//    MediaPlayer {
//        id: player
//        source: "../image/2446.mp4"
//    }
//    VideoOutput {
//        anchors.fill: parent
//        source: player
//    }
//    Component.onCompleted: {
//        player.play();
//    }

//    Rectangle {
//        id: progressBar
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.bottom: parent.bottom
//        anchors.margins: 100
//        height: 30
//        color: "lightGray"
//        Rectangle {
//            anchors.left: parent.left
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
//            width: player.duration>0?parent.width*player.position/player.duration:0
//            color: "darkGray"
//        }
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                if (player.seekable)
//                    player.position = player.duration * mouse.x/width;
//            }
//        }
//    }
//}
