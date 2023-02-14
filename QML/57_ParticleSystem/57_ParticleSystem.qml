
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
        width: 400
        height: 300
        anchors.centerIn: parent
        emitRate: 50  // 速率
        lifeSpan: 1000  // 生命周期
        lifeSpanVariation: 500  // 已发射粒子的生命周期变化
        size: 60  // 一个粒子开始的大小
        endSize: 30  // 生命周期结束时的大小

        Rectangle {
            border.color: "green"
            anchors.fill: parent
            color: Qt.rgba(0, 0, 0, 0)
        }
    }

    ImageParticle {
        source: "../image/particle.png"
        system: particleSystem
    }
}
