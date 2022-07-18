// Program Name: Login System
// Last Modification Date: 18/07/2022
// Author : Abdelrahman Mohamed
#include <iostream>
#include <fstream>
#include "Headers.h"

using namespace std;

int main()
{
    USERDATA user[100];
    ifstream ifile;
    ofstream ofile;
    loadData(ifile, user);
    cout << "Hello!" << endl;
    displayMenu(ifile, ofile, user);
    return 0;
}
