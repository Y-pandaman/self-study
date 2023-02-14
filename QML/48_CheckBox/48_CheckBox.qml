import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    visible: true
    width: 640
    height: 480

    // 默认CheckBox
    Rectangle {
        width: 100
        height: 100
        x: 10
        y: 10

        Column {
              CheckBox {
                  checked: true
                  text: qsTr("First")
              }
              CheckBox {
                  text: qsTr("Second")
              }
              CheckBox {
                  checked: true
                  text: qsTr("Third")
              }
          }
    }

    // 父、子勾选
    Rectangle {
        width: 100
        height: 100
        x: 110
        y: 10

        Column {
              ButtonGroup {
                  id: childGroup
                  exclusive: false
                  checkState: parentBox.checkState
              }

              CheckBox {
                  id: parentBox
                  text: qsTr("Parent")
                  checkState: childGroup.checkState
              }

              CheckBox {
                  checked: true
                  text: qsTr("Child 1")
                  leftPadding: indicator.width
                  ButtonGroup.group: childGroup
              }

              CheckBox {
                  text: qsTr("Child 2")
                  leftPadding: indicator.width
                  ButtonGroup.group: childGroup
              }
          }
    }

    Rectangle {
        width: 100
        height: 100
        x: 210
        y: 10

        CheckBox {
              tristate: true  // checkbox的三种状态，“√”，"-"，"空白"
              checkState: allChildrenChecked ? Qt.Checked :
                             anyChildChecked ? Qt.PartiallyChecked : Qt.Unchecked

              nextCheckState: function() {
                  if (checkState === Qt.Checked)
                      return Qt.Unchecked
                  else
                      return Qt.Checked
              }
          }
    }

    // 只能勾选一个
    Rectangle {
        width: 100
        height: 100
        x: 310
        y: 10

        Column {
              ButtonGroup {
                  id: group
                  exclusive: true
                  checkState: parentBox.checkState
              }

              CheckBox {
                  checked: true
                  text: qsTr("Child 1")
                  leftPadding: indicator.width
                  ButtonGroup.group: group
              }

              CheckBox {
                  checked: true
                  text: qsTr("Child 2")
                  leftPadding: indicator.width
                  ButtonGroup.group: group
              }

              CheckBox {
                  text: qsTr("Child 3")
                  leftPadding: indicator.width
                  ButtonGroup.group: group
              }
          }
    }

}
