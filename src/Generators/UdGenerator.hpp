#ifndef UD_GENERATOR_HPP
#define UD_GENERATOR_HPP

#include "RandomGenerator.hpp"
#include <type_traits>
#include <random>
#include <chrono>

/*

template <typename T>
class UdGenerator : public RandomGenerator<T, std::mt19937> {
public:
    T operator()(T lower_bound, T upper_bound, std::mt19937 & gen) override
    {
        if constexpr(std::is_integral<T>::value)  // without constexpr static assertion fails
        {
            std::uniform_int_distribution<int> distrib(lower_bound, upper_bound);
            return distrib(gen);
        }
        else if (std::is_floating_point<T>::value)
        {
            std::uniform_real_distribution<T> distrib(lower_bound, upper_bound);
            return distrib(gen);
        }
    }
};
*/

#endif // UD_GENERATOR_HPP

