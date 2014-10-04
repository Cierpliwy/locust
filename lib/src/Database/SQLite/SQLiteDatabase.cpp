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

#include "Locust/Database/SQLite/SQLiteDatabase.hpp"
#include "Locust/Exceptions/Database/DatabaseReinitializeException.hpp"
#include "Locust/Exceptions/Database/DatabaseOpenException.hpp"
#include "Locust/Exceptions/Database/DatabaseNotInitializedException.hpp"
#include "Locust/Exceptions/Database/DatabaseStatementException.hpp"
#include <sqlite3.h>
using namespace locust;
using namespace std;

SQLiteDatabase::SQLiteDatabase() {
    _db = nullptr;
}

SQLiteDatabase::~SQLiteDatabase() {
    close();
}

void SQLiteDatabase::initialize(const std::string &databaseFileName) {
    if (_db) {
        throw DatabaseReinitializeException(THIS_LOCATION);
    }

    int code = sqlite3_open_v2(databaseFileName.c_str(), &_db, SQLITE_OPEN_READWRITE |
                                                               SQLITE_OPEN_CREATE |
                                                               SQLITE_OPEN_FULLMUTEX |
                                                               SQLITE_OPEN_SHAREDCACHE, nullptr);
    if (code != SQLITE_OK) {
        auto reason = sqlite3_errmsg(_db);
        close();
        throw DatabaseOpenException(THIS_LOCATION, reason);
    }
}

void SQLiteDatabase::close() {
    if (_db) {
        for(auto& statement : _preparedStatements) {
            sqlite3_finalize(statement.second);
        }

        _preparedStatements.clear();
        sqlite3_close(_db);
        _db = nullptr;
    }
}

shared_ptr<ResultRow> SQLiteDatabase::executeStatement(const std::string &statement, const Values &params) {
    if (!_db) throw DatabaseNotInitializedException(THIS_LOCATION);

    sqlite3_stmt *sqliteStatement = findOrCreateStatement(statement);
    fillStatementParameters(sqliteStatement, params);
    return executeStatement(sqliteStatement);
}

// PRIVATE INTERFACE --------------------------------------------------------------------------------------------------
sqlite3_stmt *SQLiteDatabase::findOrCreateStatement(const std::string &statement) {
    sqlite3_stmt *sqliteStatement = nullptr;
    auto preparedStatement = _preparedStatements.find(statement);
    if (preparedStatement == _preparedStatements.end()) {
        int result = SQLITE_BUSY;
        while (result == SQLITE_BUSY || result == SQLITE_LOCKED) {
            result = sqlite3_prepare_v2(_db, statement.c_str(),
                                        static_cast<int>(statement.length() + 1),
                                        &sqliteStatement, nullptr);
        }
        if (result != SQLITE_OK)
            throw DatabaseStatementException(THIS_LOCATION, sqlite3_errstr(result));

        if (_preparedStatements.insert(make_pair(statement, sqliteStatement)).second != true)
            throw DatabaseStatementException(THIS_LOCATION);
    } else {
        sqliteStatement = preparedStatement->second;
    }

    return sqliteStatement;
}

void SQLiteDatabase::fillStatementParameters(sqlite3_stmt *statement, const Values &params) {
    sqlite3_clear_bindings(statement);
    if (params.size() <= 0) return;

    int index = 0;
    for (auto& param : params) {
        index++;
        int result;
        switch(param.type()) {
            case Value::Type::Integer:
                result = sqlite3_bind_int(statement, index, param.asInt());
                break;
            case Value::Type::Double:
                result = sqlite3_bind_double(statement, index, param.asDouble());
                break;
            case Value::Type::String:
                result = sqlite3_bind_text(statement, index, param.asString().c_str(), -1, SQLITE_STATIC);
                break;
            case Value::Type::Blob:
                if (param.asBlob().empty()) {
                    result = sqlite3_bind_zeroblob(statement, index, 0);
                } else {
                    result = sqlite3_bind_blob(statement, index, param.asBlob().data(),
                                               static_cast<int>(param.asBlob().size()), SQLITE_STATIC);
                }
                break;
            case Value::Type::Null:
                result = sqlite3_bind_null(statement, index);
                break;
        }
        if (result != SQLITE_OK) {
            throw DatabaseStatementException(THIS_LOCATION, sqlite3_errstr(result));
        }
    }
}

shared_ptr<ResultRow> SQLiteDatabase::executeStatement(sqlite3_stmt *statement) {
    shared_ptr<ResultRow> resultRow(new SQLiteResultRow(statement));
    return resultRow;
}


