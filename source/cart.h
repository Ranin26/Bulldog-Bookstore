#ifndef CART_H
#define CART_H
#include <QVector>
#include <QString>

class Cart
{
public:
	Cart();
	bool addToCart(int id, int qt, double price);//, QString names
	QVector<int> getItems();
	QVector<int> getQuantities();
	QVector<double> getPrices();
	int getCount();
	void clear();
	//QVector<QString> getNames();

private:
	QVector<int> items;
	QVector<int> quantities;
	QVector<double> prices;
	int count;
	//QVector<QString> names;
};

#endif // CART_H
