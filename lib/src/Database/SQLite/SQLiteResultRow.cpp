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

#include "Locust/Database/SQLite/SQLiteResultRow.hpp"
#include "Locust/Exceptions/Database/DatabaseStatementException.hpp"
#include <sqlite3.h>
#include <vector>
using namespace locust;
using namespace std;
SQLiteResultRow::SQLiteResultRow() : _statement(nullptr) {}
SQLiteResultRow::SQLiteResultRow(sqlite3_stmt *statement) : _statement(statement) {
    next();
}

SQLiteResultRow::~SQLiteResultRow() {
    cleanup();
}

void SQLiteResultRow::cleanup() {
    if (_statement) {
        _rowValues.clear();
        _statement = nullptr;
    }
}

bool SQLiteResultRow::next() {
    if (!_statement) return false;

    int result = SQLITE_BUSY;
    while (result == SQLITE_BUSY || result == SQLITE_LOCKED) {
        result = sqlite3_step(_statement);
    }
    if (result == SQLITE_DONE) {
        cleanup();
        return false;
    }
    if (result != SQLITE_ROW) {
        cleanup();
        throw DatabaseStatementException(THIS_LOCATION, sqlite3_errstr(result));
    }
    
    int columnCount = sqlite3_column_count(_statement);
    if (columnCount <= 0) {
        _rowValues.clear();
        return true;
    }

    _rowValues.resize(static_cast<size_t>(columnCount));

    for(int i = 0; i < columnCount; ++i) {
        int type = sqlite3_column_type(_statement, i);
        switch(type) {
            case SQLITE_INTEGER:
                _rowValues[static_cast<size_t>(i)] = static_cast<long>(sqlite3_column_int64(_statement, i));
                break;
            case SQLITE_FLOAT:
                _rowValues[static_cast<size_t>(i)] = sqlite3_column_double(_statement, i);
                break;
            case SQLITE_TEXT:
                _rowValues[static_cast<size_t>(i)] = reinterpret_cast<const char*>(sqlite3_column_text(_statement, i));
                break;
            case SQLITE_BLOB: {
                const char *data = reinterpret_cast<const char*>(sqlite3_column_blob(_statement, i));
                int bytesNum = sqlite3_column_bytes(_statement, i);
                _rowValues[static_cast<size_t>(i)] = vector<char>(data, data + bytesNum);
                break;
            }
            case SQLITE_NULL:
                _rowValues[static_cast<size_t>(i)] = nullptr;
                break;
        };
    }
    
    return true;
}

const Values &SQLiteResultRow::values() const {
    return _rowValues;
}

const Value &SQLiteResultRow::operator[](unsigned int i) const {
    return _rowValues[i];
}

bool SQLiteResultRow::done() const {
    return _statement == nullptr;
}

