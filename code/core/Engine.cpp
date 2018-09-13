#include "Engine.hpp"
#include "style/Guidelines.hpp"

namespace {
    Workday fakeWorkday()
    {
        std::vector<Sprint> w = {
            { SprintType::WorkdayStart, {0, 0, 0} },

            { SprintType::Work, {0, 35, 0} },
            { SprintType::Rest, {0, 15, 0} },
            { SprintType::Work, {0, 35, 0} },
            { SprintType::Rest, {0, 15, 0} },

            { SprintType::WorkdayEnd, {0, 0, 0} },
        };
        return Workday { w };
    }
}

Engine::Engine()
:   m_workday(fakeWorkday())
{
    //
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
    m_workday = workday;
}

const Workday& Engine::workday() const
{    
    return m_workday;
}

