import QtQuick 2.14
import QtQuick3D 1.14

Rectangle {
    visible: true
    width: 640
    height: 480

    View3D {
        anchors.fill: parent
        environment: SceneEnvironment {
            clearColor: "#222222"
            backgroundMode: SceneEnvironment.Color
        }

        Model {
            position: Qt.vector3d(0, 0, 0)
            source: "#Cone"
            materials: [PrincipledMaterial {baseColor: "yellow"}]
        }

        DirectionalLight{
            visible: true
            x: -20
        }

        PerspectiveCamera {
            position: Qt.vector3d(0, 200, 300)
            Component.onCompleted: lookAt(Qt.vector3d(0, 0, 0 ))
        }
    }
}
