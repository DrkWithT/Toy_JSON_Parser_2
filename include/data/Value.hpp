#ifndef VALUE_HPP
#define VALUE_HPP

#include <any>
#include <map>
#include <variant>
#include <vector>
#include <string_view>
#include <string>
#include <type_traits>
#include <memory>
#include "data/IValue.hpp"

namespace toyjson::data {
    class NullField : public IJsonValue {
        public:
            NullField() = default;

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

        private:
            // no fields needed
    };

    class BooleanField : public IJsonValue {
        public:
            BooleanField() = delete;
            BooleanField(bool flag);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

        private:
            bool value;
    };

    class NumberField : public IJsonValue {
        public:
            NumberField() = delete;
            NumberField(double num);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

        private:
            double value;
    };

    class StringField : public IJsonValue {
        public:
            StringField() = delete;
            StringField(std::string x_str);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;
        private:
            std::string value;
    };

    class ArrayField : public IJsonValue {
        public:
            ArrayField();
            ArrayField(std::vector<std::shared_ptr<IJsonValue>> x_items);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] size_t getLength() const;

            [[nodiscard]] const std::shared_ptr<IJsonValue>& getItemPtr(size_t pos) const;

        private:
            std::vector<std::shared_ptr<IJsonValue>> value;
    };

    class ObjectField : public IJsonValue {
        public:
            ObjectField();
            ObjectField(std::map<std::string, std::shared_ptr<IJsonValue>> x_map);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] size_t getPropertyCount() const;

            [[nodiscard]] bool hasProperty(const std::string& key) const;
            [[nodiscard]] const std::shared_ptr<IJsonValue>& getValuePtr(const std::string& key) const;

        private:
            std::map<std::string, std::shared_ptr<IJsonValue>> value;
    };

    /* Type Utility */

    // Base case: all unsupported native types default to 0 as null.
    template <typename T>
    constexpr int toAnyVariantPos() {
        if constexpr (std::is_same_v<T, BooleanField>)
            return 1;
        else if constexpr (std::is_same_v<T, NumberField>)
            return 2;
        else if constexpr (std::is_same_v<T, StringField>)
            return 3;
        else if constexpr (std::is_same_v<T, ArrayField>)
            return 4;
        else if constexpr (std::is_same_v<T, ObjectField>)
            return 5;

        return 0;
    }

    /* AnyField (wraps any JSON type)*/

    class AnyField : public IJsonValue {
        public:
            AnyField() = delete;
            AnyField(NullField x_null);
            AnyField(BooleanField x_boolean);
            AnyField(NumberField x_number);
            AnyField(StringField x_string);
            AnyField(ArrayField x_array);
            AnyField(ObjectField x_object);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

            template <typename Ntv>
            constexpr const Ntv& unpackValue()
            {
                constexpr int variant_pos = toAnyVariantPos<Ntv>();

                return std::get<variant_pos>(value);
            }
        private:
            std::variant<NullField, BooleanField, NumberField, StringField, ArrayField, ObjectField> value;
    };

    class ToyJsonDocument {
        public:
            ToyJsonDocument();
            ToyJsonDocument(const std::string& name_str, std::shared_ptr<IJsonValue> x_root_ptr);

            [[nodiscard]] std::string_view getTitle() const;
            [[nodiscard]] const std::shared_ptr<IJsonValue>& getRoot() const;

        private:
            std::string title;

            /// @warning Only store AnyField objects or else there's no guarantee of the IJsonValue having a desired value within.
            std::shared_ptr<IJsonValue> root_ptr;
    };
}

#endif