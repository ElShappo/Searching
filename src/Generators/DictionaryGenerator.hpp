#ifndef DICTIONARY_GENERATOR_HPP
#define DICTIONARY_GENERATOR_HPP

#include "Dictionary.hpp"

template <typename T1, typename T2>
Dictionary<T1, T2> dictionaryGenerator(const T1 minKey, const T1 maxKey, const T2 minValue, const T2 maxValue, const size_t amountOfElements)
{
    MySet<T1> keys(mySetGenerator(minKey, maxKey, amountOfElements));
    Sequence<T2> values(sequenceGenerator(minValue, maxValue, amountOfElements));

    Dictionary<T1, T2> generated(keys, values);
    return generated;
}

#endif // DICTIONARY_GENERATOR_HPP
