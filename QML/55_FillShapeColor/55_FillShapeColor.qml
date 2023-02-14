import QtQuick 2.12
import QtQuick.Shapes 1.12

Rectangle {
    id: root
    width: 640
    height: 480

    Shape {
        ShapePath {
            strokeColor: "yellow"
            fillColor: "lightblue"
            strokeWidth: 5

            startX: 20
            startY: 140

            PathLine{x:180; y: 140}
            PathArc {
                x: 20
                y:140
                direction: PathArc.Counterclockwise
                radiusX: 80
                radiusY: 80
            }
        }
    }

    // 线性渐变
    Shape {
        ShapePath {
            strokeColor: "yellow"
            fillGradient: LinearGradient{
                x1: 50; y1:300
                x2: 150; y2: 280
                GradientStop {position: 0.0; color: "lightgreen"}
                GradientStop {position: 0.7; color: "blue"}
                GradientStop {position: 1.0; color: "grey"}
            }
            strokeWidth: 5

            startX: 20
            startY: 340

            PathLine{x:180; y: 340}
            PathArc {
                x: 20
                y:340
                direction: PathArc.Counterclockwise
                radiusX: 80
                radiusY: 80
            }
        }
    }

    // 锥形渐变
    Shape {
        ShapePath {
            strokeColor: "yellow"
            fillGradient: ConicalGradient{
                centerX: 300
                centerY: 100
                angle: 90
                GradientStop {position: 0.0; color: "lightgreen"}
                GradientStop {position: 0.7; color: "blue"}
                GradientStop {position: 1.0; color: "grey"}
            }
            strokeWidth: 5

            startX: 220
            startY: 140

            PathLine{x:380; y: 140}
            PathArc {
                x: 220
                y:140
                direction: PathArc.Counterclockwise
                radiusX: 80
                radiusY: 80
            }
        }
    }

    // 径向渐变
    Shape {
        ShapePath {
            strokeColor: "yellow"
            fillGradient: RadialGradient{
                centerX: 300
                centerY: 250
                centerRadius: 120
                focalX: centerX
                focalY: centerY
                focalRadius: 30
                GradientStop {position: 0.0; color: "lightgreen"}
                GradientStop {position: 0.7; color: "blue"}
                GradientStop {position: 1.0; color: "grey"}
            }
            strokeWidth: 5

            startX: 220
            startY: 340

            PathLine{x:380; y: 340}
            PathArc {
                x: 220
                y:340
                direction: PathArc.Counterclockwise
                radiusX: 80
                radiusY: 80
            }
        }
    }
}
