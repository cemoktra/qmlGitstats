import QtQuick 2.12

Item {
    anchors.fill: parent


    TabBar {
        id: tabBar
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right

        Component.onCompleted: {
            tabBar.addTabItem("qrc:/qml/RepoAuthors.qml", "Authors")
            tabBar.addTabItem("qrc:/qml/RepoCommitsPerDay.qml", "Weekday")
            tabBar.select(0)
        }
    }

    Loader {
        id: loader
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: tabBar.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom

        source: tabBar.selectedSource
    }
}