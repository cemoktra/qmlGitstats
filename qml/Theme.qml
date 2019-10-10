pragma Singleton 
import QtQuick 2.12

Item {
    property bool dark: true

    readonly property color primary:         "#424242"
    readonly property color primary_light:   "#6d6d6d"
    readonly property color primary_dark:    "#1b1b1b"
    readonly property color secondary:       "#ff9800"
    readonly property color secondary_light: "#ffc947"
    readonly property color secondary_dark:  "#c66900"
    readonly property color primary_text:    "#ffffff"
    readonly property color secondary_text:  "#000000"

    readonly property int fontsize: 16
}