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

#ifndef LOCUST_DATABASE_HPP
#define LOCUST_DATABASE_HPP
#include "Locust/Database/Value.hpp"
#include "Locust/Database/ResultRow.hpp"
#include <string>
#include <memory>

namespace locust {

class Database {
public:
    Database();
    virtual ~Database();

    virtual void initialize(const std::string &databaseFileName) = 0;
    virtual void close() = 0;

    virtual std::shared_ptr<ResultRow> executeStatement(const std::string &statement, const Values &params = Values()) = 0;
};

}

#endif // LOCUST_DATABASE_HPP
