#include "database.h"
using namespace std;

bool dbConnect(QSqlDatabase &db)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
	db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("book_store");
	if(db.open()){
        return true;
    } else {
        return false;
    }
}
