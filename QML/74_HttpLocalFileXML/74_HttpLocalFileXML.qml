import QtQuick 2.12
import QtQuick.XmlListModel 2.12

Rectangle {
    visible: true
    width: 640
    height: 480

    GridView {
        id: gridView
        anchors.fill: parent
        cellWidth: width / 4
        cellHeight: cellWidth

        model: xmlModel
        delegate: Rectangle {
            id: delegate
            property var model
            width: gridView.cellHeight
            height: width
            color: model.value
            Text {
                id: text
                anchors.centerIn: parent
                text: delegate.model.name
            }
        }
    }

    XmlListModel {
        id: xmlModel
        source: "colors.xml"
        query: "/colors/color"
        XmlRole {
            name: "name"
            query: "name"
        }
        XmlRole {
            name: "value"
            query: "value"
        }
    }
}
