#ifndef LAB1_EMPLOYEE_INFO_H
#define LAB1_EMPLOYEE_INFO_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class Employee {
   public:
    static vector<Employee> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM employee;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<Employee> employee;
        for (const vector<string> &row : results) {
            employee.push_back(parseRow(row));
        }

        return employee;
    }

    static Employee findByName(SQLHDBC sqlhdbc, string firstName,
                               string secondName) {
        ostringstream oss;
        oss << "SELECT * FROM employee WHERE first_name = "
            << "'" << firstName << "' "
            << "AND second_name = "
            << "'" << secondName << "'\n"
            << "ORDER BY id DESC\nLIMIT 1;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("car not found");
        }

        return parseRow(results[0]);
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO employee (transfer_info_id, first_name, "
               "second_name, middle_name, birth_date, address, position, "
               "salary) VALUES ("
            << transfer_info_id << ", '" << first_name << "', '" << second_name
            << "', '" << middle_name << "', '" << birth_date << "', '"
            << address << "', '" << position << "', " << salary << ");";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    static Employee findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM employee WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("employee info not found");
        }

        return parseRow(results[0]);
    }

    static vector<Employee> findAllByJoin(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "SELECT employee.id, transfer_info_id, first_name, second_name, "
               "middle_name, birth_date, address, position, salary FROM "
               "used_info JOIN employee ON used_info.employee_id = "
               "employee.id;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("employee info not found");
        }

        return parseTable(results);
    }

    int getId() const { return id; }

    const int &getTransferInfoId() const { return transfer_info_id; }

    const string &getFirstName() const { return first_name; }

    const string &getSecondName() const { return second_name; }

    const string &getMiddleName() const { return middle_name; }

    const string &getBirthDate() const { return birth_date; }

    const string &getAddress() const { return address; }

    const string &getPosition() const { return position; }

    const int &getSalary() const { return salary; }

    void setTransferInfoId(const int &transfer_info_id) {
        Employee::transfer_info_id = transfer_info_id;
    }

    void setPosition(const string &position) { Employee::position = position; }

    void setSalary(const int &salary) { Employee::salary = salary; }

   private:
    int id;
    int transfer_info_id;
    string first_name;
    string second_name;
    string middle_name;
    string birth_date;
    string address;
    string position;
    int salary;

    Employee(int id, int transfer_info_id, string first_name,
             string second_name, string middle_name, string birth_date,
             string address, string position, int salary)
        : id(id),
          transfer_info_id(transfer_info_id),
          first_name(std::move(first_name)),
          second_name(std::move(second_name)),
          middle_name(std::move(middle_name)),
          birth_date(std::move(birth_date)),
          address(std::move(address)),
          position(std::move(position)),
          salary(salary) {}

    explicit Employee(int transfer_info_id, string first_name,
                      string second_name, string middle_name, string birth_date,
                      string address, string position, int salary)
        : transfer_info_id(transfer_info_id),
          first_name(std::move(first_name)),
          second_name(std::move(second_name)),
          middle_name(std::move(middle_name)),
          birth_date(std::move(birth_date)),
          address(std::move(address)),
          position(std::move(position)),
          salary(salary) {}

    static Employee parseRow(vector<string> row) {
        return {stoi(row[0]), stoi(row[1]), row[2], row[3],      row[4],
                row[5],       row[6],       row[7], stoi(row[8])};
    }

    static vector<Employee> parseTable(vector<vector<string>> table) {
        vector<Employee> resVector;
        for (int i = 0; i < table.size(); i++) {
            resVector.push_back(parseRow(table[i]));
        }
        return resVector;
    }
};

#endif  // LAB1_EMPLOYEE_INFO_H