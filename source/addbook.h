#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include "book.h"

namespace Ui {
class AddBook;
}

class AddBook : public QDialog
{
	Q_OBJECT

public:
	explicit AddBook(QWidget *parent = nullptr);
	~AddBook();
	bool checkValues(Book book);
	void error(QVector<QString> errors);
signals:
	void addBookSuccess(Book book);

private slots:
	void on_addBook_clicked();
	void on_Cancel_clicked();

private:
	Ui::AddBook *ui;
};

#endif // ADDBOOK_H
