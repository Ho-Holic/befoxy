#ifndef BEFOXY_CORE_COMPONENT
#define BEFOXY_CORE_COMPONENT

#include <vector>

struct SprintTime
{
    int hour = 0;
    int min = 0;
    int sec = 0;
};

enum class SprintType
{
    Unknown,
    WorkdayStart,
    NoTracking,
    Work,
    Rest,
    WorkPaused,
    RestPaused,
    WorkOvertime,
    RestOvertime,
    WorkdayEnd,
};

struct Sprint
{
    SprintType type = SprintType::Unknown;
    SprintTime time;
};

struct Workday
{
    std::vector<Sprint> sprints;
};

struct History
{
    std::vector<Workday> workdays;
};

struct ColorScheme
{
    // clock background
    // clock work
    // clock rest
    // clock timer work
    // clock timer rest
    // workday format
    // workday background
};

#endif // BEFOXY_CORE_COMPONENT

