import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

//ComboBox {
//    id: comboBox
////    model: 3
////    model: ['apple', 'banana', 'pear']
//    model: ListModel {
//        id: model
//        ListElement {text: 'Apple'}
//        ListElement {text: 'Banana'}
//        ListElement {text: 'Pear'}
//    }
//    onAccepted: {
//        if (find(editText) === -1)
//            model.append({text: editText})
//    }
//    editable: true  // 可编辑
//    Component.onCompleted: {
//        console.log(count)
//    }
//}

//ComboBox {
//    model: 3
//    onCurrentTextChanged: {
//        console.log("text:", currentText)
//    }
//    onCurrentValueChanged: {
//        console.log("value:", currentValue)
//    }
//}

//ComboBox {
//    textRole: "text"
//    valueRole: "name"
//    width: 300
//    displayText: currentIndex + " " + currentText + " " + currentValue // 控制要显示的内容
//    model: [
//        { value: 100, text: qsTr("No modifier") , name: "zhangsan"},
//        { value: 200, text: qsTr("Shift"), name: "lisi" },
//        { value: 300, text: qsTr("Control"), name: "wangwu" }
//    ]
//    onCurrentTextChanged: {
//        console.log("text:", currentText)
//    }
//    onCurrentValueChanged: {
//        console.log("value:", currentValue)
//    }
//}

//ComboBox {
//    model: 10
//    editable: true
////    validator: IntValidator{
////        top: 20  // 可输入内容的上限
////        bottom: 0  // 下限
////    }
//    validator: RegExpValidator {
////        regExp: /[0-9A-F]+/    // 0-9,A-F
//        regExp: /[0-9A-F]+[.][0-9]/     // ****.*
//    }

//    onAcceptableInputChanged: {  // 判断当前有没有匹配validator验证器，否就输出false
//        console.log(acceptableInput)
//    }
//}

// 自定义combobox
ComboBox {
      id: control
      model: ["First", "Second", "Third","First", "Second", "Third","First", "Second", "Third"]

      // 针对model中每一项的具体绘制
      delegate: ItemDelegate {
          width: control.width
          contentItem: Text {
              text: modelData
              color: index % 2 ? "red" : "blue"
              font: control.font
              elide: Text.ElideRight
              verticalAlignment: Text.AlignVCenter
          }
          highlighted: control.highlightedIndex === index
      }

      indicator: Canvas {  // Canvas可换成Image，任意Item控件
          id: canvas
          x: control.width - width - control.rightPadding
          y: control.topPadding + (control.availableHeight - height) / 2
          width: 12
          height: 8
          contextType: "2d"

          Connections {
              target: control
              onPressedChanged: canvas.requestPaint()
          }

          onPaint: {
              context.reset();
              context.moveTo(0, 0);
              context.lineTo(width, 0);
              context.lineTo(width / 2, height);
              context.closePath();
              context.fillStyle = control.pressed ? "#17a81a" : "#21be2b";
              context.fill();
          }
      }

      // 控制当前选项的内容状态
      contentItem: Text {
          leftPadding: 0
          rightPadding: control.indicator.width + control.spacing

          text: control.displayText
          font: control.font
          color: control.pressed ? "#17a81a" : "#21be2b"
          verticalAlignment: Text.AlignVCenter
          elide: Text.ElideRight  // 右侧省略
      }

      // 当前选项的背景
      background: Rectangle {
          implicitWidth: 120
          implicitHeight: 40
          border.color: control.pressed ? "#17a81a" : "#21be2b"
          border.width: control.visualFocus ? 2 : 1
          radius: 2
      }

      popup: Popup {  // 绘制整个下拉控件
          y: control.height - 1
          width: control.width
//          implicitHeight: contentItem.implicitHeight
          implicitHeight: 150  // 下拉框的高度
          padding: 1

          contentItem: ListView {
              clip: true
              implicitHeight: contentHeight
              model: control.popup.visible ? control.delegateModel : null
              currentIndex: control.highlightedIndex

              interactive: true  // 鼠标能否拖动，默认true
              boundsBehavior: Flickable.StopAtBounds  // 拖动到边界就停止

//              ScrollIndicator.vertical: ScrollIndicator { }
              ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn  // 一直显示滑条
              }
          }

          background: Rectangle {
              border.color: "yellow"
              radius: 2
              layer.enabled: true  // 开启layer.effect
              layer.effect: DropShadow {  // 添加阴影
                  horizontalOffset: 3
                verticalOffset: 3
                radius: 8
                samples: 17
                color: "#80000000"
              }
          }
      }
  }
