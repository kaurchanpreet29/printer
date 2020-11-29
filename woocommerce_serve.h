#ifndef SERVE_H
#define SERVE_H

#include <QObject>
#include <QTimer>
#include "woocommerce_connection.h"

#include <QDomDocument>

class WooCommerce_serve : public QObject
{
    Q_OBJECT

public:
    explicit WooCommerce_serve(QObject *parent = nullptr);

   // QList<OrderInfo> m_OrderInfo;

    void extract(QList<OrderInfo> *m_OrderInfo, QString Date = QDateTime::currentDateTime().toString("yyyy-MM-dd"));

signals:
    void s_addOrderEntry(QList<OrderInfo>);
    void s_addItemsEntry(QList<ItemsInfo>);
    void s_addSubItemsEntry(QList<SubItemsInfo>);

public slots:
    void v_start();
    void v_Init();
    void v_Extract(QString Date);

private :
    QTimer *timer;
};

#endif // SERVE_H
