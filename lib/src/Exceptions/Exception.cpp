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

#include "Locust/Exceptions/Exception.hpp"
#include <sstream>
#include <typeinfo>

using namespace locust;
using namespace std;

const char *locust::Exception::className() const noexcept {
    return typeid(*this).name();
}

const char *Exception::what() const noexcept {
    stringstream ss;
    ss << "Unhandled exception " << className()
       << " at " << _location.fileName
       << " in function " << _location.functionName
       << "():" << _location.lineNumber;

    if (!_reason.empty()) {
        ss << ": " << _reason;
    }

    _exceptionMessage = ss.str();
    return _exceptionMessage.c_str();
}
