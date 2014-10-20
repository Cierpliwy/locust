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

#ifndef LOCUST_MEMORY_MANAGED_HPP
#define LOCUST_MEMORY_MANAGED_HPP
#include <mutex>

namespace locust {

class MemoryManaged {
public:
    MemoryManaged() : _isCleaned(true) {}
    virtual ~MemoryManaged();
    
    virtual void fetch() = 0;
    
    virtual void cleanUnused(bool recursive = false) = 0;
    virtual void cleanAll(bool recursive = false) = 0;
    
    virtual unsigned long allocatedMemory() const = 0;
protected:
    bool _isCleaned;
};
    
}

#endif // LOCUST_MEMORY_MANAGED_HPP 
