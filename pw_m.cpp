#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Account {
    string website;
    string password;
};

string encrypt(string text, int key) {
    for (char &c : text)
        c += key;
    return text;
}

string decrypt(string text, int key) {
    for (char &c : text)
        c -= key;
    return text;
}

string generatePassword() {
    string chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%&*";

    string pass = "";

    for (int i = 0; i < 12; i++) {
        pass += chars[rand() % chars.length()];
    }

    return pass;
}

void savePassword(string website, string password) {
    ofstream file("C:\\Users\\adi\\Desktop\\codingg\\proj\\passwords.txt", ios::app);
    file << website << " " << password << endl;
    file.close();
}

vector<Account> loadPasswords() {

    vector<Account> list;

    ifstream file("C:\\Users\\adi\\Desktop\\codingg\\proj\\passwords.txt");

    Account acc;

    while (file >> acc.website >> acc.password) {
        list.push_back(acc);
    }

    file.close();

    return list;
}

void showPasswords(int key) {

    vector<Account> list = loadPasswords();

    if (list.empty()) {
        cout << "No passwords stored.\n";
        return;
    }

    cout << "\nSaved Accounts\n";

    for (auto &acc : list) {
        cout << acc.website
             << " -> "
             << decrypt(acc.password, key)
             << endl;
    }
}

void searchPassword(string website, int key) {

    vector<Account> list = loadPasswords();

    for (auto &acc : list) {

        if (acc.website == website) {

            cout << "Password: "
                 << decrypt(acc.password, key)
                 << endl;

            return;
        }
    }

    cout << "Website not found.\n";
}

void deletePassword(string website) {

    vector<Account> list = loadPasswords();

    ofstream file("passwords.txt");

    for (auto &acc : list) {

        if (acc.website != website) {

            file << acc.website
                 << " "
                 << acc.password
                 << endl;
        }
    }

    file.close();

    cout << "Password deleted (if it existed).\n";
}

bool login() {

    string master;

    cout << "Enter master password: ";
    cin >> master;

    ifstream file("C:\\Users\\adi\\Desktop\\codingg\\proj\\master.txt");

    if (!file) {

        ofstream create("master.txt");

        create << master;

        create.close();

        cout << "Master password created.\n";

        return true;
    }

    string saved;

    file >> saved;

    if (master == saved)
        return true;

    cout << "Wrong password.\n";

    return false;
}

int main() {

    srand(time(0));

    if (!login())
        return 0;

    int choice;

    string website;

    int key;

    while (true) {

        cout << "\n===== PASSWORD MANAGER =====\n";
        cout << "1. Generate Password\n";
        cout << "2. Search Password\n";
        cout << "3. Show All Passwords\n";
        cout << "4. Delete Password\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {

            cout << "Website: ";
            cin >> website;

            cout << "Encryption key (number): ";
            cin >> key;

            string pass = generatePassword();

            cout << "Generated password: "
                 << pass
                 << endl;

            savePassword(website, encrypt(pass, key));
        }

        else if (choice == 2) {

            cout << "Website: ";
            cin >> website;

            cout << "Key: ";
            cin >> key;

            searchPassword(website, key);
        }

        else if (choice == 3) {

            cout << "Key: ";
            cin >> key;

            showPasswords(key);
        }

        else if (choice == 4) {

            cout << "Website: ";
            cin >> website;

            deletePassword(website);
        }

        else if (choice == 5) {

            cout << "Exiting...\n";
            break;
        }

        else {

            cout << "Invalid option\n";
        }
    }

    return 0;
}