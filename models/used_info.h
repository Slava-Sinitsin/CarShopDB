#ifndef LAB1_USED_INFO_H
#define LAB1_USED_INFO_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class UsedInfo {
   public:
    UsedInfo(int id, int employee_id, int purchase_price,
             string certificate_date)
        : id(id),
          employee_id(employee_id),
          purchase_price(purchase_price),
          certificate_date(certificate_date) {}

    UsedInfo(int employee_id, int purchase_price, string certificate_date)
        : employee_id(employee_id),
          purchase_price(purchase_price),
          certificate_date(certificate_date) {}

    static vector<UsedInfo> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM used_info;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<UsedInfo> usedInfo;
        for (const vector<string> &row : results) {
            usedInfo.push_back(parseFromVector(row));
        }

        return usedInfo;
    }

    static UsedInfo findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM used_info WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("used info info not found");
        }

        return parseFromVector(results[0]);
    }

    static UsedInfo findLastId(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "SELECT * FROM used_info\nORDER BY id DESC\nLIMIT 1;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("transfer info not found");
        }

        return parseFromVector(results[0]);
    }

    static bool isUsedInfoExists(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT 1 FROM used_info WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (!results.empty() && results[0][0] == "1") {
            return true;
        }
        return false;
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO used_info (employee_id, purchase_price, "
               "certificate_date) VALUES ("
            << employee_id << ", " << purchase_price << ", '"
            << certificate_date << "');";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    int getId() const { return id; }

    const int &getEmployeeId() const { return employee_id; }

    const int &getPurchasePrice() const { return purchase_price; }

    const string &getCertificateDate() const { return certificate_date; }

   private:
    int id;
    int employee_id;
    int purchase_price;
    string certificate_date;

    static UsedInfo parseFromVector(vector<string> row) {
        return {stoi(row[0]), stoi(row[1]), stoi(row[2]), row[3]};
    }
};

#endif  // LAB1_USED_INFO_H