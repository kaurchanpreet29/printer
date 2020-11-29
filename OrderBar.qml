import QtQuick 2.14
import QtQuick.Layouts 1.2

Rectangle {
    id: sensor
    color: stylecolor
    property var sIndex
    property var stylecolor

    GridLayout {
          id: grid
          anchors.fill: sensor
          rows: 6
          columns: 6
          property double colMulti : grid.width / grid.columns
          property double rowMulti : grid.height / grid.rows
          function prefWidth(item){
              return colMulti * item.Layout.columnSpan
          }
          function prefHeight(item){
              return rowMulti * item.Layout.rowSpan
          }

          Rectangle {
               color: "#fa8509"
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 6
               Layout.rowSpan: 1
               Layout.row: 0
               Layout.column: 0
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)

               Text{
                   x: parent.width * .025
                   text: myModel1.orderInfo[sIndex].Updated
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }

               Text{
                   x: (parent.width * .025) + (grid.colMulti * 1)
                   text: myModel1.orderInfo[sIndex].Comment
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }

               Text {
                   property var locale: Qt.locale()
                   property date currentDate: new Date().toLocaleString(Qt.locale("de_DE"),"yyyy-MM-dd")
                   property string dateString
                   dateString : currentDate.toLocaleString(Qt.locale("de_DE"),"yyyy-MM-dd")

                   x: parent.width * 0.825
                   text: if(myModel1.orderInfo[sIndex].OrderDate==dateString) { " " } else { myModel1.orderInfo[sIndex].OrderDate }

                   color: "white"
                   font.family: "Helvetica"
                   font.pointSize: 14
                   anchors.verticalCenter:  parent.verticalCenter
               }
          }

          Rectangle {
               id :rect
               radius: 0
               color: stylecolor
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 1
               Layout.rowSpan: 4
               Layout.row: 1
               Layout.column: 0
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)

               Text{
                   text:  myModel1.get_size_Items() - index
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.horizontalCenter: parent.horizontalCenter
                   y: 10
                   color: "white"
               }

               Image {
                   id: image
                   height: parent.height -20
                   source: {
                       if (myModel1.orderInfo[sIndex].DType === "1") {
                           return "pickup.png"
                          }
                          return "delivery.png"
                      }
                   fillMode: Image.PreserveAspectFit
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.verticalCenter: parent.verticalCenter
               }

               Text{
                   text:  myModel1.orderInfo[sIndex].Time
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.horizontalCenter: parent.horizontalCenter
                   y: parent.height - 30
                   color: "white"
               }
          }

          Rectangle {
               color: "#2227a4"
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 4
               Layout.rowSpan: 1
               Layout.row: 1
               Layout.column: 1
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)

               Text{
                   x: parent.width * .025
                   text: myModel1.orderInfo[sIndex].FirstName + " " + myModel1.orderInfo[sIndex].LastName
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }
          Rectangle {
               color: "#2227a4"
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 4
               Layout.rowSpan: 1
               Layout.row: 2
               Layout.column: 1
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)
               Text{
                   x: parent.width * .025
                   text:  myModel1.orderInfo[sIndex].Street + " " + myModel1.orderInfo[sIndex].HouseNo
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }
          Rectangle {
               color: "#2227a4"
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 4
               Layout.rowSpan: 1
               Layout.row: 3
               Layout.column: 1
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)
               Text{
                   x: parent.width * .025
                   text:  myModel1.orderInfo[sIndex].Zip + " " + myModel1.orderInfo[sIndex].City
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }
          Rectangle {
               color: "#2227a4"
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 4
               Layout.rowSpan: 1
               Layout.row: 4
               Layout.column: 1
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)
               Text{

                   x: parent.width * .025
                   text:  myModel1.orderInfo[sIndex].Phone
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }
         /* Rectangle {
               radius: 20
              // border.width: 1
              color: stylecolor
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 1
               Layout.rowSpan: 4
               Layout.row: 0
               Layout.column: 6
               Text{

                   text:  "Order No. " + myModel1.orderInfo[sIndex].Orderid
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }*/
          Rectangle {
               radius: 0
               color: "#fa8509"
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 1
               Layout.rowSpan: 4
               Layout.row: 1
               Layout.column: 5
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)

              /*  Image {
                  // width: parent.width
                   height: parent.height -20
                   source: "online.png"
                   fillMode: Image.PreserveAspectFit
                   anchors.horizontalCenter: parent.horizontalCenter
                   //anchors.verticalCenter: parent.verticalCenter
                   //  anchors.horizontalCenter: parent.right - 50
                   y: 0

               }*/

               Text{

                   text:  {
                       if (myModel1.orderInfo[sIndex].PType === "1") {
                        return "Online"
                       }
                       return "Bar"
                   }
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.horizontalCenter: parent.horizontalCenter
                   color: "white"
                   y: 30
               }

               Text{
                   text:  parseFloat(myModel1.orderInfo[sIndex].Amount).toFixed(2) + " €"
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.horizontalCenter: parent.horizontalCenter
                   color: "white"
                   y: parent.height - 50
               }

          }


          Rectangle {
               color: stylecolor
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 1
               Layout.rowSpan: 1
               Layout.row: 6
               Layout.column: 0
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)

               Text{
                   x: parent.width * .025
                   text: myModel1.orderInfo[sIndex].Sender
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }

       /*   Rectangle {
               color: stylecolor
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 4
               Layout.rowSpan: 1
               Layout.row: 6
               Layout.column: 1
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)

               Text{
                   x: parent.width * .025
                   text: myModel1.orderInfo[sIndex].FirstName
                   font.family: "Helvetica"
                   font.pointSize: 15
                   //anchors.horizontalCenter: parent.horizontalCenter
                   //anchors.left: parent.left
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }*/

          Rectangle {
               color: stylecolor
               Layout.fillHeight: true
               Layout.fillWidth: true
               Layout.columnSpan: 1
               Layout.rowSpan: 1
               Layout.row: 6
               Layout.column: 5
               Layout.preferredWidth  : grid.prefWidth(this)
               Layout.preferredHeight : grid.prefHeight(this)

               Text{
                   x: parent.width * .025
                   text: "Liefert durch"
                   font.family: "Helvetica"
                   font.pointSize: 15
                   anchors.verticalCenter:  parent.verticalCenter
                   color: "white"
               }
          }
      }


    MouseArea {
        anchors.fill: parent
        onClicked: {

            orderid(myModel1.orderInfo[sIndex].Orderid);
            order(myModel1.orderInfo[sIndex].Orderid);
            orderid_text = myModel1.orderInfo[sIndex].Orderid

            totalofOrder = myModel1.orderInfo[sIndex].Amount

            deliveryCharge = myModel1.orderInfo[sIndex].DCost
            pp.open()
            //loaderactivatep();
        }
    }
}




