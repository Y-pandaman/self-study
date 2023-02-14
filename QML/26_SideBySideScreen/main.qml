import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: window
    visible: true
    width: 320
    height: 480
    title: qsTr("Side By Side")

    SwipeView {
        id: swipeView
        anchors.fill: parent

        Home {}  // 初始页面
        About {}
        EditProfile {}
        Profile {}
    }

    // 添加下方导航指示点
    PageIndicator {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        currentIndex: swipeView.currentIndex
        count: swipeView.count
    }
}
