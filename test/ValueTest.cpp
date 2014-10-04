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
#include <vector>
#include <string>
using namespace locust;
using namespace Catch;
using namespace std;

TEST_CASE("Check all available types", "[values]") {
    Value val;
    
    SECTION("Testing Null value") {
        REQUIRE(val.type() == Value::Type::Null);
        REQUIRE_THROWS_AS(val.asInt(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asDouble(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asString(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asBlob(), InvalidValueException);
    }
    
    SECTION("Testing Int value") {
        val = 30;
        REQUIRE(val.type() == Value::Type::Integer);
        REQUIRE(val.asInt() == 30);
        REQUIRE_THROWS_AS(val.asDouble(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asString(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asBlob(), InvalidValueException);
    }
    
    SECTION("Testing Double value") {
        val = 1.25;
        REQUIRE(val.type() == Value::Type::Double);
        REQUIRE_THROWS_AS(val.asInt(), InvalidValueException);
        REQUIRE(val.asDouble() == 1.25);
        REQUIRE_THROWS_AS(val.asString(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asBlob(), InvalidValueException);
    }
    
    SECTION("Testing String value") {
        val = "Ala ma kota";
        REQUIRE(val.type() == Value::Type::String);
        REQUIRE_THROWS_AS(val.asInt(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asDouble(), InvalidValueException);
        REQUIRE(val.asString() == "Ala ma kota");
        REQUIRE_THROWS_AS(val.asBlob(), InvalidValueException);
        
        std::string str = "Ala ma kota2";
        val = str;
        
        REQUIRE(val.type() == Value::Type::String);
        REQUIRE_THROWS_AS(val.asInt(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asDouble(), InvalidValueException);
        REQUIRE(val.asString() == "Ala ma kota2");
        REQUIRE_THROWS_AS(val.asBlob(), InvalidValueException);
    }
    
    SECTION("Testing Blob value") {
        vector<char> vec = {'A','B','C','D'}; 
        val = vec; 
        REQUIRE(val.type() == Value::Type::Blob);
        REQUIRE_THROWS_AS(val.asInt(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asDouble(), InvalidValueException);
        REQUIRE_THROWS_AS(val.asString(), InvalidValueException);
        REQUIRE(val.asBlob()[0] == 'A');
        REQUIRE(val.asBlob()[1] == 'B');
        REQUIRE(val.asBlob()[2] == 'C');
        REQUIRE(val.asBlob()[3] == 'D');
    }
    
    SECTION("Test copy operations") {
        Value valNull(val);
        REQUIRE(valNull.type() == Value::Type::Null);
        
        val = 12;
        Value valInt(val);
        REQUIRE(valInt.type() == Value::Type::Integer);
        REQUIRE(valInt.asInt() == 12);
        
        val = 3.14;
        Value valDouble(val);
        REQUIRE(valDouble.type() == Value::Type::Double);
        REQUIRE(valDouble.asDouble() == 3.14);
        
        val = "Test";
        Value valString(val);
        REQUIRE(valString.type() == Value::Type::String);
        REQUIRE(valString.asString() == "Test");
        
        val = vector<char>();
        Value valBlob(val);
        REQUIRE(valBlob.type() == Value::Type::Blob);
        REQUIRE(valBlob.asBlob().empty());
    }
}