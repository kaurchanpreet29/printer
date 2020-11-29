#include "woocommerce_connection.h"
#include "QThread"

WooCommerce_connection::WooCommerce_connection(QObject *parent) : QObject(parent)
{
    QString txtvalue ;
    QFile file("db.txt");

    if (!file.exists()) {
        qDebug() << "file dont exust";
    }

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        txtvalue = in.readAll();
    }

    file.close();

    db = QSqlDatabase::addDatabase("QODBC","odbc");
    db.setDatabaseName("Driver={MySQL ODBC 8.0 Unicode Driver};" + txtvalue);
}

void WooCommerce_connection::extract(QList<OrderInfo> *m_OrderInfo, QString Date)
{
    QSqlDatabase l_db = QSqlDatabase::database("odbc");

    if(!l_db.open())
    {
        qDebug() << "in odbc connection "<<l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query1 = "SELECT * FROM wp_posorder WHERE dateandtime='" + Date + "' AND order_status = '0' ORDER BY id DESC" ;
        qry.exec(query1);
        while (qry.next()) {
          QSqlRecord record1 = qry.record();
          extractPrintItems(record1.value("orderId").toString());
        }
        QString query = "SELECT * FROM wp_posorder WHERE dateandtime='" + Date + "' AND order_status = '0' ORDER BY id DESC" ;

        qry.exec(query);

        while (qry.next()) {

            QSqlRecord record = qry.record();

            OrderInfo l_orderInfo;
            l_orderInfo.m_Date = record.value("deliverydate").toString();
            l_orderInfo.m_Time = record.value("deliveryTime").toString();
            l_orderInfo.m_Orderid = record.value("orderId").toString();
            l_orderInfo.m_FirstName = record.value("firstName").toString();
            l_orderInfo.m_LastName = record.value("lastName").toString();

            l_orderInfo.m_street = record.value("street").toString();
            l_orderInfo.m_houseno = record.value("houseNo").toString();
            l_orderInfo.m_zip = record.value("zip").toString();
            l_orderInfo.m_city = record.value("city").toString();
            l_orderInfo.m_email = record.value("email").toString();
            l_orderInfo.m_phoneno = record.value("phoneNo").toString();
            l_orderInfo.m_status = record.value("order_status").toString();
            l_orderInfo.m_Amount = record.value("totalAmount").toString();
            l_orderInfo.m_Company = record.value("company").toString();
            l_orderInfo.m_DType = record.value("deliveryType").toString();
            l_orderInfo.m_PType = record.value("paymentType").toString();

            l_orderInfo.m_OrderDate = record.value("dateandtime").toString();
            l_orderInfo.m_Updated = record.value("dateandtime").toString();
            l_orderInfo.m_Sender = record.value("sender").toString();
            l_orderInfo.m_Comment = record.value("comment").toString();
            l_orderInfo.m_DCost = record.value("deliverycharges").toString();

            update(l_orderInfo.m_Orderid);
            m_OrderInfo->append(l_orderInfo);
        }
    }

    l_db.close();
}


void WooCommerce_connection::extractItems(QList<ItemsInfo> *m_ItemsInfo, QList<SubItemsInfo> *m_SubItemsInfo, QString val)
{
    QSqlDatabase l_db = QSqlDatabase::database("odbc");

    if(!l_db.open())
    {
        qDebug() << l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);

        QString query = "SELECT * FROM wp_positems WHERE orderId="+val;

        qry.exec(query);
        ItemsInfo l_itemsInfo;

        while (qry.next()) {
            QSqlRecord record = qry.record();

            l_itemsInfo.m_Orderid = record.value("orderId").toString();
            l_itemsInfo.m_ArticleName = record.value("articleName").toString();
            l_itemsInfo.m_Count = record.value("count").toString();

            l_itemsInfo.m_Price = record.value("price").toString();
            l_itemsInfo.m_UnitPrice = record.value("unitPrice").toString();
            l_itemsInfo.m_Beverage = record.value("beverage").toString();
            l_itemsInfo.m_ArticleNo = record.value("articleNo").toString();
            QUuid u = QUuid::createUuid();
            l_itemsInfo.m_UniqueIdentifier = u.toString();

            m_ItemsInfo->append(l_itemsInfo);
        }

        query = "SELECT * FROM wp_possubitems WHERE orderId="+val;
        qry.exec(query);

        while (qry.next()) {
            QSqlRecord record = qry.record();

            SubItemsInfo l_subitemsInfo;

            l_subitemsInfo.m_Orderid = record.value("orderId").toString();
            l_subitemsInfo.m_ArticleName = record.value("articleName").toString();
            l_subitemsInfo.m_Count = record.value("count").toString();

            l_subitemsInfo.m_Price = record.value("price").toString();
            l_subitemsInfo.m_UnitPrice = record.value("unitPrice").toString();
            l_subitemsInfo.m_Itemid = record.value("ItemId").toString();

            l_subitemsInfo.m_UniqueIdentifier = l_itemsInfo.m_UniqueIdentifier;

            qDebug() << l_subitemsInfo.m_Orderid;
            qDebug() << l_subitemsInfo.m_ArticleName;

            m_SubItemsInfo->append(l_subitemsInfo);
        }
    }

    l_db.close();
}

