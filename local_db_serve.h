#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QObject>
#include "structures.h"
#include "local_db_connection.h"
#include <QDomDocument>

class Local_db_serve : public QObject
{
    Q_OBJECT

public:
    explicit Local_db_serve(QObject *parent = nullptr);

    void Handler_addOrderEntry(QList<OrderInfo> p_OrderInfo);
    void Handler_addItemEntry(QList<ItemsInfo> p_ItemsInfo);
    void Handler_addSubItemEntry(QList<SubItemsInfo> p_SubItemsInfo);
    void Handler_extractOrder();

    QDomElement addElement( QDomDocument &doc, QDomNode &node,
                            const QString &tag,
                            const QString &value = QString::null )
    {
        QDomElement el = doc.createElement( tag );
        node.appendChild( el );
        if ( !value.isNull() ) {
            QDomText txt = doc.createTextNode( value );
            el.appendChild( txt );
        }
        return el;
    }

signals:
    void s_OrderInfoChanged (QList<OrderInfo>);
    void s_OrderInfoSChanged (QList<OrderInfoS>);
    void s_ItemsInfoChanged (QList<ItemsInfo>);
    void s_SubItemInfoChanged (QList<SubItemsInfo>);

    //void allDatesSignal(QList<Calndr>);
    void allDatesSignal(QList<Calndr>);

public slots:
    void Handler_extractItems(QString Val);
    void extract_printSignal(QString val);
    void writeXml(QString Orderid, OrderInfo p_OrderInfo);
    void extract_GetOrderS(QString val);
    void Handler_DateChangedOrder(QString date);
    void RecordsType_extractOrder(QString val);
    void Handler_extractDates(const QDate &date);

private:

};

#endif // DBHANDLER_H
