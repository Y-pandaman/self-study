import QtQuick 2.12

import "http://localhost:8080" 1.0 as Remote
Rectangle {
    width: 320
    height: 320
    color: '#ff0000'
    Remote.Button {
        anchors.centerIn: parent
        text: 'Click Me'
        onClicked: Qt.quit()
    }
}
