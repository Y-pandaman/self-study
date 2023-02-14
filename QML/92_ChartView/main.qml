import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.3
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ChartView {
          title: "Bar series"
          id: chartView
          anchors.fill: parent
          legend.alignment: Qt.AlignBottom
          antialiasing: true

//          BarSeries {
//              id: mySeries
//              axisX: BarCategoryAxis { categories: ["2007", "2008", "2009", "2010", "2011", "2012" ] }
//              BarSet { label: "Bob"; values: [2, 2, 3, 4, 5, 6] }
//              BarSet { label: "Susan"; values: [5, 1, 2, 4, 1, 7] }
//              BarSet { label: "James"; values: [3, 5, 8, 13, 5, 8] }
//          }

          BarCategoryAxis {
              id: axisX
              categories: ["2007", "2008", "2009", "2010", "2011", "2012" ]
          }
          ValueAxis {
              id: axisY
              min: 0
              max: 2
          }

          Component.onCompleted: {
            var bar = chartView.createSeries(ChartView.SeriesTypeBar, "MyBar", axisX, axisY)
              bar.append("mybar1", [0, 0.2, 0.2, 0.5, 0.4, 1.5, 0.9])
          }
      }













//    ChartView {
//        id: chartView
//          title: "NHL All-Star Team Players"
//          anchors.fill: parent
//          antialiasing: true

//          LineSeries {
//              id: line1
//              color: "red"
//              name: "LineSeries1"
//              XYPoint { x: 0; y: 0 }
//              XYPoint { x: 1.1; y: 2.1 }
//              XYPoint { x: 1.9; y: 3.3 }
//              XYPoint { x: 2.1; y: 2.1 }
//              XYPoint { x: 2.9; y: 4.9 }
//              XYPoint { x: 3.4; y: 3.0 }
//              XYPoint { x: 4.1; y: 3.3 }
//          }

//          LineSeries {
//              id: line2
//              color: "blue"
//              name: "LineSeries2"
//              XYPoint { x: 0; y: 0 }
//              XYPoint { x: 1.1; y: 1.1 }
//              XYPoint { x: 1.9; y: 2.3 }
//              XYPoint { x: 2.1; y: 1.1 }
//              XYPoint { x: 2.9; y: 3.9 }
//              XYPoint { x: 3.4; y: 2.0 }
//              XYPoint { x: 4.1; y: 2.3 }
//          }

//          Component.onCompleted: {
//            var area = chartView.createSeries(ChartView.SeriesTypeArea, "myArea")
//              area.upperSeries = line1  // 不代表上面的线条，可以交换顺序
//              area.lowerSeries = line2
//              area.opacity = 0.3
//              area.color = "green"
//          }


////          // Define x-axis to be used with the series instead of default one
////          ValueAxis {
////              id: valueAxis
////              min: 2000
////              max: 2011
////              tickCount: 12
////              labelFormat: "%.0f"
////          }

////          AreaSeries {
////              name: "Russian"
////              axisX: valueAxis
////              upperSeries: LineSeries {
////                  XYPoint { x: 2000; y: 1 }
////                  XYPoint { x: 2001; y: 1 }
////                  XYPoint { x: 2002; y: 1 }
////                  XYPoint { x: 2003; y: 1 }
////                  XYPoint { x: 2004; y: 1 }
////                  XYPoint { x: 2005; y: 0 }
////                  XYPoint { x: 2006; y: 1 }
////                  XYPoint { x: 2007; y: 1 }
////                  XYPoint { x: 2008; y: 4 }
////                  XYPoint { x: 2009; y: 3 }
////                  XYPoint { x: 2010; y: 2 }
////                  XYPoint { x: 2011; y: 1 }
////              }
////          }
//    }














////    property var linePoints: [Qt.point(10, 10), Qt.point(20, 20)]
//    property var  linePoints: [[0, 0, 10, 10, 20, 20, 30, 30, 40, 40], [0, 0, 10, 20, 20, 40, 30, 60]]

