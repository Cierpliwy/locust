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

#ifndef LOCUST_VALUE_HPP
#define LOCUST_VALUE_HPP
#include <string>
#include <vector>

namespace locust {

class Value {
public:
    enum class Type {
        Long,
        Double,
        String,
        Blob,
        Null
    };

    Value();
    Value(const Value& value);
    ~Value();

    Value(int intValue);
    Value(long longValue);
    Value(double doubleValue);
    Value(const char *stringValue);
    Value(const std::string &stringValue);
    Value(const std::vector<char> &blobValue);
    Value& operator=(const Value& value);
    Value& operator=(int intValue);
    Value& operator=(long longValue);
    Value& operator=(double doubleValue);
    Value& operator=(const char *stringValue);
    Value& operator=(const std::string &stringValue);
    Value& operator=(const std::vector<char> &blobValue);

    Type type() const;

    long asLong() const;
    double asDouble() const;
    const std::string& asString() const;
    const std::vector<char>& asBlob() const;

private:

    void clean();
    void copy(const Value &value);
    
    union ValueImpl {
        ValueImpl(){}
        ~ValueImpl(){}

        long longValue;
        double doubleValue;
        std::string stringValue;
        std::vector<char> blobValue;
    };

    Type _type;
    ValueImpl _value;
};

typedef std::vector<Value> Values;

}

#endif // LOCUST_VALUE_HPP
