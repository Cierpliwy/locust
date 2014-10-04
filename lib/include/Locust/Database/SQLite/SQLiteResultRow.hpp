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

#ifndef LOCUST_SQLITE_RESULT_ROW_HPP
#define LOCUST_SQLITE_RESULT_ROW_HPP
#include "Locust/Database/Database.hpp"
#include "Locust/Database/ResultRow.hpp"
struct sqlite3_stmt;

namespace locust {

class SQLiteResultRow : public ResultRow {
public:
    friend class SQLiteDatabase;

    virtual const Values& values() const;
    virtual const Value& operator[](unsigned int i) const;
    virtual bool next();
    virtual bool done() const;

protected:
    SQLiteResultRow();
    SQLiteResultRow(sqlite3_stmt *statement);

    sqlite3_stmt *_statement;
    Values _rowValues;
};

}

#endif // LOCUST_SQLITE_RESULT_ROW_HPP
