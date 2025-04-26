 #include <iostream>
#include "Account.h"

int main() {
    Account conto("conto_corrente.txt", "Mario Rossi");

    conto.addTransaction(Transaction("2025-04-01", "Stipendio", 1500, TransactionType::in));
    conto.addTransaction(Transaction("2025-04-03", "Affitto", 600, TransactionType::out));

    conto.saveFile();
    conto.printAccountStatement();
    return 0;
}
