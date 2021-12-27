#ifndef PERSON_HPP
#define PERSON_HPP

#include "PersonException.hpp"

class Person
{
public:
    Person(int age, int height, int weight, string name)
    {
        if (age <= 0 || height <= 0 || weight <= 0)
            throw PersonException("invalid data input");

        this->setAge(age)
             .setHeight(height)
             .setWeight(weight)
             .setName(name)
        ;
    }

    // GETTERS

    int getAge() const {return age_;}
    int getHeight() const {return height_;}
    int getWeight() const {return weight_;}

    string getName() const {return name_;}

    // SETTERS

    Person & setAge(int age)
    {
        if (age <= 0)
            throw PersonException("invalid age input");
        age_ = age;
        return *this;
    }
    Person & setHeight(int height)
    {
        if (height <= 0)
            throw PersonException("invalid height input");
        height_ = height;
        return *this;
    }
    Person & setWeight(int weight)
    {
        if (weight <= 0)
            throw PersonException("invalid weight input");
        weight_ = weight;
        return *this;
    }
    Person & setName(string name) {name_ = name; return *this;}

    void print()
    {
        std::cout << "Age: " << age_ << endl;
        std::cout << "Height: " << height_ << endl;
        std::cout << "Weight: " << weight_ << endl;
        std::cout << "Name: " << name_ << endl;
    }

private:
    int age_;
    int height_;
    int weight_;
    string name_;
};

#endif // PERSON_HPP
