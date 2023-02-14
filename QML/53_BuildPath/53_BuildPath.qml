import QtQuick 2.14
import QtQuick.Shapes 1.12

Rectangle {
    id: root
    width: 640
    height: 480
    color: 'black'  // 背景

    Shape {
        //直线
        ShapePath {
            strokeColor: 'green'
            strokeWidth: 4
            startX: 20
            startY: 70
            PathLine{
                x: 180
                y: 130
            }
        }

        // 多线段
        ShapePath {
            strokeColor: 'green'
            strokeWidth: 4

            PathPolyline{  // import QtQuick ≥ 2.14
                path: [
                    Qt.point(220, 100),
                    Qt.point(260, 20),
                    Qt.point(300, 170),
                    Qt.point(340, 60),
                    Qt.point(380, 100)
                ]
            }
        }

        ShapePath {
            strokeColor: 'blue'
            strokeWidth: 5
            startX: 420
            startY: 100

            PathArc {
                x: 580
                y: 180
                radiusX: 120
                radiusY: 120
                useLargeArc: true
            }
        }

        ShapePath {
            strokeColor: 'blue'
            strokeWidth: 5
            startX: 120
            startY: 300

            PathQuad {
                x: 180
                y: 200
                controlX: 60
                controlY: 110
            }
        }

        ShapePath {
            strokeColor: 'blue'
            strokeWidth: 5
            startX: 220
            startY: 300

            PathCubic {
                x: 480
                y: 200
                control1X: 260
                control1Y: 110
                control2X: 360
                control2Y: 500
            }
        }

        ShapePath {
            strokeColor: 'blue'
            strokeWidth: 5
            startX: 520
            startY: 300

            PathCurve {
                x: 580
                y: 200
            }
            PathCurve {
                x: 600
                y: 380
            }
            PathCurve {
                x: 650
                y: 280
            }
        }


    }
}
