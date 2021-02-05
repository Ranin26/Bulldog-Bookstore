#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QString>
#include <sstream>
#include <string>
#include <vector>
#include "database.h"
#include "account.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
	Account getAccount() const;
	bool login(QString uname, QString pword, QString &fname, QString &lname, QString &email, int &role);
signals:
	void loginSuccess(QString fname, QString lname, QString email, int role);

private slots:
	void on_Login_2_clicked();
	void on_Cancel_clicked();

private:
    Ui::Login *ui;
};

using namespace std;
#endif // LOGIN_H
