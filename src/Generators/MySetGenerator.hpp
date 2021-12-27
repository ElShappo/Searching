#ifndef MYSET_GENERATOR_HPP
#define MYSET_GENERATOR_HPP

#include "Generator.hpp"
#include "MySet.hpp"

template <typename T>
MySet<T> mySetGenerator(const T min, const T max, const int amount)
{
    if (amount <= 0)
        throw GeneratorException<T>("SequenceGenerator: amount should be > 0");

    return MySet<T>(sequenceGenerator(min, max, amount));
}

#endif // MYSET_GENERATOR_HPP
