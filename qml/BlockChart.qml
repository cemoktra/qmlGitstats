import QtQuick 2.12
import QtQuick.Layouts 1.12
import Theme 1.0  

Item {
    id: blockchart
    anchors.fill: parent
    property alias model: repeater.model
    property string textprop
    property string valueprop
    property string maxprop
    property string totalprop

    RowLayout {
        id: layout
        anchors.fill: parent
        spacing: 5

        Repeater {
            id: repeater
            Rectangle {
                opacity: 0.25 + ((repeater.count - index) / (2 * repeater.count))
                color: Theme.secondary_dark
                border.color: Theme.secondary

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignBottom
                Layout.maximumHeight: model[blockchart.valueprop].toFixed(2) / model[blockchart.maxprop].toFixed(2) * parent.height

                MouseArea {
                    id: mousearea
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        tooltiprow1.text = model[blockchart.textprop]
                        tooltiprow2.text = model[blockchart.valueprop] + " commits (" + (model[blockchart.valueprop].toFixed(2) / model[blockchart.totalprop].toFixed(2) * 100.0).toFixed(2) + "%)"
                        tooltip.visible = true
                        tooltip.x = parent.x + mouseX
                        tooltip.y = parent.y + mouseY
                        cursorShape = Qt.BlankCursor
                    }
                    onExited: {
                        tooltip.visible = false
                        cursorShape = Qt.NormalCursor
                    }
                    onPositionChanged: {
                        tooltip.x = parent.x + mouseX
                        tooltip.y = parent.y + mouseY
                    }
                }
            }
        }       
    }

    Item {
        id: tooltip
        z: 10
        ColumnLayout {
            Label {
                id: tooltiprow1
                pixelSize: 10
                Layout.minimumWidth: contentWidth
                Layout.minimumHeight: contentHeight
                Layout.alignment: Qt.AlignHCenter
            }
            Label {
                id: tooltiprow2
                pixelSize: 8
                Layout.minimumWidth: contentWidth
                Layout.minimumHeight: contentHeight
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }
}