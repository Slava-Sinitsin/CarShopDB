#ifndef LAB1_CLIENT_BUYER_H
#define LAB1_CLIENT_BUYER_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class ClientBuyer {
   public:
    ClientBuyer(int passport_id, int car_id, string sale_date,
                string account_number, string payment_type)
        : passport_id(passport_id),
          car_id(car_id),
          sale_date(std::move(sale_date)),
          account_number(std::move(account_number)),
          payment_type(std::move(payment_type)) {}

    static vector<ClientBuyer> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM client_buyer;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<ClientBuyer> clientBuyer;
        for (const vector<string> &row : results) {
            clientBuyer.push_back(parseFromVector(row));
        }

        return clientBuyer;
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO client_buyer (passport_id, car_id, sale_date, "
               "account_number, payment_type) VALUES ("
            << passport_id << ", " << car_id << ", '" << sale_date << "', "
            << account_number << ", '" << payment_type << "');";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    static ClientBuyer findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM client_buyer WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("client buyer not found");
        }

        return parseFromVector(results[0]);
    }

    int getId() const { return id; }

    const int &getPassportId() const { return passport_id; }

    const int &getCarId() const { return car_id; }

    const string &getSaleDate() const { return sale_date; }

    const string &getAccountNumber() const { return account_number; }

    const string &getPaymentType() const { return payment_type; }

   private:
    int id;
    int passport_id;
    int car_id;
    string sale_date;
    string account_number;
    string payment_type;

    ClientBuyer(int id, int passport_id, int car_id, string sale_date,
                string account_number, string payment_type)
        : id(id),
          passport_id(passport_id),
          car_id(car_id),
          sale_date(std::move(sale_date)),
          account_number(std::move(account_number)),
          payment_type(std::move(payment_type)) {}

    static ClientBuyer parseFromVector(vector<string> row) {
        return {stoi(row[0]), stoi(row[1]), stoi(row[2]),
                row[3],       row[4],       row[5]};
    }
};

#endif  // LAB1_CLIENT_BUYER_H