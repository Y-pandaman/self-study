import QtQuick 2.12
import QtQuick.Window 2.12

Item {  // 最基础的元素
    id: root
    x: 0
    y: 0
    z: 100  // 区分重叠，默认0
    width: 200
    height: 200
    Item {
        x: 0
        y: 0
        width: 200
        height: 200
        rotation: 30
    }
}
