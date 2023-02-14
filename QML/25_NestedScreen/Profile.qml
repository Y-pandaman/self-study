import QtQuick 2.0
import QtQuick.Controls 2.12

Page {
    title: "Profile"

    Column {
        spacing: 10
        anchors.centerIn: parent  // 完全居中
        Button {
            text: "Edit"
            onClicked: {
                stackView.push("EditProfile.qml")
            }
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter  // 水平居中
            text: "Profile Screen"
        }
    }

}

