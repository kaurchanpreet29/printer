#include "local_db_connection.h"

Local_db_connection::Local_db_connection(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE","localSqlLite");
    m_db.setDatabaseName("liefer.sqlite");
}

void Local_db_connection::createTableOrder(QSqlDatabase* p_db)
{
    QSqlQuery qry(*p_db);
    QString query;
    qDebug() << "Creating Table";

    query = "CREATE TABLE  ORDERTABLE ("
            "FIRSTNAME VARCHAR(30),"
            "LASTNAME VARCHAR(30),"
            "TELEPHONE VARCHAR(30),"
            "STREET VARCHAR(30),"
            "HOUSENUMBER VARCHAR(30),"
            "POSTCODE VARCHAR(30),"
            "CITY VARCHAR(30),"
            "ORDERDATE VARCHAR(30),"
            "ORDERPLACEDATE VARCHAR(30),"
            "DELIVERY VARCHAR(30),"
            "DELIVERYTIME VARCHAR(30),"
            "PAYMENTMETHOD VARCHAR(30),"
            "ORDERID VARCHAR(30),"
            "DELIVERYCOST VARCHAR(30),"
            "TOTAL VARCHAR(30),"
            "COMMENT VARCHAR(30),"
            "SENDER VARCHAR(30),"
            "ID INTEGER PRIMARY KEY AUTOINCREMENT"
            ");";

    if(!qry.exec(query))
    {
        qDebug() << "Error in creatingTable()";
    }
}

void Local_db_connection::createTableItems(QSqlDatabase* p_db)
{
    QSqlQuery qry(*p_db);
    QString query;
    qDebug() << "Creating Table";

    query = "CREATE TABLE ITEMTABLE ("
            "ORDERID VARCHAR(30),"
            "ITEMID VARCHAR(30),"
            "NAME VARCHAR(30),"
            "PRICE VARCHAR(30),"
            "UNITPRICE VARCHAR(30),"
            "COUNT VARCHAR(30),"
            "UNIQUE_ID VARCHAR(50)"
            ");";

    if(!qry.exec(query))
    {
        qDebug() << "Error in creatingTable()";
    }
}

void Local_db_connection::createTableSubItems(QSqlDatabase* p_db)
{
    QSqlQuery qry(*p_db);
    QString query;
    qDebug() << "Creating Table";

    query = "CREATE TABLE SUBITEMTABLE ("
            "ORDERID VARCHAR(30),"
            "ITEMID VARCHAR(30),"
            "NAME VARCHAR(30),"
            "PRICE VARCHAR(30),"
            "UNITPRICE VARCHAR(30),"
            "COUNT VARCHAR(30),"
            "UNIQUE_ID VARCHAR(50)"
            ");";

    if(!qry.exec(query))
    {
        qDebug() << "Error in creatingTable()";
    }
}


void Local_db_connection::addOrderEntry(QList<OrderInfo> *p_OrderInfo)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");
    qDebug()<<"addOrderEntry";
    if(!l_db.open())
    {
            qDebug() << "Error opening Database";
    }

    if ( !l_db.tables().contains("ORDERTABLE"))
    {
        createTableOrder(&l_db);
    }

    QSqlQuery qry(l_db);
    qry.prepare("INSERT INTO ORDERTABLE ("
                "FIRSTNAME,"
                "LASTNAME,"
                "TELEPHONE,"
                "STREET,"
                "HOUSENUMBER,"
                "POSTCODE,"
                "CITY,"
                "ORDERDATE,"
                "ORDERPLACEDATE,"
                "DELIVERY,"
                "DELIVERYTIME,"
                "PAYMENTMETHOD,"
                "ORDERID,"
                "DELIVERYCOST,"
                "TOTAL,"
                "SENDER,"
                "COMMENT"
                ")"
                "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);" );

    for (int i = 0; i < p_OrderInfo->size(); i ++)
    {
        qDebug() << p_OrderInfo->at(i).m_FirstName;

        qry.addBindValue(p_OrderInfo->at(i).m_FirstName);
        qry.addBindValue(p_OrderInfo->at(i).m_LastName);
        qry.addBindValue(p_OrderInfo->at(i).m_phoneno);
        qry.addBindValue(p_OrderInfo->at(i).m_street);
        qry.addBindValue(p_OrderInfo->at(i).m_houseno);
        qry.addBindValue(p_OrderInfo->at(i).m_zip);
        qry.addBindValue(p_OrderInfo->at(i).m_city);

        qry.addBindValue(p_OrderInfo->at(i).m_Date);
        qry.addBindValue(p_OrderInfo->at(i).m_OrderDate);

        qry.addBindValue(p_OrderInfo->at(i).m_DType);
        qry.addBindValue(p_OrderInfo->at(i).m_Time);
        qry.addBindValue(p_OrderInfo->at(i).m_PType);
        qry.addBindValue(p_OrderInfo->at(i).m_Orderid);
        qry.addBindValue(p_OrderInfo->at(i).m_DCost);
        qry.addBindValue(p_OrderInfo->at(i).m_Amount);
        qry.addBindValue(p_OrderInfo->at(i).m_Sender);
        qry.addBindValue(p_OrderInfo->at(i).m_Comment);

        if(!qry.exec())
        {
            qDebug() << "Error in addEntry()";
        }
    }


    l_db.close();
}

