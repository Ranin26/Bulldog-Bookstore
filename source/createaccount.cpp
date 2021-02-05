#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(QWidget *parent) :
	QDialog(parent), ui(new Ui::CreateAccount)
{
	ui->setupUi(this);
	ui->errorMsgs->hide();
}

CreateAccount::~CreateAccount()
{
	delete ui;
}

bool CreateAccount::newAcct(QString uname, QString pword, QString &fname, QString &lname, QString &email, int role)
{
	QSqlDatabase db;
	dbConnect(db);
	QSqlQuery query;
	QString text = "select * from book_store.accounts;";
	if (!query.exec(text)){
		QMessageBox::about(this, "Failed", "code: " + query.lastError().databaseText());
	} else {
		while(query.next()){
			if(query.value(1).toString() == uname){
				QMessageBox::about(this, "Failed", "Username already in use.");
				return false;
			}
			if(query.value(5).toString() == email){
				QMessageBox::about(this, "Failed", "Email already in use.");
				return false;
			}
		}
	}

	text = "INSERT INTO book_store.accounts(username, password, firstname, lastname, email, r_id) VALUES('" + uname +
			"', '" + pword + "', '" + fname + "', '" + lname + "', '" + email + "', " + QString::number(role) + ");";
	if (!query.exec(text)){
		QMessageBox::about(this, "Failed", "code: " + query.lastError().text());
	} else {
		return true;
	}
	return false;
}

bool CreateAccount::checkValues(QString &uname, QString &pword, QString &fname, QString &lname, QString &email){
	vector<QString> errors;
	if(uname == ""){
		errors.push_back("Username required.");
	} if(pword == ""){
		errors.push_back("Password required.");
	} if(fname == ""){
		errors.push_back("First name required.");
	} if(lname == ""){
		errors.push_back("Last name required.");
	} if(email == ""){
		errors.push_back("Email required.");
	}
	if(uname.length() < 1){
		errors.push_back("Username not long enough.");
	} if(pword.length() < 1){
		errors.push_back("Password not long enough.");
	} if(!email.contains("@")){
		errors.push_back("Email not correct format.");
	}
	if(errors.size() > 0){
		error(errors);
		return false;
	}
	return true;
}

void CreateAccount::error(vector<QString> errors){
	ui->errorMsgs->setText(errors[0]);
	for(size_t i = 1; i < errors.size(); i++)
	{
	ui->errorMsgs->setText(ui->errorMsgs->text() + "\n" + errors[i]);
	}
	ui->errorMsgs->setStyleSheet("QLabel { color : red; }");
	ui->errorMsgs->show();
}

void CreateAccount::on_createAcct_clicked()
{
	QString uname = ui->uname->text();
	QString pword = ui->pword->text();
	QString fname = ui->fname->text();
	QString lname = ui->lname->text();
	QString email = ui->email->text();
	QString roles = ui->role->text();
	int r_id;
	if(roles == "admin")
	{
		r_id = ROLES::Admin;
	} else if (roles == "manager"){
		r_id = ROLES::Manager;
	} else {
		r_id = ROLES::User;
	}

	if(checkValues(uname, pword, fname, lname, email))
	{
		if(newAcct(uname, pword, fname, lname, email, r_id))
		{
			emit acctSuccess(uname, pword, fname, lname, email);
			QMessageBox::information(this, "Create Success", "You have successfully created");
		} else {
			QMessageBox::warning(this, "Create Failed", "Create unsuccessful, Try again.");
		}
	}
}

void CreateAccount::on_Cancel_clicked()
{
	done(QDialog::Rejected);
}
