#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <vector>
#include "database.h"
#include <sstream>
#include <QString>
using namespace std;

class Book {
public:
	void setTitle(QString str) { title = str; }
	void setISBN(QString str) { isbn = str; }
	void setAuthor(QString str) { author = str; }
	void setMajor(QString str) { major = str; }
	void setCourse(QString str) { course = str; }
	void setPages(QString str) { pages = str; }
	void setQuantity(QString str) { quantity = str; }
	void setPrice(QString str) { price = str; }
	QString getTitle() { return title; }
	QString getISBN() { return isbn; }
	QString getAuthor() { return author; }
	QString getMajor() { return major; }
	QString getCourse() { return course; }
	QString getPages() { return pages; }
	QString getQuantity() { return quantity; }
	QString getPrice() { return price; }
private:
	QString title;
	QString isbn;
	QString author;
	QString pages;
	QString major;
	QString course;
	QString quantity;
	QString price;
};
#endif // BOOK_H
