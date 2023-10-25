#ifndef LAB1_MENU_H
#define LAB1_MENU_H

#include <iomanip>
#include <iostream>
#include <limits>
#include <regex>
#include <string>

#include "../models/car.h"
#include "../models/certifying_document.h"
#include "../models/client_buyer.h"
#include "../models/client_seller.h"
#include "../models/employee.h"
#include "../models/part.h"
#include "../models/passport.h"
#include "../models/transfer_info.h"
#include "../models/used_info.h"
#include "table_printer.h"

using namespace std;

#define HELP \
    "=========================================\n\
1) Get transfer info list\n\
2) Get employee list\n\
3) Get used info list \n\
4) Get part list \n\
5) Get car list\n\
6) Get certifying document list \n\
7) Get passport list \n\
8) Get clients buyer list \n\
9) Get clients seller list\n\
=========================================\n\
10) Add car\n\
11) Sell car\n\
12) Add used info\n\
13) Add certifying document\n\
14) Repair car\n\
15) Changing an employee's position\n\
16) Add part\n\
=========================================\n\
0) Exit\n\
=========================================\n\
"

class Menu {
   public:
    explicit Menu(SQLHDBC hdbc) : hdbc(hdbc) {}

    void testMenu() {
        bool isWorked = true;
        string command;

        do {
            cout << HELP;
            cout << ">";
            cin >> command;

            if (isValidCommand(command)) {
                int num = stoi(command);

                switch (num) {
                    // get transfer info list
                    case 1: {
                        vector<TransferInfo> transferInfo =
                            TransferInfo::findAll(hdbc);

                        if (!transferInfo.empty()) {
                            vector<vector<string>> data;

                            for (int i = 0; i < transferInfo.size(); i++) {
                                data.push_back(
                                    {to_string(i + 1),
                                     transferInfo[i].getPreviousPosition(),
                                     transferInfo[i].getTransferReason(),
                                     transferInfo[i].getOrderDate()});
                            }

                            vector<string> headers = {"id", "previous position",
                                                      "transfer reason",
                                                      "order date"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No transfer info found." << endl;

                        break;
                    }

                    // get employee list
                    case 2: {
                        vector<Employee> employees = Employee::findAll(hdbc);

                        if (!employees.empty()) {
                            vector<vector<string>> data;

                            for (int i = 0; i < employees.size(); ++i) {
                                data.push_back(
                                    {to_string(i + 1),
                                     to_string(
                                         employees[i].getTransferInfoId()),
                                     employees[i].getFirstName(),
                                     employees[i].getSecondName(),
                                     employees[i].getMiddleName(),
                                     employees[i].getBirthDate(),
                                     employees[i].getAddress(),
                                     employees[i].getPosition(),
                                     to_string(employees[i].getSalary())

                                    });
                            }

                            vector<string> headers = {
                                "№",           "transfer_info_id", "first_name",
                                "second_name", "middle_name",      "birth_date",
                                "address",     "position",         "salary"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No employees found." << endl;
                        break;
                    }

                    // get used info list
                    case 3: {
                        vector<UsedInfo> usedInfo = UsedInfo::findAll(hdbc);

                        if (!usedInfo.empty()) {
                            vector<Employee> employee;
                            employee = Employee::findAllByJoin(hdbc);
                            vector<vector<string>> data;

                            for (int i = 0; i < employee.size(); ++i) {
                                data.push_back(
                                    {to_string(usedInfo[i].getId()),
                                     employee[i].getFirstName(),
                                     employee[i].getSecondName(),
                                     to_string(usedInfo[i].getPurchasePrice()),
                                     usedInfo[i].getCertificateDate()});
                            }

                            vector<string> headers = {
                                "id", "employee first name",
                                "employee second name", "purchase price",
                                "certificate date"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No used info found." << endl;

                        break;
                    }

                    // get part list
                    case 4: {
                        vector<Part> part = Part::findAll(hdbc);
                        vector<Car> car;
                        car = Car::findAllByJoin(hdbc, "part");
                        if (!part.empty()) {
                            vector<vector<string>> data;
                            for (int i = 0; i < part.size(); ++i) {
                                data.push_back({to_string(part[i].getId()),
                                                car[i].getBodyNumber(),
                                                part[i].getName(),
                                                to_string(part[i].getPrice()),
                                                to_string(part[i].getCount())});
                            }

                            vector<string> headers = {"№", "car body number",
                                                      "name", "price", "count"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No part found." << endl;

                        break;
                    }

                    // get car list
                    case 5: {
                        vector<Car> cars = Car::findAll(hdbc);

                        if (!cars.empty()) {
                            vector<vector<string>> data;
                            for (int i = 0; i < cars.size(); ++i) {
                                data.push_back(
                                    {to_string(i + 1),
                                     to_string(cars[i].getUsedInfoId()),
                                     cars[i].getName(), cars[i].getColor(),
                                     cars[i].getEngineNumber(),
                                     cars[i].getRegNumber(),
                                     cars[i].getBodyNumber(),
                                     cars[i].getChassisNumber(),
                                     cars[i].getReleaseDate(),
                                     to_string(cars[i].getMileage()),
                                     to_string(cars[i].getReleasePrice()),
                                     to_string(cars[i].getSalesPrice())});
                            }

                            vector<string> headers = {
                                "№",           "used info id",   "name",
                                "color",       "engine number",  "reg number",
                                "body number", "chassis number", "release date",
                                "mileage",     "release price",  "sales price"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No car found. You can add a car\n";

                        break;
                    }

                    // get certifying document list
                    case 6: {
                        vector<CertifyingDocument> certifyingDocument =
                            CertifyingDocument::findAll(hdbc);

                        if (!certifyingDocument.empty()) {
                            vector<vector<string>> data;
                            for (int i = 0; i < certifyingDocument.size();
                                 ++i) {
                                data.push_back(
                                    {to_string(certifyingDocument[i].getId()),
                                     certifyingDocument[i].getName(),
                                     certifyingDocument[i].getIssueDate(),
                                     certifyingDocument[i].getIssuer()});
                            }

                            vector<string> headers = {"id", "name",
                                                      "issue date", "issuer"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No certifying document foundt\n";

                        break;
                    }

                        // get passport list
                    case 7: {
                        vector<Passport> passport = Passport::findAll(hdbc);

                        if (!passport.empty()) {
                            vector<vector<string>> data;
                            for (int i = 0; i < passport.size(); ++i) {
                                data.push_back({to_string(i + 1),
                                                passport[i].getFirstName(),
                                                passport[i].getSecondName(),
                                                passport[i].getMiddleName(),
                                                passport[i].getBirthDate(),
                                                passport[i].getAddress(),
                                                passport[i].getIssueDate(),
                                                passport[i].getGender()});
                            }

                            vector<string> headers = {
                                "id",          "first name", "second name",
                                "middle name", "birth date", "address",
                                "issue date",  "gender"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No passport found\n";

                        break;
                    }

                    // get cient buyer list
                    case 8: {
                        vector<ClientBuyer> cientBuyer =
                            ClientBuyer::findAll(hdbc);

                        if (!cientBuyer.empty()) {
                            vector<Car> car;
                            car = Car::findAllByJoin(hdbc, "client_buyer");
                            vector<vector<string>> data;
                            for (int i = 0; i < cientBuyer.size(); ++i) {
                                data.push_back(
                                    {to_string(i + 1),
                                     to_string(cientBuyer[i].getPassportId()),
                                     car[i].getRegNumber(),
                                     cientBuyer[i].getSaleDate(),
                                     cientBuyer[i].getAccountNumber(),
                                     cientBuyer[i].getPaymentType()});
                            }

                            vector<string> headers = {
                                "№",         "passport id",    "car reg number",
                                "sale date", "account number", "payment type"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No client buyer found\n";

                        break;
                    }

                    // get clients seller list
                    case 9: {
                        vector<ClientsSeller> clientsSeller =
                            ClientsSeller::findAll(hdbc);

                        if (!clientsSeller.empty()) {
                            vector<Car> car;
                            car = Car::findAllByJoin(hdbc, "client_seller");
                            vector<vector<string>> data;
                            for (int i = 0; i < clientsSeller.size(); ++i) {
                                data.push_back(
                                    {to_string(clientsSeller[i].getId()),
                                     to_string(
                                         clientsSeller[i].getPassportId()),
                                     car[i].getRegNumber(),
                                     to_string(clientsSeller[i]
                                                   .getCertifyingDocumentId()),
                                     clientsSeller[i].getPurchaseDate()});
                            }

                            vector<string> headers = {
                                "№", "passport id", "car reg number",
                                "certifying document id", "purchase date"};

                            TablePrinter::printTable(headers, data);

                            break;
                        }

                        cout << "No client seller found\n";

                        break;
                    }

                    // Add car
                    case 10: {
                        string tmp_used_info_id, used_info_id, name, color,
                            engine_number, reg_number, body_number,
                            chassis_number, release_date, mileage,
                            release_price, sales_price, passport_id,
                            car_reg_number, certifying_document_id,
                            purchase_date;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "If the car is new, enter '1', otherwise enter "
                                "the vehicle "
                                "acceptance document number or fill out a new "
                                "one:\n>";
                        getline(cin, tmp_used_info_id);
                        used_info_id = tmp_used_info_id;

                        if (stoi(tmp_used_info_id) != 1) {
                            if (!UsedInfo::isUsedInfoExists(
                                    hdbc, stoi(tmp_used_info_id))) {
                                string employee_first_name,
                                    employee_second_name, purchase_price,
                                    certificate_date;

                                cout << "   Document not found, add a new "
                                        "one.\n";

                                cout << "   Enter employee first name:\n   >";
                                getline(cin, employee_first_name);

                                cout << "   Enter employee second name:\n   >";
                                getline(cin, employee_second_name);

                                cout << "   Enter purchase price:\n   >";
                                getline(cin, purchase_price);

                                cout << "   Enter certificate date (like "
                                        "2001-01-01):\n   >";
                                getline(cin, certificate_date);

                                UsedInfo usedInfo(Employee::findByName(
                                                      hdbc, employee_first_name,
                                                      employee_second_name)
                                                      .getId(),
                                                  stoi(purchase_price),
                                                  certificate_date);
                                usedInfo.save(hdbc);
                                used_info_id = to_string(
                                    UsedInfo::findLastId(hdbc).getId());
                            }

                            cout << "Enter passport id:\n>";
                            getline(cin, passport_id);

                            if (!Passport::isPassportExists(
                                    hdbc, stoi(passport_id))) {
                                string first_name, second_name, middle_name,
                                    birth_date, address, issue_date, gender;

                                cout << "   Add new customer information\n";

                                cout << "   Enter first name:\n   >";
                                getline(cin, first_name);

                                cout << "   Enter second_name:\n   >";
                                getline(cin, second_name);

                                cout << "   Enter middle name:\n   >";
                                getline(cin, middle_name);

                                cout << "   Enter birth date (like "
                                        "2001-01-01):\n   >";
                                getline(cin, birth_date);

                                cout << "   Enter address:\n   >";
                                getline(cin, address);

                                cout << "   Enter issue date (like "
                                        "2001-01-01):\n   >";
                                getline(cin, issue_date);

                                cout << "   Enter gender (man, woman):\n   >";
                                getline(cin, gender);

                                Passport passport(stoi(passport_id), first_name,
                                                  second_name, middle_name,
                                                  birth_date, address,
                                                  issue_date, gender);
                                passport.save(hdbc);
                            }

                            cout << "Enter certifying document id:\n>";
                            getline(cin, certifying_document_id);

                            if (!CertifyingDocument::isCertifyingDocumentExists(
                                    hdbc, stoi(certifying_document_id))) {
                                string name, issue_date, issuer;

                                cout << "   Add new certifying document\n";

                                cout << "   Enter name:\n   >";
                                getline(cin, name);

                                cout << "   Enter issue date (like "
                                        "2001-01-01):\n   >";
                                getline(cin, issue_date);

                                cout << "   Enter issuer:\n   >";
                                getline(cin, issuer);

                                CertifyingDocument certifyingDocument(
                                    stoi(certifying_document_id), name,
                                    issue_date, issuer);
                                certifyingDocument.save(hdbc);
                            }

                            cout << "Enter purchase date (like 2001-01-01):\n>";
                            getline(cin, purchase_date);
                        }

                        cout << "Enter name of car:\n>";
                        getline(cin, name);

                        cout << "Enter color:\n>";
                        getline(cin, color);

                        cout << "Enter engine number:\n>";
                        getline(cin, engine_number);

                        cout << "Enter reg number:\n>";
                        getline(cin, reg_number);

                        cout << "Enter body number:\n>";
                        getline(cin, body_number);

                        cout << "Enter chassis number:\n>";
                        getline(cin, chassis_number);

                        cout << "Enter release date (like 2001-01-01):\n>";
                        getline(cin, release_date);

                        cout << "Enter mileage:\n>";
                        getline(cin, mileage);

                        cout << "Enter release price:\n>";
                        getline(cin, release_price);

                        cout << "Enter sales price:\n>";
                        getline(cin, sales_price);

                        Car car(stoi(used_info_id), name, color, engine_number,
                                reg_number, body_number, chassis_number,
                                release_date, stoi(mileage),
                                stoi(release_price), stoi(sales_price));
                        car.save(hdbc);
                        ClientsSeller clientsSeller(
                            stoi(passport_id),
                            Car::findByRegNumber(hdbc, reg_number).getId(),
                            stoi(certifying_document_id), purchase_date);
                        clientsSeller.save(hdbc);
                        break;
                    }

                    // Sell car
                    case 11: {
                        string passport_id, car_reg_number, sale_date,
                            account_number, payment_type;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter passport id:\n>";
                        getline(cin, passport_id);

                        if (!Passport::isPassportExists(hdbc,
                                                        stoi(passport_id))) {
                            string first_name, second_name, middle_name,
                                birth_date, address, issue_date, gender;

                            cout << "   Add new customer information\n";

                            cout << "   Enter first name:\n   >";
                            getline(cin, first_name);

                            cout << "   Enter second_name:\n   >";
                            getline(cin, second_name);

                            cout << "   Enter middle name:\n   >";
                            getline(cin, middle_name);

                            cout << "   Enter birth date (like 2001-01-01):\n  "
                                    " >";
                            getline(cin, birth_date);

                            cout << "   Enter address:\n   >";
                            getline(cin, address);

                            cout << "   Enter issue date (like 2001-01-01):\n  "
                                    " >";
                            getline(cin, issue_date);

                            cout << "   Enter gender (man, woman):\n   >";
                            getline(cin, gender);

                            Passport passport(stoi(passport_id), first_name,
                                              second_name, middle_name,
                                              birth_date, address, issue_date,
                                              gender);
                            passport.save(hdbc);
                        }

                        cout << "Enter car reg number:\n>";
                        getline(cin, car_reg_number);

                        cout << "Enter sale_date (like 2001-01-01):\n>";
                        getline(cin, sale_date);

                        cout << "Enter account number:\n>";
                        getline(cin, account_number);

                        cout << "Enter payment type (cash, card, transfer):\n>";
                        getline(cin, payment_type);

                        ClientBuyer clientBuyer(
                            stoi(passport_id),
                            Car::findByRegNumber(hdbc, car_reg_number).getId(),
                            sale_date, account_number, payment_type);
                        clientBuyer.save(hdbc);

                        break;
                    }

                    // Add used info
                    case 12: {
                        string employee_first_name, employee_second_name,
                            purchase_price, certificate_date;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter employee first name:\n>";
                        getline(cin, employee_first_name);

                        cout << "Enter employee second name:\n>";
                        getline(cin, employee_second_name);

                        cout << "Enter purchase price:\n>";
                        getline(cin, purchase_price);

                        cout << "Enter certificate date (like 2001-01-01):\n>";
                        getline(cin, certificate_date);

                        UsedInfo usedInfo(
                            Employee::findByName(hdbc, employee_first_name,
                                                 employee_second_name)
                                .getId(),
                            stoi(purchase_price), certificate_date);
                        usedInfo.save(hdbc);

                        break;
                    }

                    // Add certifying document
                    case 13: {
                        string id, name, issue_date, issuer;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter id:\n>";
                        getline(cin, id);

                        cout << "Enter name:\n>";
                        getline(cin, name);

                        cout << "Enter issue date (like 2001-01-01):\n>";
                        getline(cin, issue_date);

                        cout << "Enter issuer:\n>";
                        getline(cin, issuer);

                        CertifyingDocument certifyingDocument(
                            stoi(id), name, issue_date, issuer);
                        certifyingDocument.save(hdbc);

                        break;
                    }

                    // Repair car
                    case 14: {
                        string reg_number, part_id;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter car reg number:\n>";
                        getline(cin, reg_number);

                        vector<Part> part = Part::findByCarId(
                            hdbc,
                            Car::findByRegNumber(hdbc, reg_number).getId());

                        if (!part.empty()) {
                            vector<vector<string>> data;
                            for (int i = 0; i < part.size(); ++i) {
                                data.push_back({to_string(part[i].getId()),
                                                to_string(part[i].getCarId()),
                                                part[i].getName(),
                                                to_string(part[i].getPrice()),
                                                to_string(part[i].getCount())});
                            }

                            vector<string> headers = {"id", "car id", "name",
                                                      "price", "count"};

                            TablePrinter::printTable(headers, data);

                            cout << "Select the id of the required part:\n>";
                            getline(cin, part_id);

                            Part part = Part::findById(hdbc, stoi(part_id));
                            part.setCount(part.getCount() - 1);
                            part.update(hdbc);

                            break;
                        }

                        cout << "No part found." << endl;

                        break;
                    }

                    // Changing an employee's position
                    case 15: {
                        string first_name, second_name, position, salary,
                            transfer_reason, order_date;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter employee first name:\n>";
                        getline(cin, first_name);

                        cout << "Enter employee second name:\n>";
                        getline(cin, second_name);

                        cout << "   Add new transfer info\n";

                        cout << "   Enter new position:\n   >";
                        getline(cin, position);

                        cout << "   Enter new salary:\n   >";
                        getline(cin, salary);

                        cout << "   Enter transfer reason:\n   >";
                        getline(cin, transfer_reason);

                        cout << "   Enter order date (like 2001-01-01):\n   >";
                        getline(cin, order_date);

                        Employee employee =
                            Employee::findByName(hdbc, first_name, second_name);
                        TransferInfo newTransferInfo(employee.getPosition(),
                                                     transfer_reason,
                                                     order_date);
                        newTransferInfo.save(hdbc);

                        employee.setTransferInfoId(
                            TransferInfo::findLastId(hdbc).getId());
                        employee.setPosition(position);
                        employee.setSalary(stoi(salary));

                        employee.save(hdbc);
                        break;
                    }

                    // Add part
                    case 16: {
                        string car_body_number, name, price, count;

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Enter car body number:\n>";
                        getline(cin, car_body_number);

                        cout << "Enter part name:\n>";
                        getline(cin, name);

                        cout << "Enter price:\n>";
                        getline(cin, price);

                        cout << "Enter count:\n>";
                        getline(cin, count);

                        Part part(Car::findByBodyNumber(hdbc, car_body_number)
                                      .getId(),
                                  name, stoi(price), stoi(count));
                        part.save(hdbc);

                        break;
                    }

                    case 0: {
                        isWorked = false;

                        break;
                    }

                    default: {
                        cout << "Error" << endl;

                        break;
                    }
                }
            }
        } while (isWorked);
    }

   private:
    SQLHDBC hdbc;

    static bool isValidCommand(const string &command) {
        return isPositiveValue(string_view(command));
    }

    static bool isPositiveValue(string_view s) {
        static const regex r(R"(\d{1,})");
        return regex_match(s.data(), r);
    }
};

#endif  // LAB1_MENU_H