void Local_db_connection::addItemEntry(QList<ItemsInfo> *p_ItemsInfo)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {
            qDebug() << "Error opening Database";
    }

    if ( !l_db.tables().contains("ITEMTABLE"))
    {
        createTableItems(&l_db);
    }

    QSqlQuery qry(l_db);

    qry.prepare("INSERT INTO ITEMTABLE ("
                "ORDERID,"
                "ITEMID,"
                "NAME,"
                "PRICE,"
                "UNITPRICE,"
                "COUNT,"
                "UNIQUE_ID)"
                "VALUES (?,?,?,?,?,?,?);" );

    for (int i = 0; i < p_ItemsInfo->size(); i ++)
    {
        qry.addBindValue(p_ItemsInfo->at(i).m_Orderid);
        qry.addBindValue(p_ItemsInfo->at(i).m_ArticleNo);
        qry.addBindValue(p_ItemsInfo->at(i).m_ArticleName);
        qry.addBindValue(p_ItemsInfo->at(i).m_Price);
        qry.addBindValue(p_ItemsInfo->at(i).m_UnitPrice);
        qry.addBindValue(p_ItemsInfo->at(i).m_Count);
        qry.addBindValue(p_ItemsInfo->at(i).m_UniqueIdentifier);

        if(!qry.exec())
        {
            qDebug() << "Error in addEntry()";
        }
    }

    l_db.close();
}

void Local_db_connection::addSubItemEntry(QList<SubItemsInfo> *p_SubItemsInfo)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {

            qDebug() << "Error opening Database";
    }

    if ( !l_db.tables().contains("SUBITEMTABLE"))
    {
        createTableSubItems(&l_db);
    }

    QSqlQuery qry(l_db);

    qry.prepare("INSERT INTO SUBITEMTABLE ("
                "ORDERID,"
                "ITEMID,"
                "NAME,"
                "PRICE,"
                "UNITPRICE,"
                "COUNT,"
                "UNIQUE_ID)"
                "VALUES (?,?,?,?,?,?,?);" );
    for (int i = 0; i < p_SubItemsInfo->size(); i ++)
    {
        qry.addBindValue(p_SubItemsInfo->at(i).m_Orderid);
        qry.addBindValue(p_SubItemsInfo->at(i).m_Itemid);
        qry.addBindValue(p_SubItemsInfo->at(i).m_ArticleName);
        qry.addBindValue(p_SubItemsInfo->at(i).m_Price);
        qry.addBindValue(p_SubItemsInfo->at(i).m_UnitPrice);
        qry.addBindValue(p_SubItemsInfo->at(i).m_Count);
        qry.addBindValue(p_SubItemsInfo->at(i).m_UniqueIdentifier);

        if(!qry.exec())
        {
            qDebug() << "Error in addEntry()";
        }
    }

    l_db.close();
}

