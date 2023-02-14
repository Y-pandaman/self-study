import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.XmlListModel 2.12

// 参考链接: https://doc.qt.io/qt-5/qtdoc-demos-rssnews-example.html

Window {
    visible: true
    width: 640
    height: 480

    ListView {
        id: listView
        anchors.fill: parent
        model: imageModel
        delegate: imageDelegate
    }

    XmlListModel {
        id: imageModel
        source: "https://www.nasa.gov/rss/dyn/image_of_the_day.rss"
        query: "/rss/channel/item"
        XmlRole {
            name: "title"
            query : "title/string()"
        }
        XmlRole {
            name: "imageSource"
            query : "enclosure/@url/string()"
        }
    }

    Component {
        id: imageDelegate

        Rectangle {
            id: wrapper
            width: listView.width
            height: 220
            Column {
                Text {
                    text: title
                }
                Image {
                    source: imageSource
                    height: 200
                    width: listView.width
                    fillMode: Image.PreserveAspectCrop // 自适应图片
                }
            }
        }
    }
}
