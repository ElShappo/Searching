#ifndef SORTED_SEQUENCE_GENERATOR_HPP
#define SORTED_SEQUENCE_GENERATOR_HPP

template <typename T>
Sequence<T> sortedSequenceGenerator(const T min, const T max, const size_t amount)
{
    Sequence<T> seq(sequenceGenerator(min, max, amount));
    QuickSort<T> qSort;

    return Sequence<T>::to_array(qSort.sort(seq.to_vector(), 0, seq.size()));
}

#endif // SORTED_SEQUENCE_GENERATOR_HPP
