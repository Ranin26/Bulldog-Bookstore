#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Login)
{
	ui->setupUi(this);
}

Login::~Login()
{
	delete ui;
}

Account Login::getAccount() const {
	Account acct { ui->username->text().toStdString(), ui->password->text().toStdString() };
	return acct;
}

bool Login::login(QString uname, QString pword, QString &fname, QString &lname, QString &email, int &role)
{
	QSqlDatabase db;
	dbConnect(db);
	QSqlQuery query;
	QString text = "SELECT * from book_store.accounts WHERE username = '" + uname + "' AND password = '" + pword + "'";
	if (!query.exec(text)){
		QMessageBox::about(this, "Failed", "Query Select failed \n");
	}
	else {
		if(query.next()) {
			fname = query.value(3).toString();
			lname = query.value(4).toString();
			email = query.value(5).toString();
			role = query.value(6).toInt();
			return true;
		} else {
			return false;
		}
	}
	return false;
}

void Login::on_Login_2_clicked()
{
	QString uname = ui->username->text(),
			pword = ui->password->text();
	QString fname, lname, email;
	int role;
	if(login(uname, pword, fname, lname, email, role))
	{
		emit loginSuccess(fname, lname, email, role);
		done(QDialog::Accepted);
	} else {
		QMessageBox::about(this, "Login unsuccessful.", "No accounts match.");
	}
}

void Login::on_Cancel_clicked()
{
	done(QDialog::Rejected);
}
