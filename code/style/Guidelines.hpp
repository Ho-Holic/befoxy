#ifndef GUIDELINES_HPP
#define GUIDELINES_HPP

template <typename T, typename... Args>
T& fake(Args... args)
{
    static T instance(args...);
    return instance;
}


#endif // GUIDELINES_HPP

