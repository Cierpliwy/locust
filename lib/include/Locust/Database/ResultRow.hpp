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

#ifndef LOCUST_RESULT_ROWS_HPP
#define LOCUST_RESULT_ROWS_HPP
#include "Locust/Database/Value.hpp"

namespace locust {

class ResultRow {
public:
    virtual ~ResultRow();
    virtual const Values& values() const = 0;
    virtual const Value& operator[](unsigned int i) const = 0;
    virtual bool next() = 0;
    virtual bool done() const = 0;
    
protected:
    ResultRow();
    ResultRow(const ResultRow&);
    ResultRow& operator=(const ResultRow&);
};

}

#endif // LOCUST_RESULT_ROWS_HPP
