import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.settings 1.0
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Settings {
        id: settings1
        fileName: "G:\\BDCA\\workspace\\gitee\\self-study\\QML\\96_Settings\\setttings.ini"
        property int iData: 0
        property double dDouble: 1.23
        property string sString: "test string"
        property var vVar: [1, 2, 3, 4.5, "text"]
    }

    Settings {
        id: settings2
        fileName: "G:\\BDCA\\workspace\\gitee\\self-study\\QML\\96_Settings\\setttings.ini"
        property int iData: 10
        property double dDouble: 23.23
        property string sString: "other test string"
        property var vVar: [1, 2, 3, 4.5, "text"]
        category: "other"
    }

    Text {
        id: txt
        text: settings1.iData
        font.pixelSize: 40
    }

    Button {
        x: 100
        onClicked: {
            settings1.iData += 1
            console.log(settings1.value("iData", 0))  // 读取值
            settings2.setValue("addValue", 4)
        }
    }

}
