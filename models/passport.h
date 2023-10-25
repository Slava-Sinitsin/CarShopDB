#ifndef LAB1_PASSPORT_H
#define LAB1_PASSPORT_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class Passport {
   public:
    Passport(int id, string first_name, string second_name, string middle_name,
             string birth_date, string address, string issue_date,
             string gender)
        : id(id),
          first_name(std::move(first_name)),
          second_name(std::move(second_name)),
          middle_name(std::move(middle_name)),
          birth_date(std::move(birth_date)),
          address(std::move(address)),
          issue_date(std::move(issue_date)),
          gender(std::move(gender)) {}

    static vector<Passport> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM passport;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<Passport> passport;
        for (const vector<string> &row : results) {
            passport.push_back(parseFromVector(row));
        }

        return passport;
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO passport (id, first_name, second_name, "
               "middle_name, birth_date, address, issue_date, gender) VALUES ("
            << id << ", '" << first_name << "', '" << second_name << "', '"
            << middle_name << "', '" << birth_date << "', '" << address
            << "', '" << issue_date << "', '" << gender << "');";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    static Passport findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM passport WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("passport not found");
        }

        return parseFromVector(results[0]);
    }

    static bool isPassportExists(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT 1 FROM passport WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (!results.empty() && results[0][0] == "1") {
            return true;
        }
        return false;
    }

    int getId() const { return id; }

    const string &getFirstName() const { return first_name; }

    const string &getSecondName() const { return second_name; }

    const string &getMiddleName() const { return middle_name; }

    const string &getBirthDate() const { return birth_date; }

    const string &getAddress() const { return address; }

    const string &getIssueDate() const { return issue_date; }

    const string &getGender() const { return gender; }

   private:
    int id;
    string first_name;
    string second_name;
    string middle_name;
    string birth_date;
    string address;
    string issue_date;
    string gender;

    explicit Passport(string first_name, string second_name, string middle_name,
                      string birth_date, string address, string issue_date,
                      string gender)
        : first_name(std::move(first_name)),
          second_name(std::move(second_name)),
          middle_name(std::move(middle_name)),
          birth_date(std::move(birth_date)),
          address(std::move(address)),
          issue_date(std::move(issue_date)),
          gender(std::move(gender)) {}

    static Passport parseFromVector(vector<string> row) {
        return {stoi(row[0]), row[1], row[2], row[3],
                row[4],       row[5], row[6], row[7]};
    }
};

#endif  // LAB1_PASSPORT_H