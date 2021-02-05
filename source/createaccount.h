#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include <QString>
#include <sstream>
#include <string>
#include <vector>
#include "database.h"
#include "account.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QDialog
{
	Q_OBJECT

public:
	explicit CreateAccount(QWidget *parent = nullptr);
	~CreateAccount();
	bool newAcct(QString uname, QString pword, QString &fname, QString &lname, QString &email, int role = 1);
	bool checkValues(QString &uname, QString &pword, QString &fname, QString &lname, QString &email);
signals:
	void acctSuccess(QString uname, QString pword, QString fname, QString lname, QString email);

private slots:
	void on_createAcct_clicked();
	void error(vector<QString> errors);
	void on_Cancel_clicked();

private:
	Ui::CreateAccount *ui;
};

#endif // CREATEACCOUNT_H
