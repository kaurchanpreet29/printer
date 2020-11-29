
import QtQuick 2.14
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.1

Rectangle {
    id: ms
    x:main.width/36
    y:main.height/36
    width: main.width - main.width/12
    height: main.height -main.height/12
    visible: true
    radius: 10
    property var sIndex
    property var sIndex1 : 0;
    FontLoader { id: fixedFont; name: "Courier" }

    //FontLoader { id: webFont; source: "http://www.princexml.com/fonts/steffmann/Starburst.ttf" }

    Rectangle {
        id: close
        x: ms.width - ms.width/12
        width: ms.width /12
        height:ms.height/12
        radius: 10

        Image {
            width: close.width
            height: close.height
            source: "close.png"
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {  pp.close() }
        }
    }

    Rectangle {
        id: title
        x: ms.width *.35
        width: ms.width /12
        height:ms.height/12
        radius: 10

        Text{
            text: "Order No " + orderid_text + "<br><b>" + myModel1.orderInfoS[sIndex1].Sender + "</b>"
            x: 10
            y:  10
            font { family: fixedFont.name;  capitalization: Font.Capitalize }
            font.pointSize: 10
            anchors.horizontalCenter: parent.Left
        }
    }


    Rectangle {
        id : shoppingcart
        y:  ms.height/12
        width: parent.width
        height : ms.height - (ms.height * 3/11)

        Flickable {
            id: flick2
            anchors.bottomMargin: 0
            clip : true
            focus: true
            anchors.fill: shoppingcart
            contentHeight: grid2.height

            GridLayout {
                id: grid2
                rowSpacing: 20
                columns: 1
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                Layout.columnSpan: 2
                height: implicitHeight

                Column {

                    Pane {
                        id: box1

                        GridLayout {
                            columns: 2

                            Rectangle {
                                id:first
                                implicitHeight: kunde.height + 10
                                Layout.preferredWidth: ms.width/2
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                color: "#edf2ee"

                                Text {
                                    y:10
                                    x:10
                                    font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                    font.pointSize: 14
                                    id: kunde
                                    text: "<b> KUNDE </b><br> " + myModel1.orderInfoS[sIndex1].FirstName + " " + myModel1.orderInfoS[sIndex1].LastName + "<br>" + myModel1.orderInfoS[sIndex1].Street + " " + myModel1.orderInfoS[sIndex1].HouseNo + " <br> " + myModel1.orderInfoS[sIndex1].Zip + " " + myModel1.orderInfoS[sIndex1].City + " <br> " + myModel1.orderInfoS[sIndex1].Phone
                                }
                            }
                            Rectangle {
                                id:rect2
                                Layout.alignment: Qt.AlignTop
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                GridLayout {
                                    columns: 1
                                    Rectangle { id:first1; implicitHeight: anmerkungen.height + 10; Layout.preferredWidth: 315;
                                        color: "#edf2ee"
                                        Text {
                                            id: anmerkungen
                                            x:10
                                            y:10
                                            font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                            font.pointSize: 14
                                            text: "<b>ANMERKUNGEN</b><br> " + myModel1.orderInfoS[sIndex1].Comment
                                        }
                                    }
                                    Rectangle { id:orange; implicitHeight: lieferzeit.height + 10; Layout.preferredWidth: 315;
                                        Layout.fillHeight: true
                                        color: "#edf2ee"
                                        Text {
                                            id: lieferzeit
                                            x:10
                                            y:10
                                            font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                            font.pointSize: 14
                                            text: if(myModel1.orderInfoS[sIndex1].Time=="") { "<b>LIEFERZEIT </b><br> ASAP " } else { "<b>LIEFERZEIT </b><br> " +  myModel1.orderInfoS[sIndex1].Time + ", " + myModel1.orderInfoS[sIndex1].Date }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                GroupBox {
                    id: control


                    GridLayout  {
                        id:gridid
                        anchors.fill: parent
                        columns: 1

                        Rectangle{
                            height: destelinfo.height / 5
                            width: destelinfo.width + 10
                            Layout.bottomMargin: 15

                            Text {
                                id:destelinfo
                                color: "black"
                                font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                font.pointSize: 14
                                font.bold:true
                                text: "BESTELLINFORMATION"
                                font.underline: true
                            }
                        }

                        Repeater {
                            id: shoppingcartRepeater
                            model: myModel1.itemsInfo

                            delegate:
                                Row {

                               /* Rectangle {
                                    width: ms.width *(1/7);
                                    color: "transparent"
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    implicitHeight: text1.implicitHeight

                                    Text{
                                        id:text1
                                        text: {
                                            //return  myModel1.itemsInfo[index].Count + " x " + myModel1.itemsInfo[index].ArticleNo ;
                                            return myModel1.itemsInfo[index].ArticleNo ;
                                        }
                                        anchors.fill: parent
                                        x: 10
                                        y:  10
                                        font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                        font.pointSize: 14
                                        anchors.horizontalCenter: parent.Right
                                    }
                                }*/
                                Rectangle {
                                    id: articleName
                                    //width: ms.width *(3/6);
                                    width: ms.width *(3/5);
                                    color: "transparent"
                                    Layout.fillHeight: true
                                    implicitHeight: text2.implicitHeight

                                    Text{
                                        id:text2
                                        anchors.fill: parent
                                        text: myModel1.itemsInfo[index].ArticleName
                                        wrapMode: Text.WordWrap
                                        x:10
                                        y:  10;
                                        font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                        font.pointSize: 14
                                        anchors.horizontalCenter: parent.Left
                                    }

                                    SubItems{
                                        sindex : index
                                    }
                                }

                                Rectangle {
                                    width: ms.width *(1/4);
                                    color: "transparent"
                                    Layout.fillHeight: true
                                    implicitHeight: text3.implicitHeight

                                    Text{
                                        id: text3
                                        anchors.fill: parent
                                        text: myModel1.itemsInfo[index].Count + " x (" + parseFloat(myModel1.itemsInfo[index].UnitPrice).toFixed(2) +")"
                                        x: 10
                                        y:  10;
                                        font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                        font.pointSize: 14
                                        anchors.horizontalCenter: parent.Left
                                    }
                                }

                                Rectangle {
                                    width: ms.width *(1/6);
                                    color: "transparent"
                                    Layout.fillHeight: true
                                    implicitHeight: text4.implicitHeight

                                    Text{
                                        id:text4
                                        text: parseFloat(myModel1.itemsInfo[index].Price).toFixed(2) + " €"
                                        anchors.fill: parent
                                        x: 10
                                        y:  10;
                                        font { family: fixedFont.name;  capitalization: Font.Capitalize }
                                        font.pointSize: 14
                                        anchors.horizontalCenter: parent.Left
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        width:ms.width
        color: "green"
        //y: ms.height * (8/10) + ms.height/28
        y: ms.height * (8/10)
        Rectangle {
            id:rect4
            width: ms.width
            anchors.verticalCenter: parent.verticalCenter
            height:parent.height/3
            border.color: "black"
            border.width: 100
            anchors.centerIn: parent

            GridLayout {
                columns: 3
                anchors.fill: parent

                Rectangle {
                    id:rect1
                    width: parent.width/2
                    height:parent.height/3
                    anchors.margins: 10
                    Layout.alignment: Qt.AlignTop
                    border.color: "black"
                    border.width: 100

                    Text {
                        color: "#000"
                        font { family: fixedFont.name;  capitalization: Font.Capitalize }
                        font.pointSize: 14
                        id: first2
                        text: if(myModel1.orderInfoS[sIndex1].PType=='0'){ "Barzahlung"; } else { "Online"; }
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        lineHeight: 1.4
                    }
                }

                ColumnLayout{
                    spacing: 15

                    Rectangle {
                        Layout.alignment: Qt.AlignBottom
                        Layout.preferredWidth: ms.width/7
                        Layout.preferredHeight: 10
                        Text {
                            font { family: fixedFont.name;  capitalization: Font.Capitalize }
                            font.pointSize: 14
                            anchors.right: parent.right
                            anchors.horizontalCenter: parent.Left
                            id: name3
                            text: qsTr("Lieferkosten")
                        }
                    }

                    Rectangle {
                        Layout.alignment: Qt.AlignBottom
                        Layout.preferredWidth: ms.width/7
                        Layout.preferredHeight: 10
                        Text {
                            font { family: fixedFont.name;  capitalization: Font.Capitalize }
                            font.pointSize: 14
                            font.bold: true
                            anchors.right: parent.right
                            anchors.horizontalCenter: parent.Left
                            id: name5
                            text: "Total"
                        }
                    }
                }
                ColumnLayout{
                    spacing: 15

                    Rectangle {
                        Layout.alignment: Qt.AlignRight
                        Layout.preferredWidth: ms.width/7
                        Layout.preferredHeight: 10
                        Text {
                            font { family: fixedFont.name;  capitalization: Font.Capitalize }
                            font.pointSize: 14
                            anchors.right: parent.right
                            text: parseFloat(deliveryCharge).toFixed(2) + " €"
                        }
                    }

                    Rectangle {
                        Layout.alignment: Qt.AlignRight
                        Layout.preferredWidth: ms.width/7
                        Layout.preferredHeight: 10
                        Text {
                            font.bold: true
                            font { family: fixedFont.name;  capitalization: Font.Capitalize }
                            font.pointSize: 14
                            anchors.right: parent.right
                            text: parseFloat(totalofOrder).toFixed(2) + " €"
                        }
                    }
                }
            }
        }
    }


    Rectangle {
        id: print1
        y: ms.height * (10/11)
        x:20
        width: ms.width * (1/6)
        height:ms.height/12
        color:"#7bb587"
        radius: 10
        border.color:"#02771b"
        border.width: 1

        Text{
            text:  "Print"
            x: 10
            y:  10;
            font.family: "Helvetica"
            font.pointSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "green"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                printsignal(orderid_text)
                pp.close()
            }
        }
    }

    Rectangle {
        id :cancel
        x: ms.width - (ms.width* 3/15)
        y: ms.height * (10/11)
        width: ms.width * (1/6)
        height:ms.height/12
        color:"#e87d7d"
        radius: 10
        border.color: "#c91f0c"
        border.width: 1

        Text{
            text:  "Cancel"
            x: 10
            y:  10;
            font.family: "Helvetica"
            font.pointSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "red"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                pp.close()
            }
        }
    }
}

