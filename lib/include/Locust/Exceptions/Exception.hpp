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

#ifndef LOCUST_EXCEPTION_HPP
#define LOCUST_EXCEPTION_HPP
#include <exception>
#include <string>

#define THIS_LOCATION Exception::Location(__FILE__, __LINE__, __FUNCTION__)

namespace locust {

class Exception : public std::exception {
public:
    struct Location {
        Location(const std::string& fileName, int lineNumber, const std::string &functionName) :
            fileName(fileName), lineNumber(lineNumber), functionName(functionName) {}

        const std::string fileName;
        int lineNumber;
        const std::string functionName;
    };

    Exception(Location location) :
        _location(location) {}

    Exception(Location location, const char *reason) :
        _location(location), _reason(reason) {}

    virtual const char* what() const noexcept;
    virtual const char* className() const noexcept;
    const char* reason() const noexcept;

private:
    const Location _location;
    std::string _reason;
    mutable std::string _exceptionMessage;
};

}

#endif // LOCUST_EXCEPTION_HPP
