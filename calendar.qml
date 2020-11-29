import QtQuick 2.12
import QtQuick.Controls 1.4

import QtQuick.Controls 2.15
import QtQuick.Controls.Private 1.0
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: draggable
    width:main.width
    height: main.height
    //Text{ text:  myModel1.eventsForDate();}

    SystemPalette {
        id: systemPalette
    }

  Calendar {
    id : cal
    width: parent.width
    height:parent.height

    minimumDate: new Date(2017, 0, 1)
    maximumDate: new Date().toLocaleString(Qt.locale("de_DE"),"yyyy.MM.dd")

    selectedDate: selectedday

    locale: Qt.locale("de_DE")
    frameVisible: true
    focus: true
    property int parameterName;

    onClicked:
    {
        onSelectedDateChanged:
        {
            loaderactivate("landingscreen.qml")
            selectedday = selectedDate
            datechanged(selectedDate.toLocaleString(Qt.locale("de_DE"),"yyyy-MM-dd"));
        }
    }



           /* Image {
                visible:if(myModel1.eventDate.getDate()==styleData.date.getDate()) { "test1" } else { "Test2" }
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: -1
                width: 12
                height: width
                source:"qrc:/logo-min.png"
            }*/


        }
    }

