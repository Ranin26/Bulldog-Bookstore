#include "addaccount.h"
#include "ui_addaccount.h"

AddAccount::AddAccount(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddAccount)
{
	ui->setupUi(this);
}

AddAccount::~AddAccount()
{
	delete ui;
}
