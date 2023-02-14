import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle{
    id: root
    width: 300; height: 300

    Text {
        id: thisLabel
        x: 24; y: 16
        height: 2* width
        Rectangle {
            anchors.fill: parent
            color: "blue"
            z: parent.z - 1
        }
        property int times: 24   //自定义属性
        property alias anotherTimes: thisLabel.times   //别名
        text: "thisLable " + anotherTimes
        width: 50
//        elide: Text.ElideMiddle  // 限制文本长度，多余的用...代替
//        wrapMode: Text.WordWrap   // 自动换行
        style: Text.Sunken    // 字体风格
        styleColor: "#ff0000"  // 字体风格颜色
        font.family: "Ubuntu"
        font.pixelSize: 24   // 字体大小
        KeyNavigation.tab: thatLabel  //按键点击属性
        onHeightChanged: console.log("height:", height) //height值改变就输出
        focus: false  // 使能按键事件
        color: focus ? "red" : "black"  // 随着focus值改变字体颜色
    }

    Text {
        id: thatLabel
        text: "thatLabel " + thisLabel.times
        focus: !thisLabel.focus
        KeyNavigation.tab: thisLabel
        color: focus ? "red" : "black"  // 随着focus值改变颜色

        // function(text){} 等同于 (text)=>{}
//        onTextChanged: function(text) { console.log("text changed to: ", text) }
        onTextChanged: (text) => { console.log("text changed to: ", text) }

        // 按键事件
        Keys.onSpacePressed: { increment() }  // 调用自定义JS函数
        Keys.onEscapePressed: { thatLabel.text = ' ' }
        // 自定义JS函数
        function increment() {
            thisLabel.times += 1
        }
    }

    Rectangle {
        id: rect
        x: 200; y: 12
        width: 76; height: 96
        color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1)   // 随机色
//        gradient: Gradient {   // 渐变色
//            GradientStop { position: 0.0; color: "green" }      // 顶部 0.0
//            GradientStop { position: 1.0; color: "blue" }        // 底部 1.0
//        }

        border.color: "lightsteelblue"
        border.width: 4
        radius: 20
    }

}



/*
Item {
    // 属性格式；name: value
    id: root  // id唯一，首字符必须是小写字母或下划线，整体由字母、数字、下划线组成

    // 附加属性
    Text {
        id: toptext
        focus: true  // 启动获取焦点的能力
        text: "text"
        Keys.onPressed: { // 点击键盘
            console.log("clicked")
        }
    }

    // 列表属性
    children: [  //如果列表里只有一个元素，可以省略方括号
        Text {
            id: text
            focus: true  // 启动获取焦点的能力
            text: qsTr("text")
            Keys.onPressed: {
                console.log("clicked")
            }

            // 分组属性
//            font.pixelSize: 24
//            font.bold: true
            font {
                pixelSize: 24
                bold: true
            }
        },

        Button {
            id: bt
            text: "按钮"
            x: 0
            y: 50
        }
    ]

}*/
