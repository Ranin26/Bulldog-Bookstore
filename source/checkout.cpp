#include "checkout.h"
#include "ui_checkout.h"
#include <QtDebug>
#include <QMessageBox>
#include "database.h"

Checkout::Checkout(Cart *_cart, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Checkout)
{
	ui->setupUi(this);
	cart = _cart;
	fillTable();
}

Checkout::~Checkout()
{
	delete ui;
}

void Checkout::fillTable()
{
	QVector<int> items = cart->getItems();
	QVector<int> quantities = cart->getQuantities();
	QVector<double> prices = cart->getPrices();
	QStringList horizontalHeader;
	QStringList verticalHeader;

	horizontalHeader.append("Book Id");
	horizontalHeader.append("Price");
	horizontalHeader.append("Quantity");
	horizontalHeader.append("Total");

	model = new QStandardItemModel(items.size(),4, this);

	double total = 0;
	double itemTotal;

	for(int r = 0; r < items.size(); r ++){
		itemTotal = quantities[r]*prices[r];
		QModelIndex index;
		index = model->index(r, 0, QModelIndex());
		model->setData(index, QString::number(items[r]));
		qDebug() << items[r];

		index = model->index(r, 1, QModelIndex());
		model->setData(index, QString::number(prices[r]));
		qDebug() << prices[r];

		index = model->index(r, 2, QModelIndex());
		model->setData(index, QString::number(quantities[r]));

		index = model->index(r, 3, QModelIndex());
		model->setData(index, QString::number(itemTotal));

		total += itemTotal;
	}

	model->setHorizontalHeaderLabels(horizontalHeader);
	ui->table->setModel(model);
	ui->total->setText(QString::number(total));
	model->setVerticalHeaderLabels(verticalHeader);
 // This is necessary to display the data on table view
	ui->table->verticalHeader()->setVisible(false);
	ui->table->verticalHeader()->setDefaultSectionSize(10);
	//ui->table->setShowGrid(false);
}

void Checkout::purchase(){
	QVector<int> items = cart->getItems();
	QVector<int> quantities = cart->getQuantities();

	for(int i = 0; i < cart->getCount(); i++)
	{
		qDebug() << quantities[i];
		updateBooks(QString::number(items[i]), quantities[i]);
	}

	QMessageBox::information(this, "Cart", "Purchase complete");
	cart->clear();
	done(QDialog::Accepted);
}

bool Checkout::updateBooks(QString id, int quantity){
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	if(dbConnect(db)){
		QSqlQuery query;
		QString text = "UPDATE book_store.book_stock SET quantity = quantity - " + QString::number(quantity)
						+ " WHERE id = " + id;
		qDebug() << text;
		if(!query.exec(text)){
			QMessageBox::about(this, "hi", "Cant UPDATE " + query.lastError().text());
		} else {
			//QMessageBox::about(this, "hi", QString::number(available));
			return true;
		}
	} else {
		QMessageBox::about(this, "hi", "Cant CONNECT 2 DB UPDATE");
	}
	return false;
}

void Checkout::on_checkout_clicked()
{
	purchase();
}

void Checkout::on_Cancel_clicked()
{
	done(QDialog::Rejected);
}
