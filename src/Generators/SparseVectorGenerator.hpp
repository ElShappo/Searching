#ifndef SPARSE_VECTOR_GENERATOR_HPP
#define SPARSE_VECTOR_GENERATOR_HPP

#include "Sequence.hpp"
#include "SequenceGenerator.hpp"
#include "MySetGenerator.hpp"

template <typename T>
SparseVector<T> && sparseVectorGenerator(int amount, int sparsity, T lower, T higher)
// generate keys and values to get sparse vector
// amount is the number of generated values (including possible zeros)
// T lower is lower_bound, T higher is upper_bound
{
    if (sparsity <= 70)
        throw SparseVectorException<T>("insufficient sparsity (should be more than 70%)");

    if (lower >= higher)
        throw SparseVectorException<T>("lower_border should be less and higher");

    Sequence<T> generatedValues(sequenceGenerator<T>(lower, higher, amount)); // generate values (without zeroes)

    int zeroesAmount = ceil(sparsity*amount/100);
    MySet<int> generatedZeroIndexes = mySetGenerator<int>(0, amount-1, zeroesAmount); // generate indexes corresponding to zeroes (the max index equals amount-1)

    MySet<int> nonZeroIndexes; // generate indexes corresponding to zeroes (the max index equals amount-1)
    Sequence<T> nonZeroValues;

    for (int i=0; i<generatedValues.size(); ++i)
    {
        if (generatedZeroIndexes.find(i)) // if i index is the one that stands for the one having zero
            generatedValues[i] = 0; // then nullify element of this index
        else
        {
            nonZeroIndexes.add(i);
            nonZeroValues.push_back(generatedValues[i]);
        }
    }
    Dictionary<int, T>* dict = new Dictionary<int, T>(nonZeroIndexes, nonZeroValues);

    dict->printKeys();
    dict->printValues();
    cout << dict->getMaxKey() << endl;

    SparseVector<T> generatedSparseVector = SparseVector<T>(*dict);
    return move(generatedSparseVector);
}

#endif // SPARSE_VECTOR_GENERATOR_HPP
