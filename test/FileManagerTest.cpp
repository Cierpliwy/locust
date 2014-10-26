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
#include <memory>
using namespace std;
using namespace locust;
using namespace Catch;

TEST_CASE("Test File Manager","[filemanager]") {
    const std::string dbFileName = ".filemanagertestdb";
    
    // Make sure that database is cleaned
    int result = remove(dbFileName.c_str());
    REQUIRE((result == 0 || errno == ENOENT));
    
    shared_ptr<SQLiteDatabase> db(new SQLiteDatabase);
    REQUIRE_NOTHROW(db->initialize(dbFileName));
    
    shared_ptr<FileManager> fm; 
    REQUIRE_NOTHROW(fm = FileManager::getInstance(db));
}