#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <QDialog>
#include "cart.h"
#include <QStandardItemModel>

namespace Ui {
class Checkout;
}

class Checkout : public QDialog
{
	Q_OBJECT

public:
	explicit Checkout(Cart *_cart, QWidget *parent = nullptr);
	~Checkout();
	void fillTable();
	void purchase();
	bool updateBooks(QString, int);

private slots:
	void on_checkout_clicked();

	void on_Cancel_clicked();

private:
	Ui::Checkout *ui;
	Cart *cart;
	QStandardItemModel *model;
};

#endif // CHECKOUT_H
