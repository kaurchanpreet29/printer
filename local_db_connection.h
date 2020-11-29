#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QtDebug>
#include <QtSql>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include "Singleton.h"
#include "structures.h"

#include <QString>
#include <QStringList>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include<QTextDocument>
#include <QList>
#include <QAbstractTextDocumentLayout>
#include <QPainter>

class Local_db_connection : public QObject
{
    Q_OBJECT

public:
    explicit Local_db_connection(QObject *parent = nullptr);

    void Init();

    void createTableOrder(QSqlDatabase* p_db);
    void createTableItems(QSqlDatabase* p_db);
    void createTableSubItems(QSqlDatabase* p_db);

    void dropTable(QString l_tablename);

    void addOrderEntry(QList<OrderInfo> *p_OrderInfo);
    void addItemEntry(QList<ItemsInfo> *p_ItemsInfo);
    void addSubItemEntry(QList<SubItemsInfo> *p_SubItemsInfo);

    void extractOrder(QList<OrderInfo> *p_OrderInfo);

    void AllDate_extract(QList<Calndr> *p_Calndr,const QDate &date);

    void extractItems(QList<ItemsInfo> *p_ItemsInfo, QList<SubItemsInfo> *p_SubItemsInfo, QString Val);
    void extractPrintItems(QString Val);
    void extractSingleOrder(QList<OrderInfoS> *p_SOrderInfo, QString val);
    void extractDateChange(QList<OrderInfo> *p_OrderInfo, QString date);
    void RecordsType_extractOrder(QList<OrderInfo> *p_OrderInfo, QString sender);

private:
    QSqlDatabase m_db;
};

typedef Singleton<Local_db_connection> Local_DB_Singleton;


#endif // DB_H
