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

struct Option {
    int price;
    string name;
    string nameInCaps;  // name of the option in all capital letters
};

/**
 *  Function: readInteger
 *  @brief Attempts to read integers from cin until a positive integer is entered.
 * 
 *  @return a positive integer from cin
 */
int readInteger();

/**
 *  Function: stringToUpper
 *  @brief Converts an entire string to uppercase.
 * 
 *  @param input the string to be converted
 *  @return the string in uppercase
 */
string stringToUpper(string input);

/**
 *  Function: calculatePrice
 *  @brief Calculates the price of a car.
 * 
 *  @param model the model of the car
 *  @param selectedOptions the vector containing all the selected options
 *  @param options the vector containing all the possible options
 *  @return the price of the car
 */
double calculatePrice(char model, vector<int> selectedOptions, vector<Option> options);

/**
 *  Function: readModel
 *  @brief Attempts to read models from cin until a valid model is entered.
 * 
 *  @return a valid model from cin
 */
char readModel();

/**
 *  Function: printOptions
 *  @brief Prints all available options along with their prices.
 * 
 *  @param options the vector containing all the possible options
 */
void printOptions(vector<Option> options);

/**
 *  Function: addOption
 *  @brief Prompts the user for which option to add and adds it to the selectedOptions vector.
 * 
 *  @param options the vector containing all the possible options
 *  @param selectedOptions the vector containing all the selected options
 *  @param selectedModel the car model selected
 */
void addOption(vector<Option> options, vector<int> &selectedOptions, char selectedModel);

/**
 *  Function: removeOption
 *  @brief Prompts the user for which option to remove and removes it from the selectedOptions vector.
 * 
 *  @param options the vector containing all the possible options
 *  @param selectedOptions the vector containing all the selected options
 *  @param selectedModel the car model selected
 */
void removeOption(vector<Option> options, vector<int> &selectedOptions, char selectedModel);

/**
 *  Function: resetOrder
 *  @brief Clears all selected options and the selected model.
 * 
 *  @param selectedOptions the vector containing all the selected options
 *  @param selectedModel the char containing the car model selected
 */
void resetOrder(vector<int> &selectedOptions, char &selectedModel);


int main(int argc, char const *argv[]) {
    bool quit = false;    // false until user selects quit in the main menu
    ifstream optionFile;  // file with the option data
    string lineIn;        // lines of data from the options file will be stored here
    
    vector<int> selectedOptions;  // contains all the numbers corresponding to the indices of options that were selected
    char selectedModel = ' ';     // which car model the user selected

    vector<Option> options;  // contains all the possible options


    // read options file
    optionFile.open("options.txt");
    if (optionFile.fail()) {
		cout << "Failed to open file." << endl;
		exit(0);
	}

    // load options line by line
    while (getline(optionFile, lineIn)) {
        Option option;
        int spaceIndex = lineIn.find(" ");

        option.price = stoi(lineIn.substr(0, spaceIndex));
        option.name = lineIn.substr((spaceIndex + 1), (lineIn.length() - spaceIndex));
        option.nameInCaps = stringToUpper(option.name);

        options.push_back(option);
    }
    optionFile.close();

    while (!quit) {
        // display selected model and options
        if (selectedModel == ' ') {
            cout << "NO MODEL SELECTED" << endl;
        }
        else {
            cout << "Model: " << selectedModel << ", $";
            cout << fixed << setprecision(2) << calculatePrice(selectedModel, selectedOptions, options) << ", Options: ";

            if (selectedOptions.size() == 0) {
                cout << "None";
            }
            else {
                // print all but the last option with a comma and space
                for (size_t i = 0; i < selectedOptions.size() - 1; i++) {
                    cout << options[selectedOptions[i]].name << ", ";
                }
                cout << options[selectedOptions[(selectedOptions.size() - 1)]].name;  // print the last option with no comma or space
            }
            cout << endl;
        }
        cout << endl;

        // display menu and get choice
        cout << "1. Select a model (E, L, X)" << endl;
        cout << "2. Display available options and prices" << endl;
        cout << "3. Add an option" << endl;
        cout << "4. Remove an option" << endl;
        cout << "5. Cancel order" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter a choice: ";
        int menuChoice = readInteger();

        switch (menuChoice) {
            case 1:
                selectedModel = readModel();
                break;
            case 2:
                printOptions(options);
                break;
            case 3:
                addOption(options, selectedOptions, selectedModel);
                break;
            case 4:
                removeOption(options, selectedOptions, selectedModel);
                break;
            case 5:
                resetOrder(selectedOptions, selectedModel);
                break;
            case 6:
                quit = true;
                break;
        }
        cout << endl;
    }

    return 0;
}/// main


