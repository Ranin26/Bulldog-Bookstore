#ifndef DATABASE_H
#define DATABASE_H
#include <mysql.h>
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>


#pragma comment(lib, "advapi32.lib")

bool dbConnect(QSqlDatabase &db);
#endif
