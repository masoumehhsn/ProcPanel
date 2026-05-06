import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels

Flickable {
    id: flick
    // anchors.fill: parent

    contentWidth: width
    contentHeight: height

    clip: true
    property int selected_pid: -1

    Column {
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        // HEADER

        HorizontalHeaderView {
            id: header
            syncView: table
            clip: true
            height: 40
            width: parent.width

            delegate: Rectangle {
                implicitHeight: 40
                border.width: 1
                property int sortOrder: Qt.AscendingOrder
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#E0E0E0" }
                    GradientStop { position: 0.5; color: "#CACACA" }
                    GradientStop { position: 1.0; color: "#B5B5B5" }
                }

                Text {
                    property string arrow: {
                        if(table.sortColumn == index)
                            if(table.sortOrder == Qt.AscendingOrder)
                                " ▵"
                            else
                                " ▿"
                        else
                            ""
                    }

                    anchors.centerIn: parent
                    text: display+ arrow
                    color: "#444444"
                    font.bold: true
                    id: mainTxt
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if (table.sortColumn === index) {
                                    // same column → toggle
                                    table.sortOrder = table.sortOrder === Qt.AscendingOrder
                                                      ? Qt.DescendingOrder
                                                      : Qt.AscendingOrder
                                } else {
                                    // new column → reset to ascending
                                    table.sortColumn = index
                                    table.sortOrder = Qt.AscendingOrder
                                }

                                procManager.sort(table.sortColumn, table.sortOrder)

                                console.log("Column:", table.sortColumn,
                                            "Order:", table.sortOrder === Qt.AscendingOrder ? "ASC" : "DESC")
                    }
                }
            }
        }

        // TABLE
        TableView {
            id: table
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.VerticalFlick
            height: parent.height*0.9
            width: parent.width
            model: procManager.procModel
            clip: true
            property int sortColumn: -1
            property int sortOrder: Qt.AscendingOrder
            columnWidthProvider: function(column) {
                switch (column) {
                case 0: return 80    // PID
                case 1: return 300   // Name
                case 2: return 100   // State
                case 3: return 180   // Memory
                default: return 100
                }
            }
            property int selectedRow: -1
            delegate: Rectangle {
                Rectangle{
                    width: parent.width
                    height: table.selectedRow === row ? 1.2:1
                    anchors.top: parent.top
                    color: table.selectedRow === row ? "#2c27bc" : "#877d7d"
                }
                Rectangle{
                    width: parent.width
                    height: table.selectedRow === row ? 1.2:1
                    anchors.bottom: parent.bottom
                    color: table.selectedRow === row ? "#2c27bc" : "#d6cfcf"
                }
                implicitHeight: 35
                border.width: 0.5
                border.color: "#877d7d"
                color: row% 2 == 0? "white": "lightgray"
                Text {
                    anchors.centerIn: parent
                    text: display
                    font.bold: table.selectedRow === row ? true : false

                    font.pixelSize: table.selectedRow === row? 14 :13
                }

                TapHandler {
                    onTapped: table.selectedRow = row
                }
                MouseArea{
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                    onClicked: function(mouse) {
                        var p = mapToItem(null, mouse.x, mouse.y) // window coords
                        menu.x = p.x
                        menu.y = p.y
                        menu.open()
                        table.selectedRow = row
                        selected_pid = pid

                        console.log("PID:", pid)
                    }

                }
            }
            }

        }


    // }
    Menu {
        id: menu

        MenuItem {
            text: "Pause/Stop"
            onTriggered: procManager.stopProc(selected_pid)
        }
        MenuItem {
            text: "Terminate"
            onTriggered: procManager.terminateProc(selected_pid)
        }
        MenuItem {
            text: "Resume"
            onTriggered: procManager.resumeProc(selected_pid)
        }
    }

    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AsNeeded
    }

}