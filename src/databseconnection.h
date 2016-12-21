#ifndef DATABSECONNECTION_H
#define DATABSECONNECTION_H
#include<QSqlDatabase>
#include<QSql>

class DatabseConnection
{
public:
    DatabseConnection();


    ~DatabseConnection();


private:

    QSqlDatabase db;
};

#endif // DATABSECONNECTION_H
