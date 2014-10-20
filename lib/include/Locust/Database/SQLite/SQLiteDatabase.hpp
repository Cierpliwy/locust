/*
 * Locust
 * Copyright (C) 2014 Przemysław Lenart <przemek.lenart@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LOCUST_SQLITE_DATABASE_HPP
#define LOCUST_SQLITE_DATABASE_HPP

#include "Locust/Database/Database.hpp"
#include "Locust/Database/SQLite/SQLiteResultRow.hpp"
#include <unordered_map>
struct sqlite3;
struct sqlite3_stmt;

namespace locust {

class SQLiteDatabase : public Database {
public:
    SQLiteDatabase();
    ~SQLiteDatabase();

    virtual void initialize(const std::string &databaseFileName);
    virtual void close();

    virtual std::shared_ptr<ResultRow> executeStatement(const std::string &statement, const Values &params = Values());
    virtual unsigned long lastRowID();
    
private:
    sqlite3_stmt* findOrCreateStatement(const std::string &statement);
    void fillStatementParameters(sqlite3_stmt* statement, const Values &params);
    std::shared_ptr<ResultRow> executeStatement(sqlite3_stmt *statement);
    
    void prepareTables();

    sqlite3 *_db;
    std::unordered_map<std::string, sqlite3_stmt*> _preparedStatements;
    sqlite3_stmt *_lastPreparedStatement;
};

}

#endif //LOCUST_SQLITE_DATABASE_HPP
