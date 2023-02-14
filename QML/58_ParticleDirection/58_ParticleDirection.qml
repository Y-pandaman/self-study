
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
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: 1
        height: 1
        emitRate: 50  // 速率
        lifeSpan: 4800  // 生命周期
        lifeSpanVariation: 500  // 已发射粒子的生命周期变化
        size: 10  // 一个粒子开始的大小
        endSize: 50  // 生命周期结束时的大小

//        velocity: AngleDirection {
//            angle: -90
//            angleVariation: 15  // 范围
//            magnitude: 100  // 数量
//            magnitudeVariation: 50  // 偏差
//        }

//        velocity: PointDirection {
//            x: 100
//            y: 0
//            xVariation: 0
//            yVariation: 20
//        }

//        velocity: TargetDirection {
//            targetX: 100
//            targetY: 0
//            targetVariation: 20
//            magnitude: 100
//            magnitudeVariation: 50
//        }

        velocity: AngleDirection {
            angle: -45
            angleVariation: 0
            magnitude: 100
        }

        // 加速度
        acceleration: AngleDirection {
            angle: 90
            magnitude: 25
        }
    }

    ImageParticle {
        source: "../image/particle.png"
        system: particleSystem
    }
}
