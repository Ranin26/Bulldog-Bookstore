#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->addBooks->hide();
	ui->checkout->hide();
	ui->manageBooks->hide();
	current = NULL;
	ui->searchBox->setPlaceholderText(" search by title, ISBN, author, course, etc..");
	ui->Logout->hide();
	loginDiag = new Login(this);
	acctDiag = new CreateAccount(this);
	connect(loginDiag, SIGNAL(loginSuccess(QString, QString, QString, int)), this , SLOT(loginSlot(QString, QString, QString, int)));
	connect(acctDiag, SIGNAL(acctSuccess(QString, QString, QString, QString, QString)), this , SLOT(acctSlot(QString, QString, QString, QString, QString)));
	connect(loginDiag, SIGNAL(finished(int)), this , SLOT(loginDone(int)));
	ui->Search->click();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_Search_clicked()
{
	if(dbConnect(db)){
		QString term = ui->searchBox->text();
		table = new QSqlRelationalTableModel();
		table->setTable("books");
		table->setFilter("name LIKE '%"+term+"%' OR author LIKE '%"+term+"%' OR ISBN like '%"+term+"%' OR major LIKE '%"
						 +term+"%' OR course LIKE '%"+term+"%'");
		table->setRelation(7, QSqlRelation("book_stock", "id", "quantity"));
		table->setRelation(8, QSqlRelation("book_stock", "id", "price"));
		table->select();
		ui->table->setModel(table);
		ui->table->resizeColumnsToContents();
		ui->table->resizeRowsToContents();
		ui->table->horizontalHeader ()->setStyleSheet ("QHeaderView{font: 9pt Verdana; color: black;}");
		ui->table->verticalHeader ()->setVisible (false);
		ui->table->setAlternatingRowColors(true);
		ui->table->setStyleSheet("alternate-background-color:grey; background-color:white;");
    } else {
        QMessageBox::about(this, "Failed", "Failed database connection.");
	}
	db.close();
}

void MainWindow::on_addBooks_clicked()
{
	cartDiag = new AddToCart(this);
	connect(cartDiag, SIGNAL(addSuccess(QString, QString, QString, QString)), this , SLOT(addSlot(QString, QString, QString, QString)));
	cartDiag->setModal(true);
	cartDiag->exec();
}

void MainWindow::addSlot(QString id, QString quantity, QString price, QString available){
	if(cart->addToCart(id.toInt(), quantity.toInt(), price.toDouble())){
		QMessageBox::about(this, "hi", "Item(s) added to cart.");
	}else {
		QMessageBox::about(this, "hi", "Cant addToCart");
	}
	cartDiag->close();
	ui->Search->click();
}

