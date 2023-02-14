import QtQuick 2.12
import QtQuick.Window 2.12

Rectangle {
    visible: true
    width: 640
    height: 480

    GridView {
        id: view
        anchors.fill: parent
        cellHeight: width/4
        cellWidth: cellHeight
        delegate: Rectangle {
            property var modelData
            width: view.cellWidth
            height: view.cellHeight
            color: modelData.value
        }
    }

    function request() {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState ===XMLHttpRequest.DONE) {
                if (request.status && request.status === 200){
                    var response = JSON.parse(xhr.responseText.toString())
                    view.model = response.colors
                }
                else {
                    console.log("HTTP:", request.status, request.statusText)
                }
            }
        }
        xhr.open("GET", "colors.json")
        xhr.send()
    }

    Component.onCompleted: request()
}
