#ifndef MANAGEBOOKS_H
#define MANAGEBOOKS_H

#include <QDialog>
#include "addbook.h"

namespace Ui {
class ManageBooks;
}

namespace mBooks {
	enum Status{Add, Delete, Update};
}

class ManageBooks : public QDialog
{
	Q_OBJECT

public:
	explicit ManageBooks(QWidget *parent = nullptr);
	~ManageBooks();
	bool checkValues(int status, QString price, QString avail="", QString id="");
	void error(QVector<QString> errors);
	void getBookInfo(QString id);
signals:
	void mBooksSuccess(int status, QString id, QString price="", QString avail="");
private slots:
	void on_bookId_textEdited(const QString &arg1);
	void on_add_clicked();
	void on_delete_2_clicked();
	void on_update_clicked();
	void on_Cancel_clicked();

private:
	Ui::ManageBooks *ui;
	AddBook *addBookDiag;
	int max;
};

#endif // MANAGEBOOKS_H
