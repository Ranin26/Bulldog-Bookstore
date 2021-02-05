#include "database.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std; 

//awoolen
//123

//login

void login(string uname, string pword);
void signup(string uname, string pword, string email);
void addAccount(string uname, string pword, string email);

class Account {
public:

private:
	string uname;
	string pword;	
	string email;
};

class Book {
public:
	void setTitle(string str) { title = str; }
	void setISBN(string str) { isbn = str; }
	void setAuthor(string str) { author = str; }
	void setMajor(string str) { major = str; }
	void setCourse(string str) { course = str; }
	void setPages(int num) { pages = num; }
	string getTitle() { return title; }
	string getISBN() { return isbn; }
	string getAuthor() { return author; }
	string getMajor() { return major; }
	string getCourse() { return course; }
	int getPages() { return pages; }
private:
	string title;
	string isbn;
	string author;
	int pages;
	string major;
	string course;
};

class BookList {
public:
	void searchBooks(string term);
	void printBooks();
private:
	vector<Book> books;
};

int main()
{
	login("awoolen", "123");
	signup("jcena", "456", "jcena@gmail.com");

	BookList results;
	results.searchBooks("a");
	
	results.printBooks();
	return 0;
}

void login(string uname, string pword)
{
	MYSQL* conn = NULL;
	dbConnect(conn);

	//const char* query = new char[512];
	stringstream query;
	string str;
	MYSQL_ROW row;
	MYSQL_RES* res;
	query << "Select * from book_store.accounts where username = '" << uname << "' and password ='" << pword << "'";
	str = query.str();
	if (mysql_query(conn, str.c_str()))
	{
		cout << "Query Select failed \n";
		system("pause");
		exit(1);
	}
	else {
		res = mysql_use_result(conn);
		if ((row = mysql_fetch_row(res)))
		{
			cout << "Login successful.\n";
		}
		else {
			cout << "Login unsuccessful.\n";
		}
	}
}

void signup(string uname, string pword, string email)
{
	bool error = false;
	MYSQL* conn = NULL;
	dbConnect(conn);

	//const char* query = new char[512];
	stringstream query;
	string str;
	MYSQL_ROW row;
	MYSQL_RES* res;
	query << "Select * from book_store.accounts";
	str = query.str();
	if (mysql_query(conn, str.c_str()))
	{
		cout << "Query Select failed \n";
		system("pause");
		exit(1);
	}
	else {
		res = mysql_use_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			if (row[1] == uname)
			{
				cout << "Username already taken.\n";
				error = true;
			}
			if (row[3] == email)
			{
				cout << "Email already registered.\n";
				error = true;
			}
		}
		if (!error)
		{
			addAccount(uname, pword, email);
		}
	}
}


void addAccount(string uname, string pword, string email)
{
	bool error = false;
	MYSQL* conn = NULL;
	dbConnect(conn);

	//const char* query = new char[512];
	stringstream query;
	string str;
	MYSQL_ROW row;
	MYSQL_RES* res;
	query << "INSERT into book_store.accounts(username, password, email) VALUES('" << uname << "', '" << pword << "', '" << email << "');";
	str = query.str();
	if (mysql_query(conn, str.c_str()))
	{
		cout << "Insert query failed \n";
		system("pause");
		exit(1);
	} else {
		cout << "Account created successful.\n";
	}
}

void BookList::searchBooks(string term)
{
	Book temp;

	MYSQL* conn = NULL;
	dbConnect(conn);

	//const char* query = new char[512];
	stringstream query;
	string str;
	MYSQL_ROW row;
	MYSQL_RES* res;
	query << "Select * from book_store.books where name like '%" << term << "%' or author like '%" << term << "' or ISBN like '%" << term << "' or major like '%" << term << "' or course like '%" << term << "'";
	str = query.str();
	if (mysql_query(conn, str.c_str()))
	{
		cout << "Select query failed \n";
		system("pause");
		exit(1);
	}
	else {
		res = mysql_use_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			temp.setISBN(row[1]);
			temp.setTitle(row[2]);
			temp.setAuthor(row[3]);
			temp.setPages(strtol(row[4], NULL, 10));
			temp.setMajor(row[5]);
			temp.setCourse(row[6]);
			books.push_back(temp);
		}
	}
}

void BookList::printBooks()
{
	for (int i = 0; i < books.size(); i++)
	{
		cout << "\n==========================\n" << endl;
		cout << books[i].getTitle() << endl;
		cout << books[i].getAuthor() << endl;
		cout << books[i].getISBN() << endl;
		cout << books[i].getMajor() << endl;
		cout << books[i].getCourse() << endl;
		cout << books[i].getPages() << endl;
	}
}
