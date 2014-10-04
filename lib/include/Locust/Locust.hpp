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

#ifndef LOCUST_HPP
#define LOCUST_HPP

#include "Locust/Exceptions/Exception.hpp"
#include "Locust/Exceptions/Database/DatabaseException.hpp"
#include "Locust/Exceptions/Database/DatabaseReinitializeException.hpp"
#include "Locust/Exceptions/Database/DatabaseOpenException.hpp"
#include "Locust/Exceptions/Database/InvalidValueException.hpp"
#include "Locust/Exceptions/Database/DatabaseNotInitializedException.hpp"
#include "Locust/Exceptions/Database/DatabaseStatementException.hpp"

#include "Locust/Database/Database.hpp"
#include "Locust/Database/SQLite/SQLiteDatabase.hpp"
#include "Locust/Database/Value.hpp"

#endif // LOCUST_HPP
