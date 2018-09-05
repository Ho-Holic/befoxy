#include "Engine.hpp"

Engine::Engine()
{

}

Sprint Engine::sprint()
{
    Sprint sprint;
    sprint.type = SprintType::Work;
    sprint.time = { 0, 34, 59 };
    return sprint;
}

void Engine::update()
{
    // 1. update engine clock
    // 2. recalculate sprint
}

void Engine::setWorkday(const Workday& workday)
{
    // replace workday
}

const Workday& Engine::workday() const
{
    static Workday w;
    return w;
}

