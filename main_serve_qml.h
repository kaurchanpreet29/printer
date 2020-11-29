#ifndef SERVEQML_H
#define SERVEQML_H

#include <QObject>
#include <QDebug>
#include "structures.h"
#include "QFile"
#include "QDir"
#include <QtMultimedia/QSound>
#include <QAudioDeviceInfo>
#include <QDomDocument>
#include <QTimer>
#include <QDate>
#include <QAudioDecoder>
#include "event.h"

class Main_Serve_Qml : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<OrderInfo> orderInfo READ getOrderInfo
               WRITE setOrderInfo NOTIFY OrderInfoChanged)

    Q_PROPERTY(QList<ItemsInfo> itemsInfo READ getItemsInfo
               WRITE setItemsInfo NOTIFY ItemsInfoChanged)

    Q_PROPERTY(QList<SubItemsInfo> subitemsInfo READ getSubItemsInfo
               WRITE setSubItemsInfo NOTIFY SubItemsInfoChanged)

    Q_PROPERTY(QList<OrderInfoS> orderInfoS READ getOrderInfoS
               WRITE setOrderInfoS NOTIFY OrderInfoSChanged)

    Q_PROPERTY(QDateTime eventDate READ getEventDate
               WRITE setEventDate NOTIFY EventDateChanged)

public:

    explicit Main_Serve_Qml(QObject *parent = nullptr);
    //Q_INVOKABLE QList<QObject*> eventsForDate(const QDate &date);

    QList<OrderInfo> m_OrderInfo;

    QList<OrderInfo>  getOrderInfo() const
    {
        return m_OrderInfo;
    }

    void setOrderInfo(QList<OrderInfo> val)
    {
        m_OrderInfo = val;
        v_playSound();
        emit OrderInfoChanged();
    }

    QList<SubItemsInfo> m_SubItemsInfo;

    QList<SubItemsInfo>  getSubItemsInfo() const
    {
        return m_SubItemsInfo;
    }

    void setSubItemsInfo(QList<SubItemsInfo> val)
    {
        m_SubItemsInfo = val;
        emit SubItemsInfoChanged();
    }

    QList<ItemsInfo> m_ItemsInfo;

    QList<ItemsInfo>  getItemsInfo() const
    {
        return m_ItemsInfo;
    }

    void setItemsInfo(QList<ItemsInfo> val)
    {
        m_ItemsInfo = val;
        emit ItemsInfoChanged();
    }

    QList<OrderInfoS> m_OrderInfoS;

    QList<OrderInfoS>  getOrderInfoS() const
    {
        return m_OrderInfoS;
    }

    void setOrderInfoS(QList<OrderInfoS> val)
    {
        m_OrderInfoS = val;
        //v_playSound();
        emit OrderInfoSChanged();
    }

    Q_INVOKABLE int get_size_subItems(){
        return m_SubItemsInfo.size();
    }

    Q_INVOKABLE int get_size_Items(){
        return m_OrderInfo.size();
    }

    QDateTime getEventDate() const;

signals:
    void OrderInfoChanged();
    void OrderInfoSChanged();
    void SubItemsInfoChanged();
    void ItemsInfoChanged();

    void s_GetOrders();
    void s_getRecordsType(QString val);
    void v_GetOrderS(QString val);
    void printSignal(QString val);
    void s_GetItems(QString Val);
    void s_DataChanged(QString val);

    void allDatesSignal(const QDate &date);

    void EventDateChanged(QDateTime eventDate);

public slots:
    void OrderInfoRcvd(QList<OrderInfo> val);

    void SOrderInfoRcvd(QList<OrderInfoS> val);
    void SubItemsInfoRcvd(QList<SubItemsInfo> val);
    void ItemsInfoRcvd(QList<ItemsInfo> val);

    void DateChanged(QString val);
    void Print(QString val);
    //void printSignal(QString val);
    void v_GetOrders();
    void v_GetItems(QString Val);
    void v_GetOrder(QString val);
    void v_playSound();

    void RecordsType(int val);
    void getRecordsType(QString val);
    void startTime();
    void stopTimer();

    Q_INVOKABLE void eventsForDate(const QDate &date);

    Q_INVOKABLE QList<QObject*> get_AllDates(QList<Calndr> val);

    void setEventDate(QDateTime eventDate);

private :
    QTimer *timer;
    QString mName;
    QDateTime m_eventDate;
};

#endif // SERVEQML_H
