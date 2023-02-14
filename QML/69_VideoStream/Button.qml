import QtQuick 2.0
import QtQuick.Controls 2.12

Button {
    id: shotButton
    width: 200
    height: 75
    text: "Take Photo"
    onClicked: {
        camera.imageCapture.capture();
    }
}
