cmake_minimum_required(VERSION 3.28)
project(financial_transactions)

set(CMAKE_CXX_STANDARD 17)

add_executable(financial_transactions main.cpp
        Transaction.cpp
        "Transaction.h"
        Current_account.cpp
        Current_account.h
        Transaction.h
        Transaction.h)
