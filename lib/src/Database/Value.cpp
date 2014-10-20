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

#include "Locust/Database/Value.hpp"
#include "Locust/Exceptions/Database/InvalidValueException.hpp"
using namespace locust;
using namespace std;

Value::Value() {
    _type = Type::Null;
}

void Value::clean() {
    if (_type == Type::String)
        _value.stringValue.~string();
    if (_type == Type::Blob)
        _value.blobValue.~vector<char>();
    _type = Type::Null;
}

Value::~Value() {
    clean();
}

void Value::copy(const Value &value) {
    clean();
    _type = value._type;
    switch(_type) {
        case Type::Long:
            _value.longValue = value._value.longValue;
            break;
        case Type::Double:
            _value.doubleValue = value._value.doubleValue;
            break;
        case Type::String:
            new (&_value.stringValue) string(value._value.stringValue);
            break;
        case Type::Blob:
            new (&_value.blobValue) vector<char>(value._value.blobValue);
            break;
        case Type::Null:
            break;
    };
}

Value::Value(const Value &value) {
    _type = Type::Null;
    copy(value);
}

Value::Value(int intValue) {
    _type = Type::Long;
    _value.longValue = intValue;
}

Value::Value(long longValue) {
    _type = Type::Long;
    _value.longValue = longValue;
}

Value::Value(double doubleValue) {
    _type = Type::Double;
    _value.doubleValue = doubleValue;
}

Value::Value(const char *stringValue) {
    if (stringValue) {
        _type = Type::String;
        new (&_value.stringValue) string(stringValue);
    } else {
        _type = Type::Null;
    }
}

Value::Value(const std::string &stringValue) {
    _type = Type::String;
    new (&_value.stringValue) string(stringValue);
    _value.stringValue = stringValue;
}

Value::Value(const std::vector<char> &blobValue) {
    _type = Type::Blob;
    new (&_value.blobValue) vector<char>(blobValue);
    _value.blobValue = blobValue;
}

Value &Value::operator=(const Value& value) {
    copy(value);
    return *this;
}

Value &Value::operator=(int intValue) {
    *this = Value(intValue);
    return *this;
}

Value &Value::operator=(long longValue) {
    *this = Value(longValue);
    return *this;
}

Value &Value::operator=(double doubleValue) {
    *this = Value(doubleValue);
    return *this;
}

Value &Value::operator=(const char *stringValue) {
    *this = Value(stringValue);
    return *this;
}

Value &Value::operator=(const std::string &stringValue) {
    *this = Value(stringValue);
    return *this;
}

Value &Value::operator=(const std::vector< char > &blobValue) {
    *this = Value(blobValue);
    return *this;
}

Value::Type Value::type() const {
    return _type;
}

long Value::asLong() const {
    if (_type != Type::Long)
        throw InvalidValueException(THIS_LOCATION);
    return _value.longValue;
}

double Value::asDouble() const {
    if (_type != Type::Double)
        throw InvalidValueException(THIS_LOCATION);
    return _value.doubleValue;
}

const std::string &Value::asString() const {
    if (_type != Type::String)
        throw InvalidValueException(THIS_LOCATION);
    return _value.stringValue;
}

const std::vector<char>& Value::asBlob() const {
    if (_type != Type::Blob)
        throw InvalidValueException(THIS_LOCATION);
    return _value.blobValue;
}
