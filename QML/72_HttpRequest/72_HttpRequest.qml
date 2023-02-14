import QtQuick 2.12

Rectangle {
    id: root
    visible: true
    width: 640
    height: 480

    Image {
        id: icon
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        clip: true
    }

    Text {
        id: label
        anchors.fill: parent
        color: "white"
        font.pixelSize: 18
    }

    function request() {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange =function () {
            if(xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED){
                print("HEADERS_RECEIVED")
            }
            else if (xhr.readyState === XMLHttpRequest.DONE) {
                print("DONE")
                var response = JSON.parse(xhr.responseText.toString())
                label.text = "code:" + response.code
                icon.source = response.imgurl
                print(xhr.responseText)
            }
        }
        xhr.open("GET", "https://api.ixiaowai.cn/gqapi/gqapi.php?reture=json")
        xhr.send()
    }

    MouseArea {
        anchors.fill: parent
        onClicked: request()
    }

    Component.onCompleted: request()
}