int readInteger() {
    // get positive integer
    int result;
    do {
        cin >> result;
    } while (result < 0);

    // remove the newline char from the buffer
    char temp;
    cin.get(temp);

    return result;
}

string stringToUpper(string input) {
    string output = "";
    for (size_t i = 0; i < input.length(); i++) {
        output += toupper(input.at(i));
    }

    return output;
}

double calculatePrice(char model, vector<int> selectedOptions, vector<Option> options) {
    double price = 0;

    // add cost for model
    switch (model) {
        case 'E':
            price += 10000;
            break;
        case 'L':
            price += 12000;
            break;
        case 'X':
            price += 18000;
    }

    // add costs for options
    for (size_t i = 0; i < selectedOptions.size(); i++) {
        price += options[selectedOptions[i]].price;
    }
    
    return price;
}

char readModel() {
    char model;
    do {
        cout << "Enter the model (E, L, X): ";
        model = toupper(cin.get());
        cin.ignore(1, '\n');  // discard newline at the end
    } while (! (model == 'E' || model == 'L' || model == 'X'));

    return model;
}

void printOptions(vector<Option> options) {
    cout << "Prices for model E, L, & X: $10000.00, $12000.00, $18000.00" << endl;
    cout << "Available options" << endl;
    cout << endl;

    // print all the options and prices, divided into three columns
    for (int i = 0; i < (static_cast<double>(options.size()) / 3); i++) {
        // print a row
        for (int j = 0; j < 3; j++) {
            cout << left << setw(30) << (options[(i * 3) + j].name + "($" + to_string(options[(i * 3) + j].price) + ")");
        }
        cout << endl;
    }
}

void addOption(vector<Option> options, vector<int> &selectedOptions, char selectedModel) {
    if (selectedModel != ' ') {
        cout << "Enter option: ";
        string optionChoice;
        getline(cin, optionChoice);
        optionChoice = stringToUpper(optionChoice);

        if (selectedOptions.size() < 6) {  // limit to 6 options
            // iterate through all the selected options to see if the new option was already added
            bool found = false;
            for (size_t i = 0; i < selectedOptions.size(); i++){
                if (options[selectedOptions[i]].nameInCaps == optionChoice) {
                    found = true;
                    break;
                }
            }

            // add the new option to selectedOptions
            if (!found) {
                for (size_t i = 0; i < options.size(); i++) {
                    if (optionChoice == options[i].nameInCaps) {
                        selectedOptions.push_back(i);
                        break;
                    }
                }
            }
        }
    }
}

void removeOption(vector<Option> options, vector<int> &selectedOptions, char selectedModel) {
    if (selectedModel != ' ') {
        cout << "Enter option: ";
        string optionChoice;
        getline(cin, optionChoice);
        optionChoice = stringToUpper(optionChoice);

        // iterate through all the selected options until the right one is found, then delete that element
        for (size_t i = 0; i < selectedOptions.size(); i++) {
            if (optionChoice == options[selectedOptions[i]].nameInCaps) {
                selectedOptions.erase(selectedOptions.begin() + i);
                break;
            }
        }
    }
}

void resetOrder(vector<int> &selectedOptions, char &selectedModel) {
    // set selectedModel to default
    selectedModel = ' ';

    // remove all selected options
    while (selectedOptions.size() > 0) {
        selectedOptions.erase(selectedOptions.begin());
    }
}