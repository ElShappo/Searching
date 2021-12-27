#ifndef HISTOGRAM_EXCEPTION_HPP
#define HISTOGRAM_EXCEPTION_HPP

class HistogramException : public std::invalid_argument
{
public:
    HistogramException(const char* ex)
    : invalid_argument(ex)
    {

    }
private:
};

#endif // HISTOGRAM_EXCEPTION_HPP
