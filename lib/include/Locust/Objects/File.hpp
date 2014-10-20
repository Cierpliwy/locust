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

#ifndef LOCUST_FILE_HPP
#define LOCUST_FILE_HPP
#include "Object.hpp"
#include <string>

namespace locust {

class FileManager;

class File : public Object {
    friend class FileManager;
    
public:
    unsigned int ID() const;
    unsigned int categoryID() const;
    std::string name() const;
    std::string date() const;
    std::string content() const;
    
    void setID(unsigned int ID) const;
    void setCategoryID(unsigned int categoryID) const;
    void setName(const std::string &name) const;
    void setDate(const std::string &date) const;
    void setContent(const std::string& content) const;
    
    virtual void save();
    virtual void fetch(); 
    virtual long unsigned int allocatedMemory() const;
    virtual void cleanAll(bool recursive = false);
    virtual void cleanUnused(bool recursive = false);
    
protected:
    File(FileManager &manager) : _manager(manager) {}
    
    unsigned int _ID;
    unsigned int _categoryID;
    std::string _name;
    std::string _date;
    std::string _content;
    FileManager &_manager;
};

}

#endif // LOCUST_FILE_HPP

