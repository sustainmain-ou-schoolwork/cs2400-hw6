/**
 *   @file: car-dealer.cc
 * @author: Josh Marusek
 *   @date: 2021-10-30
 *  @brief: Gets a user's car order
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

/**
 *  Function: getInteger
 *  @brief Attempts to read integers from cin until a positive integer is entered.
 * 
 *  @return a positive integer from cin
 */
int getInteger();


struct Option {
    int price;
    string name;
};

int main(int argc, char const *argv[]) {
    int choice;
    string lineIn;

    vector<Option> options;

    // read options file
    ifstream optionFile;
    optionFile.open("options.txt");
    if (optionFile.fail()) {
		cout << "Failed to open file." << endl;
		exit(0);
	}

    // load options
    while (getline(optionFile, lineIn)) {
        Option option;
        int spaceIndex = lineIn.find(" ");
        option.price = stoi(lineIn.substr(0, spaceIndex));
        option.name = lineIn.substr((spaceIndex + 1), (lineIn.length() - spaceIndex));

        options.push_back(option);
    }

    while (true) {
        // display menu and get choice
        cout << "1. Select a model (E, L, X)" << endl;
        cout << "2. Display available options and prices" << endl;
        cout << "3. Add an option" << endl;
        cout << "4. Remove an option" << endl;
        cout << "5. Cancel order" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter a choice: ";
        choice = getInteger();

        // display selected options

        // show menu

        // get choice
    }

    return 0;
}/// main


int getInteger() {
    int result;
    do {
        cin >> result;
    } while (result < 0);

    return result;
}