import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.qmlmodels 1.0

TableView {
    width: 400
    height: 400

    columnSpacing: 5  // 列间距
    rowSpacing: 5  // 行间距
    model: TableModel {
        TableModelColumn { display: "name" }  // 第一列
        TableModelColumn { display: "color" }  // 第二列

        // 行数据
        rows: [
            {
                "color": "color",
                "name": "animal name"
            },
            {
                "color": "black",
                "name": "cat"
            },
            {
                "name": "dog",  // name与 color的位置不重要，由上面的display决定
                "color": "white"
            },
            {
                "name": "duck",
                "color": "blue"
            },
            {
                "color": "green",
                "name": "pig"
            }
        ]
    }

    delegate: Rectangle {
        // 设置表格尺寸，不能使用anchors
        implicitHeight: 50
        implicitWidth: 100
        border.width: 1

        Text {
            text: display
            anchors.centerIn: parent
        }
    }

}
