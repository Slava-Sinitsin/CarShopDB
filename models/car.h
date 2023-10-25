#ifndef LAB1_CAR_H
#define LAB1_CAR_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class Car {
   public:
    Car(int used_info_id, string name, string color, string engine_number,
        string reg_number, string body_number, string chassis_number,
        string release_date, int mileage, int release_price, int sales_price)
        : used_info_id(used_info_id),
          name(std::move(name)),
          color(std::move(color)),
          engine_number(std::move(engine_number)),
          reg_number(std::move(reg_number)),
          body_number(std::move(body_number)),
          chassis_number(std::move(chassis_number)),
          release_date(std::move(release_date)),
          mileage(mileage),
          release_price(release_price),
          sales_price(sales_price) {}

    static vector<Car> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM car;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<Car> car;
        for (const vector<string> &row : results) {
            car.push_back(parseRow(row));
        }

        return car;
    }

    static Car findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM car WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("car not found");
        }

        return parseRow(results[0]);
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO car (used_info_id, name, color, engine_number, "
               "reg_number, body_number, chassis_number, release_date, "
               "mileage, release_price, sales_price) VALUES ("
            << used_info_id << ", '" << name << "', '" << color << "', '"
            << engine_number << "', '" << reg_number << "', '" << body_number
            << "', '" << chassis_number << "', '" << release_date << "', "
            << mileage << ", " << release_price << ", " << sales_price << ");";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    static bool isCarExists(SQLHDBC sqlhdbc, string reg_number) {
        ostringstream oss;
        oss << "SELECT 1 FROM car WHERE reg_number = "
            << "'" << reg_number << "'"
            << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (!results.empty() && results[0][0] == "1") {
            return true;
        }
        return false;
    }

    static Car findByRegNumber(SQLHDBC sqlhdbc, string reg_number) {
        ostringstream oss;
        oss << "SELECT * FROM car WHERE reg_number = "
            << "'" << reg_number << "'"
            << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("car not found");
        }

        return parseRow(results[0]);
    }

    static Car findByBodyNumber(SQLHDBC sqlhdbc, string body_number) {
        ostringstream oss;
        oss << "SELECT * FROM car WHERE body_number = "
            << "'" << body_number << "'"
            << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("car not found");
        }

        return parseRow(results[0]);
    }

    static vector<Car> findAllByJoin(SQLHDBC sqlhdbc, string table) {
        ostringstream oss;
        oss << "SELECT car.id, used_info_id, car.name, color, engine_number, "
               "reg_number, body_number, chassis_number, release_date, "
               "mileage, "
               "release_price, sales_price FROM car JOIN "
            << table << " ON " << table << ".car_id = car.id;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("employee info not found");
        }

        return parseTable(results);
    }

    int getId() const { return id; }

    const int &getUsedInfoId() const { return used_info_id; }

    const string &getName() const { return name; }

    const string &getColor() const { return color; }

    const string &getEngineNumber() const { return engine_number; }

    const string &getRegNumber() const { return reg_number; }

    const string &getBodyNumber() const { return body_number; }

    const string &getChassisNumber() const { return chassis_number; }

    const string &getReleaseDate() const { return release_date; }

    const int &getMileage() const { return mileage; }

    const int &getReleasePrice() const { return release_price; }

    const int &getSalesPrice() const { return sales_price; }

   private:
    int id;
    int used_info_id;
    string name;
    string color;
    string engine_number;
    string reg_number;
    string body_number;
    string chassis_number;
    string release_date;
    int mileage;
    int release_price;
    int sales_price;

    Car(int id, int used_info_id, string name, string color,
        string engine_number, string reg_number, string body_number,
        string chassis_number, string release_date, int mileage,
        int release_price, int sales_price)
        : id(id),
          used_info_id(used_info_id),
          name(std::move(name)),
          color(std::move(color)),
          engine_number(std::move(engine_number)),
          reg_number(std::move(reg_number)),
          body_number(std::move(body_number)),
          chassis_number(std::move(chassis_number)),
          release_date(std::move(release_date)),
          mileage(mileage),
          release_price(release_price),
          sales_price(sales_price) {}

    static Car parseRow(vector<string> row) {
        return {stoi(row[0]), stoi(row[1]), row[2],        row[3],
                row[4],       row[5],       row[6],        row[7],
                row[8],       stoi(row[9]), stoi(row[10]), stoi(row[11])};
    }

    static vector<Car> parseTable(vector<vector<string>> table) {
        vector<Car> resVector;
        for (int i = 0; i < table.size(); i++) {
            resVector.push_back(parseRow(table[i]));
        }
        return resVector;
    }
};

#endif  // LAB1_CAR_H