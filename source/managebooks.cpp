#include "managebooks.h"
#include "ui_managebooks.h"
#include "database.h"

ManageBooks::ManageBooks(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ManageBooks)
{
	ui->setupUi(this);
	ui->errorMsgs->hide();
	QSqlDatabase db;
	dbConnect(db);
	QSqlQuery query;
	QString text = "SELECT max(id) max from book_store.books";
	if (!query.exec(text)){
		QMessageBox::about(this, "Failed", "Query Select failed \n");
	} else {
		if(query.next()) {
			max = query.value(0).toInt();
		}
	}
	db.close();
}

ManageBooks::~ManageBooks()
{
	delete ui;
}

void ManageBooks::getBookInfo(QString id)
{
	QString price, quantity;
	QSqlDatabase db;
	dbConnect(db);
	QSqlQuery query;
	QString text = "SELECT bs.quantity, bs.price from book_store.books b JOIN book_store.book_stock bs ON b.id = bs.id "
				   "WHERE b.id = " + id;
	if (!query.exec(text)){
		QMessageBox::about(this, "Failed", "Query Select failed \n");
	}
	else {
		if(query.next()) {
			price = query.value(1).toString();
			quantity = query.value(0).toString();
		} else {
			price = "";
			quantity = "";
		}
		ui->price->setText(price);
		ui->available->setText(quantity);
	}
	db.close();
}

void ManageBooks::on_bookId_textEdited(const QString &arg1)
{
	getBookInfo(arg1);
}

bool ManageBooks::checkValues(int status, QString id, QString price, QString avail){
	QVector<QString> errors;
	if(id.toInt() > max || id.toInt() < 1)
	{
		errors.push_back("No book with that id found.");
		error(errors);
		return false;
	}
	if(status == mBooks::Update)
	{
		if(avail == "") {
			errors.push_back("New quantity required.");
		} if(avail.toInt() < 0) {
			errors.push_back("New quantity can't be negative.");
		} if(price == "") {
			errors.push_back("New price required.");
		} if(price.toDouble() < 0) {
			errors.push_back("New price can't be negative.");
		}
	}
	if(errors.size() > 0)
	{
		error(errors);
		return false;
	}
	return true;
}

void ManageBooks::error(QVector<QString> errors){
	ui->errorMsgs->setText(errors[0]);
	for(int i = 1; i < errors.size(); i++)
	{
	ui->errorMsgs->setText(ui->errorMsgs->text() + "\n" + errors[i]);
	}
	ui->errorMsgs->setStyleSheet("QLabel { color : red; }");
	ui->errorMsgs->show();
}

void ManageBooks::on_add_clicked()
{
	addBookDiag = new AddBook(this);
	connect(addBookDiag, SIGNAL(addBookSuccess(Book)), this->parent(), SLOT(addBookSlot(Book)));
	addBookDiag->setModal(true);
	addBookDiag->exec();
}

void ManageBooks::on_delete_2_clicked()
{
	QString id;
	id = ui->bookId->text();
	if(checkValues(mBooks::Delete, id))
	{
		//QMessageBox::information(this, "Delete Success", "You have successfully Delete");
		emit mBooksSuccess(mBooks::Delete, id);
	} else {
		QMessageBox::warning(this, "Delete Failed", "Delete unsuccessful, Try again.");
	}
}

void ManageBooks::on_update_clicked()
{
	QString id, price, avail;
	id = ui->bookId->text();
	price = ui->price->text();
	avail = ui->available->text();
	if(checkValues(mBooks::Update, id, price, avail))
	{
		//QMessageBox::information(this, "Update Success", "You have successfully Update");
		emit mBooksSuccess(mBooks::Update, id, price, avail);
		//done(QDialog::Accepted);
	} else {
		QMessageBox::warning(this, "Update Failed", "Update unsuccessful, Try again.");
	}
}

void ManageBooks::on_Cancel_clicked()
{
	done(QDialog::Rejected);
}
