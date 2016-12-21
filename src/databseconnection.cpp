#include "databseconnection.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSql>

DatabseConnection::DatabseConnection()
{

    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setDatabaseName("qt1");
        db.setUserName("elango");
        db.setPassword("elango");
        bool ok = db.open();
     if(ok)
        {
           qDebug() << "Connected";
        }
        else
            {
            qDebug()<<"Not Connected";
    }



}

DatabseConnection::~DatabseConnection()
{
    db.close();
}
