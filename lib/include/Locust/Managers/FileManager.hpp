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

#ifndef LOCUST_FILE_MANAGER_HPP
#define LOCUST_FILE_MANAGER_HPP
#include "ObjectManager.hpp"
#include "../Database/Database.hpp"
#include <memory>
#include <vector>

namespace locust {
class File;

class FileManager : public ObjectManager {
public:
    virtual ~FileManager();
    
    static std::shared_ptr<FileManager> getInstance(std::shared_ptr<Database> database);
    std::shared_ptr<File> createFile(const std::string &name = "");
    
    virtual void fetch() const;
    virtual void save();
    
    virtual void cleanUnused(bool recursive = false);
    virtual void cleanAll(bool recursive = false);
    virtual long unsigned int allocatedMemory() const;
    
protected:
    FileManager(std::shared_ptr<Database> database);
    std::vector<std::shared_ptr<File>> _files;
    std::shared_ptr<Database> _database;
};

}

#endif // LOCUST_FILE_MANAGER_HPP

