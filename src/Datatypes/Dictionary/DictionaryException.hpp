#ifndef DICTIONARY_EXCEPTION_HPP
#define DICTIONARY_EXCEPTION_HPP

class DictionaryException : public std::invalid_argument
{
public:
    DictionaryException(const char* ex)
    : invalid_argument(ex)
    {

    }
};


#endif // DICTIONARY_EXCEPTION_HPP
