#include <iostream>
#include <fstream>
#include <cstring>
#include <regex>
#include <conio.h>
#include "Headers.h"

using namespace std;

int lastID = 0;
bool Login = false;
bool validEmail (const string emailAddress){
    regex validMail ("[a-zA-Z0-9]+[@][a-zA-Z]+[.][a-zA-Z]+([.][a-zA-Z])*");
    return regex_match(emailAddress, validMail);
}

bool validMobileNumber (const string mobileNumber){
    regex validNumber ("[0][1][0215][0-9]+");
    if (mobileNumber.length() != 11){
        return false;
    }
    return regex_match(mobileNumber, validNumber);
}

bool validFirstName (const string firstName){
    regex validFirstN ("[A-Z]*[a-z-]+");
    return regex_match(firstName, validFirstN);
}

bool validLastName (const string lastName){
    regex validLastN ("[A-Z]*[a-z-]+");
    return regex_match(lastName, validLastN);
}

bool validUserName(const string userName){
    regex validUN ("[a-zA-Z0-9]+");
    return regex_match(userName, validUN);
}

bool validPassword(const string Password){
    regex validP ("[a-zA-Z0-9!#@$_]+");
    return regex_match(Password, validP);
}

bool powerFulPaswword(const string Password){
    regex powerFullP ("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$_])[a-zA-Z0-9!#@$_]{8,}");
    return regex_match(Password, powerFullP);
}

string encrypt(string password){
    int key = 2,pSize;
    string encrypted;
    pSize = password.length();
    char arr [key][pSize];
    for (int k = 0; k < key; ++k){ // 2D array with number of rows == encryption key and number of columns == message size (number of characters);
        for (int s = 0; s < pSize; ++s){
            arr [k][s] = 0;
        }
    }
    for (int k = 0,s = 0,d = 1; s < pSize; k+= d,++s){ //d for direction, s for message size, k for encryption key
        arr [k][s] = password[s];
        if (k == key-1){ // changing the direction
            d = -1;
        }
        else if (k == 0) { // taking the char/s in the bottom of the rows
            d = 1;
        }
    }
    for (int k = 0; k < key; ++k){
        for (int s = 0; s < pSize; ++s){
            if (arr [k][s] != 0){
                encrypted += (arr [k][s]-20);
            }
        }
    }
    return encrypted;
}

string decrypt(string password){
    int key = 2,epSize;
    string message;
    epSize = password.length();
    char arr [key][epSize];
    for (int k = 0; k < key; ++k){ // 2D array with number of rows == encryption key and number of columns == encrypted message size (number of characters);
        for (int s = 0; s < epSize; ++s){
            arr [k][s] = 0;
        }
    }
    for (int k = 0,s = 0,d = 1; s < epSize; k += d,++s){ //d for direction, s for encrypted message size, k for encryption key
        arr [k][s] = '*'; // putting '*' char in the right positions of the encryption method
        if (k == key-1){ // changing the direction
            d = -1;
        }
        else if (k == 0) { // taking the char/s in the bottom of the rows
            d = 1;
        }
    }
    int counter = 0;
    for (int k = 0; k < key; ++k){ //d for direction, s for encrypted message size, k for encryption key
        for (int s = 0; s < epSize; ++s){
            if (arr [k][s] == '*'){
                arr [k][s] = password[counter++];
            }
        }
    }
    for (int k = 0,s = 0,d = 1; s < epSize; k += d,++s){ //d for direction, s for message size, k for encryption key
        message += (arr [k][s]+20);
        if (k == key-1){ // changing the direction
            d = -1;
        }
        else if (k == 0) { // taking the char/s in the bottom of the rows
            d = 1;
        }
    }
    return message;
}

string hidePassword (string& password){
    string pass;
    char chr;
    while(true){
        for(int i = 0; i < 100; i++){
            chr = getch();
            if(chr == '\b' && i >= 1){
                cout << '\b';
                cout << " ";
                cout << '\b';
                i = i - 2;
            }
            else if(chr != '\b' && chr != '\r'){
                cout << '*';
                pass += chr;
            }
            else if(chr == '\r'){
                break;
            }
            else{
                if(i == 0){
                    i = i - 1;
                }
            }
        }
        if(chr == '\r'){
            break;
        }
    }
    cout << endl;
    password = pass;
    return password;
}

bool repeatedEmailAddress(const USERDATA u[], const string emailAddress){
    bool result;
    for (int i = 0 ; i < lastID ; i ++){
        if (u[i].emailAddress == emailAddress){
            result = true;
            break;
        }
        else{
            result = false;
        }
    }
    return result;
}

bool repeatedMobileNumber(const USERDATA u[], const string mobileNumber){
    bool result;
    for (int i = 0 ; i < lastID ; i ++){
        if (u[i].mobileNumber == mobileNumber){
            result = true;
            break;
        }
        else{
            result = false;
        }
    }
    return result;
}

