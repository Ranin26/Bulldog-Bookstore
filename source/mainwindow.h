#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QtDebug>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include "login.h"
#include "account.h"
#include "book.h"
#include "createaccount.h"
#include "cart.h"
#include "addtocart.h"
#include "managebooks.h"
#include "checkout.h"
#include <QtSql>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	bool updateBooks(QString, int);
	bool updateBook(QString id, QString price, QString avail);
	bool deleteBook(QString id);
	bool addBook(Book book);

public slots:
	void loginSlot(QString fname, QString lname, QString email, int _role);
	void loginDone(int status);
	void acctSlot(QString uname, QString pword, QString fname, QString lname, QString email);
	void addSlot(QString id, QString quantity, QString price, QString available);
	void mBooksSlot(int status, QString id, QString price="", QString avail="");
	void addBookSlot(Book book);

private slots:
	void on_Search_clicked();
    void on_Login_clicked();
    void on_CreateAccount_clicked();
	void on_Logout_clicked();
	void on_addBooks_clicked();
	void on_manageBooks_clicked();
	void on_checkout_clicked();

private:
	Ui::MainWindow *ui;
    Login *loginDiag;
	CreateAccount *acctDiag;
	AddToCart *cartDiag;
	ManageBooks *mBooksDiag;
	Checkout *checkoutDiag;
	Account *current;
	QSqlRelationalTableModel *table;
	Cart *cart;
	QSqlDatabase db;
};
#endif // MAINWINDOW_H