bool MainWindow::updateBooks(QString id, int quantity){
	if(dbConnect(db)){
		QSqlQuery query;
		QString text = "UPDATE book_store.book_stock SET quantity = quantity - " + QString::number(quantity)
						+ " WHERE id = " + id;
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

void MainWindow::on_Login_clicked()
{
	loginDiag->setModal(true);
	loginDiag->exec();
}

void MainWindow::loginSlot(QString fname, QString lname, QString email, int _role) {
	current = new Account(loginDiag->getAccount());
	current->setEmail(email.toStdString());
	current->setFirstN(fname.toStdString());
	current->setLastN(lname.toStdString());
	current->setRole(_role);
	QString role;
	switch(_role){
		case ROLES::Admin:
			role = "Admin";
			break;
		case ROLES::User:
			role = "User";
			break;
		case ROLES::Manager:
			role = "Manager";
			break;
		default:
			break;
	}
	if(current->getRole() != ROLES::Admin)
		ui->CreateAccount->hide();
	if(current->getRole() != ROLES::User){
		ui->manageBooks->show();
	}
	ui->addBooks->show();
	ui->checkout->show();
	ui->Login->hide();
	ui->DisplayName->setText(QString::fromStdString("Logged in as: " + current->getFirstN() +" "+ current->getLastN())+
							 ", " + role);
	ui->Logout->show();
	//loginDiag->close();
	cart = new Cart();
	//ui->Search->click();
}

void MainWindow::loginDone(int status) {
	if(status == QDialog::Accepted){
	} else if(status == QDialog::Rejected){
	}
	loginDiag->close();
	ui->Search->click();
}

void MainWindow::on_CreateAccount_clicked()
{
	acctDiag->setModal(true);
	acctDiag->exec();
}

void MainWindow::acctSlot(QString uname, QString pword, QString fname, QString lname, QString email) {
	acctDiag->close();
	ui->Search->click();
}
void MainWindow::on_Logout_clicked()
{
	ui->DisplayName->setText("");
	ui->Logout->hide();
	ui->manageBooks->hide();
	ui->addBooks->hide();
	ui->checkout->hide();
	ui->Login->show();
	ui->CreateAccount->show();
	current = NULL;
	delete cart;
}


void MainWindow::mBooksSlot(int status, QString id, QString price, QString avail){
	if(status == mBooks::Update){
		updateBook(id, price, avail);
	} if(status == mBooks::Delete){
		deleteBook(id);
	}
}

bool MainWindow::updateBook(QString id, QString price, QString avail){
	if(dbConnect(db)){
		QSqlQuery query;
		QString text = "UPDATE book_store.book_stock SET quantity = " + avail + ", price = " + price
						+ " WHERE id = " + id;
		if(!query.exec(text)){
			QMessageBox::about(this, "hi", "Cant UPDATE " + query.lastError().text());
		} else {
			QMessageBox::about(this, "hi", avail);
			db.close();
			return true;
		}
	} else {
		QMessageBox::about(this, "hi", "Cant CONNECT 2 DB UPDATE");
	}
	db.close();
	return false;
}

bool MainWindow::deleteBook(QString id){
	if(dbConnect(db)){
		QSqlQuery query;
		QString text = "DELETE FROM book_store.books WHERE id = " + id +
						"; DELETE FROM book_store.book_stock WHERE id = " + id + ";";
		if(!query.exec(text)){
			QMessageBox::about(this, "hi", "Cant DELETE " + query.lastError().text());
		} else {
			QMessageBox::about(this, "hi", id);
			db.close();
			return true;
		}
	} else {
		QMessageBox::about(this, "hi", "Cant CONNECT 2 DB UPDATE");
	}
	db.close();
	return false;
}

void MainWindow::addBookSlot(Book book){
	addBook(book);
}

bool MainWindow::addBook(Book book){
	if(dbConnect(db)){
		QSqlQuery query;
		QString text = "INSERT INTO book_store.books(name, ISBN, author, pages, major, course) VALUES"
						"('"+book.getTitle()+"', '"+book.getISBN()+"', '"+book.getAuthor()+"', "+book.getPages()+
						", '"+book.getMajor()+"', '"+book.getCourse()+"'); "
						"SET @userId := LAST_INSERT_ID(); "
						"UPDATE book_store.books SET q_id = @userId, p_id = @userId WHERE id = @userId; "
						"INSERT INTO book_store.book_stock(id, quantity, price) VALUES"
						 "(@userId, " + book.getQuantity() + ", " + book.getPrice() + ");";
		if(!query.exec(text)){
			QMessageBox::about(this, "hi", "Cant INSERT " + query.lastError().text());
			db.close();
			return false;
		} else {
			QMessageBox::about(this, "hi", "GOOD");
			db.close();
			return true;
		}
	} else {
		QMessageBox::about(this, "hi", "Cant CONNECT 2 DB UPDATE");
	}
	db.close();
	return false;
}

void MainWindow::on_manageBooks_clicked()
{
	mBooksDiag = new ManageBooks(this);
	connect(mBooksDiag, SIGNAL(mBooksSuccess(int, QString, QString, QString)), this , SLOT(mBooksSlot(int, QString, QString, QString)));
	mBooksDiag->setModal(true);
	mBooksDiag->exec();
}

void MainWindow::on_checkout_clicked()
{
	if(cart->getCount()< 1){
		QMessageBox::warning(this, "Cart", "No items in cart.");
	} else {
		checkoutDiag = new Checkout(cart, this);
		checkoutDiag->setModal(true);
		checkoutDiag->exec();
	}
}
