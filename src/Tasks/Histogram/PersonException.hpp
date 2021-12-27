#ifndef PERSON_EXCEPTION_HPP
#define PERSON_EXCEPTION_HPP

class PersonException : public std::invalid_argument
{
public:
    PersonException(const char* ex)
    : invalid_argument(ex)
    {

    }
private:
};

#endif // PERSON_EXCEPTION_HPP
