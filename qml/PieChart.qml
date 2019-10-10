import QtQuick 2.12
import Theme 1.0  

Item {
    id: piechart
    anchors.fill: parent
    property alias model: repeater.model
    property string textprop
    property string valueprop
    property string maxprop

    Repeater {
        id: repeater
        anchors.fill: parent
        property double currentArcStart: 0.0
        property double centerx: x + width / 2
        property double centery: y + height / 2
        property double radius: Math.min(width / 2, height / 2)
        
        Canvas {
            id: pichartcanvas
            z: 1
            anchors.fill: parent
            property double arcStart
            property double arcEnd
            property string author
            property double percent
            
            onPaint: {
                var ctx = getContext("2d");
                ctx.globalAlpha = (repeater.count - index) / repeater.count
                ctx.fillStyle = Theme.secondary_dark

                ctx.beginPath()
                ctx.moveTo(repeater.centerx, repeater.centery);
                ctx.arc(repeater.centerx, repeater.centery, repeater.radius, arcStart * Math.PI * 2.0, arcEnd * Math.PI * 2.0)
                ctx.lineTo(repeater.centerx, repeater.centery);
                ctx.fill();

                var x_ = repeater.centerx + (repeater.radius / 2)
                var y_ = repeater.centery
                var x_2 = x_ - repeater.centerx
                var y_2 = y_ - repeater.centery

                var s = Math.sin((arcStart + ((arcEnd - arcStart) / 2.0)) * Math.PI * 2.0);
                var c = Math.cos((arcStart + ((arcEnd - arcStart) / 2.0)) * Math.PI * 2.0);

                author.posx = (x_2 * c - y_2 * s) + repeater.centerx
                author.posy = (x_2 * s - y_2 * c) + repeater.centery
            }

            Component.onCompleted: {
                arcStart = repeater.currentArcStart
                arcEnd = repeater.currentArcStart + (model[piechart.valueprop].toFixed(2) / model[piechart.maxprop].toFixed(2))
                author = model[piechart.textprop]
                percent = ((arcEnd - arcStart) * 100).toFixed(2)
                repeater.currentArcStart = repeater.currentArcStart + (model[piechart.valueprop].toFixed(2) / model[piechart.maxprop].toFixed(2));
            }

            MouseArea {
                id: mousearea
                anchors.fill: parent
                hoverEnabled: true

                onPositionChanged:
                {
                    var x1 = mouseX - repeater.centerx
                    var y1 = mouseY - repeater.centery
                    var distance = Math.sqrt(x1 * x1 + y1 * y1)
                    var x2 = repeater.radius / 2
                    var y2 = 0
                    var xy = (x1 * x2 + y1 * y2) / (Math.sqrt(x1 * x1 + y1 * y1) * Math.sqrt(x2 * x2 + y2 * y2))
                    var angle = Math.acos(xy)
                    if (mouseY < repeater.centery)
                        angle = 2 * Math.PI - angle
                    angle = angle / (2 * Math.PI)
                    
                    tooltip.visible = false
                    for (var i = 0; i < repeater.count; i++)
                    {
                        if (distance < repeater.radius && angle > repeater.itemAt(i).arcStart && angle < repeater.itemAt(i).arcEnd)
                        {
                            tooltip.text = repeater.itemAt(i).author + " [" + repeater.itemAt(i).percent + "%]"
                            tooltip.visible = true
                            tooltip.x = mouseX
                            tooltip.y = mouseY - tooltip.contentHeight
                            return
                        }
                    }
                }
            }
        }
    }

    Label {
        id: tooltip
        z: 10
        pixelSize: 10
    }

}