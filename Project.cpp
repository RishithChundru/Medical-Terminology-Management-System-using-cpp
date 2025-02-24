#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void EnsureFileExists() {
    ofstream file("dictionary.txt", ios::app); // Creates file if not present
    file.close();
}

void AddRecord() {
    ofstream file("dictionary.txt", ios::app);
    int n;
    cout << "Enter number of records to add: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string term, definition;
        cout << "Enter new term: ";
        getline(cin, term);
        cout << "Enter definition: ";
        getline(cin, definition);

        file << term << " : " << definition << endl;
    }

    cout << "Records added successfully!\n";
    file.close();
}

void DisplayTerms() {
    ifstream file("dictionary.txt");
    string line;
    int count = 1;

    cout << "Medical Terms:\n";
    while (getline(file, line)) {
        cout << count++ << ". " << line << endl;
    }
    file.close();
}

void Update() {
    ifstream file("dictionary.txt");
    ofstream temp("temp.txt");
    string search_term, line;
    bool found = false;

    cout << "Enter the term whose definition you want to update: ";
    cin.ignore();
    getline(cin, search_term);

    while (getline(file, line)) {
        size_t pos = line.find(" : ");
        if (pos != string::npos) {
            string term = line.substr(0, pos);
            if (term == search_term) {
                string new_definition;
                cout << "Enter new definition: ";
                getline(cin, new_definition);
                temp << term << " : " << new_definition << endl;
                found = true;
            } else {
                temp << line << endl;
            }
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("dictionary.txt");
    rename("temp.txt", "dictionary.txt");

    if (found)
        cout << "Record updated successfully!\n";
    else
        cout << "No record found with the given term name.\n";
}

void SearchTerm() {
    ifstream file("dictionary.txt");
    string search_term, line;
    bool found = false;

    cout << "Enter the term name you want to search: ";
    cin.ignore();
    getline(cin, search_term);

    while (getline(file, line)) {
        size_t pos = line.find(" : ");
        if (pos != string::npos && line.substr(0, pos) == search_term) {
            cout << "Term Found:\n" << line << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "No record found with the given term name.\n";
}


void Delete() {
    ifstream file("dictionary.txt");
    ofstream temp("temp.txt");
    string delete_term, line;
    bool found = false;

    cout << "Enter the term name to delete: ";
    //cin.ignore(); // Remove if unnecessary
    getline(cin, delete_term);

    while (getline(file, line)) {
        size_t pos = line.find(" : ");
        if (pos != string::npos) {
            string term = line.substr(0, pos);
            if (term != delete_term) {  // Compare terms correctly
                temp << line << endl;
            } else {
                found = true;
            }
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    if (found) {
        if (remove("dictionary.txt") != 0) {
            cout << "Error deleting original file.\n";
        } else if (rename("temp.txt", "dictionary.txt") != 0) {
            cout << "Error renaming temp file.\n";
        } else {
            cout << "Record deleted successfully!\n";
        }
    } else {
        cout << "No record found with the given term name.\n";
        remove("temp.txt"); // Remove temp file if not needed
    }
}


int main() {
    EnsureFileExists();
    int choice;
    do {
        cout << "\n1. Add Record\n2. Display Terms\n3. Update Definition\n4. Search Term\n5. Delete Record\n6. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: AddRecord(); break;
            case 2: DisplayTerms(); break;
            case 3: Update(); break;
            case 4: SearchTerm(); break;
            case 5: Delete(); break;
            case 6: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice, try again.\n"; break;
        }
    } while (choice != 6);
    return 0;
}
