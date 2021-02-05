#ifndef ADDTOCART_H
#define ADDTOCART_H

#include <QDialog>
#include "database.h"
#include <QString>

namespace Ui {
class AddToCart;
}

class AddToCart : public QDialog
{
	Q_OBJECT

public:
	explicit AddToCart(QWidget *parent = nullptr);
	~AddToCart();
	void getBookInfo(QString id);
	void calcTotal(QString price, QString quantity);
	bool checkValues(QString id, QString quant, QString price, QString avail);
	void error(QVector<QString> errors);

signals:
	void addSuccess(QString id, QString quant, QString price, QString avail);

private slots:
	void on_bookId_textEdited(const QString &arg1);
	void on_quantity_textEdited(const QString &arg1);
	void on_addToCart_clicked();
	void on_Cancel_clicked();

private:
	Ui::AddToCart *ui;
	int max;
	//QVector<QString> errors;
};

#endif // ADDTOCART_H
