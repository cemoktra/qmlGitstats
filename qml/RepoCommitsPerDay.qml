import QtQuick 2.12
import QtQuick.Layouts 1.12

Item {
    // PieChart {
    //     anchors.fill: parent
    //     textprop: "weekday"
    //     valueprop: "commits"
    //     totalprop: "totalCommits"
    //     model: repoObj.getCommitsPerDay()
    // }

    BlockChart {
        anchors.fill: parent
        textprop: "weekday"
        valueprop: "commits"
        maxprop: "maxCommits"
        totalprop: "totalCommits"
        model: repoObj.getCommitsPerDay(20)
    }    
}