void Local_db_connection::extractOrder(QList<OrderInfo> *p_OrderInfo)
{
    qDebug()<<"extractOrder local-db-connection";
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {
        qDebug() << "in db.h error extract func"<<l_db.lastError().text();

    } else if ( !l_db.tables().contains("ORDERTABLE"))
    {
        createTableOrder(&l_db);
    }
    else
    {
        qDebug()<<"extract order in query";
        QSqlQuery qry(l_db);
        QString query = "SELECT * FROM ORDERTABLE ORDER BY ID DESC" ;

        qry.exec(query);

        while (qry.next()) {
            QSqlRecord record = qry.record();

            OrderInfo l_orderInfo;

            l_orderInfo.m_FirstName = record.value("FIRSTNAME").toString();
            l_orderInfo.m_LastName = record.value("LASTNAME").toString();
            l_orderInfo.m_phoneno = record.value("TELEPHONE").toString();
            l_orderInfo.m_street = record.value("STREET").toString();
            l_orderInfo.m_houseno = record.value("HOUSENUMBER").toString();
            l_orderInfo.m_zip = record.value("POSTCODE").toString();
            l_orderInfo.m_city = record.value("CITY").toString();
            l_orderInfo.m_Date = record.value("ORDERDATE").toString();
            l_orderInfo.m_OrderDate = record.value("ORDERPLACEDATE").toString();

            l_orderInfo.m_DType = record.value("DELIVERY").toString();
            l_orderInfo.m_Time = record.value("DELIVERYTIME").toString();
            l_orderInfo.m_PType = record.value("PAYMENTMETHOD").toString();
            l_orderInfo.m_Orderid = record.value("ORDERID").toString();
            l_orderInfo.m_DCost = record.value("DELIVERYCOST").toString();
            l_orderInfo.m_Amount = record.value("TOTAL").toString();
            l_orderInfo.m_Sender = record.value("SENDER").toString();
            l_orderInfo.m_Comment = record.value("COMMENT").toString();
           qDebug()<<"extractOrder "<<l_orderInfo.m_FirstName;
            p_OrderInfo->append(l_orderInfo);
        }
    }

    l_db.close();
}

void Local_db_connection::AllDate_extract(QList<Calndr> *p_Calndr,const QDate &date)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {
        qDebug() << "in db.h error extract func"<<l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query = QString::fromLatin1("SELECT * FROM ORDERTABLE WHERE '%1' >= ORDERPLACEDATE AND '%1' <= ORDERPLACEDATE ").arg(date.toString("yyyy-MM-dd"));

        qry.exec(query);

        while (qry.next()) {

            QSqlRecord record = qry.record();
            Calndr l_calnder;
            l_calnder.m_date = record.value("ORDERPLACEDATE").toString();

            p_Calndr->append(l_calnder);
        }
        return;
    }

    l_db.close();
}

void Local_db_connection::extractItems(QList<ItemsInfo> *p_ItemsInfo, QList<SubItemsInfo> *p_SubItemsInfo, QString Val)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {
        qDebug() << "in db.h error extract func"<<l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query = "SELECT * FROM ITEMTABLE WHERE ORDERID="+Val;

        qry.exec(query);

        while (qry.next()) {
            QSqlRecord record = qry.record();

            ItemsInfo l_ItemsInfo;

            l_ItemsInfo.m_Orderid = record.value("ORDERID").toString();
            l_ItemsInfo.m_ArticleNo = record.value("ITEMID").toString();
            l_ItemsInfo.m_ArticleName = record.value("NAME").toString();
            l_ItemsInfo.m_Price = record.value("PRICE").toString();
            l_ItemsInfo.m_UnitPrice = record.value("UNITPRICE").toString();
            l_ItemsInfo.m_Count = record.value("COUNT").toString();
            l_ItemsInfo.m_UniqueIdentifier = record.value("UNIQUE_ID").toString();
            l_ItemsInfo.m_Beverage = record.value("Beverage").toString();
            p_ItemsInfo->append(l_ItemsInfo);
        }

        query = "SELECT * FROM SUBITEMTABLE WHERE ORDERID="+Val ;

        qry.exec(query);

        while (qry.next()) {
            QSqlRecord record = qry.record();

            SubItemsInfo l_subItemsInfo;

            l_subItemsInfo.m_Orderid= record.value("ORDERID").toString();
            l_subItemsInfo.m_Itemid = record.value("ITEMID").toString();
            l_subItemsInfo.m_ArticleName = record.value("NAME").toString();
            l_subItemsInfo.m_Price = record.value("PRICE").toString();
            l_subItemsInfo.m_UnitPrice = record.value("UNITPRICE").toString();
            l_subItemsInfo.m_Count = record.value("COUNT").toString();
            l_subItemsInfo.m_UniqueIdentifier = record.value("UNIQUE_ID").toString();

            p_SubItemsInfo->append(l_subItemsInfo);
        }
    }

    l_db.close();
}

