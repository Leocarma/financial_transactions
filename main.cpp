#include <iostream>
#include "Account.h"
#include "Transaction.h"
#include <io.h>

int main() {
    chdir("..");
    try {
        // Creazione di un account
        Account myAccount("account_data.txt", "Mario Bianchi");

        // Creazione di alcune transazioni
        Transaction t1("2025-04-25", "Salary", 1500.00, in);
        Transaction t2("2025-04-26", "Groceries", 200.00, out);
        Transaction t3("2025-04-27", "Gym Membership", 50.00, out);

        // Aggiunta delle transazioni all'account
        myAccount.addTransaction(t1);
        myAccount.addTransaction(t2);
        myAccount.addTransaction(t3);

        // Stampa dello stato dell'account
        cout << "=== Account Statement Before Saving ===" << endl;
        myAccount.printAccountStatement();

        // Salvataggio dell'account su file
        myAccount.saveAccountToFile();
        cout << "Account saved to file." << endl;

        // Creazione di un nuovo account per il caricamento
        Account loadedAccount;
        loadedAccount.loadAccountFromFile("account_data.txt");
        loadedAccount.setFileName("newaccountdata.txt");

        // Stampa dello stato dell'account caricato
        cout << "\n=== Account Statement After Loading ===" << endl;
        loadedAccount.printAccountStatement();
        loadedAccount.saveAccountToFile();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
