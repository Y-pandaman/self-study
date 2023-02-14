import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import MyObj 1.0

Window {
    id: root
    objectName: "root"
    visible: true
//    width: Screen.desktopAvailableWidth  // 跨屏幕全屏
    width: WINDOW_WIDTH
    height: 480
    title: qsTr("Hello World")
    property int value: myObj.iValue

    signal qmlSig(int i, string s)

    function qmlSlot(i, s) {  // 参数类型 对应CPP端都是QVariant
        console.log("qml", i, s)
    }

    //  方式1： 通过访问函数来做信号与槽
//    Connections {
//        target: root
//        function onQmlSig(i, s) {
//            myObj.cppSlot(i, s)
//        }
//    }

    // 方式2: 通过信号的connect方式绑定信号与槽
    Component.onCompleted: {
        qmlSig.connect(myObj.cppSlot)
    }

//    MyRectangle {
//        Component.onCompleted: {
//            attr.testValue = 200
//            console.log(attr.testValue)
//        }
//    }
    Button {
        x: 200
        objectName: "myButton"
        onClicked: {
//            myObj.func()\
            MyObject.func() // 单例法
            qmlSig(10, "lisi")
//            myObj.cppSig(99, "wangwu")
        }
    }

        Connections {
//            target: myObj
            target: MyObject // 单例法
            function onCppSig(i, s) {
                qmlSlot(i, s)
            }
        }

        function qmlFunc(i, s){
            return "success"
        }


//    MyObject {
//        id: myObj
//        iValue: 10
//        sString: "zhangsan"

////        Component.onCompleted: {
////            console.log(iValue, sString)
////        }
//    }

//    onValueChanged: {
//        console.log(value)
//    }

//    Button {
//        onClicked: {
//            myObj.iValue += 20
//        }
//    }
}