void Local_db_connection::extractPrintItems(QString val)
{
      QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");
      qDebug()<<"call extractPrintItems";
      if(!l_db.open())
      {
          qDebug() << "in db.h error extract func"<<l_db.lastError().text();
      }
      else
      {
      QSqlQuery qry(l_db);
      QString query = "SELECT * FROM ORDERTABLE WHERE ORDERID = " + val ;

      qry.exec(query);

      qry.next();
          QSqlRecord record = qry.record();
      QString pMethod;
      QString dType;
      QString dTime;
      if(record.value("PAYMENTMETHOD")==0){ pMethod =  "Barzahlung"; } else { pMethod =  "Online";  }
      if(record.value("DELIVERY")==0) { dType= "Lieferung";  } else { dType= "Abholung"; }
      if(record.value("DELIVERYTIME")=="") { QString dTime ="ASAP"; } else { QString dTime = record.value("DELIVERYTIME").toString();  }
      QString strStream;
      QTextStream out(&strStream);
      out << "<p style='text-align:center'><img style='width:10px; height:10px;' src='qrc:/logo-min.png'><h3>KHANA GMBH</h3>Keine Rechnung</p>";

      out << "<p style='text-align:left'>Little India<br>Glauburgstr. 6, 60318<br> Frankfurt<br>Hessen</p>";
      out << "<p>Bestellnr #"+val+"<br>Bestelldatum: " + record.value("ORDERDATE").toString() + "<br>Bestellzeit:"+ dTime +"</p><hr>";
      out << "<b>"+ pMethod +"</b><hr>";
      out << "<b>"+ dType +"</b><hr>";
      out << "<p style='text-align:left'>"+ record.value("FIRSTNAME").toString() +" "+ record.value("LASTNAME").toString() +"<br>"+record.value("STREET").toString()+ " " + record.value("HOUSENUMBER").toString() +"<br>" +record.value("CITY").toString() + " "+ record.value("POSTCODE").toString() +"<br>Phone: "+ record.value("TELEPHONE").toString() +"<hr>";
      QString qury = "SELECT * FROM ITEMTABLE WHERE ORDERID="+val;

      qry.exec(qury);
      out << "<table style='width:100%'>";
      while (qry.next()) {
          QSqlRecord record1 = qry.record();
          ItemsInfo l_ItemsInfo;
          out << "<tr><td> "+record1.value("ITEMID").toString() +" </td><td> "+record1.value("COUNT").toString()+" *</td><td> "+record1.value("NAME").toString()+"</td><td>"+record1.value("PRICE").toString()+"</td></tr>";
      }
      out << "</table><hr>";
      out << "<table style='width:100%'><tr><th>Gesamt</th><td></td><td>"+ record.value("TOTAL").toString() +"</td></tr></table>";
      out<<"<hr>";
      out << "<b>Notiz vom Kunden</b>";
      out << "<p>"+ record.value("COMMENT").toString() +"</p>";

      QTextDocument document;
      document.setHtml(strStream);

      QPrinter printer;

      printer.setPrinterName("desired printer name here");
      printer.setPaperSize(QSizeF(80, document.size().height()/2.5), QPrinter::Millimeter);
      printer.setFullPage(true);

      printer.setPageMargins(-10,-20,0,-20 , QPrinter::Millimeter);

      QPrintDialog dialog(&printer, 0);
      document.print(&printer);
      }
}

void Local_db_connection::extractSingleOrder(QList<OrderInfoS> *p_SOrderInfo,QString val)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {
        qDebug() << "in db.h error extract func"<<l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query = "SELECT * FROM ORDERTABLE WHERE ORDERID = " + val ;

        qry.exec(query);

        while (qry.next()) {
            QSqlRecord record = qry.record();

            qDebug()<<"Get Single Order "<<query;
            OrderInfoS l_orderInfoS;

            l_orderInfoS.m_FirstName = record.value("FIRSTNAME").toString();
            l_orderInfoS.m_LastName = record.value("LASTNAME").toString();
            l_orderInfoS.m_phoneno = record.value("TELEPHONE").toString();
            l_orderInfoS.m_street = record.value("STREET").toString();
            l_orderInfoS.m_houseno = record.value("HOUSENUMBER").toString();
            l_orderInfoS.m_zip = record.value("POSTCODE").toString();
            l_orderInfoS.m_city = record.value("CITY").toString();
            l_orderInfoS.m_Date = record.value("ORDERDATE").toString();

            l_orderInfoS.m_DType = record.value("DELIVERY").toString();
            l_orderInfoS.m_Time = record.value("DELIVERYTIME").toString();
            l_orderInfoS.m_PType = record.value("PAYMENTMETHOD").toString();
            l_orderInfoS.m_Orderid = record.value("ORDERID").toString();
            l_orderInfoS.m_DCost = record.value("DELIVERYCOST").toString();
            l_orderInfoS.m_Amount = record.value("TOTAL").toString();
            l_orderInfoS.m_Sender = record.value("SENDER").toString();
            l_orderInfoS.m_Comment = record.value("COMMENT").toString();

            p_SOrderInfo->append(l_orderInfoS);

            qDebug()<<"Order Detail "<<l_orderInfoS.m_FirstName <<l_orderInfoS.m_LastName ;
    }

    l_db.close();
}

}

