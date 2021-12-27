#ifndef MYSET_HPP
#define MYSET_HPP

#include "MySetException.hpp"
#include "Sequence.hpp"

template <typename T>
class MySet
{
private:
    Sequence<T> seq_;

public:
    explicit MySet<T>()
    {
        cout << "MySet<T>() has been called!" << endl;
    }

    explicit MySet<T>(T* arr, int arrSize)
    {
        cout << "MySet<T>(T* arr, int arrSize) has been called!" << endl;
        Sequence<T> seq(arr, arrSize);
        seq_ = seq; // basic assignment operator is called here
    }

    explicit MySet<T>(const Sequence<T> & rawSeq)
    {
        cout << "MySet<T>(const Sequence<T> & rawSeq) has been called!" << endl;
        Sequence<T> seq = rawSeq;

        for (int i=0; i<seq.size(); ++i)
            seq.removeRepetitions(seq[i]); // leave only one occurrence of each element which is met

        seq_ = seq;
    }

    MySet<T>(MySet<T> &&other) noexcept
    {
        seq_ = move(other.toSequence());
    }

    T & operator[] (int index)
    {
        if (index >= size() || index < 0)
            throw MySetException<T>("index out of range");
        return seq_[index];
    }

    /*
    explicit MySet<T>(const MySet<T> & mySet)
    : //seq_(move(mySet.get()))
    {
        seq_ = MySet.get();
        cout << "MySet<T>(const MySet<T> & mySet) has been called!" << endl;
    }
    */

    /*
    MySet<T>& operator= (MySet<T>&& mySet)
    {
        seq_ = mySet.get();
        return *this;
    }
    */

    MySet<T> & operator= (const MySet<T> & mySet)
    {
        cout << "MySet<T> & operator= (const MySet<T> & mySet) has been called!" << endl;
        seq_ = mySet.get();
        return *this;
    }

    MySet<T> & operator= (const Sequence<T> & rawSeq)
    {
        cout << "MySet<T> & operator= (const Sequence<T> & rawSeq) has been called!" << endl;
        Sequence<T> seq = rawSeq;

        for (int i=0; i<seq.size(); ++i)
            seq.removeRepetitions(seq[i]); // leave only one occurrence of each element which is met
        seq_ = seq;
        return *this;
    }

    int size() const
    {
        return seq_.size();
    }

    bool find(const T & element) const
    {
        for (int i=0; i<seq_.size(); ++i)
        {
            if (seq_[i] == element)
                return true;
        }
        return false;
    }

    void add(const T & element)
    {
        if (!find(element)) // if no such element exists in the MySet, we should add it
            seq_.push_back(element);
    }

    void remove(const T & element)
    {
        size_t oldSize = this->size();
        seq_.removeAllOccurrences(element); // remove all occurrences of the element
        size_t newSize = this->size();

        if (oldSize == newSize)
            throw MySetException<T>("deleting unexisting element");
    }

    Sequence<T> get() const
    {
        return seq_;
    }

    void print()
    {
        seq_.print();
    }

    Sequence<T> & toSequence() const
    {
        Sequence<T>* seq = new Sequence<T>(seq_);
        return *seq;
    }


};

#endif // MYSET_HPP
