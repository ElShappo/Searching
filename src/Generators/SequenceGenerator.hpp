#ifndef SEQUENCE_GENERATOR_HPP
#define SEQUENCE_GENERATOR_HPP

#include "Generator.hpp"
#include "Sequence.hpp"

template <typename T>
Sequence<T> sequenceGenerator(const T min, const T max, const size_t amount)
{
    if (min >= max)
        throw GeneratorException<T>("sequenceGenerator: lower_bound should be less than upper_bound");

    srand ( time(NULL) );
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    MyGenerator<T> gen;
    Sequence<T> generated;
    std::mt19937 generator(rand()); // Standard mersenne_twister_engine seeded with rand()

    for (size_t i=0; i<amount; ++i)
        generated.push_back(gen(min, max, generator));

    return generated;
}

#endif // SEQUENCE_GENERATOR_HPP
