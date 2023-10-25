#ifndef LAB1_CERTIFYING_DOCUMENT_H
#define LAB1_CERTIFYING_DOCUMENT_H

#include <string>

#include "../utils/sql_executor.h"

using namespace std;

class CertifyingDocument {
   public:
    CertifyingDocument(int id, string name, string issue_date, string issuer)
        : id(id),
          name(std::move(name)),
          issue_date(std::move(issue_date)),
          issuer(std::move(issuer)) {}

    static vector<CertifyingDocument> findAll(SQLHDBC sqlhdbc) {
        string selectSql = "SELECT * FROM certifying_document;";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, selectSql);

        vector<CertifyingDocument> certifyingDocument;
        for (const vector<string> &row : results) {
            certifyingDocument.push_back(parseFromVector(row));
        }

        return certifyingDocument;
    }

    static CertifyingDocument findById(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT * FROM certifying_document WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (results.empty()) {
            throw runtime_error("certifying document not found");
        }

        return parseFromVector(results[0]);
    }

    static bool isCertifyingDocumentExists(SQLHDBC sqlhdbc, int id) {
        ostringstream oss;
        oss << "SELECT 1 FROM certifying_document WHERE id = " << id << ";";
        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, oss.str());

        if (!results.empty() && results[0][0] == "1") {
            return true;
        }
        return false;
    }

    void save(SQLHDBC sqlhdbc) {
        ostringstream oss;
        oss << "INSERT INTO certifying_document (id, name, issue_date, issuer) "
               "VALUES ("
            << id << ", '" << name << "', '" << issue_date << "', '" << issuer
            << "');";

        string insertSql = oss.str();

        vector<vector<string>> results =
            SqlExecutor::executeSql(sqlhdbc, insertSql);
    }

    int getId() const { return id; }

    const string &getName() const { return name; }

    const string &getIssueDate() const { return issue_date; }

    const string &getIssuer() const { return issuer; }

   private:
    int id;
    string name;
    string issue_date;
    string issuer;

    explicit CertifyingDocument(string name, string issue_date, string issuer)
        : name(std::move(name)),
          issue_date(std::move(issue_date)),
          issuer(std::move(issuer)) {}

    static CertifyingDocument parseFromVector(vector<string> row) {
        return {stoi(row[0]), row[1], row[2], row[3]};
    }
};

#endif  // LAB1_CERTIFYING_DOCUMENT_H