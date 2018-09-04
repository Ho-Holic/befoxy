#ifndef COMPONENT
#define COMPONENT

struct Workday
{
    std::vector<Sprint> sprints;
};

struct Sprint
{
    SprintTime time;
    SprintType type;
};

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

