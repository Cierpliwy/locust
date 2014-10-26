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

#include "Locust/Managers/ObjectManager.hpp"
using namespace locust;
using namespace std;

ObjectManager::ObjectManager(const ObjectManager &) {

}

ObjectManager::ObjectManager() {

}

std::unordered_set<ObjectManager*> ObjectManager::_objects;
std::mutex ObjectManager::_registrationMutex;

void ObjectManager::registerObjectManager(ObjectManager *manager) {
    lock_guard<mutex> lock(_registrationMutex);
    _objects.insert(manager);
}

void ObjectManager::unregisterObjectManager(ObjectManager *manager) {
    lock_guard<mutex> lock(_registrationMutex);
    _objects.erase(manager);
}
