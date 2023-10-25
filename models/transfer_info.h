#ifndef LAB1_TRANSFER_INFO_H
#define LAB1_TRANSFER_INFO_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class TransferInfo {
   public:
    TransferInfo(string previous_position, string transfer_reason,
                 string order_date)
        : previous_position(std::move(previous_position)),
          transfer_reason(std::move(transfer_reason)),
          order_date(std::move(order_date)) {}

    static vector<TransferInfo> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM transfer_info;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<TransferInfo> transferInfo;
        for (const vector<string> &row : results) {
            transferInfo.push_back(parseFromVector(row));
        }

        return transferInfo;
    }

    static TransferInfo findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM transfer_info WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("transfer info not found");
        }

        return parseFromVector(results[0]);
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO transfer_info (previous_position, transfer_reason, "
               "order_date) VALUES ('"
            << previous_position << "', '" << transfer_reason << "', '"
            << order_date << "');";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    static TransferInfo findLastId(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "SELECT * FROM transfer_info\nORDER BY id DESC\nLIMIT 1;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("transfer info not found");
        }

        return parseFromVector(results[0]);
    }

    int getId() const { return id; }

    const string &getPreviousPosition() const { return transfer_reason; }

    const string &getTransferReason() const { return transfer_reason; }

    const string &getOrderDate() const { return order_date; }

   private:
    int id;
    string previous_position;
    string transfer_reason;
    string order_date;

    TransferInfo(int id, string previous_position, string transfer_reason,
                 string order_date)
        : id(id),
          previous_position(std::move(previous_position)),
          transfer_reason(std::move(transfer_reason)),
          order_date(std::move(order_date)) {}

    static TransferInfo parseFromVector(vector<string> row) {
        return {stoi(row[0]), row[1], row[2], row[3]};
    }
};

#endif  // LAB1_TRANSFER_INFO_H