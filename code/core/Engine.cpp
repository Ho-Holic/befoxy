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
    tap(); // initial tap
}

Sprint Engine::sprint() const
{    
    using namespace std::chrono;

    require(!m_current.sprints.empty());

    auto sprintCopy = m_current.sprints.back();

    if (sprintCopy.type != SprintType::WorkdayStart) {

        auto now = Clock::now();
        bool hasOvertime = now > m_sprintEnd;
        auto diff = (!hasOvertime) ? (m_sprintEnd - now) : (now - m_sprintEnd);

        sprintCopy.time.hour = duration_cast<hours>(diff).count();

        diff -= hours(sprintCopy.time.hour);

        sprintCopy.time.min = duration_cast<minutes>(diff).count();

        diff -= minutes(sprintCopy.time.min);

        sprintCopy.time.sec = duration_cast<seconds>(diff).count();

        sprintCopy.state = hasOvertime ? SprintState::Overtime : SprintState::Normal;
    }

    return sprintCopy;
}

void Engine::tap()
{
    // tap to affect sprint: start/pause/continue
    using namespace std::chrono;

    if (m_ideal.sprints.empty()) return;

    require(!m_ideal.sprints.empty());


    auto now = Clock::now();

    bool hasOvertime = now > m_sprintEnd;
    if (hasOvertime) {

        // add overtime sprint
        if (!m_current.sprints.empty()) {
            Sprint overtimeSprint = sprint();
            m_current.sprints.push_back(overtimeSprint);
        }

        // add next real sprint
        auto sprint = m_ideal.sprints.back();
        m_ideal.sprints.pop_back();
        m_current.sprints.push_back(sprint);


        m_sprintEnd = now
                + hours(sprint.time.hour)
                + minutes(sprint.time.min)
                + seconds(sprint.time.sec);
    }
}

void Engine::skip()
{
    // tap to skip this sprint
    // you need to track skips in analytics too
}

const Workday& Engine::workday() const
{        
    return m_ideal;
}

