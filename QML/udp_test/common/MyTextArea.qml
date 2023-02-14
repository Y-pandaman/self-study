import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root
    property int textSize   //字体大小

    property alias textArea: textArea
    property alias readOnly: textArea.readOnly

    property alias rowHeight: fontFlag.height
    property alias lineCount: textArea.lineCount
    property alias contentY:flickable.contentY
    //辅助元素：用来确定行号的宽度和高度
    //可以让标号的字体大小和textarea的字体大小保持一致
    Text{
        id:fontFlag
        visible: false
        font: textArea.font
        text:textArea.lineCount
    }
    //行号
    Item{
        id:lineNumbers
        height: parent.height
        width: fontFlag.width + 10
        clip: true
        x: 5
        //行号旁边的分割线
        Rectangle {
            height: parent.height
            anchors.right: parent.right
            width: 1
            color: "black"
        }
        Column{
            id: column
            y: -flickable.contentY
            //相当于占位空间，因为textarea区域四周默认是有padding距离的，
            //要把上方的toppadding空间预留掉，才能保证行号和内容是顶部对齐的
            Item{
                height: textArea.topPadding
                width: height
            }
            //重复实现行号显示
            Repeater {
                id: repeater
                model: textArea.lineCount

                Text{
                    id: tNum
                    font.pointSize: textSize
                    width: fontFlag.width
                    height: fontFlag.height
                    horizontalAlignment: Text.AlignRight
                    text: index+1
                }
            }
        }
    }
    //编辑框(使用flickable.textarea附加属性进行实现)
    Flickable {
        id: flickable
        clip: true
        anchors.fill : parent
        anchors.leftMargin:  lineNumbers.width
        anchors.bottomMargin: hbar.height
        contentX: hbar.position * textArea.width
        interactive: true   //交互
        flickableDirection: Flickable.VerticalFlick //交互方向

        TextArea.flickable: TextArea {
            id: textArea
            anchors.left: lineNumbers.right
            anchors.right: parent.right
            rightPadding: 35
            inputMethodHints: Qt.ImhNoAutoUppercase
            wrapMode: TextArea.NoWrap
            persistentSelection: true
            selectByMouse: true
            font.pointSize: textSize
        }
        ScrollBar.vertical: ScrollBar {
            id: vbar
            width: 30
            active: true
            orientation: Qt.Vertical
            policy: ScrollBar.AlwaysOn       //滚动条始终显示
            contentItem: Rectangle{
                implicitWidth: 30
                implicitHeight: 10
                radius: width / 2
                color: "#00000000"
                Rectangle{
                    height: parent.height
                    width: parent.width/3
                    radius: width / 2
                    anchors.centerIn: parent
                    color: parent.parent.pressed ? "#5E5E5F" : "#CDCECF"
                }
            }
        }
    }
    ScrollBar {
        id: hbar
        height: 30
        active: true
        orientation: Qt.Horizontal
        size: (flickable.width / textArea.width)
        policy: ScrollBar.AlwaysOn       //滚动条始终显示
        anchors.left: flickable.left
        anchors.leftMargin: textArea.leftPadding
        anchors.right: flickable.right
        anchors.rightMargin: vbar.width
        anchors.bottom: parent.bottom
        contentItem: Rectangle{
            implicitHeight: 30
            implicitWidth: 10
            color: "#00000000"

            Rectangle{
                height: parent.height/3
                width: parent.width
                radius: height / 2
                anchors.centerIn: parent
                color: parent.parent.pressed ? "#5E5E5F" : "#CDCECF"
            }
        }
    }
}
