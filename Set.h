//
// Created by ljh on 2024/6/11.
//

#ifndef MATH_SET_H
#define MATH_SET_H

#include "Number.h"
#include <variant>
#include <vector>
#include <ranges>
#include <algorithm>
#include <set>
#include <memory>

namespace Math {
    template<typename T, typename U>
    struct is_same {
        static constexpr bool value = std::is_same<T, U>::value;

         bool operator()(T x) const {
            return value;
        }
    };

    template<typename T>
    using is_Real = is_same<T, REAL>;
    template<typename T>
    using is_Integer = is_same<T, INTEGER>;
    template<typename T>
    using is_Natural = is_same<T, NATURAL>;

    template<typename T>
    class Set_condition_base {
    public:
        using value_type = T;

        virtual ~Set_condition_base() = default;

        virtual bool contains(T x) const = 0;
    };

    template<typename T, typename Condition>
    class Set_condition : public Set_condition_base<T> {
        Condition _condition;
    public:
        using value_type = T;

         Set_condition(Condition c=Condition()) : _condition(std::move(c)) {}

         bool contains(T x) const override {
            return _condition(x);
        }
    };

    using Real_Set = Set_condition<REAL, is_Real<REAL>>;
    using Integer_Set = Set_condition<INTEGER, is_Integer<INTEGER>>;
    using Natural_Set = Set_condition<NATURAL, is_Natural<NATURAL>>;


    template<typename T>
    class Set_enum {
        std::set<T> _elements;
    public:
        using value_type = T;

        template<std::ranges::input_range Range>
        Set_enum(Range range) : _elements(range.begin(), range.end()) {}

        bool contains(T x) {
            //return std::ranges::any_of(_elements, [x](T y) { return x == y; });
            return _elements.contains(x);
        }

        bool insert(T x) {
            return _elements.insert(std::move(x));
        }

    };

    class Set_empty {
    public:
        using value_type = REAL;

        bool contains(REAL x) {
            return false;
        }
    };

    template<typename T>
    class Set {
        std::variant<Set_enum<T>, Set_empty, std::unique_ptr<Set_condition_base<T>>> _set;
    public:
        using value_type = T;

        Set() : _set(Set_empty()) {}

        Set(Set_enum<T> set) : _set(set) {}

        template<typename Condition>
        Set(Set_condition<T, Condition> set):_set(std::make_unique(std::move(set))) {}

        Set(Set_empty set) : _set(set) {}

        bool contains(T x) {
            return std::visit([&](auto &&set) -> bool {
                using Type = std::decay_t<decltype(set)>;
                if constexpr (std::is_same_v<Type, Set_enum < T>>) {
                return set.contains(x);
            } else if constexpr (std::is_same_v<Type, Set_empty>) {
                return set.contains(x);
            } else if constexpr (std::is_same_v<Type, std::unique_ptr<Set_condition_base < T>> >) {
                return (*set).contains(x);
            }
                return false;
            }, _set);
        }
    };

} // Math

#endif //MATH_SET_H
