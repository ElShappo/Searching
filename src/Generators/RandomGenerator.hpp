#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

template <typename T, typename ... Ts>
class RandomGenerator
{
public:
   virtual T operator()(T lower_bound, T upper_bound, Ts & ...) = 0;
};

#endif // RANDOM_GENERATOR_HPP
