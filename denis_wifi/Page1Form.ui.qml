import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.0
import QtCharts 2.3

Page {
    id: page
    width: 700
    height: 500

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
            text: qsTr("Network Speed:")
            font.bold: true
            horizontalAlignment: Text.AlignRight
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: parent.bottom
            anchors.topMargin: 3
            font.pixelSize: 12

            Text {
                id: element10
                color: "#ffffff"
                text: qsTr("120 Mb/s")
                anchors.fill: parent
                font.pixelSize: 12
            }
        }

        Text {
            id: element4
            width: 117
            height: 15
            color: "#ffffff"
            text: qsTr("Encryption Type:")
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
                text: qsTr("WPA")
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
        text: qsTr("Signal Strength [ mBm ]")
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
        id: line
        x: 50
        y: 284
        width: tabBar.width - 50
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

            name: "Signal Strength"
            XYPoint {
                id: y0
                x: 0
                y: 1
            }

            XYPoint {
                id: y1
                x: 1
                y: 1.2
            }

            XYPoint {
                id: y2
                x: 2
                y: 3.3
            }

            XYPoint {
                id: y3
                x: 5
                y: 2.1
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
