#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

class ItemTracker {           //itemTracker class used to find and output items.
public:
    ItemTracker(const string& filename) {
        loadItemFrequencies(filename);
    }

    void searchItem() const { //Searches for individual items in the file
        string item;
        cout << "Enter the item to search for: ";
        cin >> item;
        auto it = items.find(item);
        if (it != items.end()) {    //outputs frequency of the item found
            cout << item << " was purchased " << it->second << " times." << endl;
        } else {
            cout << "Item not found." << endl;
        }
    }

    void displayAllItems() const { // displays all items
        if (items.empty()) {
            cout << "No items to display." << endl;
            return;
        }

        cout << "All items and their frequencies:" << endl;
        for (const auto& pair : items) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void displayHistogram() const {  //Displays histogram of all items
        if (items.empty()) {
            cout << "No data available to display a histogram." << endl;
            return;
        }

        cout << "Histogram of item purchases:" << endl;
        for (const auto& pair : items) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << '*';
            }
            cout << endl;
        }
    }

    void saveFrequenciesToFile(const string& filename) const {  //Saves frequencies of items to data file
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Failed to open file for writing." << endl;
            return;
        }

        for (const auto& pair : items) {
            outFile << pair.first << " " << pair.second << endl;
        }
        outFile.close();
        cout << "Data successfully saved to " << filename << endl;
    }

private:
    map<string, int> items;

    void loadItemFrequencies(const string& filename) {  //This function opens the input file
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file." << endl;
            return;
        }

        string item;
        while (file >> item) {
            ++items[item];
        }
        file.close();
    }
};

void displayMenu() {                //This function displays menu options
    cout << "\nMenu Options:\n";
    cout << "1. Search for an item\n";
    cout << "2. Display all items\n";
    cout << "3. Display histogram\n";
    cout << "4. Save data to file\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt");   //input file designater

    int choice = 0;
    bool exit = false;

    while (!exit) {  //Handles menu option behaviour and error handling
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                tracker.searchItem();
                break;
            case 2:
                tracker.displayAllItems();
                break;
            case 3:
                tracker.displayHistogram();
                break;
            case 4:
                tracker.saveFrequenciesToFile("frequency.dat");
                break;
            case 5:
                tracker.saveFrequenciesToFile("frequency.dat");
                exit = true;
                break;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
