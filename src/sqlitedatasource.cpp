#include "sqlitedatasource.h"

#include <algorithm>
#include <QSql>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <string>
#include <stdexcept>
#include <vector>
#include "addressbookview.h"
#include "contact.h"
#include "errorinfo.h"
#include "databseconnection.h"
//#include "sqliteutils.h"


//Non Member Utility Functions


   
/*SQLiteDataSource::SQLiteDataSource(const std::string &filename, bool createDB):
                            database(filename,
                            (createDB ? (SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE) :
                            SQLITE_OPEN_READWRITE))
{
    createTable();
}
*/
SQLiteDataSource::SQLiteDataSource()
{
    database;
}



SQLiteDataSource::~SQLiteDataSource()
{
}

void SQLiteDataSource::createTable()
{
  /* //Prepare the SQLite statement
    std::string sqlStr = "CREATE TABLE IF NOT EXISTS Contacts"
                        "(id INTEGER PRIMARY KEY,"
                        "firstname TEXT NOT NULL,"
                        "lastname TEXT NOT NULL,"
                        "phonenum TEXT NOT NULL,"
                        "address TEXT,"
                        "email TEXT);";

    SQLiteStatementHandle createTableStatement(sqlStr, database.get());

    //Execute the SQLite statement
    int result = sqlite3_step(createTableStatement.get());

    if(result != SQLITE_DONE)
    {
        std::string errMsg = sqlite3_errmsg(database.get());
        throw std::runtime_error(errMsg);
    }
*/
 
}


