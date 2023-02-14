import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyListView {}

//    MyPopup{
//        id: myPopup
//    }

//    Button {
//        text: "Open"
//        onClicked:{
////            popup.open()  // 外部调用open打开popup窗口
//            myPopup.close()
//        }
//    }

//    Popup {  // 类似于Rectangle
//        id: popup
////        visible: true  // 可显示
//        x: 100
//        y: 100
//        width: 100
//        height: 100
//        modal: true
//        focus: true
//        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
//    }

//    Rectangle {  // 当rectangle父控件设置成不可见时，子控件也不可见
//        width: 100
//        height: 100
//        x: 100
//        y: 100
//        color: "red"
//        visible: false
////        Rectangle {  // 因父控件不可见而不可见
//        Popup {  // popup例外，不因为父控件不可见二不可见
//            width: 50
//            height: 50
//            x: 50
//            y: 50
////            color: "blue"
//            visible: true
//        }
//    }

//    // 先后顺序（rectangle的z值）不影响popup出现在最上层
//    // 多个popup框由z值决定上下层
//    Rectangle {
//        width: 100
//        height: 50
//        x: 300
//        color: "black"
//        z: 2
//    }
////    Rectangle {
//    Popup {
//        width: 100
//        height: 50
//        x: 350
////        color: "red"
//        visible: true
//        z: 1
//    }

}
