import QtQuick 2.12
import QtQuick.Shapes 1.12

Rectangle {
    visible: true
    width: 600
    height: 600

    Shape {
        anchors.centerIn: parent

        ShapePath {
            id: shapePath
            property real t: 0.0

            NumberAnimation on t {
                from: 0.0
                to: 1.0
                duration: 500
                loops: Animation.Infinite
                running: true
            }
            strokeColor: 'blue'  // 边框色
            fillColor: 'green'  // 填充色
            strokeWidth: 3

            startX: -40
            startY: 200
            PathArc{x: 40; y: 200; radiusX: 200; radiusY: 200; useLargeArc: true}
            PathLine{x: 40; y: 120}
            PathArc{x: -40; y: 120; radiusX: 120; radiusY: 120; useLargeArc: true; direction: PathArc.Counterclockwise} // 终点，半径，大圆，逆时针
            PathLine{x: -40; y: 200}

            PathMove{x: -20 + (1 - shapePath.t) * 20; y: 80 + shapePath.t * 50}
            PathArc{x: 20 -  (1 - shapePath.t) * 20; y: 80 + shapePath.t * 50; radiusX: 20 * shapePath.t; radiusY: 20 * shapePath.t}
            PathArc{x: -20 +  (1 - shapePath.t) * 20; y: 80 + shapePath.t * 50; radiusX: 20 * shapePath.t; radiusY: 20 * shapePath.t}

            PathMove{x: -20; y: 130 + shapePath.t * 50}
            PathArc{x: 20; y: 130 + shapePath.t * 50; radiusX: 20; radiusY: 20}
            PathArc{x: -20; y: 130 + shapePath.t * 50; radiusX: 20; radiusY: 20}

            PathMove{x: -20; y: 180 + shapePath.t * 50}
            PathArc{x: 20; y: 180 + shapePath.t * 50; radiusX: 20; radiusY: 20}
            PathArc{x: -20; y: 180 + shapePath.t * 50; radiusX: 20; radiusY: 20}

            PathMove{x: -20 + shapePath.t * 20; y: 230 + shapePath.t * 50}
            PathArc{x: 20 - shapePath.t * 20; y: 230 + shapePath.t * 50; radiusX: 20 * (1 - shapePath.t); radiusY: 20 * (1 - shapePath.t)}
            PathArc{x: -20 + shapePath.t * 20; y: 230 + shapePath.t * 50; radiusX: 20 * (1 - shapePath.t); radiusY: 20 * (1 - shapePath.t)}
        }
    }

}
