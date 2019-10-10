import QtQuick 2.12
import Theme 1.0  

Item {
    id: tabbaritem
    property alias text: itemtext.text
    property bool active: false
    property int contentHeight: itemtext.contentHeight + 6
    property int contentWidth: itemtext.contentWidth + 20

    signal clicked()
    height: contentHeight
    width: contentWidth

    Rectangle {
        id: itemrect
        color: "transparent"
        anchors.fill: parent
        
        states: 
        [   
            State {
                name: "active"
                when: tabbaritem.active && !mousearea.containsMouse
                PropertyChanges { target: itembottomrect; color: Theme.secondary; }
                PropertyChanges { target: itemtext; color: Theme.primary_text; }
            },
            State {
                name: "active_hovered"
                when: tabbaritem.active && mousearea.containsMouse
                PropertyChanges { target: itembottomrect; color: Theme.secondary_light; }
                PropertyChanges { target: itemtext; color: Theme.secondary_light; }
            },
            State {
                name: "inactive"
                when: !tabbaritem.active && !mousearea.containsMouse
                PropertyChanges { target: itembottomrect; color: Theme.primary_light; }
                PropertyChanges { target: itemtext; color: Theme.primary_text; }
            },
            State {
                name: "inactive_hovered"
                when: !tabbaritem.active && mousearea.containsMouse
                PropertyChanges { target: itembottomrect; color: Theme.secondary_light; }
                PropertyChanges { target: itemtext; color: Theme.secondary_light; }
            }
        ]

        transitions: Transition {
            from: ""; to: "down"; reversible: true
            ParallelAnimation {
                ColorAnimation { duration: 200 }
            }
        }

        Rectangle {
            id: itembottomrect
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 3
        }


        Label {
            id: itemtext
            anchors.centerIn: parent
        }

        MouseArea {
            id: mousearea
            hoverEnabled: true
            anchors.fill: parent
            onClicked: {
                tabbaritem.clicked()
            }
        }
    }
}