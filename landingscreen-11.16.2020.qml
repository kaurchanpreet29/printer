import QtQuick 2.14

Rectangle {
    id : landingscreen
    width:main.width
    height: main.height
    FontLoader { id: fixedFont; name: "Courier" }

    Rectangle {
        id : title
        width: landingscreen.width
        height: 50
        anchors.topMargin: 0

        Rectangle {
            id : dateTime
            width: parent.width
            height : parent.height
            radius : 0
            border.width: 1
            color: "#af215e"

            Text{
                x: parent.width * 0.005
                y: parent.height * 0.02
                text: currdate + " " + currtime + "  Uhr"
                font.family: "Helvetica"
                font.pointSize: 15
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
            }

            Image {
                id: image
                height: parent.height
                source: "calendar.png"
                fillMode: Image.PreserveAspectFit
                anchors.right: parent.right
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    //loaderactivate("calendar.qml",300)
                    loader.setSource("calendar.qml")
                }
            }
        }
    }

    Flow {
      id:displayOrder
      width: parent.width
      flow:Flow.LeftToRight
      y: 60
      x:10
      spacing: 20

        Rectangle{
           id: all
           width: 80
           height:40
           Text {
               anchors.fill: parent
               text:"All"
               color: "#8c0808"
               font.pointSize: 16
               font { family: fixedFont.name;  capitalization: Font.Capitalize }
           }
           MouseArea {
               anchors.fill: parent
               onClicked: {
                     all_Records()
               }
           }
        }

     /*   Rectangle{
           id: fleksa
           width: 120
           height:40
           anchors.left: all.right;
           Text {
               anchors.fill: parent
               text:"Fleksa"
               color: "#8c0808"
               font.pointSize: 16
               font { family: fixedFont.name;  capitalization: Font.Capitalize }
           }
           MouseArea {
               anchors.fill: parent
               onClicked: {
                     records(0)
               }
           }
        }

    Rectangle {
       id: primalieferung
       width: 200
       height:40
       anchors.left: fleksa.right;
       Text {
           anchors.fill: parent
           text:"Primalieferung"
           color: "#8c0808"
           font.pointSize: 16
           font { family: fixedFont.name;  capitalization: Font.Capitalize }
       }
       MouseArea {
           anchors.fill: parent
           onClicked: {
                 records(1)
           }
       }
    }

    Rectangle{
       id: lieferando
       width: 200
       height:40
       anchors.left: primalieferung.right;
       Text {
           anchors.fill: parent
           text:"Lieferando"
           color: "#8c0808"
           font.pointSize: 16
           font { family: fixedFont.name;  capitalization: Font.Capitalize }
       }
    }*/
}

    Rectangle {
        id:cards
        width: parent.width
        height: parent.height - 160
        y: 100

        Component {
            id: contactDelegate

            OrderBar {
                width: cards.width *.99
                height : cards.height * 1/3.5
                sIndex : index
                radius : 0
                stylecolor : "#af215e"
            }
        }

        ListView {
            anchors.fill: cards
            model: myModel1.orderInfo
            clip : true
            spacing: 20
            delegate: contactDelegate
        }
    }

    Rectangle {
        id : footer
        y: parent.height -50
        width: parent.width
        height: 50
        radius : 0
        border.width: 1
        color: "#af215e"

        Text{
            x: parent.width * 0.005
            y: parent.height * 0.02
            text: "KHANA Kassensysteme GmbH, Frankfurt am Main "

            font.family: "Helvetica"
            font.pointSize: 15
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter:  parent.horizontalCenter

            color: "white"
        }
    }
}

