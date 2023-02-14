import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.14

Window {
    visible: true
    width: 640
    height: 480

    // delayButton
    DelayButton {
        width: 100
        height: 20
        delay: 3000
        onProgressChanged: {
            console.log(progress)
        }
    }

    // radioButton,自动排它性
    Rectangle {
        width: 100
        height: 100
        y: 100

        ColumnLayout {
              RadioButton {
                  checked: true
                  text: qsTr("First")
              }
              RadioButton {
                  text: qsTr("Second")
              }
              RadioButton {
                  text: qsTr("Third")
              }
          }
    }

    // switch,没有自动排它属性
    Rectangle {
        width: 100
        height: 100
        y: 250

        // 设置排它属性
        ButtonGroup {
            id: btngrp
            exclusive: true
            buttons: col.children
        }
        ColumnLayout {
            id: col
              Switch {
                  text: qsTr("Wi-Fi")
                  onPositionChanged: {
                    console.log("pos: ", position)
                  }
                  onVisualPositionChanged: {
                    console.log("vis pos:", visualPosition)
                  }
              }
              Switch {
                  LayoutMirroring.enabled: true  //镜像   文字，按钮交换左右位置
                  text: qsTr("Bluetooth")
              }
          }
    }

    // TabButton,自带排它性
    Rectangle {
        width: 100
        height: 100
        x: 150
        TabBar {
              TabButton {
                  text: qsTr("Home")
              }
              TabButton {
                  text: qsTr("Discover")
              }
              TabButton {
                  text: qsTr("Activity")
              }
          }
    }

    // RoundButton
    Rectangle {
        width: 100
        height: 50
        x: 350

        RoundButton {
              text: "text" // Unicode Character 'CHECK MARK'
              onClicked: textArea.readOnly = true
          }
    }

    // ToolButton
    Rectangle {
        width: 100
        height: 100
        x: 400

        ToolBar {
              RowLayout {
                  anchors.fill: parent
                  ToolButton {
                      text: qsTr("‹")
                      onClicked: stack.pop()
                  }
                  Label {
                      text: "Title"
                      elide: Label.ElideRight
                      horizontalAlignment: Qt.AlignHCenter
                      verticalAlignment: Qt.AlignVCenter
                      Layout.fillWidth: true
                  }
                  ToolButton {
                      text: qsTr("⋮")
                      onClicked: menu.open()
                  }
              }
          }
    }

    Button {
        id: btn
        width: 150
        height: 100
        x: 200
        y: 200
        text: "button"  // 不能直接更改文本属性，如大小、颜色
        background: Rectangle {
            anchors.fill:parent
            color: btn.checked | btn.down ? "blue" : "green"  // 按下变蓝
        }
        // 更改文本属性
        contentItem: Text {
            id: text
            text: btn.text
            font.pixelSize: 20  // 字体大小
            font.bold: true  // 粗体
            font.italic: true // 斜体
            color: "red"  // 颜色
        }
    }
}
