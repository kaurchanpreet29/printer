#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <qsharedmemory.h>
#include <QSystemTrayIcon>

#include "woocommerce_serve.h"
#include "systemtray.h"
#include "local_db_serve.h"
#include "main_serve_qml.h"

#include <QLocalSocket>
#include <QLocalServer>
#include <QQuickWindow>

#include <QThread>
#include <QPointer>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // QGuiApplication app(argc, argv);
    QApplication app(argc,argv);

    const QString appKey = "applicationKey";

    QLocalSocket *socket = new QLocalSocket();
    socket->connectToServer(appKey);

    if (socket->isOpen()) {
        socket->close();
        socket->deleteLater();
        return 0;
    }
    socket->deleteLater();

    QPointer<SystemTray> systemTrayObj = new SystemTray();

    QThread l_newThread1,
            l_newThread2;


    QPointer<Main_Serve_Qml> l_Main_Serve_QmlObj = new Main_Serve_Qml();

    QPointer<WooCommerce_serve> WooCommerce_serveObj = new WooCommerce_serve();
    QPointer<Local_db_serve> Local_db_serveObj = new Local_db_serve();


    WooCommerce_serveObj->moveToThread(&l_newThread1);
    Local_db_serveObj->moveToThread(&l_newThread2);


    QObject::connect(&l_newThread1, &QThread::started, WooCommerce_serveObj, &WooCommerce_serve::v_start);
    l_newThread1.start();
    l_newThread2.start();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("myModel1",l_Main_Serve_QmlObj);
    engine.rootContext()->setContextProperty("systemTray", systemTrayObj);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /****************************************************/
    /*               Thread Connections                 */
    /*****==================*****************************/

    QObject::connect(l_Main_Serve_QmlObj, &Main_Serve_Qml::s_GetOrders, Local_db_serveObj, &Local_db_serve::Handler_extractOrder);
    QObject::connect(Local_db_serveObj, &Local_db_serve::s_OrderInfoChanged, l_Main_Serve_QmlObj, &Main_Serve_Qml::OrderInfoRcvd);

    QObject::connect(l_Main_Serve_QmlObj, &Main_Serve_Qml::s_GetItems, Local_db_serveObj, &Local_db_serve::Handler_extractItems);
    QObject::connect(Local_db_serveObj, &Local_db_serve::s_ItemsInfoChanged, l_Main_Serve_QmlObj, &Main_Serve_Qml::ItemsInfoRcvd);
    QObject::connect(Local_db_serveObj, &Local_db_serve::s_SubItemInfoChanged, l_Main_Serve_QmlObj, &Main_Serve_Qml::SubItemsInfoRcvd);

    QObject::connect(WooCommerce_serveObj, &WooCommerce_serve::s_addOrderEntry, Local_db_serveObj, &Local_db_serve::Handler_addOrderEntry);
    QObject::connect(WooCommerce_serveObj, &WooCommerce_serve::s_addItemsEntry, Local_db_serveObj, &Local_db_serve::Handler_addItemEntry);
    QObject::connect(WooCommerce_serveObj, &WooCommerce_serve::s_addSubItemsEntry, Local_db_serveObj, &Local_db_serve::Handler_addSubItemEntry);

    QObject::connect(l_Main_Serve_QmlObj, &Main_Serve_Qml::v_GetOrderS, Local_db_serveObj, &Local_db_serve::extract_GetOrderS);
    QObject::connect(Local_db_serveObj, &Local_db_serve::s_OrderInfoSChanged, l_Main_Serve_QmlObj, &Main_Serve_Qml::SOrderInfoRcvd);

    QObject::connect(l_Main_Serve_QmlObj, &Main_Serve_Qml::s_DataChanged, Local_db_serveObj, &Local_db_serve::Handler_DateChangedOrder);
    QObject::connect(l_Main_Serve_QmlObj, &Main_Serve_Qml::s_getRecordsType, Local_db_serveObj, &Local_db_serve::RecordsType_extractOrder);

    QObject::connect(l_Main_Serve_QmlObj, &Main_Serve_Qml::allDatesSignal, Local_db_serveObj, &Local_db_serve::Handler_extractDates);
    QObject::connect(Local_db_serveObj, &Local_db_serve::allDatesSignal, l_Main_Serve_QmlObj, &Main_Serve_Qml::get_AllDates);

    QObject::connect(l_Main_Serve_QmlObj, &Main_Serve_Qml::printSignal, Local_db_serveObj, &Local_db_serve::extract_printSignal);

    /****************************************************/

    QPointer<QObject> item = engine.rootObjects().first();

    QObject::connect(item, SIGNAL(orderid(QString)),
                     l_Main_Serve_QmlObj, SLOT(v_GetItems(QString)));
    QObject::connect(item, SIGNAL(order(QString)),
                     l_Main_Serve_QmlObj, SLOT(v_GetOrder(QString)));

    QObject::connect(item, SIGNAL(datechanged(QString)),
                    l_Main_Serve_QmlObj, SLOT(DateChanged(QString)));

    QObject::connect(item, SIGNAL(printsignal(QString)),
                     l_Main_Serve_QmlObj, SLOT(Print(QString)));

    QObject::connect(item, SIGNAL(all_Records()),
                     l_Main_Serve_QmlObj, SLOT(v_GetOrders()));
   /* QObject::connect(item, SIGNAL(records(int)),
                     l_Main_Serve_QmlObj, SLOT(RecordsType(int)));*/

    /*QObject::connect(item, SIGNAL(allDates(QString)),
                     l_Main_Serve_QmlObj, SLOT(allDates(QString)));*/

    QPointer<QQuickWindow> window = qobject_cast<QQuickWindow *>(item);

    // use serveqml signal here
    /*QObject::connect(serveobj, &serve::s_OrderInfoChanged,[window]{

        window->showNormal();
        window->raise();
        window->requestActivate();
    });

    QLocalServer server;

    QObject::connect(&server,
                     &QLocalServer::newConnection,
                     [window] () {

        window->showNormal();
        window->raise();
        window->requestActivate();
       // screenback(window);
    });
    server.listen(appKey);

   // window->show();
*/

    if (engine.rootObjects().isEmpty())
        return -1;

    int result = app.exec();

    l_newThread1.quit();
    l_newThread2.quit();

    l_newThread1.wait();
    l_newThread2.wait();

    return result;
}

