import QtQuick 2.12
import QtQuick.Layouts 1.12

Item {
    PieChart {
        anchors.fill: parent
        model: repoObj.getTopAuthors(20)
    }
}