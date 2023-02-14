import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    id: root
    state: "analog"
    visible: true
    width: 640
    height: 480

    property int speed: 0
    SequentialAnimation {
        running: true
        loops: Animation.Infinite
        NumberAnimation {
            target: root
            properties: "speed"
            to: 145
            easing.type:Easing.InOutQuad
            duration: 4000
        }
        NumberAnimation {
            target: root
            properties: "speed"
            to: 10
            easing.type:Easing.InOutQuad
            duration: 2000
        }
    }
    Loader {
        id: loader
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: analogButton.top
        onLoaded: {
            binder.target = loader.item
        }
    }

    Binding {
        id: binder
        property: "speed"
        value: root.speed
    }

    Rectangle {
        id: analogButton
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: parent.width/2
        height: 100
        color: "gray"
        Text {
            anchors.centerIn: parent
            text: "Analog"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: root.state = "analog"
        }
    }

    Rectangle {
        id: digitalButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: parent.width/2
        height: 100
        color: "lightgray"
        Text {
            anchors.centerIn: parent
            text: "Digital"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: root.state = "digital"
        }
    }

    states: [
        State{
            name: "analog"
            PropertyChanges {
                target: analogButton
                color: "green"
            }
            PropertyChanges {
                target: loader
                source: "Analog.qml"
            }
        },
        State{
            name: "digital"
            PropertyChanges {
                target: digitalButton
                color: "green"
            }
            PropertyChanges {
                target: loader
                source: "Digital.qml"
            }
        }
    ]
}
