#include "woocommerce_serve.h"
#include "QThread"

WooCommerce_serve::WooCommerce_serve(QObject *parent) : QObject(parent)
{
}

void WooCommerce_serve::v_Init()
{
    QList<OrderInfo> l_OrderInfo;
    extract(&l_OrderInfo);


    emit s_addOrderEntry(l_OrderInfo);

    for(int i= 0; i < l_OrderInfo.size(); i++)
    {
        QList<ItemsInfo> l_ItemsInfo;
        QList<SubItemsInfo> l_SubItemsInfo;

        qRegisterMetaType<QList<SubItemsInfo>>("l_SubItemsInfo");

        auto val = l_OrderInfo.at(i).m_Orderid ;

        WooCommerce_DB_Singleton::Instance()->extractItems(&l_ItemsInfo,&l_SubItemsInfo,val);

        emit s_addItemsEntry(l_ItemsInfo);
        emit s_addSubItemsEntry(l_SubItemsInfo);
    }
}


void WooCommerce_serve::v_Extract(QString Date)
{
    qDebug() << Date;

    timer->stop();

    QList<OrderInfo> l_OrderInfo;

    if(Date == QDateTime::currentDateTime().toString("yyyy-MM-dd"))
        timer->start();

    extract(&l_OrderInfo,Date);

    emit s_addOrderEntry(l_OrderInfo);
}


void WooCommerce_serve::extract(QList<OrderInfo> *m_OrderInfo, QString Date)
{
    WooCommerce_DB_Singleton::Instance()->extract(m_OrderInfo,Date);
}

void WooCommerce_serve::v_start()
{
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(v_Init()));

    timer->start(5000);

    QTimer::singleShot(3000, [this](){v_Init();});
}
