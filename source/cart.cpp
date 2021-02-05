#include "cart.h"
#include <QMessageBox>
#include <QDebug>

Cart::Cart()
{
	count = 0;
}

bool Cart::addToCart(int id, int qt, double price)
{
	items.push_back(id);
	quantities.push_back(qt);
	prices.push_back(price);
	count++;
	return true;
}

void Cart::clear(){
	items.clear();
	quantities.clear();
	prices.clear();
}

int Cart::getCount(){
	return count;
}

QVector<int> Cart::getItems(){
	return items;
}

QVector<int> Cart::getQuantities(){
	return quantities;
}

QVector<double> Cart::getPrices(){
	return prices;
}
