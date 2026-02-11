#include <iostream>
#include <fstream>
using namespace std;

class ATM {
private:
    int pin;
    double balance;

public:
    ATM() {
        pin = 1234;
        balance = 1000.0;
        loadData();
    }

    void saveData() {
        ofstream file("atm.dat", ios::binary);
        file.write((char*)this, sizeof(*this));
        file.close();
    }

    void loadData() {
        ifstream file("atm.dat", ios::binary);
        if (file)
            file.read((char*)this, sizeof(*this));
        file.close();
    }

    bool verifyPIN(int enteredPin) {
        return enteredPin == pin;
    }

    void checkBalance() {
        cout << "\nCurrent Balance: ₹" << balance << endl;
    }

    void deposit() {
        double amt;
        cout << "Enter deposit amount: ₹";
        cin >> amt;
        if (amt > 0) {
            balance += amt;
            cout << "Deposit Successful!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw() {
        double amt;
        cout << "Enter withdrawal amount: ₹";
        cin >> amt;
        if (amt > 0 && amt <= balance) {
            balance -= amt;
            cout << "Please collect your cash.\n";
        } else {
            cout << "Invalid or insufficient balance!\n";
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\n==========================";
            cout << "\n        ATM MENU";
            cout << "\n==========================";
            cout << "\n1. Check Balance";
            cout << "\n2. Deposit";
            cout << "\n3. Withdraw";
            cout << "\n4. Exit";
            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: checkBalance(); break;
            case 2: deposit(); saveData(); break;
            case 3: withdraw(); saveData(); break;
            case 4: cout << "Thank you for using ATM!\n"; break;
            default: cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }
};

int main() {
    ATM atm;
    int enteredPin;

    cout << "==========================\n";
    cout << "      ATM SIMULATOR\n";
    cout << "==========================\n";
    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (atm.verifyPIN(enteredPin)) {
        atm.menu();
    } else {
        cout << "Incorrect PIN! Access Denied.\n";
    }

    return 0;
}
