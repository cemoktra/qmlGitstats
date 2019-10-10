import QtQuick 2.12
import Theme 1.0  

Item {
    id: label
    property alias text: labeltext.text
    property alias color: labeltext.color
    property alias contentWidth: labeltext.contentWidth
    property alias contentHeight: labeltext.contentHeight
    property alias pixelSize: labeltext.font.pixelSize

    width: contentWidth
    height: contentHeight

    Text {
        id: labeltext
        color: Theme.primary_text
        anchors.centerIn: parent
        font.pixelSize: Theme.fontsize
    }
}