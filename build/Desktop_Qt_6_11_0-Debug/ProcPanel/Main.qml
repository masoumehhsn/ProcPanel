import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels
import QtQuick.Layouts
import QtCharts 2.15

ApplicationWindow {
    width: 800
    height: 400
    visible: true

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        TabBar {
            id: tabBar
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            TabButton {
                height: parent.height

                text: "Overview"
            }

            TabButton {
                height: parent.height
                text: "Details"
            }

        }

        StackLayout {
            Layout.fillWidth: true
            // Layout.fillHeight: true
            currentIndex: tabBar.currentIndex
            Overview {
                Layout.fillWidth: true
                Layout.fillHeight: true

            }
            Details{
                Layout.fillWidth: true
                Layout.fillHeight: true

            }

        }
    }


}
