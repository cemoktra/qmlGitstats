import QtQuick 2.12
import QtQuick.Layouts 1.12

Item {
    ListView {
        anchors.fill: parent
        spacing: 0
        model: repoObj.getCommitsPerDay()

        delegate: Label {                
            text: model.weekday + ": " + model.commits + " commits"
        }
    }
}