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
#include "Catch.hpp"
#include <Locust/Locust.hpp>
#include <string>
#include <cstdio>
#include <cerrno>
#include <thread>
using namespace std;
using namespace locust;
using namespace Catch;

TEST_CASE("Test database SQLite implementation","[database]") {
    const std::string dbFileName = ".testdb";
    
    // Make sure that database is cleaned
    int result = remove(dbFileName.c_str());
    REQUIRE((result == 0 || errno == ENOENT));
    
    SQLiteDatabase db;
    REQUIRE_NOTHROW(db.initialize(dbFileName));
    REQUIRE_THROWS_AS(db.initialize(dbFileName), DatabaseReinitializeException);
    
    SECTION("Check bad syntax") {
        REQUIRE_THROWS_AS(db.executeStatement("BAD SYNTAX"), DatabaseStatementException);
    }
    
    SECTION("Check insertion and deletion of basic types") {
        shared_ptr<ResultRow> resultRow;
        REQUIRE_NOTHROW(resultRow = db.executeStatement("CREATE TABLE Test (myInteger INTEGER, myReal REAL, myText TEXT, myBlob BLOB)"));
        
        // Check if we won't have any strage results after out of bounds getNextRow() call
        REQUIRE(resultRow->values().empty());
        REQUIRE_FALSE(resultRow->next());
        REQUIRE_FALSE(resultRow->next());
        REQUIRE(resultRow->done());
        
        // Insert values
        vector<char> data = {'a','b','c'};
        REQUIRE_NOTHROW(resultRow = db.executeStatement("INSERT INTO Test VALUES(?,?,?,?)", {32, 0.3, "Olek", data}));
        REQUIRE(resultRow->done());
        REQUIRE_NOTHROW(resultRow = db.executeStatement("INSERT INTO Test VALUES(?,?,?,?)", {nullptr, 0.4, "Olek2", vector<char>()}));
        REQUIRE(resultRow->done());
        
        // Check values
        REQUIRE_NOTHROW(resultRow = db.executeStatement("SELECT * FROM Test"));
        REQUIRE(resultRow->values().size() == 4);
        
        Value val = (*resultRow)[0];
        REQUIRE_NOTHROW(val.asInt() == 32); 
        val = (*resultRow)[1];
        REQUIRE_NOTHROW(val.asDouble() == 0.3);
        val = (*resultRow)[2];
        REQUIRE_NOTHROW(val.asString() == "Olek");
        REQUIRE_NOTHROW(val.asString().length() == 4);
        val = (*resultRow)[3];
        REQUIRE_NOTHROW(val.asBlob().size() == 3);
        REQUIRE_NOTHROW(val.asBlob()[0] == 'a');
        REQUIRE_NOTHROW(val.asBlob()[0] == 'b');
        REQUIRE_NOTHROW(val.asBlob()[0] == 'c');
        
        REQUIRE(resultRow->next());
        REQUIRE_FALSE(resultRow->done());
        REQUIRE(resultRow->values().size() == 4);
        
        val = (*resultRow)[0];
        REQUIRE_NOTHROW(val.type() == Value::Type::Null);
        val = (*resultRow)[1];
        REQUIRE_NOTHROW(val.asDouble() == 0.4);
        val = (*resultRow)[2];
        REQUIRE_NOTHROW(val.asString() == "Olek2");
        REQUIRE_NOTHROW(val.asString().length() == 5);
        val = (*resultRow)[3];
        REQUIRE_NOTHROW(val.asBlob().empty());
        
        REQUIRE_FALSE(resultRow->next());
        REQUIRE(resultRow->done());
    }
    
    SECTION("Test concurrent database access") {
        SQLiteDatabase db2;
        REQUIRE_NOTHROW(db2.initialize(dbFileName));
        
        shared_ptr<ResultRow> resultRow;
        REQUIRE_NOTHROW(resultRow = db.executeStatement("CREATE TABLE Atomic (val INTEGER)"));
        REQUIRE(resultRow->done());
        REQUIRE_NOTHROW(resultRow = db.executeStatement("INSERT INTO Atomic VALUES(?)",{0}));
        REQUIRE(resultRow->done());
        
        thread thread1([&resultRow, &db]{
            for (int i = 0; i < 50; ++i) {
                resultRow = db.executeStatement("BEGIN IMMEDIATE TRANSACTION");
                resultRow = db.executeStatement("SELECT * FROM Atomic");
                int value = (*resultRow)[0].asInt();
                resultRow = db.executeStatement("UPDATE Atomic SET val = ?", {++value});
                resultRow = db.executeStatement("END TRANSACTION");
            }
        });
        thread thread2([&db2]{
            shared_ptr<ResultRow> resultRow2;
            for (int i = 0; i < 50; ++i) {
                resultRow2 = db2.executeStatement("BEGIN IMMEDIATE TRANSACTION");
                resultRow2 = db2.executeStatement("SELECT * FROM Atomic");
                int value = (*resultRow2)[0].asInt();
                resultRow2 = db2.executeStatement("UPDATE Atomic SET val = ?", {++value});
                resultRow2 = db2.executeStatement("END TRANSACTION");
            }
        });
        
        thread1.join();
        thread2.join();
        
        REQUIRE_NOTHROW(resultRow = db.executeStatement("SELECT * FROM Atomic"));
        REQUIRE(resultRow->values().size() == 1);
        int value = (*resultRow)[0].asInt();
        REQUIRE(value == 100);
    }
}