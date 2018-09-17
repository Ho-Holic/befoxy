#include "Engine.hpp"
#include "style/Guidelines.hpp"
#include <algorithm>

Engine::Engine()
:   m_ideal()
,   m_current()
{
    //
}

void Engine::init(const Workday& workday)
{
    // clean up
    m_ideal.sprints.clear();
    m_current.sprints.clear();

    // make a stack from ideal workday
    m_ideal = workday;
    std::reverse(m_ideal.sprints.begin(), m_ideal.sprints.end());

    require(!workday.sprints.empty());

    auto sprint = m_ideal.sprints.back();
    m_ideal.sprints.pop_back();

    m_current.sprints.push_back(sprint);

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

const Workday& Engine::workday() const
{        
    return m_ideal;
}

