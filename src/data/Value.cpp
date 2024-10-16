/**
 * @file Value.cpp
 * @author DrkWithT
 * @brief Implements JSON value classes.
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <exception>
#include <stdexcept>
#include <utility>
#include "data/IValue.hpp"
#include "data/Value.hpp"

namespace toyjson::data {
    /* NullField */

    JsonType NullField::getType() const {
        return JsonType::j_null;
    }

    std::any NullField::toBoxedValue() const {
        return std::any {};
    }

    /* BooleanField */

    BooleanField::BooleanField(bool flag)
        : value {flag} {}

    JsonType BooleanField::getType() const {
        return JsonType::j_boolean;
    }

    std::any BooleanField::toBoxedValue() const {
        return std::any {value};
    }

    NumberField::NumberField(double num)
        : value {num} {}

    JsonType NumberField::getType() const {
        return JsonType::j_number;
    }

    std::any NumberField::toBoxedValue() const {
        return std::any {value};
    }

    /* StringField */

    StringField::StringField(std::string x_str)
        : value(std::move(x_str)) {}

    JsonType StringField::getType() const {
        return JsonType::j_string;
    }

    std::any StringField::toBoxedValue() const {
        return std::any {value};
    }

    ArrayField::ArrayField()
        : value {} {}

    ArrayField::ArrayField(std::vector<std::shared_ptr<IJsonValue>> x_items)
        : value(std::move(x_items)) {}

    JsonType ArrayField::getType() const {
        return JsonType::j_array;
    }

    std::any ArrayField::toBoxedValue() const {
        throw std::runtime_error {"Not implemented"};
    }

    bool ArrayField::isEmpty() const {
        return value.empty();
    }

    size_t ArrayField::getLength() const {
        return value.size();
    }

    const std::shared_ptr<IJsonValue>& ArrayField::getItemPtr(size_t pos) const {
        return value.at(pos);
    }

    /* ObjectField */

    ObjectField::ObjectField()
        : value {} {}

    ObjectField::ObjectField(std::map<std::string, std::shared_ptr<IJsonValue>> x_map)
        : value(std::move(x_map)) {}

    JsonType ObjectField::getType() const {
        return JsonType::j_object;
    }

    std::any ObjectField::toBoxedValue() const {
        throw std::runtime_error {"Not implemented"};
    }

    bool ObjectField::isEmpty() const {
        return value.empty();
    }

    size_t ObjectField::getPropertyCount() const {
        return value.size();
    }

    bool ObjectField::hasProperty(const std::string& key) const {
        return value.find(key) != value.end();
    }

    const std::shared_ptr<IJsonValue>& ObjectField::getValuePtr(const std::string& key) const {
        return value.at(key);
    }

    /* AnyField */
    AnyField::AnyField(NullField x_null)
        : value(std::move(x_null)) {}

    AnyField::AnyField(BooleanField x_boolean)
        : value(std::move(x_boolean)) {}

    AnyField::AnyField(NumberField x_number)
        : value(std::move(x_number)) {}

    AnyField::AnyField(StringField x_string)
        : value(std::move(x_string)) {}

    AnyField::AnyField(ArrayField x_array)
        : value(std::move(x_array)) {}

    AnyField::AnyField(ObjectField x_object)
        : value(std::move(x_object)) {}

    JsonType AnyField::getType() const
    {
        return JsonType::j_any;
    }

    std::any AnyField::toBoxedValue() const
    {
        return std::any {*this};
    }

    /* ToyJsonDocument */

    ToyJsonDocument::ToyJsonDocument(const std::string& name_str, std::shared_ptr<IJsonValue> x_root_ptr)
        : title {name_str}, root_ptr(std::move(x_root_ptr)) {}

    std::string_view ToyJsonDocument::getTitle() const {
        return title;
    }

    const std::shared_ptr<IJsonValue>& ToyJsonDocument::getRoot() const {
        return root_ptr;
    }
}