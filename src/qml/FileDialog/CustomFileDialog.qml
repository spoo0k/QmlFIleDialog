import QtQuick 2.15

Rectangle{
    id:baseItem
    signal accepted();
    signal regected();
    width: 600
    height:600
    color: "lightgrey"
    anchors.centerIn: parent
    radius: 10

}
