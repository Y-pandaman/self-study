import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import QtQuick.Particles 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "grey"

    ParticleSystem {
        id: particleSystem
    }

    Emitter {
        id: emitter
        anchors.centerIn: parent
        width: 300
        height: 300
        system: particleSystem
        emitRate: 10
        lifeSpan: 1600  // 粒子的生命周期
        lifeSpanVariation: 400   // 创建粒子的间隔
        size: 30
        velocity: PointDirection {  //  粒子移动的方向
            x: 45
            xVariation: 0  // 偏移
            yVariation: 100 / 6
        }
    }

    ImageParticle {
        id: img
        source: "../image/particle.png"
        system: particleSystem
        colorVariation: 1  // 颜色偏移范围
    }

    Attractor {
        anchors.fill: parent
        system: particleSystem
        enabled: true
        pointX: mouse.mouseX
        pointY: mouse.mouseY

        strength: -100000000
        affectedParameter: Attractor.Acceleration
        proportionalToDistance: Attractor.InverseQuadratic
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
    }



    Text {
        id: txt
        text: qsTr("watting")
        font.pixelSize: 60
        anchors.centerIn: parent
    }

    Glow {
        id: glow
        anchors.fill: txt
        radius: 8
        samples: 17
        color: "white"
        source: txt
        SequentialAnimation {  // 队列动画效果
            running: true
            loops: Animation.Infinite  //  循环 运行动画
            NumberAnimation {
                target: glow
                property: "spread"
                to: 0
                duration: 1000
            }
            NumberAnimation {
                target: glow
                property: "spread"
                to: 0.5
                duration: 1000
            }
        }
    }

    BusyIndicator {
        width: 100
        height: 100
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
    }

}
