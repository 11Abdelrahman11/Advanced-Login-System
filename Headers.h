#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

using namespace std;

struct USERDATA {
    string userName;
    string Password;
    string mobileNumber;
    string firstName;
    string lastName;
    string emailAddress;
    int ID;
};

bool validEmail (const string emailAddress);
bool validMobileNumber (const string mobileNumber);
bool validFirstName (const string firstName);
bool validLastName (const string lastName);
bool validUserName(const string userName);
bool validPassword(const string Password);
bool powerFulPaswword(const string Password);
string encrypt(string password);
string decrypt(string password);
string hidePassword (string& password);
bool repeatedEmailAddress(const USERDATA u[], const string emailAddress);
bool repeatedMobileNumber(const USERDATA u[], const string mobileNumber);
void Registration (USERDATA& u, USERDATA data[]);
void login (USERDATA data[]);
void printUserData (USERDATA u);
void saveData (ofstream& file, USERDATA u[]);
void loadData (ifstream& file, USERDATA u[]);
void displayMenu (ifstream& ifile, ofstream& ofile, USERDATA data[]);

#endif // HEADERS_H_INCLUDED
