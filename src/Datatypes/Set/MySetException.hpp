#ifndef MYSET_EXCEPTION_HPP
#define MYSET_EXCEPTION_HPP

template <class T>
class MySetException : public std::invalid_argument
{
public:
    MySetException(const char* ex)
    : invalid_argument(ex)
    {

    }
};

#endif // MYSET_EXCEPTION_HPP
