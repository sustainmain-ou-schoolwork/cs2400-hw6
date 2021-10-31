/**
 *   @file: car-dealer.cc
 * @author: Josh Marusek
 *   @date: 2021-10-30
 *  @brief: Gets a user's car order
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/**
 *  Function: getInteger
 *  @brief Attempts to read integers from cin until a positive integer is entered.
 * 
 *  @return a positive integer from cin
 */
int getInteger();


int main(int argc, char const *argv[]) {
    int choice;

    // read options file

    // load options

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