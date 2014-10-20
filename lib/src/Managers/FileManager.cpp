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

#include "Locust/Managers/FileManager.hpp"
#include "Locust/Exceptions/Database/DatabaseNotInitializedException.hpp"
#include <chrono>
using namespace std;
using namespace locust;

FileManager::FileManager(shared_ptr<Database> database) : _database(database) {
    if (!database) {
        throw DatabaseNotInitializedException(THIS_LOCATION);
    }
    registerObjectManager(this);
}

FileManager::~FileManager() {
    unregisterObjectManager(this);
}

shared_ptr<FileManager> FileManager::getInstance(shared_ptr<Database> database) {
    return shared_ptr(new FileManager(database));
}

shared_ptr<File> FileManager::createFile(const string &name) {
    //TODO: Category id
    lock_guard lock(_mutex);
    auto currentTime = chrono::system_clock::now();
    time_t t;
    
    _database->executeStatement("INSERT INTO File VALUES(?,?,?,?,?)", {nullptr, 0, name, currentTime.to_time_t(),});
}
