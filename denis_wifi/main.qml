import QtQuick 2.13
import QtQuick.Controls 2.13
import QtCharts 2.3
import itu.fit.vutbr.cz 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    width: 1000
    height: 700
    title: qsTr("NetApp")

    Page {
        id: page
        anchors.fill : parent
        Text {
            id: element
            x: 105
            y: 100
            width: 241
            height: 41
            color: "#ffffff"
            text: qsTr("Network SSID")
            styleColor: "#ffffff"
            font.bold: true
            fontSizeMode: Text.VerticalFit
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenterOffset: -56
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 91
            font.pixelSize: 20
        }

        Rectangle {
            id: rectangle1
            x: 456
            width: 231
            height: 211
            color: "#ffffff"
            radius: 50
            anchors.right: parent.right
            anchors.rightMargin: 13
            anchors.top: parent.top
            anchors.topMargin: 24
            border.width: 0
            opacity: 0.4

            Text {
                id: element1
                x: 0
                width: 200
                height: 45
                color: "#ffffff"
                text: qsTr("Network Information")
                elide: Text.ElideNone
                opacity: 1
                textFormat: Text.AutoText
                fontSizeMode: Text.HorizontalFit
                font.family: "Tahoma"
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 19
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 13
            }
        }

        Text {
            id: element2
            x: 487
            y: 88
            width: 114
            height: 14
            color: "#ffffff"
            text: qsTr("Channel:")
            horizontalAlignment: Text.AlignRight
            font.bold: true
            anchors.right: parent.right
            anchors.rightMargin: 99
            anchors.top: rectangle1.top
            anchors.topMargin: 67
            font.pixelSize: 12

            Text {
                id: element9
                x: 64
                y: 0
                height: 14
                color: "#ffffff"
                text: qsTr("1")
                anchors.left: parent.right
                anchors.leftMargin: 6
                font.pixelSize: 12
            }

            Text {
                id: element3
                width: 112
                height: 14
                color: "#ffffff"
                text: qsTr("Avr. Signal Str.:")
                font.bold: true
                horizontalAlignment: Text.AlignRight
                anchors.left: parent.left
                anchors.leftMargin: 2
                anchors.top: parent.bottom
                anchors.topMargin: 3
                font.pixelSize: 12

                Text {
                    id: element10
                    y: 0
                    width: 53
                    height: 15
                    color: "#ffffff"
                    text: qsTr("-53 dBm")
                    anchors.left: parent.right
                    anchors.leftMargin: 6
                    font.pixelSize: 12
                }
            }

            Text {
                id: element4
                width: 117
                height: 15
                color: "#ffffff"
                text: qsTr("Frequency:")
                horizontalAlignment: Text.AlignRight
                font.bold: true
                anchors.left: parent.left
                anchors.leftMargin: -3
                anchors.top: element3.bottom
                anchors.topMargin: 3
                font.pixelSize: 12

                Text {
                    id: element11
                    y: 0
                    color: "#ffffff"
                    text: qsTr("2.4GHz")
                    anchors.left: parent.right
                    anchors.leftMargin: 6
                    font.pixelSize: 12
                }
            }
        }

        ProgressBar {
            id: progressBar
            x: 161
            y: 172
            width: appWindow.width - 450
            height: 38
            transformOrigin: Item.Left
            enabled: false
            indeterminate: false
            value: 0.5
        }

        Text {
            id: element5
            x: 9
            y: 183
            width: 146
            height: 17
            color: "#ffffff"
            text: qsTr("Signal Strength [ dBm ]")
            horizontalAlignment: Text.AlignRight
            fontSizeMode: Text.Fit
            font.pixelSize: 14
        }

        ProgressBar {
            id: progressBar1
            x: 161
            y: 216
            width: appWindow.width - 450
            height: 38
            value: 0.5
            enabled: false
            indeterminate: false
        }

        Text {
            id: element6
            x: 9
            y: 225
            width: 146
            height: 20
            color: "#ffffff"
            text: qsTr("Link Quality [ % ]")
            horizontalAlignment: Text.AlignRight
            fontSizeMode: Text.FixedSize
            font.pixelSize: 13
        }

        ChartView {
            id: chartView
            x: 50
            y: 284
            width: appWindow.width - 50
            height: appWindow.height - 350
            theme: ChartView.ChartThemeDark
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 42
            anchors.horizontalCenter: parent.horizontalCenter
            LineSeries {
                id: chart
                axisY: ValueAxis {
                    min: 0
                    max: 100
                }
                axisX: ValueAxis{
                    min: 0
                    max: 10
                }
                name: "Signal Strength"
            }
            Timer{
                interval: 1500; repeat: true; running: true
                onTriggered: {
                    backEnd.update(chartView.series(0))
                }
            }
        }

        Text {
            id: element7
            y: 185
            width: 34
            height: 15
            color: "#ffffff"
            text: qsTr("50%")
            anchors.left: progressBar.right
            anchors.leftMargin: 10
            font.pixelSize: 12
        }

        Text {
            id: element8
            y: 228
            color: "#ffffff"
            text: qsTr("50 %")
            anchors.left: progressBar1.right
            anchors.leftMargin: 10
            font.pixelSize: 12
        }

        Text {
            id: element12
            x: 56
            y: 55
            text: chart.count
            font.pixelSize: 12
        }
    }
    Timer{
        interval: 500; repeat:true; running: true

        onTriggered: function deleteGraph() {
            chart.replace(y0.x,y0.y,y0.x,y1.y)
            chart.replace(y1.x,y1.y,y1.x,y2.y)
            chart.replace(y2.x,y2.y,y2.x,y3.x)
        }
    }
    BackEnd{
        id: backEnd
    }
}
