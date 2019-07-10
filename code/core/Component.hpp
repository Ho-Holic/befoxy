#ifndef BEFOXY_CORE_COMPONENT_HPP
#define BEFOXY_CORE_COMPONENT_HPP

#include <vector>
#include <cstdint>
#include <chrono>

using TimePoint = std::chrono::system_clock::time_point;
using Clock = std::chrono::system_clock;

struct SprintTime
{
    int64_t hour = 0;
    int64_t min = 0;
    int64_t sec = 0;
};

enum class SprintType
{
    Unknown,
    NoTracking,
    WorkdayStart,
    WorkdayEnd,
    Work,
    Rest,
};

enum class SprintState
{
    Unknown,
    Normal,
    Paused,
    Overtime,
};

struct Sprint
{
    SprintType type = SprintType::Unknown;
    SprintState state = SprintState::Normal;
    SprintTime time;
    TimePoint startTime;
    TimePoint finishTime;
    TimePoint actualFinishTime;
};

struct Workday
{
    TimePoint day;
    std::vector<Sprint> sprints;    
};

struct WorkProgress
{
    int32_t current = 0;
    int32_t maximum = 0;
};

//
// TODO: replace 'sprintSchemeMap' return type with SprintScheme
// Also do this for serialization routine
//
struct SprintScheme
{
    SprintType type = SprintType::Unknown;
    SprintState state = SprintState::Normal;
    SprintTime time;
};

struct WorkdayScheme
{
    std::vector<Sprint> sprints;
};


#endif // BEFOXY_CORE_COMPONENT_HPP

