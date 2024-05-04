#ifndef VALUE_HPP
#define VALUE_HPP

#include <any>
#include <map>
#include <vector>
#include <string_view>
#include <string>
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
            ArrayField(std::vector<std::unique_ptr<IJsonValue>> x_items);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] size_t getLength() const;

            [[nodiscard]] const std::unique_ptr<IJsonValue>& getItemPtr(size_t pos) const;

        private:
            std::vector<std::unique_ptr<IJsonValue>> value;
    };

    class ObjectField : public IJsonValue {
        public:
            ObjectField();
            ObjectField(std::map<std::string, std::unique_ptr<IJsonValue>> x_map);

            [[nodiscard]] JsonType getType() const override;
            [[nodiscard]] std::any toBoxedValue() const override;

            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] size_t getPropertyCount() const;

            [[nodiscard]] bool hasProperty(const std::string& key) const;
            [[nodiscard]] const std::unique_ptr<IJsonValue>& getValuePtr(const std::string& key) const;

        private:
            std::map<std::string, std::unique_ptr<IJsonValue>> value;
    };

    class ToyJsonDocument {
        public:
            ToyJsonDocument();
            ToyJsonDocument(const std::string& name_str, std::unique_ptr<IJsonValue> x_root_ptr);

            [[nodiscard]] std::string_view getTitle() const;
            [[nodiscard]] const std::unique_ptr<IJsonValue>& getRoot() const;

        private:
            std::string title;
            std::unique_ptr<IJsonValue> root_ptr;
    };
}

#endif