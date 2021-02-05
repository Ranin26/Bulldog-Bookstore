#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;

namespace ROLES{
	enum roles{Admin, User, Manager};
}

class Account {
public:
    void setUserN(string str) {uname = str;}
    void setPassW(string str) {pword = str;}
    void setEmail(string str) {email = str;}
	void setLastN(string str) {lname = str;}
	void setFirstN(string str) {fname = str;}
	void setRole(int num) {role = num;}
    string getUserN() {return uname;}
    string getPassW() {return pword;}
    string getEmail() {return email;}
	string getFirstN() {return fname;}
	string getLastN() {return lname;}
	int getRole() {return role;}
	Account(string un = "", string pw = "", string em = "", string ln = "", string fn = "", int r = 1) {
        uname = un;
        pword = pw;
        email = em;
		lname = ln;
		fname = fn;
		role = r;
    }
private:
    string uname;
    string pword;
    string email;
	string lname;
	string fname;
	int role;
};
#endif // ACCOUNT_H
