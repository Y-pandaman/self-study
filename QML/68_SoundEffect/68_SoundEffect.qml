import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 500
    height: 500

    SoundEffect {
        id: beep
        source: "../image/beep.wav"
        volume: 0.5
    }

    SoundEffect {
        id: swosh
        source: "../image/swosh.wav"
        loops: 2
        volume: 1
    }

    Rectangle {
        anchors.centerIn: parent
        id: rectangle
        width: 300
        height: width
        color: "red"
        state: "DEFAULT"

        states: [
            State {
                name: "DEFAULT"
                PropertyChanges {
                    target: rectangle
                    rotation: 0
                }
            },
            State {
                name: "REVERSE"
                PropertyChanges {
                    target: rectangle
                    rotation: 90
                }
            }
        ]

        transitions: [
            Transition {
                to: "DEFAULT"
                ParallelAnimation {
                    ScriptAction {
                        script: beep.play()
                    }
                    PropertyAnimation {
                        properties: "rotation"
                        duration: 200
                    }
                }
            },
            Transition {
                to: "REVERSE"
                ParallelAnimation {
                    ScriptAction {
                        script: swosh.play()
                    }
                    PropertyAnimation {
                        properties: "rotation"
                        duration: 200
                    }
                }
            }
        ]
    }

    Button {
        anchors.centerIn: parent
        text: "Flip!"
        onClicked: rectangle.state=rectangle.state==="DEFAULT"?"REVERSE":"DEFAULT"
    }
}
