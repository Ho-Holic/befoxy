#include "Engine.hpp"
#include "style/Guidelines.hpp"

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

void Engine::tap()
{
    // tap to affect sprint: start/pause/continue
}

void Engine::skip()
{
    // tap to skip this sprint
    // you need to track skips in analytics too
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
    return fake<Workday>();
}

