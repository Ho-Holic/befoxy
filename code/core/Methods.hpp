#ifndef BEFOXY_CORE_METHODS_HPP
#define BEFOXY_CORE_METHODS_HPP

#include <chrono>
#include "core/Component.hpp"

inline TimePoint operator+(const TimePoint& t0, const SprintTime& t1)
{
    using namespace std::chrono;

    return t0 + hours(t1.hour) + minutes(t1.min) + seconds(t1.sec);
}

inline bool isImportantSprint(const Sprint& sprint)
{
    return sprint.type == SprintType::Work || sprint.type == SprintType::Rest;
}

#endif // BEFOXY_CORE_METHODS_HPP
