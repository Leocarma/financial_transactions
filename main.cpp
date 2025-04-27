#include <iostream>
#include "Account.h"
#include "Transaction.h"
#include <io.h>

int main() {
    chdir("..");
    try {
        Account myAccount("account_data.txt", "Mario Bianchi");
        Transaction t1("2025-04-25", "Salary", 1500.00, in);
        Transaction t2("2025-04-26", "Groceries", 200.00, out);
        Transaction t3("2025-04-27", "Gym Membership", 50.00, out);
        myAccount.addTransaction(t1);
        myAccount.addTransaction(t2);
        myAccount.addTransaction(t3);

        cout << "=== Account Statement Before Saving ===" << endl;
        myAccount.printAccountStatement();
        myAccount.saveAccountToFile();
        cout << "Account saved to file." << endl;

        Account loadedAccount;
        loadedAccount.loadAccountFromFile("account_data.txt");
        loadedAccount.setFileName("newaccountdata.txt");
        loadedAccount.setAccountName("Mario Rossi");
        cout << "\n=== Account Statement After Loading ===" << endl;
        loadedAccount.printAccountStatement();
        loadedAccount.saveAccountToFile();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
