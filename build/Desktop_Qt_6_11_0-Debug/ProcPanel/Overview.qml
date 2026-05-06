import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts 2.15

ColumnLayout {
    property int xCpu: 0
    property int xMem: 0
    TabBar {
        id: tabBar
        Layout.fillWidth: true

        TabButton { text: "Cpu" }
        TabButton { text: "Memory" }
    }

    StackLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        currentIndex: tabBar.currentIndex

        ChartView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            title: "CPU Usage (%)"
            antialiasing: true

            ValueAxis { id: cpuAxisY; min: 0; max: 100 }
            ValueAxis { id: cpuAxisX; min: 0; max: 50 }

            LineSeries {
                id: cpuSeries
                axisX: cpuAxisX
                axisY: cpuAxisY
            }
        }

        // 🔥 This is the important part
        ChartView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            title: "Memory Usage (%)"
            antialiasing: true

            ValueAxis { id: memAxisY; min: 0; max: 100 }
            ValueAxis { id: memAxisX; min: 0; max: 50 }

            LineSeries {
                id: memSeries
                axisX: memAxisX
                axisY: memAxisY
            }
        }
        // ================= UPDATES =================

        Rectangle {
            color: "lightcoral"
            Label { anchors.centerIn: parent; text: "Content 3" }
        }
    }
    Connections {
        target: procManager

        // 🔵 CPU updates
        function onCpuUsageChanged() {
            cpuSeries.append(xCpu, procManager.cpuUsage)
            xCpu++

            if (cpuSeries.count > 50)
                cpuSeries.remove(0)

            cpuAxisX.min = Math.max(0, xCpu - 50)
            cpuAxisX.max = xCpu
        }

        // 🟢 MEMORY updates
        function onMemUsageChanged() {
            memSeries.append(xMem, procManager.memUsage)
            xMem++

            if (memSeries.count > 50)
                memSeries.remove(0)

            memAxisX.min = Math.max(0, xMem - 50)
            memAxisX.max = xMem
        }
    }
}
