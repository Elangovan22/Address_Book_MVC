#include "addressbookcontroller.h"
#include "databseconnection.h"
#include "sqlitedatasource.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

  //  QSqlDatabase dSrc("addbook.db");


   // DatabseConnection DB;
    //SqlDatabase DB("addbook.db");
    SQLiteDataSource DB;
   // AddressBookController myBook(dSrc);
      AddressBookController myBook(DB);
      myBook.start();
  //  myBook.start();
    return app.exec();
}

