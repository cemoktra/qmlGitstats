import QtQuick 2.12
import QtQuick.Window 2.12
import Theme 1.0  

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("gitstats")
    color: Theme.primary

    Loader {
        anchors.fill: parent
        anchors.margins: 5
        source: repoObj.open ? "qrc:/qml/Repo.qml" : "qrc:/qml/OpenRepo.qml"
    }
}