bool SQLiteDataSource::isViewRegistered(AddressBookView *viewToCheck)
{
    std::vector<AddressBookView*>::const_iterator it;
    it = std::find(observerList.begin(), observerList.end(), viewToCheck);

    if(it == observerList.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void SQLiteDataSource::registerView(AddressBookView *viewToRegister)
{
    
    if(viewToRegister && !isViewRegistered(viewToRegister))
    {
        observerList.push_back(viewToRegister);
    }

}

void SQLiteDataSource::removeView(AddressBookView *viewToRemove)
{
    if(viewToRemove)
    {
        //Find the view in the list and remove it
        std::vector<AddressBookView*>::iterator it;
        it = std::find(observerList.begin(), observerList.end(), viewToRemove);

        if(it != observerList.end())
            observerList.erase(it);

    }
 
}

void SQLiteDataSource::notifyViews()
{
    std::vector<AddressBookView*>::iterator it;

    for(it = observerList.begin(); it != observerList.end(); it++)
    {
        (*it)->updateView();
    }

}
//void SQLiteDataSource::fillContactFromRow(sqlite3_stmt *s, Contact& c)

void SQLiteDataSource::fillContactFromRow(Contact& c)
{
 
 /*   c.id = sqlite3_column_int(s, 0);
    c.firstName = reinterpret_cast<const char*>(sqlite3_column_text(s, 1));
    c.lastName = reinterpret_cast<const char*>(sqlite3_column_text(s, 2));
    c.phoneNumber = reinterpret_cast<const char*>(sqlite3_column_text(s, 3));
    c.address = reinterpret_cast<const char*>(sqlite3_column_text(s, 4));
    c.email = reinterpret_cast<const char*>(sqlite3_column_text(s, 5));
*/
}


ErrorInfo SQLiteDataSource::getContact(Contact::ContactId id, Contact& c)
{
    qDebug()<<"Getting student rollnumber";
    qDebug()<<(id);
    Contact::ContactId CIR;
    CIR = id;
    qDebug()<<"The number is";
    qDebug()<<CIR;
    QString query_String = "Select * from addbook where id= " +QString::number(CIR);
    qDebug()<<"Content is";
    qDebug()<<query_String;

    QSqlQuery query(query_String);
    query.exec();
    qDebug()<<"Working";
    if(query.first())
    {
        qDebug()<<(query.value(1));
        qDebug()<<"Working1";
        c.firstName=query.value(1).toString();
        c.lastName=query.value(2).toString();
        c.phoneNumber=query.value(3).toLongLong();
        c.address=query.value(4).toString();
        c.email=query.value(5).toString();

        qDebug()<<c.firstName;
        qDebug()<<c.lastName ;
        qDebug()<<c.phoneNumber ;
        qDebug()<<c.address ;
        qDebug()<<c.email ;

    }







    fillContactFromRow(c);

    return ErrorInfo(ERR_OK, "OK");






 /*   //create sql prepared statement
    std::string sqlStr = "SELECT * FROM Contacts WHERE id=?;";

    SQLiteStatementHandle queryStatement(sqlStr, database.get());

    //bind parameters to SQL statement
    sqlite3_bind_int(queryStatement.get(), 1, id);

    //execute statement & check result
    int stepResult = sqlite3_step(queryStatement.get());
    
   if(stepResult != SQLITE_ROW)
   {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not retrieve contact.");
    }

   */ //package column values into Out parameter
    }

ErrorInfo SQLiteDataSource::getAllContacts(Contact::ContactRecordSet &rs)
{
    Contact::ContactRecordSet CRS;
    Contact temp1;
    QSqlTableModel model1;
    model1.setTable("addbook");
    model1.setSort(1,Qt::AscendingOrder);
    model1.select();
    qDebug()<<"Entered inside";
    qDebug()<<(model1.rowCount());
    for(int i=0;i<(model1.rowCount());++i)
    {
        QSqlRecord record = model1.record(i);
        temp1.id =record.value(0).toInt();
        temp1.firstName = record.value(1).toString();
        temp1.lastName = record.value(2).toString();
        temp1.phoneNumber = record.value(3).toUInt();
        temp1.address = record.value(4).toString();
        temp1.email = record.value(5).toString();

        CRS.push_back(temp1);
    }
    rs = CRS;








  /*  //create sql prepared statement
    std::string sqlStr = "SELECT * FROM Contacts;"; 

    SQLiteStatementHandle queryStatement(sqlStr, database.get());


    //execute statement & check result
    int stepResult = sqlite3_step(queryStatement.get());
    
    if(stepResult != SQLITE_ROW)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not retrieve contacts.");
    }

    Contact::ContactRecordSet rows;

    while(stepResult == SQLITE_ROW)
    {
        Contact temp;
                
        //package column values into Out parameter 
        fillContactFromRow(queryStatement.get(), temp);
        rows.push_back(temp);

        stepResult = sqlite3_step(queryStatement.get());
    }

    rs = rows;
*/
    return ErrorInfo(ERR_OK, "OK");
}


ErrorInfo SQLiteDataSource::addContact(const Contact& c)
{

    QSqlTableModel model;
    model.setTable("addbook");
    model.setEditStrategy(QSqlTableModel::OnFieldChange);
    QSqlRecord record = model.record();
   // record.setValue("id",QVariant(c.id));
    record.setValue("firstname",QVariant(c.firstName));
    record.setValue("lastname",QVariant(c.lastName));
    record.setValue("phno",QVariant(c.phoneNumber));
    record.setValue("address",QVariant(c.address));
    record.setValue("email",QVariant(c.email));
    if(model.insertRecord(model.rowCount()-1,record))
        qDebug()<<"Inserted";
   // qDebug()<<c.id;
    qDebug()<<c.firstName;
    qDebug()<<c.lastName;
    qDebug()<<c.phoneNumber;
    qDebug()<<c.address;
    qDebug()<<c.email;


  /*  //create sql prepared statement
    std::string sqlStr = "INSERT INTO Contacts VALUES("
                        "NULL,?,?,?,?,?);";
    
    SQLiteStatementHandle insertStatement(sqlStr, database.get()); 

    //bind contact fields to variables in SQL statement
    //id is not bound, it is an auto-incrementing key field
    sqlite3_bind_text(insertStatement.get(), 1, c.firstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 2, c.lastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 3, c.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 4, c.address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(insertStatement.get(), 5, c.email.c_str(), -1, SQLITE_STATIC);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(insertStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not add contact");
    }

*/
    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo SQLiteDataSource::updateContact(Contact::ContactId id, const Contact& c)
{

    QString UpdateC = "update addbook SET firstname='"+c.firstName + "'where id ="+ QString::number(id);
    QSqlQuery UpdateQ(UpdateC);
    UpdateQ.exec();



  /*  //create sql prepared statement
    std::string sqlStr = "UPDATE Contacts SET "
                         "firstname=?, lastname=?,"
                         "phonenum=?, address=?,"
                         "email=? WHERE id=?;"; 
    
    SQLiteStatementHandle updateStatement(sqlStr, database.get()); 

    sqlite3_bind_text(updateStatement.get(), 1, c.firstName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 2, c.lastName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 3, c.phoneNumber.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 4, c.address.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateStatement.get(), 5, c.email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(updateStatement.get(), 6, id);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(updateStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not update contact.");
    }
*/
    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}

ErrorInfo SQLiteDataSource::deleteContact(Contact::ContactId id)
{
    QString DelC = "DELETE FROM addbook where id="+QString::number(id);
    QSqlQuery DelQ(DelC);
    DelQ.exec();




  /*  //create sql prepared statement
    std::string sqlStr = "DELETE FROM Contacts WHERE id=?;"; 
    
    SQLiteStatementHandle deleteStatement(sqlStr, database.get()); 

    sqlite3_bind_int(deleteStatement.get(), 1, id);

    //execute SQL statement & check results
    int stepResult = sqlite3_step(deleteStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not delete contact.");
    }
*/
    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}


ErrorInfo SQLiteDataSource::deleteAllContacts()
{
  /*  //create sql prepared statement
    std::string sqlStr = "DELETE FROM Contacts;"; 
    
    SQLiteStatementHandle deleteAllStatement(sqlStr, database.get()); 

    //execute SQL statement & check results
    int stepResult = sqlite3_step(deleteAllStatement.get());
    
    if(stepResult != SQLITE_DONE)
    {
        return ErrorInfo(ERR_DATASOURCE_ERROR, "Could not delete contacts.");
    }
*/
    notifyViews();

    return ErrorInfo(ERR_OK, "OK");
}

