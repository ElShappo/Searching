#ifndef PERSON_GENERATOR_HPP
#define PERSON_GENERATOR_HPP

#include "Person.hpp"

#include "Generator.hpp"
#include "SequenceGenerator.hpp"


std::vector<Person> personGenerator(size_t number, // number of people
                                    std::pair<int, int> ageRange,
                                    std::pair<int, int> heightRange,
                                    std::pair<int, int> weightRange,
                                    size_t shortestName, size_t longestName)
{
    if (ageRange.first >= ageRange.second || heightRange.first >= heightRange.second || weightRange.first >= weightRange.second || shortestName >= longestName)
        throw GeneratorException<Person>("invalid borders");

    Sequence<int> ages = sequenceGenerator<int>(ageRange.first, ageRange.second, number);
    Sequence<int> heights = sequenceGenerator<int>(heightRange.first, heightRange.second, number);
    Sequence<int> weights = sequenceGenerator<int>(weightRange.first, weightRange.second, number);

    Sequence<int> randomNameLengths = sequenceGenerator<int>(shortestName, longestName, number);

    vector<Person> people;

    for (int i=0; i<number; ++i)
    {
        std::string name = randomString(randomNameLengths[i]);
        Person buff(ages[i], heights[i], weights[i], name);
        people.push_back(buff);
    }

    return people;
}

#endif // PERSON_GENERATOR_HPP
