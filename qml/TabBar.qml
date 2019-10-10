import QtQuick 2.12
import QtQuick.Layouts 1.12
import Theme 1.0  

Item {
    id: tabBar
    height: 30
    
    property string selectedHeader
    property string selectedSource
    property int selected: -1

    QtObject {
        id: privates
        property variant sources: []
        property variant texts: []
    }

    function addTabItem(source, text)
    {
        privates.sources.push(source)
        privates.texts.push(text)
        repeater.model = privates.sources.length
    }

    function select(item)
    {
        selected = item
        selectedHeader = privates.texts[item]
        selectedSource = privates.sources[item]
    }

    RowLayout {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        
        Repeater {
            id: repeater
            model: privates.sources.length
            TabBarItem {
                Layout.preferredWidth: contentWidth
                Layout.preferredHeight: contentHeight
                Layout.maximumWidth: contentWidth
                Layout.fillWidth: true
                text: privates.texts[index]
                active: tabBar.selected == index
                onClicked: {
                    select(index)
                }
            }
        }
    }
}