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

#ifndef LOCUST_OBJECT_MANAGER_HPP
#define LOCUST_OBJECT_MANAGER_HPP
#include "../Interfaces/Threadsafe.hpp"
#include "../Interfaces/MemoryManaged.hpp"
#include <mutex>
#include <memory>
#include <unordered_set>

namespace locust {

class ObjectManager : public Threadsafe, public MemoryManaged {
public:
protected:
    ObjectManager();
    ObjectManager(const ObjectManager&);
    
    static void registerObjectManager(ObjectManager *manager);
    static void unregisterObjectManager(ObjectManager *manager);
    static std::unordered_set<ObjectManager*> _objects;
    static std::mutex _registrationMutex;
};

}

#endif // LOCUST_OBJECT_MANAGER_HPP
