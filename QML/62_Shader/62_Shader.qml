
import QtQuick 2.12

Rectangle {
    id: root
    width: 640
    height: 480
    color: "#333"

    Row {
        anchors.centerIn: parent
        spacing: 20

        Image {
            id: sourceImage
            source: "../image/1.png"
            width: 90
            height: width
        }

        ShaderEffect {
            id: effect
            width: 90
            height: 90
            property variant source: sourceImage
        }

        ShaderEffect {
            id: effect2
            width: 90
            height: 90
            property variant source: sourceImage
            vertexShader: "
                uniform highp mat4 qt_Matrix;
                attribute highp vec4 qt_Vertex;
                attribute highp vec2 qt_MultiTexCoord0;
                varying highp vec2 qt_TexCoord0;
                void main() {
                    qt_TexCoord0 = qt_MultiTexCoord0;
                    gl_Position = qt_Matrix * qt_Vertex;
                }"
            fragmentShader: "
                varying highp vec2 qt_TexCoord0;
                uniform sampler2D source;
                uniform lowp float qt_Opacity;
                void main() {
                    gl_FragColor = texture2D(source, qt_TexCoord0) * qt_Opacity;
                }"
        }
    }
}
