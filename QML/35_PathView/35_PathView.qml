import QtQuick 2.12
import QtQuick.Window 2.12
import "../common"

Rectangle {
    id: root
    width: 300
    height: 480

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "#234567"
        }
        GradientStop {
            position: 1.0
            color: "#765432"
        }
    }

    // View
    PathView {
        model: 100  // 总共数据量
        anchors.fill: parent

        delegate: flipCardDelegate

        path: Path {
            startX: root.width / 2
            startY: 0
            PathAttribute {
                name: "itemZ"
                value: 0
            }
            PathAttribute {
                name: "itemAngle"
                value: -90.0
            }
            PathAttribute {
                name: "itemScale"
                value: 0.5
            }
            PathLine {  // 路径关键点
                x: root.width / 2
                y: root.height * 0.4
            }
            PathPercent {
                value: 0.48
            }
            PathLine {  // 路径关键点
                x: root.width / 2
                y: root.height * 0.5
            }
            PathAttribute {
                name: "itemZ"
                value: 100
            }
            PathAttribute {
                name: "itemAngle"
                value: 0
            }
            PathAttribute {
                name: "itemScale"
                value: 1
            }
            PathLine {  // 路径关键点
                x: root.width / 2
                y: root.height * 0.6
            }
            PathPercent {
                value: 0.52
            }
            PathLine {  // 路径关键点
                x: root.width / 2
                y: root.height
            }
            PathAttribute {
                name: "itemZ"
                value: 0
            }
            PathAttribute {
                name: "itemAngle"
                value: 90.0
            }
            PathAttribute {
                name: "itemScale"
                value: 0.5
            }
        }
        pathItemCount: 16  // 显示数量

        // 高亮位置区域，0.5表示中间
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
    }

    // delegate
    Component {
        id: flipCardDelegate
        GreenBox {
            id: wrapper
            width: 64
            height: 64
            text: index
            z: PathView.itemZ
            scale: PathView.itemScale

            // 抗锯齿
            antialiasing: true

            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#2ed5fa"
                }
                GradientStop {
                    position: 1.0
                    color: "#2467ec"
                }
            }

            // 透明度
            opacity: PathView.isCurrentItem ? 1 : 0.5

            transform: Rotation {
                axis{  // 旋转轴
                    x: 1
                    y: 0
                    z: 0
                }
                angle: wrapper.PathView.itemAngle  // 旋转角度
                origin{  // 旋转中心
                    x: 32
                    y: 32
                }
            }
        }
    }
}