void Registration (USERDATA& u, USERDATA data[]){
    cout << "Enter Your FirstName: ";
    cin >> u.firstName;
    while (!validFirstName(u.firstName)){
        cout << "Sorry That is not a Valid FirstName" << endl;
        cout << "Enter a Valid FirstName: ";
        cin >> u.firstName;
    }
    cout << "Enter Your LastName: ";
    cin >> u.lastName;
    while (!validLastName(u.lastName)){
        cout << "Sorry That is not a Valid LastName" << endl;
        cout << "Enter a Valid LastName: ";
        cin >> u.lastName;
    }
    cout << "Enter Your UserName: ";
    cin >> u.userName;
    while (!validUserName(u.userName)){
        cout << "Sorry That is not a Valid UserName" << endl;
        cout << "Enter a Valid UserName: ";
        cin >> u.userName;
    }
    cout << "Enter Your Password: ";
    cin >> u.Password;
    while (!validPassword(u.Password) || !powerFulPaswword(u.Password)){
        cout << "Sorry That is not a Valid Password" << endl;
        cout << "Enter a Valid Password (8 characters with at least one special character): ";
        cin >> u.Password;
    }
    cout << "Enter Your Email Address: ";
    cin >> u.emailAddress;
    while (!validEmail(u.emailAddress) || repeatedEmailAddress(data, u.emailAddress)){
        cout << "Sorry That is not a Valid Email Address" << endl;
        cout << "Enter a Valid Email Address: ";
        cin >> u.emailAddress;
    }
    cout << "Enter Your Mobile Number: ";
    cin >> u.mobileNumber;
    while (!validMobileNumber(u.mobileNumber) || repeatedMobileNumber(data, u.mobileNumber)){
        cout << "Sorry That is not a Valid Mobile Number" << endl;
        cout << "Enter a Valid Mobile Number: ";
        cin >> u.firstName;
    }
    u.ID = lastID + 1;
    lastID++;
    cout << "Done!" << endl;
}

void login (USERDATA data[]){
    int tries = 1;
    string userName, Password;
    cout << "Enter Your UserName: ";
    cin >> userName;
    cout << "Enter Your Password: ";
    Password = hidePassword(Password);
    for (int i = 0; i < lastID; i++){
        if (data[i].userName == userName){
            if (data[i].Password == Password){
                Login = true;
                cout << "Welcome " << data[i].firstName << endl;
            }
            else{
                while (data[i].Password == Password && tries < 4){
                    cout << "Wrong Password " << tries << "/3" << endl;
                    cout << "Enter Your Password: ";
                    Password = hidePassword(Password);
                }
            }
        }
    }
    if (!Login){
        cout << "Login Faild!" << endl;;
        cout << "Please Login Again" << endl;
    }
}

void printUserData (USERDATA u){
    cout << "Full Name: " << u.firstName << " " << u.lastName << endl;
    cout << "UserName: " << u.userName << endl;
    cout << "Password: " << u.Password << endl;
    cout << "Mobile Number: " << u.mobileNumber << endl;
    cout << "Email Address: " << u.emailAddress << endl;
}

void saveData (ofstream& file, USERDATA u[]){
    file.open("Data.txt");
    for (int i = 0; i < lastID; i++){
        file << u[i].ID;
        file << endl;
        file << u[i].userName;
        file << endl;
        file << encrypt(u[i].Password);
        file << endl;
        file << u[i].mobileNumber;
        file << endl;
        file << u[i].firstName;
        file << endl;
        file << u[i].lastName;
        file << endl;
        file << u[i].emailAddress;
        file << endl;
    }
    file.close();
}

void loadData (ifstream& file, USERDATA u[]){
    file.open("Data.txt");
    bool emptyFile = false;
    char word[100];
    int arrCounter = 0, counter = 1;
    while (!file.eof()){
        file.getline(word,100,'\n');
        if (counter == 1){
            u[arrCounter].ID = int (word[0] - '0');
            if (u[arrCounter].ID == -48 && arrCounter == 0){
                emptyFile = true;
                break;
            }
        }
        else if (counter == 2){
            u[arrCounter].userName = string{word};
        }
        else if (counter == 3){
            u[arrCounter].Password = decrypt(string{word});
        }
        else if (counter == 4){
            u[arrCounter].mobileNumber = string{word};
        }
        else if (counter == 5){
            u[arrCounter].firstName = string{word};
        }
        else if (counter == 6){
            u[arrCounter].lastName = string{word};
        }
        else if (counter == 7){
            u[arrCounter].emailAddress = string{word};
        }
        counter++;
        if (counter == 8){
            arrCounter++;
            counter = 1;
        }
    }
    cout << "Finished Loading!" << endl;
    if(!emptyFile){
        lastID = u[arrCounter - 1].ID;
    }
    cout << "Last ID: " << lastID << endl;
}

void displayMenu (ifstream& ifile, ofstream& ofile, USERDATA data[]){
    string answer;
    while (true){
        cout << "How Could I Help You Sir? " << endl;
        cout << "1- Registration" << endl;
        cout << "2- Login" << endl;
        cout << "0- END" << endl;
        cin >> answer;

        if (answer == "0"){
            break;
        }
        else if (answer == "1"){
            Registration(data[lastID], data);
            saveData(ofile, data);
        }
        else{
            login(data);
        }
    }
    saveData(ofile, data);
    cout << "Thanks For Using Our Program :)" << endl;
}
