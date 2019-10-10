import QtQuick 2.12
import Theme 1.0  

Item {
    id: button
    property alias text: buttontext.text
    property bool enabled: true
    width: buttontext.contentWidth + 10
    height: buttontext.contentHeight + 10

    signal clicked()

    Rectangle {
        id: buttonrect
        color: Theme.secondary
        anchors.fill: parent
        
        states: 
        [   
            State {
                name: "enabled"
                when: button.enabled && !mousearea.containsMouse && !mousearea.pressed
                PropertyChanges { target: buttonrect; color: Theme.primary_light; border.color: "transparent" }
                PropertyChanges { target: buttontext; color: Theme.primary_text; }
            },
            State {
                name: "disabled"
                when: !button.enabled
                PropertyChanges { target: buttonrect; color: Theme.primary; border.color: Theme.primary_light; }
                PropertyChanges { target: buttontext; color: Theme.primary_text; }
            },
            State {
                name: "hovered"
                when: button.enabled && mousearea.containsMouse && !mousearea.pressed
                PropertyChanges { target: buttonrect; color: Theme.secondary; border.color: "transparent" }
                PropertyChanges { target: buttontext; color: Theme.secondary_text; }
            },
            State {
                name: "pressed"
                when: button.enabled && mousearea.containsMouse && mousearea.pressed
                PropertyChanges { target: buttonrect; color: Theme.secondary_dark; border.color: "transparent" }
                PropertyChanges { target: buttontext; color: Theme.secondary_text; }
            }
        ]

        transitions: Transition {
            from: ""; to: "down"; reversible: true
            ParallelAnimation {
                ColorAnimation { duration: 200 }
            }
        }

        Label {
            id: buttontext
            anchors.centerIn: parent
        }

        MouseArea {
            id: mousearea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                button.clicked()
            }
        }
    }
}