#ifndef COMPONENT
#define COMPONENT

#include <vector>

struct SprintTime
{
    int hour;
    int min;
    int sec;
};

enum class SprintType
{
    Unknown,
    FuckUp,
    Work,
    Rest,
    WorkPaused,
    RestPaused,
};

struct Sprint
{
    SprintTime time;
    SprintType type;
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

#endif // COMPONENT

