#include "local_db_serve.h"

Local_db_serve::Local_db_serve(QObject *parent) : QObject(parent)
{

}

void Local_db_serve::Handler_addOrderEntry(QList<OrderInfo> p_OrderInfo)
{
    Local_DB_Singleton::Instance()->addOrderEntry(&p_OrderInfo);
}

void Local_db_serve::Handler_addItemEntry(QList<ItemsInfo> p_ItemsInfo)
{
    Local_DB_Singleton::Instance()->addItemEntry(&p_ItemsInfo);
}

void Local_db_serve::Handler_addSubItemEntry(QList<SubItemsInfo> p_SubItemsInfo)
{
    Local_DB_Singleton::Instance()->addSubItemEntry(&p_SubItemsInfo);
}

void Local_db_serve::Handler_extractOrder()
{
    QList<OrderInfo> p_OrderInfo;

    Local_DB_Singleton::Instance()->extractOrder(&p_OrderInfo);

    emit s_OrderInfoChanged(p_OrderInfo);

    for (int i = 0; i < p_OrderInfo.size() ; i++)
    {
        writeXml(p_OrderInfo.at(i).m_Orderid, p_OrderInfo.at(i));
    }
}

void Local_db_serve::Handler_extractItems(QString Val)
{
    QList<ItemsInfo> p_ItemsInfo;
    QList<SubItemsInfo> p_SubItemsInfo;

    qRegisterMetaType<QList<SubItemsInfo>>("p_SubItemsInfo");

    Local_DB_Singleton::Instance()->extractItems(&p_ItemsInfo, &p_SubItemsInfo, Val);

    emit s_ItemsInfoChanged(p_ItemsInfo);
    emit s_SubItemInfoChanged(p_SubItemsInfo);
}

void Local_db_serve::extract_printSignal(QString val)
{
    QList<ItemsInfo> p_ItemsInfo;
    QList<SubItemsInfo> p_SubItemsInfo;

    qRegisterMetaType<QList<SubItemsInfo>>("p_SubItemsInfo");

    Local_DB_Singleton::Instance()->extractPrintItems(val);
}

