//
// Created by Leonardo on 26/04/2025.
//

#include <gtest/gtest.h>
#include <fstream>
#include "../Account.h"

using namespace std;

// Test costruttore corretto
TEST(AccountTest, Constructor_ValidInput) {
    Account acc("testfile.txt", "Mario Rossi");
    EXPECT_EQ(acc.getAccountName(), "Mario Rossi");
    EXPECT_EQ(acc.getFileName(), "testfile.txt");
}

// Test costruttore con nome account vuoto
TEST(AccountTest, Constructor_EmptyAccountName) {
    EXPECT_THROW(Account("testfile.txt", ""), invalid_argument);
}

// Test costruttore con nome file vuoto
TEST(AccountTest, Constructor_EmptyFileName) {
    EXPECT_THROW(Account("", "Mario Rossi"), invalid_argument);
}

// Test getAccountName
TEST(AccountTest, GetAccountName) {
    Account acc("testfile.txt", "Mario Rossi");
    EXPECT_EQ(acc.getAccountName(), "Mario Rossi");
}

// Test getFileName
TEST(AccountTest, GetFileName) {
    Account acc("testfile.txt", "Mario Rossi");
    EXPECT_EQ(acc.getFileName(), "testfile.txt");
}

// Test setAccountName corretto
TEST(AccountTest, SetAccountName_Valid) {
    Account acc("testfile.txt", "Mario Rossi");
    acc.setAccountName("Mario Bianchi");
    EXPECT_EQ(acc.getAccountName(), "Mario Bianchi");
}

// Test setAccountName vuoto
TEST(AccountTest, SetAccountName_Empty) {
    Account acc("testfile.txt", "Mario Rossi");
    EXPECT_THROW(acc.setAccountName(""), invalid_argument);
}

// Test setFileName corretto
TEST(AccountTest, SetFileName_Valid) {
    Account acc("testfile.txt", "Mario Rossi");
    acc.setFileName("newfile.txt");
    EXPECT_EQ(acc.getFileName(), "newfile.txt");
}

// Test setFileName vuoto
TEST(AccountTest, SetFileName_Empty) {
    Account acc("testfile.txt", "Mario Rossi");
    EXPECT_THROW(acc.setFileName(""), invalid_argument);
}

// Test addTransaction
TEST(AccountTest, AddTransaction) {
    Account acc("testfile.txt", "Mario Rossi");
    Transaction t("2024-04-26", "Stipendio", 2000.0, in);
    acc.addTransaction(t);
    EXPECT_EQ(acc.totalTransactions(), 1);
}

// Test findForDate trovando una transazione
TEST(AccountTest, FindForDate_Found) {
    Account acc("testfile.txt", "Mario Rossi");
    Transaction t1("2024-04-26", "Stipendio", 2000.0, in);
    Transaction t2("2024-05-01", "Regalo", 100.0, in);
    acc.addTransaction(t1);
    acc.addTransaction(t2);

    auto result = acc.findForDate("2024-04-26");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].getDescription(), "Stipendio");
}

// Test findForDate non trovando nulla
TEST(AccountTest, FindForDate_NotFound) {
    Account acc("testfile.txt", "Mario Rossi");
    Transaction t1("2024-04-26", "Stipendio", 2000.0, in);
    acc.addTransaction(t1);

    auto result = acc.findForDate("2025-01-01");
    EXPECT_TRUE(result.empty());
}
// Test findForDate con data vuota
TEST(AccountTest, FindForDate_EmptyDate) {
    Account acc("testfile.txt", "Mario Rossi");
    auto results = acc.findForDate("");
    EXPECT_TRUE(results.empty());
}

// Test findForDescription trovando una transazione
TEST(AccountTest, FindForDescription_Found) {
    Account acc("testfile.txt", "Mario Rossi");
    Transaction t1("2024-04-26", "Stipendio", 2000.0, in);
    Transaction t2("2024-05-01", "Regalo compleanno", 100.0, in);
    acc.addTransaction(t1);
    acc.addTransaction(t2);

    auto result = acc.findForDescription("Regalo");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].getDescription(), "Regalo compleanno");
}

