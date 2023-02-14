import QtQuick 2.12
import QtQuick.Particles 2.12

Rectangle {
    width: 640
    height: 280
    id: root
    color: "#1f1f1f"
    property bool tracer: false

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
    }

    ImageParticle {
        id: smokePainter
        system: particleSystem
        groups: ['smoke']
        source: "../image/particle.png"
        alpha: 0.3
    }

    ItemParticle {
        id: rocketPainter
        groups: ["rocket"]
        system: particleSystem
        delegate: itemDelegate
    }

    property var images: []
    Component.onCompleted: {
        images.push("rocket.png")
        images.push("1.png")
        images.push("5.jpg")
        images.push("ball.png")
    }
    Component {
        id: itemDelegate
        Item {
            id: container
            width: 32 * Math.ceil(Math.random() * 3)
            height: width
            Image {
                anchors.fill: parent
                anchors.margins: 4
//                source: "../image/rocket.png"
                source: "../image/" + root.images[Math.floor(Math.random() * 4)]
            }
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
}
