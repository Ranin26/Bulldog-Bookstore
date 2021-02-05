#include "addbook.h"
#include "ui_addbook.h"

AddBook::AddBook(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddBook)
{
	ui->setupUi(this);
}

AddBook::~AddBook()
{
	delete ui;
}

bool AddBook::checkValues(Book book){
	QVector<QString> errors;
		if(book.getTitle() == "") {
			errors.push_back("Title required.");
		} if(book.getAuthor() == "") {
			errors.push_back("Author required.");
		} if(book.getISBN() == "") {
			errors.push_back("ISBN required.");
		} if(book.getPages() == "") {
			errors.push_back("Page number required.");
		} if(book.getMajor() == "") {
			errors.push_back("Major required.");
		} if(book.getCourse() == "") {
			errors.push_back("Course required.");
		} if(book.getQuantity() == "") {
			errors.push_back("Quantity required.");
		} if(book.getQuantity().toInt() < 0) {
			errors.push_back("Quantity can't be negative.");
		} if(book.getPrice() == "") {
			errors.push_back("Price required.");
		} if(book.getPrice().toDouble() < 0) {
			errors.push_back("Price can't be negative.");
		} if(book.getPages().toInt() < 0) {
			errors.push_back("Quantity can't be negative.");
		}
	if(errors.size() > 0)
	{
		error(errors);
		return false;
	}
	return true;
}

void AddBook::error(QVector<QString> errors){
	ui->errorMsgs->setText(errors[0]);
	for(int i = 1; i < errors.size(); i++)
	{
	ui->errorMsgs->setText(ui->errorMsgs->text() + "\n" + errors[i]);
	}
	ui->errorMsgs->setStyleSheet("QLabel { color : red; }");
	ui->errorMsgs->show();
}

void AddBook::on_addBook_clicked()
{
	Book book;
	book.setTitle(ui->Title->text());
	book.setISBN(ui->ISBN->text());
	book.setAuthor(ui->author->text());
	book.setMajor(ui->major->text());
	book.setCourse(ui->course->text());
	book.setPages(ui->pages->text());
	book.setQuantity(ui->quantity->text());
	book.setPrice(ui->price->text());
	if(checkValues(book))
	{
		QMessageBox::information(this, "Add Success", "You have successfully Add");
		emit addBookSuccess(book);
	} else {
		QMessageBox::warning(this, "Add Failed", "Add unsuccessful, Try again.");
	}
}

void AddBook::on_Cancel_clicked()
{
	done(QDialog::Rejected);
}
