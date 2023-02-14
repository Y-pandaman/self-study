import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    width: 200
    height: 100
    color: "blue"

    property alias attr: attributes  // 设置别名，外部可访问
    // 属性私有化，外部不能访问
    QtObject {
        id: attributes
        property int testValue: 100
    }

    Component.onCompleted: {
        console.log(attributes.testValue)
    }
}
