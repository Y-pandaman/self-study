import QtQuick 2.12
import QtQuick.Window 2.12
import "../common"

Window {
    visible: true
    width: 640
    height: 480

    ListView {
        delegate: spaceManDelegate
        section.delegate: sectionDelegate
        section.property: "nation"  // 分组的属性
        section.criteria: ViewSection.FullString  // 按nation分组
//        section.criteria: ViewSection.FirstCharacter  // 按nation首字母分组
        model: spaceMen

        anchors.fill: parent
        anchors.margins: 20

        clip: true  // 自动裁剪
    }

    Component {
        id: spaceManDelegate

        Item {
            id: spaceManWrapper
            width: ListView.view.width
            height: 20
            Text {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 8
                font.pixelSize: 12
                text: model.name
            }
        }
    }

    Component {
        id: sectionDelegate

        GreenBox {
            width: ListView.view.width
            height: 20
            text: section
        }
    }

    ListModel {
        id: spaceMen

        ListElement {
            name: "Abdul Mohmand"
            nation: "Afganistan"
        }
        ListElement {
            name: "Marcos Pontest"
            nation: "Brazil"
        }
        ListElement {
            name: "Alexandar Panayotox Alexandrov"
            nation: "Bulgaria"
        }
        ListElement {
            name: "Georgi Ivanov"
            nation: "Bulgaria"
        }
        ListElement {
            name: "Roberta Bondar"
            nation: "Canada"
        }
        ListElement {
            name: "Marc Garneau"
            nation: "Canada"
        }
        ListElement {
            name: "Chris Hadfield"
            nation: "Canada"
        }
        ListElement {
            name: "Guy Laliberte"
            nation: "Canada"
        }
        ListElement {
            name: "Steven MacLean"
            nation: "Canada"
        }
        ListElement {
            name: "Julie Payette"
            nation: "Canada"
        }ListElement {
            name: "Robert Thirsk"
            nation: "Canada"
        }
        ListElement {
            name: "Bjarni Tryggvason"
            nation: "Canada"
        }
        ListElement {
            name: "Dafydd Williams"
            nation: "Canada"
        }
    }
}