// Test findForDescription non trovando nulla
TEST(AccountTest, FindForDescription_NotFound) {
    Account acc("testfile.txt", "Mario Rossi");
    Transaction t1("2024-04-26", "Stipendio", 2000.0, in);
    acc.addTransaction(t1);

    auto result = acc.findForDescription("Affitto");
    EXPECT_TRUE(result.empty());
}

// Test findoForDescription con descrizione vuota
TEST(AccountTest, FindForDescription_EmptyDesc) {
    Account acc("testfile.txt", "Mario Rossi");
    auto results = acc.findForDescription("");
    EXPECT_TRUE(results.empty());
}

// Test totalTransactions
TEST(AccountTest, TotalTransactions) {
    Account acc("testfile.txt", "Mario Rossi");
    EXPECT_EQ(acc.totalTransactions(), 0);

    Transaction t1("2024-04-26", "Stipendio", 2000.0, in);
    Transaction t2("2024-05-01", "Affitto", 800.0, out);
    acc.addTransaction(t1);
    acc.addTransaction(t2);

    EXPECT_EQ(acc.totalTransactions(), 2);
}

// Test totalBalance
TEST(AccountTest, TotalBalance) {
    Account acc("testfile.txt", "Mario Rossi");
    Transaction t1("2024-04-26", "Stipendio", 2000.0, in);
    Transaction t2("2024-05-01", "Affitto", 800.0, out);
    Transaction t3("2024-05-05", "Spesa", 200.0, out);
    acc.addTransaction(t1);
    acc.addTransaction(t2);
    acc.addTransaction(t3);

    EXPECT_DOUBLE_EQ(acc.totalBalance(), 1000.0);
}

//Test stampa estratto conto
TEST(AccountTest, PrintAccountStatement) {
    Account acc("testfile.txt", "Mario Rossi");
    Transaction t("2024-04-25", "Deposito", 100.0, in);
    acc.addTransaction(t);
    EXPECT_NO_THROW(acc.printAccountStatement());
}

// Test salvataggio file
TEST(AccountTest, SaveAccountToFile_SavesCorrectly) {
    Account acc("testfile.txt", "TestAccount");
    acc.addTransaction(Transaction("2024-04-25", "Stipendio", 1500.0, in));
    acc.addTransaction(Transaction("2024-04-26", "Affitto", 500.0, out));
    acc.saveAccountToFile();
    ifstream file("testfile.txt");
    ASSERT_TRUE(file.is_open());
    string line;
    getline(file, line);
    EXPECT_EQ(line, "AccountName: TestAccount");
    getline(file, line);
    EXPECT_EQ(line, "FileName: testfile.txt");
    getline(file, line);
    EXPECT_EQ(line, "Transactions:");
    getline(file, line);
    EXPECT_EQ(line, "2024-04-25;Stipendio;1500;in");
    getline(file, line);
    EXPECT_EQ(line, "2024-04-26;Affitto;500;out");
    file.close();
}

// Test caricamento file
TEST(AccountTest, LoadAccountFromFile_LoadsCorrectly) {
    ofstream file("loadedfile.txt");
    file << "AccountName: LoadedAccount\n";
    file << "FileName: loadedfile.txt\n";
    file << "Transactions:\n";
    file << "2024-04-25;Stipendio;1500;in\n";
    file << "2024-04-26;Affitto;500;out\n";
    file.close();
    Account acc("newfile.txt", "newaccount");
    acc.loadAccountFromFile("loadedfile.txt");
    EXPECT_EQ(acc.getAccountName(), "LoadedAccount");
    EXPECT_EQ(acc.getFileName(), "loadedfile.txt");
    ASSERT_EQ(acc.totalTransactions(), 2);
    auto transactions = acc.findForDescription("Stipendio");
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0].getAmount(), 1500.0);
    EXPECT_EQ(transactions[0].getType(), in);
    transactions = acc.findForDescription("Affitto");
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0].getAmount(), 500.0);
    EXPECT_EQ(transactions[0].getType(), out);
}

