import QtQuick 2.14
import QtQuick.Layouts 1.14
//import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Controls 2.14

ApplicationWindow {
    id: main
    visible: true
    // visibility: "FullScreen"
    visibility: "Windowed"
    width: 720
    height: 650
    title: qsTr("KHANA Liefersoftware")


    property var arrayFromFireBase: []

    /*onLoggedIn:  {
         firebaseDb.getUserValue("dates/selectedDates", {},
                                       function(success, key, value) {
                                       if(success) {
                                            for(var idx in value)
                                               arrayFromFireBase.push(new Date(value[idx].date).getTime())
                                       }})}*/

    Connections {
        target: systemTray
        // Сигнал - показать окно
        onSignalShow: {
            main.show();
        }

        // The signal - close the application by ignoring the check-box
        onSignalQuit: {
            Qt.quit()
        }

        // Minimize / maximize the window by clicking on the default system tray
        onSignalIconActivated: {
            if(main.visibility === Window.Hidden) {
                main.show()
            } else {
                main.hide()
            }
        }
    }

    // Handler window closing event
    onClosing: {
        main.hide()
    }

    function windowStateChange()
    {
        console.log("qml slot - windowStateChange");
        //show();
        //hide();
        showMinimized();
    }

    signal orderid(string value)
    signal order(string value)
    signal datechanged(string value)
    signal printsignal(string value)
    signal all_Records()
    signal records(int value)

    property var selectedday
    property var orderid_text

    Loader {
        id: loader
        anchors.fill: parent

        function reload()
        {
            var oldsource = source
            source = ''
            source = oldsource
            console.log("Reloaded")
            myModel1.v_clear();
        }
    }

    property var currdate: 0
    property var currtime: 0

    property var totalofOrder: 0
    property var deliveryCharge: 0

    function timeChanged() {
        currdate = new Date().toLocaleString(Qt.locale("de_DE"),"dd.MM.yyyy")
        currtime = new Date().toLocaleString(Qt.locale("de_DE"),"hh:mm:ss")
    }

    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: main.timeChanged()
    }

    Timer {
        id: timer
        running: false
        repeat: false
        onTriggered: loaderpp.close()
    }

    function loaderactivate(valuestring, value = 1000) {
        loaderpp.open()
        timer.interval = value
        timer.running = true
        loader.setSource(valuestring)
    }

    function loaderactivatep(value = 1000) {
        loaderpp.open()
        timer.interval = value
        timer.running = true
    }

    Popup {
        id: pp

        Loader {
            id: pploader
            source: "orderpopup.qml"
            sourceComponent: pploader.ms
        }

        background: Rectangle {
            color:"transparent"
        }

        modal: true

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }

    Popup {
        id: loaderpp

        Loader {
            id: loaderppid
            source: "loaderpopup.qml"
            sourceComponent: loaderppid.busyIndication
        }

        background: Rectangle {
            color:"transparent"
        }

        modal: true

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
    }



    Component.onCompleted:loader.setSource("landingscreen.qml");
}