//    ChartView {
//        id: chartView
//          title: "Line"
//          anchors.fill: parent
//          antialiasing: true

//          // 坐标系范围
//          ValueAxis {
//              id: xAxis
//              min: 0
//              max: 50
//          }
//          ValueAxis {
//              id: yAxis
//              min: 0
//              max: 40
//              tickCount: 3  // 分割3大份
//              minorTickCount: 5  // 每大份分割5小份
//          }

////          LineSeries {
////              name: "LineSeries"
////              XYPoint { x: 0; y: 0 }
////              XYPoint { x: 1.1; y: 2.1 }
////              XYPoint { x: 1.9; y: 3.3 }
////              XYPoint { x: 2.1; y: 2.1 }
////              XYPoint { x: 2.9; y: 4.9 }
////              XYPoint { x: 3.4; y: 3.0 }
////              XYPoint { x: 4.1; y: 3.3 }
////          }
//      }


//    Button {
//        id: btn
//        x: 500
//        width: 50
//        height: 50
//        onClicked: {
////            var pie = chartView.createSeries(ChartView.SeriesTypePie, "MyPie")
////            pie.append("pie1", 50)
////            pie.append("pie2", 100)

////            var line = chartView.createSeries(ChartView.SeriesTypeLine, "MyLine", xAxis, yAxis)
//////            line.append(10, 10)
//////            line.append(20, 20)
////            for(var i = 0; i < linePoints.length; i ++) {
////                line.append(linePoints[i].x, linePoints[i].y)
////            }

////            for(var i = 0; i < linePoints.length; i ++){
////                var line = chartView.createSeries(ChartView.SeriesTypeLine, "MyLine", xAxis, yAxis)
////                line.style = Qt.DotLine  // 线型
////                var points = linePoints[i]
////                for(var j = 0; j < points.length; j += 2){
////                    line.append(points[j], points[j + 1])
////                }
////            }

//            var line = chartView.createSeries(ChartView.SeriesTypeSpline, "MyLine", xAxis, yAxis)   // 曲线
//            for(var i = 0; i < 10; i ++){
//                line.append(i, i ** 2)
//            }
//        }
//    }












//    Button {
//        x: 500
//        height: 50
//        width: 50
//        onClicked: {
//            var slice = pieSeries.append("mySlice", 50)
//            slice.borderColor = "transparent"
//            slice.borderWidth = 0
//            slice.labelVisible = true
//            slice.labelPosition = PieSlice.LabelInsideHorizontal
//        }
//    }

//    ChartView {
//        width: 400
//        height: 400
//        theme: ChartView.ChartThemeBrownSand  // 背景主题
//        antialiasing: true  // 抗锯齿
////        scale: 3
////        legend.visible: false // b不显示图例
//        legend.alignment: Qt.AlignBottom  // 图例的位置

//        PieSeries {
//            id: pieSeries
////            size: 1  // 默认0.7
////            horizontalPosition: 0.4  // 默认0.5
//            PieSlice {
//                label: "eaten"  // 图例
//                labelVisible: true  // 绘制 饼状图的标签
//                labelArmLengthFactor: 1  // 标签的显示距离
//                labelPosition: PieSlice.LabelInsideNormal  // 标签的显示位置
//                borderColor: "transparent"
//                borderWidth: 0
//                value: 100  // 根据value值，会自动计算所占的比例
//                exploded: true  // 将当前饼状图分离出来
//                explodeDistanceFactor: 0.1  // 分离的距离
//                Component.onCompleted: {
//                    console.log("1: " , angleSpan, percentage, startAngle)  // 当前饼状图所占的角度、百分比、起始角度
//                }
//            }
//            PieSlice {
//                label: "not yet eaten"
//                labelVisible: true
//                borderColor: "transparent"
//                borderWidth: 0
//                value: 50
//                Component.onCompleted: {
//                    console.log("2: " , angleSpan)  // 当前所占的角度
//                }
//            }
//        }
//    }
}
