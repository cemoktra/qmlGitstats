import QtQuick 2.12

Item {
    Button {
        anchors.centerIn: parent
        text: "Open repository"

        onClicked:
        {
            repoObj.chooseRepository()
        }
    }
}