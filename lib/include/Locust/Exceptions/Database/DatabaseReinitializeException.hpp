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

#ifndef LOCUST_DATABASE_REINITIALIZE_EXCEPTION_HPP
#define LOCUST_DATABASE_REINITIALIZE_EXCEPTION_HPP

#include "Locust/Exceptions/Database/DatabaseException.hpp"

namespace locust {

class DatabaseReinitializeException : public DatabaseException {
public:
    DatabaseReinitializeException(Location location);
    DatabaseReinitializeException(Location location, const char *reason);
};

}

#endif // LOCUST_DATABASE_REINITIALIZE_EXCEPTION_HPP
