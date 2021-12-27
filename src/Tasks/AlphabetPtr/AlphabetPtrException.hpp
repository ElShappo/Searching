#ifndef ALPHABET_PTR_EXCEPTION_HPP
#define ALPHABET_PTR_EXCEPTION_HPP

class AlphabetPtrException : public std::invalid_argument
{
public:
    AlphabetPtrException(const std::string& msg)
    : invalid_argument(msg)
    {

    }

};

#endif // ALPHABET_PTR_EXCEPTION_HPP
