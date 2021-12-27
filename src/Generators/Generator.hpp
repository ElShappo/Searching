#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <time.h>
#include <chrono>
#include <thread>

#include "MySet.hpp"
#include "SparseVector.hpp"
#include "GeneratorException.hpp"
#include "Dictionary.hpp"
#include "SparseVector.hpp"

std::string randomString(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

template <typename T>
class MyGenerator {
public:
    T operator()(const T lower_bound, const T upper_bound, std::mt19937 & gen)
    {
        if (lower_bound >= upper_bound)
            throw GeneratorException<T>("lower_bound should be less than upper_bound");

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
        else
            throw GeneratorException<T>("unsupported type");
    }
};


/*
template<Sequence<char>, typename T>
Dictionary<Sequence<char>, T> dictionaryGenerator(const Sequence<char> minKey, const Sequence<char> maxKey, const T minValue, const T maxValue, const size_t amountOfElements)
{
    MySet<Sequence<char>> keys(mySetGenerator(minKey, maxKey, amountOfElements));
    Sequence<T> values(sequenceGenerator(minValue, maxValue, amountOfElements));

    Dictionary<Sequence<char>, T> generated(keys, values);
    return generated;
}
*/

/*
template <typename T>
class SequenceGenerator
{
public:
    Sequence<T> & operator()(T low, T high, int amount)
    {
        if (amount <= 0)
            throw GeneratorException<T>("SequenceGenerator error: amount should be > 0");

        MyGenerator<T> gen;

        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 generator(rd()); // Standard mersenne_twister_engine seeded with rd()
        Sequence<T>* random = new Sequence<T>();

         for (int i=0; i<amount; ++i)
            random->push_back(gen(low, high, generator));

        return *random;
    }
};
*/

/*
template <typename T1, typename T2>
class DictionaryGenerator
{
public:
    Dictionary<T1,T2> && operator()(T1 low1, T1 high1, T2 low2, T2 high2, int amount)
    //
    {
        if (amount <= 0)
            throw GeneratorException<T1>("SequenceGenerator: amount should be > 0");

        MyGenerator<T1> gen1;
        Generator<T2> gen2;

        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 generator(rd()); // Standard mersenne_twister_engine seeded with rd()
        MySet<T1>* randomSet = new MySet<T1>();

         for (int i=0; i<amount; ++i)
            randomSet->add(gen1(low1, high1, generator));

        Sequence<T2>* randomSequence = new Sequence<T2>();

        for (int i=0; i<amount; ++i)
        {
            randomSequence->push_back(gen2(low2, high2, generator));
            cout << "Printing some items" << endl;
            cout << (*randomSequence)[i] << endl;
            cout << "End of printing" << endl;
        }

        Dictionary<T1, T2> dict(*randomSet, *randomSequence);

        return move(dict);
    }
};
*/


#endif // RANDOM_HPP

