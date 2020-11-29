#include "main_serve_qml.h"
#include <QDate>

Main_Serve_Qml::Main_Serve_Qml(QObject *parent) : QObject(parent)
{
    startTime();
}

QDateTime Main_Serve_Qml::getEventDate() const
{
    return m_eventDate;
}

void Main_Serve_Qml::startTime(){
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(v_GetOrders()));
           timer->start(5000);
}

void Main_Serve_Qml::stopTimer(){
    timer->stop();
}

void Main_Serve_Qml::v_GetOrders()
{
   s_GetOrders();
}

void Main_Serve_Qml::RecordsType(int val)
{
    switch (val) {
      case 0:
         getRecordsType("https://qa.fleksa.com");
        break;

       case 1:
        getRecordsType("primalieferung.de");
        break;
    }
}

void Main_Serve_Qml::getRecordsType(QString val)
{
   stopTimer();
   s_getRecordsType(val);
}

void Main_Serve_Qml::DateChanged(QString val)
{
   /*  QString s = QDate::currentDate().toString("yyyy-MM-dd");
     if(s==val){
         s_DataChanged(val);
     } else {
        qDebug()<<"CURRENT DATE "<<s<<"selected date "<<val;*/
        stopTimer();
        s_DataChanged(val);
}

void Main_Serve_Qml::v_GetItems(QString Val)
{
    s_GetItems(Val);
}

void Main_Serve_Qml::v_GetOrder(QString val)
{
    v_GetOrderS(val);
}

void Main_Serve_Qml::eventsForDate(const QDate &date)
{
  allDatesSignal(date);
}

QList<QObject*> Main_Serve_Qml::get_AllDates(QList<Calndr> val)
{
    QList<QObject*> events;
    for(int i=0; i<val.size(); i++){

      Event *event = new Event(this);

      QDateTime startDate;
      startDate.setDate(QDate::fromString(val[i].m_date,"yyyy-MM-dd"));
      //startDate.setTime(QTime(0, 0).addSecs(query.value("startTime").toInt()));
      event->setStartDate(startDate);

      setEventDate(startDate);

      QDateTime endDate;
      endDate.setDate(QDate::fromString(val[i].m_date,"yyyy-MM-dd"));
      //endDate.setTime(QTime(0, 0).addSecs(query.value("endTime").toInt()));
      event->setEndDate(endDate);

      events.append(event);
    }
    return events;
}

void Main_Serve_Qml::setEventDate(QDateTime eventDate)
{
    qDebug()<<"test setEventDate"<<eventDate;
    if (m_eventDate == eventDate)
        return;

    m_eventDate = eventDate;
    emit EventDateChanged(m_eventDate);
}

void Main_Serve_Qml::OrderInfoRcvd(QList<OrderInfo> val)
{
    if (( m_OrderInfo.size() != val.size()))
    {
        setOrderInfo(val);
    }
    else if ((m_OrderInfo.size() > 0) && (val.size() > 0))
    {
        if (m_OrderInfo[0].m_Orderid != val[0].m_Orderid)
        {
            setOrderInfo(val);
        }
    }
}

void Main_Serve_Qml::SOrderInfoRcvd(QList<OrderInfoS> val)
{
    setOrderInfoS(val);
}

void Main_Serve_Qml::SubItemsInfoRcvd(QList<SubItemsInfo> val)
{
    setSubItemsInfo(val);
}

void Main_Serve_Qml::ItemsInfoRcvd(QList<ItemsInfo> val)
{
    setItemsInfo(val);
}

void Main_Serve_Qml::Print(QString val)
{
    QDomDocument doc;
    QFile file("_pos/orders/" + val +".xml");
    QFile file1("_pos/print/" + val +".xml");

    doc.setContent(&file);

    file1.open(QIODevice::ReadWrite);
    file1.write(doc.toByteArray(1));
    file1.close();

    printSignal(val);
}

void Main_Serve_Qml::v_playSound()
{
    for (int i = 0; i < 1; i++)
    {      
        QSound::play(":/pling.wav");
    }
}

