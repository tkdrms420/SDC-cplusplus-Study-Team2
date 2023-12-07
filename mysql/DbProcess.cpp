//
// Created by eddi on 23. 11. 29.
//

#include "DbProcess.h"
#include <iostream>


DbProcess::DbProcess(const char* host, const char* user, const char* pass, const char* dbName)
        : conn(nullptr), DB_HOST(host), DB_USER(user), DB_PASS(pass), DB_NAME(dbName) {}

DbProcess::~DbProcess() {
    if (conn != nullptr) {
        mysql_close(conn);
    }
}

bool DbProcess::connect() {

    conn = mysql_init(nullptr);
    return (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, nullptr, 0) != nullptr);
}

// DbProcess.cpp

bool DbProcess::insertAccountData(const std::string& accountId, const std::string& password) {
    std::string insertQuery = "INSERT INTO account (account_id, password, reg_date, upd_date) VALUES ('" +
                              accountId + "', '" + password + "', NOW(6), NOW(6))";

    return (mysql_query(conn, insertQuery.c_str()) == 0);
}

bool DbProcess::insertBoardData(const std::string& title, const std::string& writer, const std::string& content) {
    std::string insertQuery = "INSERT INTO board (title, writer, content, reg_date, upd_date) VALUES ('" +
                              title + "', '" + writer + "', '" + content + "',NOW(6), NOW(6))";

    return (mysql_query(conn, insertQuery.c_str()) == 0);
}

bool DbProcess::updateBoardData(int boardId, const std::string& newTitle, const std::string& newContent) {
    std::string updateQuery = "UPDATE board SET title = '" + newTitle +
                              "', content = '" + newContent +
                              "' WHERE board_id = " + std::to_string(boardId);

    return (mysql_query(conn, updateQuery.c_str()) == 0);
}

void DbProcess::selectAccountData() {
    std::string selectQuery = "SELECT * FROM account";
    if (mysql_query(conn, selectQuery.c_str()) == 0) {
        MYSQL_RES* result = mysql_store_result(conn);
        if (result == nullptr) {
            std::cerr << "mysql_store_result() failed" << std::endl;
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            std::cout << "id: " << row[0] << ", account_id: " << row[1]
                      << ", password: " << row[2]
                      << ", reg_date: " << (row[3] ? row[3] : "NULL") << ", upd_date: "
                      << (row[4] ? row[4] : "NULL") << std::endl;
        }

        mysql_free_result(result);
    } else {
        std::cerr << "mysql_query() failed" << std::endl;
    }
}

void DbProcess::selectBoardData() {

    std::string selectQuery = "SELECT * FROM board";

    if (mysql_query(conn, selectQuery.c_str()) == 0) {
        // 위에서 처리한 select 결과를 result에 저장
        MYSQL_RES* result = mysql_store_result(conn);
        if (result == nullptr) {
            std::cerr << "mysql_store_result() failed" << std::endl;
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != nullptr) {
            std::cout << "board_id: " << row[0] << ", content: " << row[1]
                      << ", reg_date: " << (row[2] ? row[2] : "NULL") << ", title: " << row[3]
                      << ", upd_date: " << (row[4] ? row[4] : "NULL") << ", writer: " << row[5] << std::endl;
        }

        mysql_free_result(result);
    } else {
        std::cerr << "mysql_query() failed" << std::endl;
    }
}

bool DbProcess::deleteBoardData(int boardId) {
    std::string deleteQuery = "DELETE FROM board WHERE board_id = " + std::to_string(boardId);

    return (mysql_query(conn, deleteQuery.c_str()) == 0);
}

void DbProcess::readBoardData(int boardId) {

    std::string readQuery = "SELECT * FROM board WHERE board_id = " + std::to_string(boardId);
    if (mysql_query(conn, readQuery.c_str()) == 0) {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result == nullptr) {
            std::cerr << "mysql_store_result() failed" << std::endl;
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row != nullptr) {
            std::cout << "board_id: " << row[0] << ", content: " << row[1]
                      << ", reg_date: " << (row[2] ? row[2] : "NULL") << ", title: " << row[3]
                      << ", upd_date: " << (row[4] ? row[4] : "NULL") << ", writer: " << row[5] << std::endl;
        } else {
            std::cout << "Record not found for board_id: " << boardId << std::endl;
        }

        mysql_free_result(result);
    } else {
        std::cerr << "mysql_query() failed" << std::endl;
    }
}
MYSQL *DbProcess::getConn()
{
    std::cout << "여기냐아" << std::endl;
    return conn;
}