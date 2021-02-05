#include "addtocart.h"
#include "ui_addtocart.h"

AddToCart::AddToCart(QWidget *parent) :
	QDialog(parent), ui(new Ui::AddToCart)
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

AddToCart::~AddToCart(){
	delete ui;
}

void AddToCart::getBookInfo(QString id)
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
		calcTotal(price, ui->quantity->text());
	}
	db.close();
}

void AddToCart::calcTotal(QString price, QString quantity){
	if(price != "" && quantity != "" && !(quantity.toInt() < 0)) {
		ui->total->setText(QString::number(price.toDouble() * quantity.toInt()));
	}
}

void AddToCart::on_bookId_textEdited(const QString &arg1)
{
	getBookInfo(arg1);
}

void AddToCart::on_quantity_textEdited(const QString &arg1)
{
	calcTotal(ui->price->text(), arg1);
}

bool AddToCart::checkValues(QString id, QString quant, QString price, QString avail)
{
	QVector<QString> errors;
	if(id.toInt() > max || id.toInt() < 1) {
		errors.push_back("No book with that id found.");
		error(errors);
		return false;
	} if(quant == "") {
		errors.push_back("Quantity required.");
	} if(quant.toInt() <= 0) {
		errors.push_back("Quantity must be more than 0.");
	} if(quant.toInt() > avail.toInt()) {
		errors.push_back("Not enough books available.");
	} if(avail.toInt() < 1) {
		errors.push_back("That book is out of stock.");
	}
	if(errors.size() > 0)
	{
		error(errors);
		return false;
	}
	return true;
}

void AddToCart::error(QVector<QString> errors){
	ui->errorMsgs->setText(errors[0]);
	for(int i = 1; i < errors.size(); i++)
	{
	ui->errorMsgs->setText(ui->errorMsgs->text() + "\n" + errors[i]);
	}
	ui->errorMsgs->setStyleSheet("QLabel { color : red; }");
	ui->errorMsgs->show();
}

void AddToCart::on_addToCart_clicked()
{
	QString id, quant, price, avail;
	id = ui->bookId->text();
	quant = ui->quantity->text();
	price = ui->price->text();
	avail = ui->available->text();
	if(checkValues(id, quant, price, avail))
	{
		emit addSuccess(id, quant, price, avail);
	}
}

void AddToCart::on_Cancel_clicked()
{
	done(QDialog::Rejected);
}