void Local_db_connection::extractDateChange(QList<OrderInfo> *p_OrderInfo, QString date)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {
        qDebug() << "in db.h error extract func"<<l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query = "SELECT * FROM ORDERTABLE WHERE ORDERPLACEDATE = '"  + date + "'" ;
        qry.exec(query);

        while (qry.next()) {
            QSqlRecord record = qry.record();
            OrderInfo l_orderInfo;

            l_orderInfo.m_FirstName = record.value("FIRSTNAME").toString();
            l_orderInfo.m_LastName = record.value("LASTNAME").toString();
            l_orderInfo.m_phoneno = record.value("TELEPHONE").toString();
            l_orderInfo.m_street = record.value("STREET").toString();
            l_orderInfo.m_houseno = record.value("HOUSENUMBER").toString();
            l_orderInfo.m_zip = record.value("POSTCODE").toString();
            l_orderInfo.m_city = record.value("CITY").toString();
            l_orderInfo.m_Date = record.value("ORDERDATE").toString();

            l_orderInfo.m_OrderDate = record.value("ORDERPLACEDATE").toString();
            l_orderInfo.m_DType = record.value("DELIVERY").toString();
            l_orderInfo.m_Time = record.value("DELIVERYTIME").toString();
            l_orderInfo.m_PType = record.value("PAYMENTMETHOD").toString();
            l_orderInfo.m_Orderid = record.value("ORDERID").toString();
            l_orderInfo.m_DCost = record.value("DELIVERYCOST").toString();
            l_orderInfo.m_Amount = record.value("TOTAL").toString();
            l_orderInfo.m_Sender = record.value("SENDER").toString();
            l_orderInfo.m_Comment = record.value("COMMENT").toString();

            p_OrderInfo->append(l_orderInfo);
    }
    l_db.close();
 }
}

void Local_db_connection::RecordsType_extractOrder(QList<OrderInfo> *p_OrderInfo, QString sender)
{
    QSqlDatabase l_db = QSqlDatabase::database("localSqlLite");

    if(!l_db.open())
    {
        qDebug() << "in db.h error extract func"<<l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query = "SELECT * FROM ORDERTABLE WHERE SENDER = '"  + sender + "'" ;
        qry.exec(query);

        while (qry.next()) {
            QSqlRecord record = qry.record();
            OrderInfo l_orderInfo;

            l_orderInfo.m_FirstName = record.value("FIRSTNAME").toString();
            l_orderInfo.m_LastName = record.value("LASTNAME").toString();
            l_orderInfo.m_phoneno = record.value("TELEPHONE").toString();
            l_orderInfo.m_street = record.value("STREET").toString();
            l_orderInfo.m_houseno = record.value("HOUSENUMBER").toString();
            l_orderInfo.m_zip = record.value("POSTCODE").toString();
            l_orderInfo.m_city = record.value("CITY").toString();
            l_orderInfo.m_Date = record.value("ORDERDATE").toString();

            l_orderInfo.m_OrderDate = record.value("ORDERPLACEDATE").toString();
            l_orderInfo.m_DType = record.value("DELIVERY").toString();
            l_orderInfo.m_Time = record.value("DELIVERYTIME").toString();
            l_orderInfo.m_PType = record.value("PAYMENTMETHOD").toString();
            l_orderInfo.m_Orderid = record.value("ORDERID").toString();
            l_orderInfo.m_DCost = record.value("DELIVERYCOST").toString();
            l_orderInfo.m_Amount = record.value("TOTAL").toString();
            l_orderInfo.m_Sender = record.value("SENDER").toString();
            l_orderInfo.m_Comment = record.value("COMMENT").toString();

            p_OrderInfo->append(l_orderInfo);
    }
    l_db.close();
 }
}
