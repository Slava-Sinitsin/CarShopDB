#ifndef LAB1_CLIENT_SELLER_H
#define LAB1_CLIENT_SELLER_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class ClientsSeller {
   public:
    ClientsSeller(int passport_id, int car_id, int certifying_document_id,
                  string purchase_date)
        : passport_id(passport_id),
          car_id(car_id),
          certifying_document_id(certifying_document_id),
          purchase_date(std::move(purchase_date)) {}

    static vector<ClientsSeller> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM client_seller;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<ClientsSeller> clientSeller;
        for (const vector<string> &row : results) {
            clientSeller.push_back(parseRow(row));
        }

        return clientSeller;
    }

    static ClientsSeller findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM client_seller WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("client seller not found");
        }

        return parseRow(results[0]);
    }

    static vector<ClientsSeller> findAllByJoin(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "SELECT client_seller.id, passport_id, car_id, "
               "certifying_document_id, purchase_date FROM client_seller JOIN "
               "car ON client_seller.car_id = car.id;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("client seller info not found");
        }

        return parseTable(results);
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO client_seller (passport_id, car_id, "
               "certifying_document_id, purchase_date) VALUES ("
            << passport_id << ", " << car_id << ", " << certifying_document_id
            << ", '" << purchase_date << "');";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    int getId() const { return id; }

    const int &getPassportId() const { return passport_id; }

    const int &getCarId() const { return car_id; }

    const int &getCertifyingDocumentId() const {
        return certifying_document_id;
    }

    const string &getPurchaseDate() const { return purchase_date; }

   private:
    int id;
    int passport_id;
    int car_id;
    int certifying_document_id;
    string purchase_date;

    ClientsSeller(int id, int passport_id, int car_id,
                  int certifying_document_id, string purchase_date)
        : id(id),
          passport_id(passport_id),
          car_id(car_id),
          certifying_document_id(certifying_document_id),
          purchase_date(std::move(purchase_date)) {}

    static ClientsSeller parseRow(vector<string> row) {
        return {stoi(row[0]), stoi(row[1]), stoi(row[2]), stoi(row[3]), row[4]};
    }

    static vector<ClientsSeller> parseTable(vector<vector<string>> table) {
        vector<ClientsSeller> resVector;
        for (int i = 0; i < table.size(); i++) {
            resVector.push_back(parseRow(table[i]));
        }
        return resVector;
    }
};

#endif  // LAB1_CLIENT_SELLER_H