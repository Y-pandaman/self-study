import QtQuick 2.12
import QtQuick.Window 2.12
import MyModel 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        width: 200
        height: 300
        model: MyListModel
        delegate: Text {
            id: txt
            text: name + " " + value
        }
    }
}