void WooCommerce_connection::update(QString val)
{
    QSqlDatabase l_db = QSqlDatabase::database("odbc");

    if(!l_db.open())
    {
        qDebug() << l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query = "UPDATE wp_posorder SET order_status = 1 WHERE orderId="+val;

        qry.exec(query);
    }

    l_db.close();
}

void WooCommerce_connection::extractPrintItems(QString Val){
    QSqlDatabase l_db = QSqlDatabase::database("odbc");

    if(!l_db.open())
    {
        qDebug() << "in odbc connection "<<l_db.lastError().text();
    }
    else
    {
        QSqlQuery qry(l_db);
        QString query = "SELECT * FROM wp_posorder WHERE orderId='" + Val + "'" ;

        qry.exec(query);

        while (qry.next()) {
        QSqlRecord record = qry.record();

        QString pMethod;
        QString dType;
        QString dTime;
        if(record.value("paymentType")==0){ pMethod =  "Barzahlung"; } else { pMethod =  "Online";  }
        if(record.value("deliveryType")==0) { dType= "Lieferung";  } else { dType= "Abholung"; }
        if(record.value("deliveryTime")=="") { QString dTime ="ASAP"; } else { QString dTime = record.value("DELIVERYTIME").toString();  }
        QString strStream;
        QTextStream out(&strStream);
        out << "<p style='text-align:center'><img style='width:10px; height:10px;' src='qrc:/logo-min.png'><h3>KHANA GMBH</h3>Keine Rechnung</p>";

        out << "<p style='text-align:left'>Little India<br>Glauburgstr. 6, 60318<br> Frankfurt<br>Hessen</p>";
        out << "<p>Bestellnr #"+Val+"<br>Bestelldatum: " + record.value("dateandtime").toString() + "<br>Bestellzeit:"+ dTime +"</p><hr>";
        out << "<b>"+ pMethod +"</b><hr>";
        out << "<b>"+ dType +"</b><hr>";
        out << "<p style='text-align:left'>"+ record.value("firstName").toString() +" "+ record.value("lastName").toString() +"<br>"+record.value("street").toString()+ " " + record.value("houseNo").toString() +"<br>" +record.value("city").toString() + " "+ record.value("zip").toString() +"<br>Phone: "+ record.value("phoneNo").toString() +"<hr>";

        QSqlQuery qry1(l_db);
        QString qury = "SELECT * FROM wp_positems WHERE orderId="+Val;

        qry1.exec(qury);
        ItemsInfo l_itemsInfo;

        out << "<table style='width:100%'>";
        while (qry1.next()) {
            QSqlRecord record1 = qry1.record();

            out << "<tr><td> "+record1.value("articleNo").toString() +" </td><td> "+record1.value("count").toString()+" *</td><td> "+record1.value("articleName").toString()+"</td><td>"+record1.value("price").toString()+"</td></tr>";
        }
        out<< "</table><hr>";
        out<< "<table style='width:100%'><tr><th>Gesamt</th><td></td><td>"+ record.value("totalAmount").toString() +"</td></tr></table>";
        out<<"<hr>";
        out<< "<b>Notiz vom Kunden</b>";
        out<< "<p>"+ record.value("COMMENT").toString() +"</p>";

        QTextDocument document;
        document.setHtml(strStream);

        QPrinter printer;
        printer.setPrinterName("desired printer name here");
        printer.setPaperSize(QSizeF(80, document.size().height()/2.5), QPrinter::Millimeter);
        printer.setFullPage(true);
        printer.setPageMargins(0,-20,-10,-20 , QPrinter::Millimeter);

        QPrintDialog dialog(&printer, 0);
        document.print(&printer);
     }
   }
}


