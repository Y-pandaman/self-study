import QtQuick 2.12
import QtQuick.Window 2.12
import "create-component.js" as ImageCreator

Item {
    id: root
    width: 640
    height: 480

    //    Component.onCompleted: ImageCreator.createImageObject()

    function createItem() {
        Qt.createQmlObject(
                    "import QtQuick 2.0;
                     Rectangle {
                        x: 100;
                        y: 100;
                        width: 100;
                        height:100;
                        color: \"blue\"
                        }",
                    root,
                    "dynamicItem");
    }

    Component.onCompleted: createItem()
}
