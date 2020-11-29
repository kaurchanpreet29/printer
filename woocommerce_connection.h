#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

#include "structures.h"
#include "Singleton.h"
#include "QFile"
#include "QDir"

#include <QDateTime>

#include <QString>
#include <QStringList>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include<QTextDocument>
#include <QList>
#include <QAbstractTextDocumentLayout>
#include <QPainter>

class WooCommerce_connection : public QObject
{
    Q_OBJECT
public:
    explicit WooCommerce_connection(QObject *parent = nullptr);

    void extract(QList<OrderInfo> *m_OrderInfo, QString Date);
    void extractItems(QList<ItemsInfo> *m_ItemsInfo,QList<SubItemsInfo> *m_SubItemsInfo, QString Val);
    void extractPrintItems(QString Val);
    void update(QString m_orderId);

    QSqlDatabase connect();

    QSqlDatabase db;

    void closedb();

signals:

};

typedef Singleton<WooCommerce_connection> WooCommerce_DB_Singleton;

#endif // CONNECTION_H
