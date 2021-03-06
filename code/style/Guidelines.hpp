#ifndef BEFOXY_STYLE_GUIDELINES_HPP
#define BEFOXY_STYLE_GUIDELINES_HPP

#include <utility>
#include <assert.h>

template <typename T, typename... Args>
T& fake(Args... args)
{    
    static T instance(std::forward(args)...);
    return instance;
}

template <typename T, typename... Args>
T unreachable(Args... args)
{
    assert(false);
    return T(std::forward(args)...);
}

inline void require(bool holds)
{
    assert(holds);
}

inline void unexpected_path()
{
    assert(false);
}



#endif // BEFOXY_STYLE_GUIDELINES_HPP

