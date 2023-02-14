
import QtQuick 2.12
import QtQuick.Particles 2.12

Rectangle {
    id: root
    width: 640
    height: 480
    color: "#1f1f1f"

    ParticleSystem {
        id: particleSystem
    }

    Emitter {
        system: particleSystem
        anchors.fill: parent
        emitRate: 50  // 速率
        lifeSpan: 4800  // 生命周期
        lifeSpanVariation: 500  // 已发射粒子的生命周期变化
        size: 10  // 一个粒子开始的大小
        endSize: 50  // 生命周期结束时的大小

        velocity: AngleDirection {
            angle: 0
            angleVariation: 15  // 范围
            magnitude: 100  // 数量
            magnitudeVariation: 50  // 偏差
        }
    }

//    Age {
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: 240
//        height: 120
//        system: particleSystem
//        lifeLeft: 1000
//        once: true
//        advancePosition: true

//        Rectangle {
//            anchors.fill: parent
//            border.color: "red"
//            color: Qt.rgba(0, 0, 0, 0)
//        }
//    }

    // 吸引
//    Attractor {
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: 240
//        height: 120
//        pointX: 0  // 目标位置
//        pointY: 0
//        strength: 1.0  // 速率
//        system: particleSystem
//        once: true

//        Rectangle {
//            anchors.fill: parent
//            border.color: "red"
//            color: Qt.rgba(0, 0, 0, 0)
//        }
//    }

    // 降速
//    Friction {
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: 240
//        height: 120

//        factor: 0.2
//        threshold: 25

//        system: particleSystem
//        once: true

//        Rectangle {
//            anchors.fill: parent
//            border.color: "red"
//            color: Qt.rgba(0, 0, 0, 0)
//        }
//    }

    // 重力
//    Gravity {
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: 240
//        height: 120

//        magnitude: 50
//        angle: 90

//        system: particleSystem
//        once: true

//        Rectangle {
//            anchors.fill: parent
//            border.color: "red"
//            color: Qt.rgba(0, 0, 0, 0)
//        }
//    }

    // 抖动，无序运动
//    Turbulence {
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: 240
//        height: 120

//        strength: 100

//        system: particleSystem
//        Rectangle {
//            anchors.fill: parent
//            border.color: "red"
//            color: Qt.rgba(0, 0, 0, 0)
//        }
//    }

    // 抖动
    Wander {
        anchors.horizontalCenter: parent.horizontalCenter
        width: 240
        height: 120

        affectedParameter: Wander.Position  // 影响位置值
        pace: 200  // 频率
        yVariance: 120
        xVariance: 500

        system: particleSystem
        Rectangle {
            anchors.fill: parent
            border.color: "red"
            color: Qt.rgba(0, 0, 0, 0)
        }
    }

    ImageParticle {
        source: "../image/particle.png"
        system: particleSystem
    }
}
