//
// Created by Leonardo on 26/04/2025.
//

#include "gtest/gtest.h"
#include "../Transaction.h"

// Test costruttore corretto
TEST(TransactionTest, Constructor_ValidInput) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_EQ(t.getDate(), "2024-04-25");
    EXPECT_EQ(t.getDescription(), "Stipendio");
    EXPECT_DOUBLE_EQ(t.getAmount(), 1500.0);
    EXPECT_EQ(t.getType(), TransactionType::in);
}

// Test costruttore con data in formato non valido
TEST(TransactionTest, Constructor_InvalidDateFormat) {
    EXPECT_THROW(Transaction("25-04-2024", "Stipendio", 1000.0, TransactionType::in), std::invalid_argument);
}

// Test costruttore con data errata
TEST(TransactionTest, Constructor_InvalidDateValues) {
    EXPECT_THROW(Transaction("2024-00-25", "Stipendio", 1000.0, TransactionType::in), std::invalid_argument);
    EXPECT_THROW(Transaction("0000-04-25", "Stipendio", 1000.0, TransactionType::in), std::invalid_argument);
    EXPECT_THROW(Transaction("2024-04-00", "Stipendio", 1000.0, TransactionType::in), std::invalid_argument);
}

// Test costruttore con data vuota
TEST(TransactionTest, Constructor_EmptyDate) {
    EXPECT_THROW(Transaction("", "stipendio", 100.0, TransactionType::in), std::invalid_argument);
}


// Test costruttore con descrizione vuota
TEST(TransactionTest, Constructor_EmptyDescription) {
    EXPECT_THROW(Transaction("2024-04-25", "", 1000.0, TransactionType::in), std::invalid_argument);
}

// Test costruttore con ammonto negativo
TEST(TransactionTest, Constructor_NegativeAmount) {
    EXPECT_THROW(Transaction("2024-04-25", "Stipendio", -1000.0, TransactionType::in), std::invalid_argument);
}

// Test costruttore con ammonto vuoto
TEST(TransactionTest, Constructor_ZeroAmount) {
    EXPECT_THROW(Transaction("2024-04-25", "Stipendio", 0.0, TransactionType::in), std::invalid_argument);
}

// Test getDate
TEST(TransactionTest, GetDate) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_EQ(t.getDate(), "2024-04-25");
}

// Test getDescription
TEST(TransactionTest, GetDescription) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_EQ(t.getDescription(), "Stipendio");
}

// Test getAmount
TEST(TransactionTest, GetAmount) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_DOUBLE_EQ(t.getAmount(), 1500.0);
}

// Test getType
TEST(TransactionTest, GetType) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_EQ(t.getType(), TransactionType::in);
}

// Test setDate corretto
TEST(TransactionTest, SetDate_Valid) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    t.setDate("2025-05-01");
    EXPECT_EQ(t.getDate(), "2025-05-01");
}

// Test setDate sbagliato
TEST(TransactionTest, SetDate_Invalid) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_THROW(t.setDate("01-05-2025"), std::invalid_argument);
}

// Test setDescription valido
TEST(TransactionTest, SetDescription_Valid) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    t.setDescription("Stipendio Aprile");
    EXPECT_EQ(t.getDescription(), "Stipendio Aprile");
}

// Test setDescription vuoto
TEST(TransactionTest, SetDescription_Empty) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_THROW(t.setDescription(""), std::invalid_argument);
}

// Test setAmount corretto
TEST(TransactionTest, SetAmount_Valid) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    t.setAmount(2000.0);
    EXPECT_DOUBLE_EQ(t.getAmount(), 2000.0);
}

// Test setAmount negativo
TEST(TransactionTest, SetAmount_Negative) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_THROW(t.setAmount(-500.0), std::invalid_argument);
}

// Test setType
TEST(TransactionTest, SetType) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    t.setType(TransactionType::out);
    EXPECT_EQ(t.getType(), TransactionType::out);
}

// Test typeToString
TEST(TransactionTest, TypeToString) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_EQ(t.typeToString(), "in");
    EXPECT_EQ(t.typeToString(), "out"); //non serve
}

// Test stringToType valido
TEST(TransactionTest, StringToType_Valid) {
    EXPECT_EQ(Transaction::stringToType("in"), TransactionType::in);
    EXPECT_EQ(Transaction::stringToType("out"), TransactionType::out);
}

// Test stringToType invalido
TEST(TransactionTest, StringToType_Invalid) {
    EXPECT_THROW(Transaction::stringToType("42"), std::invalid_argument);
}

// Test toString
TEST(TransactionTest, ToString) {
    Transaction t("2024-04-25", "Stipendio", 1500.0, TransactionType::in);
    EXPECT_EQ(t.toString(), "2024-04-25;Salary;1500;in");
}

// Test fromString valido
TEST(TransactionTest, FromString_Valid) {
    Transaction t = Transaction::fromString("2024-04-25;Salary;1500;in");
    EXPECT_EQ(t.getDate(), "2024-04-25");
    EXPECT_EQ(t.getDescription(), "Salary");
    EXPECT_DOUBLE_EQ(t.getAmount(), 1500.0);
    EXPECT_EQ(t.getType(), TransactionType::in);
}

// Test fromString non valido
TEST(TransactionTest, FromString_Invalid) {
    EXPECT_THROW(Transaction::fromString("Stringa non valida"), std::invalid_argument);
}