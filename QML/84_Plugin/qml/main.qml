import QtQuick 2.12
import QtQuick.Window 2.12
import com.pandaman.cppmodel 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Background {
        id: backGround
    }

//    ListView {
//        id: view
//        anchors.fill: parent
//        model: CppModel{}
//        delegate: ListDelegate {
//            text: model.display
//            onClicked: {
//                view.currentIndex = model.index
//            }
//        }
//        highlight: ListHighlight{}
//    }

    ListView {
        id: view
        anchors.fill: parent
        model: CppModel{}
        delegate: ListDelegate {
            text: model.name + 'hsv(' + Number(model.hue).toFixed(2) + ',' + Number(model.saturation).toFixed(2) + ',' + Number(model.brightness).toFixed(2) + ')'
            color: model.name

            onClicked: {
                view.currentIndex = model.index
            }
        }
        highlight: ListHighlight{}
    }
}
