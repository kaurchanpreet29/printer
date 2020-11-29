import QtQuick.Controls 1.3
import QtQuick 2.14

Rectangle{
    id: busyIndication
    x:main.width/36
    y:main.height/36
    width: main.width - main.width/12
    height: main.height -main.height/12
    visible: true
    color: "Transparent"

BusyIndicator {
   id: busyIndication1
   width: parent.width * 0.5
   height: parent.height * 0.5

   anchors.horizontalCenter: parent.horizontalCenter
   anchors.verticalCenter: parent.verticalCenter
}
}
