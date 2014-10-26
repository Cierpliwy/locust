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

#include "Locust/Objects/File.hpp"
using namespace locust;
using namespace std;

unsigned int File::ID() const {
    lock_guard<mutex> lock(_mutex);
    if (_isCleaned) fetch();
    return _ID;
}

unsigned int File::categoryID() const {
    lock_guard<mutex> lock(_mutex);
    if (_isCleaned) fetch();
    return _categoryID;
}

string File::name() const {
    lock_guard<mutex> lock(_mutex);
    if (_isCleaned) fetch();
    return _name;
}

string File::date() const {
    lock_guard<mutex> lock(_mutex);
    if (_isCleaned) fetch();
    return _date;
}

string File::content() const {
    lock_guard<mutex> lock(_mutex);
    if (_isCleaned) fetch();
    return _content;
}

void File::setID(unsigned int ID) {
    lock_guard<mutex> lock(_mutex);
    _ID = ID;
}

void File::setCategoryID(unsigned int categoryID) {
    lock_guard<mutex> lock(_mutex);
    _categoryID = categoryID;
}

void File::setName(const string &name) {
    lock_guard<mutex> lock(_mutex);
    _name = name;
}

void File::setDate(const string &date) {
    lock_guard<mutex> lock(_mutex);
    _date = date;
}

void File::setContent(const string &content) {
    lock_guard<mutex> lock(_mutex);
    _content = content; 
}

void File::save() {
    lock_guard<mutex> lock(_mutex);
    //TODO: Save
}

void File::fetch() const {
    lock_guard<mutex> lock(_mutex);
    //TODO: Fetch
    _isCleaned = false;
}

void File::cleanUnused(bool) {
    // Not implemented
}

void File::cleanAll(bool) {
    lock_guard<mutex> lock(_mutex);
    //TODO: Implement 
    _isCleaned = true;
}

long unsigned int File::allocatedMemory() const {
    lock_guard<mutex> lock(_mutex);
    
    unsigned int usedMemory = 0;
    usedMemory += sizeof(*this);
    usedMemory += _name.capacity();
    usedMemory += _date.capacity();
    usedMemory += _content.capacity();
    return usedMemory;
}
