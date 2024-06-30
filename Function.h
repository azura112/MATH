//
// Created by ljh on 2024/6/10.
//

#ifndef MATH_FUNCTION_H
#define MATH_FUNCTION_H

#include "Number.h"
#include <functional>
#include <cmath>
#include "Set.h"

namespace Math {
    template<typename F, typename domain_set=Real_Set>
    concept Func= requires(F f) {
        { f(domain_set::value_type()) } -> std::same_as<typename domain_set::value_type>;
    };
    enum class FunctionType {
        CONSTANT,
        POWER, EXP, LOG, SIN, COS, TAN, SINH, COSH, TANH,
    };

    template<typename domain_set=Real_Set>
    struct IdentityFunction {
        using value_type = typename domain_set::value_type;
        static constexpr  FunctionType type = FunctionType::CONSTANT;
        value_type operator()(const value_type &x) const {
            return x;
        }

        Set<value_type> range_set() const {
            return domain_set();
        }
    };


    template<typename domain_set=Real_Set, typename U=IdentityFunction<domain_set>>
    class PowerFunction {
    public:
        using value_type = typename domain_set::value_type;
        static constexpr FunctionType type = FunctionType::POWER;

        explicit PowerFunction(const value_type &p, const value_type &c = value_type(), U u = U()) : _p(p), C(c),
                                                                                                     _u(u) {
        }

        value_type operator()(const value_type &x) const {
            return std::pow(_u(x), _p) + C;
        }

        Set<value_type> range_set() const {
            if (_p > 0) {
                return Real_Set();
            }
            return {};
        }


        value_type _p;
        value_type C;
        U _u;
    };

    template<typename domain_set=Real_Set, typename U=IdentityFunction<domain_set>>
    class ExpFunction {
    public:
        using value_type = typename domain_set::value_type;
        static constexpr FunctionType type = FunctionType::EXP;

        explicit ExpFunction(const value_type &a, const value_type &c = value_type(), U u = U()) : _a(a), C(c), _u(u) {
        }

        value_type operator()(const value_type &x) const {
            return std::pow(_a, _u(x)) + C;
        }

        Set<value_type> range_set() const {
            return Real_Set();
        }
        const value_type& get_a() const {
            return _a;
        }
        const value_type& get_c() const {
            return C;
        }
        const U& get_u() const {
            return _u;
        }


        value_type _a;
        value_type C;
        U _u;

    };
    ExpFunction exp(std::numbers::e_v<Real_Set::value_type>);

    template<typename domain_set=Real_Set, typename U=IdentityFunction<domain_set>>
    class LogFunction {
    public:
        using value_type = typename domain_set::value_type;
        static constexpr FunctionType type = FunctionType::LOG;

        explicit LogFunction(const value_type &a, const value_type &c = value_type(), U u = U()) : _a(a), C(c), _u(u) {
        }

        value_type operator()(const value_type &x) const {
            if constexpr (decltype(_u)::type == FunctionType::EXP) {
                return _u.get_u()(x) * std::log(_u.get_a()) + C;
            }
            return (std::log(_u(x)) / std::log(_a)) + C;
        }

        Set<value_type> range_set() const {
            return Real_Set();
        }


        value_type _a;
        value_type C;
        U _u;

    };
    LogFunction ln(std::numbers::e_v<Real_Set::value_type>);

    template<typename domain_set=Real_Set, typename U=IdentityFunction<domain_set>>
    class SinFunction {
    public:
        using value_type = typename domain_set::value_type;
        static constexpr FunctionType type = FunctionType::SIN;

        explicit SinFunction(const value_type &c, U u = U()) : C(c), _u(u) {
        }

        value_type operator()(const value_type &x) const {
            return std::sin(_u(x)) + C;
        }

        Set<value_type> range_set() const {
            return Real_Set();
        }


        value_type C;
        U _u;
    };


    template<Func F>
    class Function : public std::function<F> {
    };


}

#endif //MATH_FUNCTION_H
