#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "DictionaryException.hpp"
#include "Sequence.hpp"
#include "MySet.hpp"

template <typename T1, typename T2>
class Dictionary
{
public:
    Dictionary() {}

    Dictionary & operator= (const Dictionary<T1, T2> & dictionary)
    {
        keys_ = dictionary.getKeys();
        values_ = dictionary.getValues();
        return *this;
    }

    explicit Dictionary(const Dictionary<T1, T2> & dictionary)
    {
        MySet<T1> mySet(std::move(dictionary.getKeys()));

        keys_ = mySet;
        values_ = dictionary.getValues();
    }

    Dictionary(Dictionary<T1, T2> && dictionary)
    {
        MySet<T1> mySet(std::move(dictionary.getKeys()));

        keys_ = mySet;
        values_ = dictionary.getValues();
    }

    explicit Dictionary(const MySet<T1> & keys, const Sequence<T2> & values)
    {
        if (keys.size() != values.size())
            throw DictionaryException("Dictionary: keys and values are different in amounts");

        keys_ = keys;
        values_ = values;
    }


    T1 getMaxKey() const
    // get key with the max value (arithmetic types)
    {
        T1 max = 0;

        for (int i=0; i<keys_.size(); ++i)
        {
            if constexpr (std::is_arithmetic_v<T1>)
            {
                if (isKey(i))
                {
                    if (max < keys_[i])
                        max = keys_[i];
                }
            }
            else
                throw DictionaryException("unsupported datatype for Dictionary keys has been used");
        }
        return max;
    }

    int size() const
    {
        return keys_.size();
    }
    int capacity() const
    {
        return keys_->capacity();
    }
    bool isKey(T1 key) const
    {
        for (int i=0; i<keys_.size(); ++i)
        {
            if (key == keys_[i])
                return true;
        }
        return false;
    }
    void add(T1 & key, T2 & value)
    {
        if (!isKey(key)) // if there is no such key
        {
            keys_.add(key); // add the key
            values_.push_back(value); // add the corresponding value
        }
        else // if such key already exists
        {
            int index = findKey(key); // get index of the given key
            values_[index] = value; // change the value corresponding to the passed key
        }
    }
    T2 get(const T1 key) const
    {
        //cout << "Current key: " << key << endl;
        if (!isKey(key))
            throw DictionaryException("no such key");

        int index = findKey(key); // find the index corresponding to the given key
        return values_[index];
    }

    T2 & operator[] (const T1 key) const
    // equivalent to get
    {
        int index = findKey(key); // find the index corresponding to the given key
        return values_[index];

        //return get(key);
    }

    void remove(T1 key)
    {
        if (!isKey(key))
            throw DictionaryException("no such key");

        MySet<T1> new_keys;
        Sequence<T2> new_values;

        for (int i=0; i<keys_.size(); ++i)
        {
            if (key == keys_[i]) // if found the key which we need to remove we just skip it
                {}
            else
            {
                new_keys.add(keys_[i]); // otherwise we add the key and corresponding value to the new list
                new_values.push_back(values_[i]);
            }
        }
        keys_ = new_keys;
        values_ = new_values;
    }

    void set(MySet<T1> & keys, Sequence<T2> & values)
    {
        if (keys.size() != values.size())
            throw DictionaryException("amount of passed keys doesn't equal to the amount of passed values");
        keys_ = keys;
        values_ = values;
    }

    MySet<T1> getKeys()
    {
        return move(keys_);
    }

    Sequence<T2> getValues() const
    {
        return values_;
    }

    size_t findKey(const T1 & key) const
    // return the index corresponding to the given key
    {
        for (size_t i=0; i<size_t(keys_.size()); ++i)
        {
            if (key == keys_.toSequence()[i])
                return i;
        }
        throw DictionaryException("no such key");
    }

    void printKeys()
    {
        cout << "Printing keys: " << endl;
        keys_.print();
    }

    void printValues()
    {
        cout << "Printing values: " << endl;
        values_.print();
    }


private:
    MySet<T1> keys_; // array of keys
    Sequence<T2> values_;  // array of values
};

#endif // DICTIONARY_HPP
