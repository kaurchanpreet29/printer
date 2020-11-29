#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QObject>
#include <QUuid>

struct OrderInfo {
    Q_GADGET

public:
    QString m_Date;
    QString m_OrderDate;
    QString m_Time;
    QString m_Orderid;
    QString m_FirstName;
    QString m_LastName;
    QString m_street;
    QString m_houseno;
    QString m_city;
    QString m_zip;
    QString m_email;
    QString m_phoneno;
    QString m_status;
    QString m_Company;
    QString m_DType;
    QString m_PType;

    QString m_Amount;
    QString m_Sender;
    QString m_Updated;
    QString m_Comment;
    QString m_DCost;

    Q_PROPERTY(QString Date MEMBER m_Date)
    Q_PROPERTY(QString OrderDate MEMBER m_OrderDate)
    Q_PROPERTY(QString Time MEMBER m_Time)
    Q_PROPERTY(QString Orderid MEMBER m_Orderid)
    Q_PROPERTY(QString FirstName MEMBER m_FirstName)
    Q_PROPERTY(QString LastName MEMBER m_LastName)

    Q_PROPERTY(QString Street MEMBER m_street)
    Q_PROPERTY(QString HouseNo MEMBER m_houseno)
    Q_PROPERTY(QString City MEMBER m_city)
    Q_PROPERTY(QString Zip MEMBER m_zip)
    Q_PROPERTY(QString Email MEMBER m_email)
    Q_PROPERTY(QString Phone MEMBER m_phoneno)
    Q_PROPERTY(QString Status MEMBER m_status)
    Q_PROPERTY(QString Company MEMBER m_Company)
    Q_PROPERTY(QString DType MEMBER m_DType)
    Q_PROPERTY(QString PType MEMBER m_PType)
    Q_PROPERTY(QString Sender MEMBER m_Sender)
    Q_PROPERTY(QString Updated MEMBER m_Updated)
    Q_PROPERTY(QString Comment MEMBER m_Comment)
    Q_PROPERTY(QString DCost MEMBER m_DCost)

    Q_PROPERTY(QString Amount MEMBER m_Amount)
};

Q_DECLARE_METATYPE(OrderInfo);

struct OrderInfoS {
    Q_GADGET

public:
    QString m_Date;
    QString m_OrderDate;
    QString m_Time;
    QString m_Orderid;
    QString m_FirstName;
    QString m_LastName;
    QString m_street;
    QString m_houseno;
    QString m_city;
    QString m_zip;
    QString m_email;
    QString m_phoneno;
    QString m_status;
    QString m_Company;
    QString m_DType;
    QString m_PType;

    QString m_Amount;
    QString m_Sender;
    QString m_Updated;
    QString m_Comment;
    QString m_DCost;

    Q_PROPERTY(QString Date MEMBER m_Date)
    Q_PROPERTY(QString OrderDate MEMBER m_OrderDate)
    Q_PROPERTY(QString Time MEMBER m_Time)
    Q_PROPERTY(QString Orderid MEMBER m_Orderid)
    Q_PROPERTY(QString FirstName MEMBER m_FirstName)
    Q_PROPERTY(QString LastName MEMBER m_LastName)

    Q_PROPERTY(QString Street MEMBER m_street)
    Q_PROPERTY(QString HouseNo MEMBER m_houseno)
    Q_PROPERTY(QString City MEMBER m_city)
    Q_PROPERTY(QString Zip MEMBER m_zip)
    Q_PROPERTY(QString Email MEMBER m_email)
    Q_PROPERTY(QString Phone MEMBER m_phoneno)
    Q_PROPERTY(QString Status MEMBER m_status)
    Q_PROPERTY(QString Company MEMBER m_Company)
    Q_PROPERTY(QString DType MEMBER m_DType)
    Q_PROPERTY(QString PType MEMBER m_PType)
    Q_PROPERTY(QString Sender MEMBER m_Sender)
    Q_PROPERTY(QString Updated MEMBER m_Updated)
    Q_PROPERTY(QString Comment MEMBER m_Comment)
    Q_PROPERTY(QString DCost MEMBER m_DCost)
    Q_PROPERTY(QString Amount MEMBER m_Amount)
};

Q_DECLARE_METATYPE(OrderInfoS);

struct ItemsInfo {
    Q_GADGET

public:
    QString m_Orderid;
    QString m_ArticleName;
    QString m_Count;
    QString m_Price;
    QString m_UnitPrice;
    QString m_Beverage;
    QString m_ArticleNo;
    QString m_UniqueIdentifier;


    Q_PROPERTY(QString Orderid MEMBER m_Orderid)
    Q_PROPERTY(QString ArticleName MEMBER m_ArticleName)
    Q_PROPERTY(QString Count MEMBER m_Count)

    Q_PROPERTY(QString Price MEMBER m_Price)
    Q_PROPERTY(QString UnitPrice MEMBER m_UnitPrice)
    Q_PROPERTY(QString Beverage MEMBER m_Beverage)
    Q_PROPERTY(QString ArticleNo MEMBER m_ArticleNo)
    Q_PROPERTY(QString UniqueIdentifier MEMBER m_UniqueIdentifier)


};

Q_DECLARE_METATYPE(ItemsInfo);

struct SubItemsInfo {
    Q_GADGET

public:
    QString m_Orderid;
    QString m_Itemid;
    QString m_ArticleName;
    QString m_Count;
    QString m_Price;
    QString m_UnitPrice;
    QString m_UniqueIdentifier;


    Q_PROPERTY(QString Orderid MEMBER m_Orderid)
    Q_PROPERTY(QString ArticleName MEMBER m_ArticleName)
    Q_PROPERTY(QString Count MEMBER m_Count)

    Q_PROPERTY(QString Price MEMBER m_Price)
    Q_PROPERTY(QString UnitPrice MEMBER m_UnitPrice)
    Q_PROPERTY(QString Itemid MEMBER m_Itemid)
    Q_PROPERTY(QString UniqueIdentifier MEMBER m_UniqueIdentifier)
};

Q_DECLARE_METATYPE(SubItemsInfo);

struct Calndr {
    Q_GADGET

public:
   QString m_date;

   Q_PROPERTY(QString Date MEMBER m_date)
};
Q_DECLARE_METATYPE(Calndr)

#endif // STRUCTURES_H
