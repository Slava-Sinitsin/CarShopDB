#ifndef LAB1_PART_H
#define LAB1_PART_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class Part {
   public:
    Part(int car_id, string name, int price, int count)
        : car_id(car_id), name(std::move(name)), price(price), count(count) {}

    static vector<Part> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM part;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<Part> part;
        for (const vector<string> &row : results) {
            part.push_back(parseFromVector(row));
        }

        return part;
    }

    static Part findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM part WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("part not found");
        }

        return parseFromVector(results[0]);
    }

    static vector<Part> findByCarId(SQLHDBC sqlhdbc, int car_id) {
        ostringstream oss;
        oss << "SELECT * FROM part WHERE car_id = " << car_id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        vector<Part> part;
        for (const vector<string> &row : results) {
            part.push_back(parseFromVector(row));
        }

        return part;
    }

    void update(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "UPDATE part SET count = " << count << " WHERE id = " << id
            << ";\n"
            << "DELETE FROM part WHERE count = 0;";
        SqlExecutor::executeSql(sqlhdbc, oss.str());
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO part (car_id, name, price, count) VALUES ("
            << car_id << ", '" << name << "', " << price << ", " << count
            << ");";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    void setCount(const int &count) { Part::count = count; }

    int getId() const { return id; }

    const int &getCarId() const { return car_id; }

    const string &getName() const { return name; }

    const int &getPrice() const { return price; }

    const int &getCount() const { return count; }

   private:
    int id;
    int car_id;
    string name;
    int price;
    int count;

    Part(int id, int car_id, string name, int price, int count)
        : id(id),
          car_id(car_id),
          name(std::move(name)),
          price(price),
          count(count) {}

    static Part parseFromVector(vector<string> row) {
        return {stoi(row[0]), stoi(row[1]), row[2], stoi(row[3]), stoi(row[4])};
    }
};

#endif  // LAB1_PART_H