cmake_minimum_required(VERSION 3.22.1)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

find_package(ODBC REQUIRED)

include_directories(${ODBC_INCLUDE_DIRS})
link_directories(${ODBC_LIBRARY_DIRS})

add_executable(lab1 main.cpp
        utils/config_reader.h
        utils/menu.h
        utils/sql_executor.h
        utils/table_printer.h
        models/car.h
        models/certifying_document.h
        models/client_buyer.h
        models/client_seller.h
        models/employee.h
        models/part.h
        models/passport.h
        models/transfer_info.h
        models/used_info.h
)

target_link_libraries(lab1 ${ODBC_LIBRARIES})
