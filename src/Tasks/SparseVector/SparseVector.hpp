#ifndef RAREVECTOR_HPP
#define RAREVECTOR_HPP

#include "Sequence.hpp"
#include "Dictionary.hpp"
#include "MySet.hpp"

#include <ctime>
#include "epsilon.h"

template <class T>
class SparseVectorException : public std::invalid_argument
{
public:
    SparseVectorException(const char* ex)
    : invalid_argument(ex)
    {

    }
};

template <typename T>
class SparseVector
{
private:
    Dictionary<int, T> dict_;

public:
    Dictionary<int, T> getDictionary()
    {
        return dict_;
    }

    /*
    explicit SparseVector(SparseVector & sparseVector)
    {
        dict_ = sparseVector.getDictionary();
    }
    */
    /*

    explicit SparseVector(SparseVector && sparseVector)
        //: dict_(SparseVector.getDictionary())
    {
        dict_ = sparseVector.getDictionary();
    }*/

    explicit SparseVector(Dictionary<int, T> & dict)
    {
        set(dict);
    }

    SparseVector & operator= (SparseVector<T> & sparseVector)
    {
        dict_ = sparseVector.getDictionary();
    }

    void set(Sequence<int> & indexes,  Sequence<T> & values)
    {
        if (indexes.size() != values.size())
            throw DictionaryException("amount of passed indexes doesn't equal to the amount of passed values");

        for (int i=0; i<values.size(); ++i)
        {
            if constexpr (std::is_integral_v<T>)
            {
                if (values[i] != 0)
                    dict_.add(indexes[i], values[i]);
            }
            else if (std::is_floating_point_v<T>)
            {
                if (!AreSame(values[i], 0))
                    dict_.add(indexes[i], values[i]);
            }
            else
                throw SparseVectorException("unsupported datatype for values in SparseVector");
        }
        dict_.set(indexes, values);
    }

    void set(Dictionary<int, T> & dict)
    {
        cout << dict.getMaxKey() << endl;
        for (int i=0; i<=dict.getMaxKey(); ++i)
        {
            if constexpr (std::is_integral_v<T>)
            {
                if (dict.isKey(i))
                {
                    cout << "isKey i: " << i << endl;
                    if (dict[i] != 0) // check value != 0
                        dict_.add(i, dict[i]);
                }
            }
            else if (std::is_floating_point_v<T>)
            {
                if (dict.isKey(i))
                {
                    cout << "isKey i: " << i << endl;
                    if (!areSame(dict[i], 0))
                        dict_.add(i, dict[i]);
                }
            }

            else
                throw SparseVectorException<T>("unsupported datatype for values in SparseVector");
        }
        dict_.printKeys();
        dict_.printValues();
        cout << "Max: " << dict_.getMaxKey() << endl;
        //dict_ = dict;
    }

    T get(int index)
    // index acts like a key
    {
        if (index >= dict_.getMaxKey())
            throw SparseVectorException<T>("index out of range");
        if (!dict_.isKey(index))
            return 0; // if there is no such key, then this element of the vector is 0
        else
            return dict_[index];
    }

    void print()
    {
        cout << "Sparse vector print" << endl << endl;
        cout << dict_.getMaxKey() << endl;

        for (int i=0; i<=dict_.getMaxKey(); ++i)
        {
            if (dict_.isKey(i))
                cout << i << ": " << dict_[i] << endl; // if such key exists, return the corresponding value
            else
                cout << i << ": " << 0 << endl; // otherwise the element which isn't saved in memory is zero
        }
    }
};


/*
template <typename T>
SparseVector<T> gen(int totalSize, int percentage)
// percentage describes the amount of zeroes (80% zeros etc)
// totalSize includes the amount of zeros too
{
    int arr[] = {1, 2, 3, 4};
    int freq[] = {10, 5, 20, 100};
    int i, n = sizeof(arr) / sizeof(arr[0]);

    // Use a different seed value for every run.
    srand(time(NULL));

    // Let us generate 10 random numbers according to
    // given distribution
    for (i = 0; i < 5; i++)
    cout << myRand(arr, freq, n) << endl;
}
*/


#endif // RAREVECTOR_HPP
