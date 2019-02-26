#ifndef BEFOXY_CORE_COMPONENT
#define BEFOXY_CORE_COMPONENT

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
    TimePoint tapTime;
};

struct Workday
{
    TimePoint day;
    std::vector<Sprint> sprints;
};

struct Config
{
    float sprintSwitchThresholdSec = 3.0;
};

#endif // BEFOXY_CORE_COMPONENT