void Local_db_serve::writeXml(QString Orderid, OrderInfo p_OrderInfo)
{
    QString path ="_pos/orders/";
    QString path1 ="_pos/print/";
    QString path2 ="_pos/ok/";
    QString path3 ="_pos/cancel/";
    QDir dir;
    QFile file(path + Orderid +".xml");
    QFile file1(path1 + Orderid +".xml");

    if(!dir.exists(path))
    {
        dir.mkpath(path);
    }

    if(!dir.exists(path1))
    {
        dir.mkpath(path1);
    }
    if(!dir.exists(path2))
    {
        dir.mkpath(path2);
    }
    if(!dir.exists(path3))
    {
        dir.mkpath(path3);
    }

    if (!file.exists())
    {
        if ( file.open(QIODevice::ReadWrite) )
        {
            QList<ItemsInfo> l_ItemsInfo;
            QList<SubItemsInfo> l_SubItemsInfo;

            Local_DB_Singleton::Instance()->extractItems(&l_ItemsInfo,&l_SubItemsInfo,Orderid);

            QDomDocument doc;
            QDomProcessingInstruction instr = doc.createProcessingInstruction(
                        "xml", "version='1.0' encoding='UTF-8'");
            doc.appendChild(instr);

            QDomElement Ordersetelement = addElement( doc, doc, "order" );

            QDomElement Restsetelement =  addElement( doc, Ordersetelement, "restaurant" );
            addElement( doc, Restsetelement, "restaurantid");
            addElement( doc, Restsetelement, "courier");

            QDomElement Customersetelement = addElement( doc, Ordersetelement, "customer" );

            addElement( doc, Customersetelement, "newcustomer");
            addElement( doc, Customersetelement, "customerbusinessname");
            addElement( doc, Customersetelement, "customername");
            addElement( doc, Customersetelement, "firstname",p_OrderInfo.m_FirstName);
            addElement( doc, Customersetelement, "lastname",p_OrderInfo.m_LastName);
            addElement( doc, Customersetelement, "customertelephone",p_OrderInfo.m_phoneno);

            QDomElement Deliverysetelement = addElement( doc, Ordersetelement, "deliveryaddress" );

            addElement( doc, Deliverysetelement, "street",p_OrderInfo.m_street);
            addElement( doc, Deliverysetelement, "housenumber",p_OrderInfo.m_houseno);
            addElement( doc, Deliverysetelement, "postcode",p_OrderInfo.m_zip);
            addElement( doc, Deliverysetelement, "deliveryarea");
            addElement( doc, Deliverysetelement, "city",p_OrderInfo.m_city);

            addElement( doc, Ordersetelement, "source" );
            addElement( doc, Ordersetelement, "paymentreference" );
            addElement( doc, Ordersetelement, "orderdate",p_OrderInfo.m_Date );
            addElement( doc, Ordersetelement, "delivery",p_OrderInfo.m_DType );
            addElement( doc, Ordersetelement, "deliverytime",p_OrderInfo.m_Time );

            QDomElement Paydetailssetelement = addElement( doc, Ordersetelement, "paydetails" );
            addElement( doc, Paydetailssetelement, "paysexact");
            addElement( doc, Paydetailssetelement, "alternativeamount");
            addElement( doc, Paydetailssetelement, "electronicallypaid");
            addElement( doc, Paydetailssetelement, "paymentmethod",p_OrderInfo.m_PType);

            addElement( doc, Ordersetelement, "customerremarks" );

            QDomElement ProductsSetElement =  addElement( doc, Ordersetelement, "products");

            for ( int i = 0; i < l_ItemsInfo.size(); ++i)
            {
                QDomElement ItemSetElement =  addElement( doc, ProductsSetElement, "product");
                addElement( doc, ItemSetElement, "productid",l_ItemsInfo[i].m_ArticleNo );
                addElement( doc, ItemSetElement, "number" );
                addElement( doc, ItemSetElement, "name",l_ItemsInfo[i].m_ArticleName  );
                addElement( doc, ItemSetElement, "count",l_ItemsInfo[i].m_Count );
                addElement( doc, ItemSetElement, "price",l_ItemsInfo[i].m_Price );
                addElement( doc, ItemSetElement, "Getränke",l_ItemsInfo[i].m_Beverage );

                addElement( doc, ItemSetElement, "UnitPrice",l_ItemsInfo[i].m_UnitPrice );
                addElement( doc, ItemSetElement, "categoryname" );
                QDomElement SubItemsSetElement =  addElement( doc, ItemSetElement, "sidedishes");

                for ( int j = 0; j < l_SubItemsInfo.size(); ++j)
                {
                    if(l_ItemsInfo[i].m_ArticleNo == l_SubItemsInfo[j].m_Itemid)
                    {
                        QDomElement SubItemSetElement =  addElement( doc, SubItemsSetElement, "sidedish");
                        addElement( doc, SubItemSetElement, "id",l_SubItemsInfo[j].m_Itemid);
                        addElement( doc, SubItemSetElement, "name",l_SubItemsInfo[j].m_ArticleName);
                        addElement( doc, SubItemSetElement, "count",l_SubItemsInfo[j].m_Count);
                        addElement( doc, SubItemSetElement, "price",l_SubItemsInfo[j].m_Price);
                        addElement( doc, SubItemSetElement, "UnitPrice",l_SubItemsInfo[j].m_UnitPrice);
                    }
                }

                addElement( doc, ItemSetElement, "sidedishesinfo");
                addElement( doc, ItemSetElement, "remarks");
            }

            addElement( doc, Ordersetelement, "discounts");
            QDomElement AmountsSetElement =  addElement( doc, Ordersetelement, "amounts");
            addElement( doc, AmountsSetElement, "subtotal");
            addElement( doc, AmountsSetElement, "deliverycosts",p_OrderInfo.m_DCost);
            addElement( doc, AmountsSetElement, "total",p_OrderInfo.m_Amount);

            qDebug()<<"file now exists";
            file.write(doc.toByteArray(1));
            file.close();

            if (p_OrderInfo.m_status == "0")
            {
             file1.open(QIODevice::ReadWrite);
             file1.write(doc.toByteArray(1));
             file1.close();
            }
        }
    }
}

void Local_db_serve::extract_GetOrderS(QString val)
{
   QList<OrderInfoS> p_SOrderInfo;
   Local_DB_Singleton::Instance()->extractSingleOrder(&p_SOrderInfo,val);
   emit s_OrderInfoSChanged(p_SOrderInfo);
}

void Local_db_serve::Handler_DateChangedOrder(QString date)
{
    QList<OrderInfo> p_OrderInfo;
    Local_DB_Singleton::Instance()->extractDateChange(&p_OrderInfo,date);
    emit s_OrderInfoChanged(p_OrderInfo);
}

void Local_db_serve::RecordsType_extractOrder(QString val)
{
    QList<OrderInfo> p_OrderInfo;
    Local_DB_Singleton::Instance()->RecordsType_extractOrder(&p_OrderInfo,val);
    emit s_OrderInfoChanged(p_OrderInfo);
}

void Local_db_serve::Handler_extractDates(const QDate &date)
{
    QList<Calndr> p_Calndr;
    qRegisterMetaType<QList<Calndr>>("p_Calndr");
    Local_DB_Singleton::Instance()->AllDate_extract(&p_Calndr,date);
    emit allDatesSignal(p_Calndr);
}
