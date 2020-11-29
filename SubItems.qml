import QtQuick 2.14
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.1

Rectangle {
    id : ssubItems
    y: 15
    width: articleName.width


    property var sindex: 0

    Column {
        spacing: 10
        Repeater {
            model: myModel1.subitemsInfo
            delegate:
                Row{
                Rectangle {
                    width: articleName.width; height: 10
                    color: "transparent"
                    visible: {
                        if( (myModel1.itemsInfo[sindex].ArticleNo === myModel1.subitemsInfo[index].Itemid)
                                && (myModel1.itemsInfo[sindex].UniqueIdentifier === myModel1.subitemsInfo[index].UniqueIdentifier) ){

                            const result = myModel1.subitemsInfo.filter(word => word.Itemid === myModel1.itemsInfo[sindex].ArticleNo);

                            articleName.height = 85 + result.length;

                            return true;
                        }
                        return false;
                    }

                    Text{
                        text: " + " + myModel1.subitemsInfo[index].ArticleName
                        x: 40
                        y:  10;
                        font.family: "Helvetica"
                        font.pointSize: 10
                        anchors.horizontalCenter: parent.Left
                    }
                }
                Rectangle {
                    x : articleName.width
                    width: articleName.width/12; height: 10
                    color: "transparent"
                    visible: {

                        if( (myModel1.itemsInfo[sindex].ArticleNo === myModel1.subitemsInfo[index].Itemid)
                                && (myModel1.itemsInfo[sindex].UniqueIdentifier === myModel1.subitemsInfo[index].UniqueIdentifier)){

                            const result = myModel1.subitemsInfo.filter(word => word.Itemid === myModel1.itemsInfo[sindex].ArticleNo);

                            // console.log("myModel1.itemsInfo[sindex].ArticleNo  " + myModel1.itemsInfo[sindex].ArticleNo);

                            //articleName.height = 40 * result.length;
                            articleName.height = 85 + result.length;
                            console.log("articleName.height  " + articleName.height);

                            return true;
                        }
                        return false;
                    }

                    Text{
                        text: " + " + parseFloat(myModel1.subitemsInfo[index].UnitPrice).toFixed(2)
                        x : 20
                        y:  10;
                        font.family: "Helvetica"
                        font.pointSize: 10
                        anchors.horizontalCenter: parent.Left
                    }
                }
            }
        }
    }
}


