 import QtQuick 2.12
import QtQuick.Particles 2.12

Rectangle {
    width: 640
    height: 280
    id: root
    color: "#1f1f1f"
    property bool tracer: true

    ParticleSystem {
        id: particleSystem
    }

    Emitter {
        id: rocketEmitter
        anchors.bottom: root.bottom
        width: root.width
        height: 40
        system: particleSystem
        group: "rocket"
        emitRate: 2
        maximumEmitted: 40
        lifeSpan: 5000
        lifeSpanVariation: 400
        size: 32
        velocity: AngleDirection {
            angle: 270
            magnitude: 150
            magnitudeVariation: 10
        }
        acceleration:  AngleDirection {
            angle: 90
            magnitude: 50
        }
        Tracer {
            color: "red"
            visible: root.tracer
        }
    }

    TrailEmitter {
        id: smokeEmitter
        system: particleSystem
        emitHeight: 1
        emitWidth: 10
        group: "smoke"
        follow: "rocket"
        emitRatePerParticle: 50
        lifeSpan: 200
        size: 16
        sizeVariation: 4
        endSize: 0
        velocity: AngleDirection {
            angle: 90
            magnitude: 100
            angleVariation: 5
        }
    }

    Friction {
        groups: ["rocket"]
        anchors.top: parent.top
        width: parent.width
        height: 80
        system: particleSystem
        threshold: 5
        factor: 0.9
    }

    Turbulence {
        groups: ["rocket"]
        anchors.bottom: root.bottom
        width: root.width
        height: 200
        system: particleSystem
        strength: 25
        Tracer {
            color: "green"
            visible: root.tracer
        }
    }

    GroupGoal {
        id: rocketChanger
        anchors.top: root.top
        width: root.width
        height: 80
        system: particleSystem
        groups: ["rocket"]
        goalState: "explosion"
        jump: true
        Tracer {
            color: "blue"
            visible: root.tracer
        }
    }

    ParticleGroup {
        name: "explosion"
        system: particleSystem

        TrailEmitter {
            id: explosionEmitter
            group: "sparkle"
            follow: "rocket"
            lifeSpan: 1000
            emitRatePerParticle: 100
            size: 20
            velocity: AngleDirection {
                angle: -90
                angleVariation: 180
                magnitude: 50
            }
        }
    }

    ImageParticle {
        id: smokeParticle
        system: particleSystem
        groups: ['smoke']
        source: "../image/particle.png"
        alpha: 0.3
        entryEffect: ImageParticle.Fade   // 淡入淡出效果
    }

    ImageParticle {
        id: rocketParticle
        system: particleSystem
        groups: ['rocket']
        source: "../image/rocket.png"
        entryEffect: ImageParticle.Fade   // 淡入淡出效果
    }

    ImageParticle {
        id: sparklePainter
        system: particleSystem
        groups: ['sparkle']
        source: "../image/particle.png"
        color: "red"
        colorVariation: Math.random() * 10
        alpha: 0.3
        entryEffect: ImageParticle.Fade   // 淡入淡出效果
    }



}
