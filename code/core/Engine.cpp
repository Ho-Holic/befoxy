#include "Engine.hpp"
#include <style/Guidelines.hpp>
#include <algorithm>
#include <core/Methods.hpp>

Engine::Engine()
:   m_ideal()
,   m_current()
,   m_nextSprintIndex()
{
    //
}

void Engine::init(const Workday& idealWorkday)
{
    Workday currentWorkday;
    currentWorkday.day = idealWorkday.day;

    init(idealWorkday, currentWorkday, 0);
}

void Engine::init(const Workday& idealWorkday, const Workday& currentWorkday, size_t nextSprintIndex)
{
    // clean up
    m_ideal.sprints.clear();
    m_current.sprints.clear();    

    m_ideal = idealWorkday;    
    m_current = currentWorkday;
    m_nextSprintIndex = nextSprintIndex;

    if (m_current.sprints.empty()) {
        auto now = Clock::now();
        activateNextSprint(now);
    }
}

Sprint Engine::sprint() const
{    
    using namespace std::chrono;

    require(!m_current.sprints.empty());

    auto sprintCopy = m_current.sprints.back();
    auto sprintEnd = sprintCopy.finishTime;

    if (sprintCopy.type != SprintType::WorkdayStart && sprintCopy.type != SprintType::WorkdayEnd) {

        auto now = Clock::now();
        bool hasOvertime = now > sprintEnd;
        auto diff = (!hasOvertime) ? (sprintEnd - now) : (now - sprintEnd);

        sprintCopy.time.hour = duration_cast<hours>(diff).count();

        diff -= hours(sprintCopy.time.hour);

        sprintCopy.time.min = duration_cast<minutes>(diff).count();

        diff -= minutes(sprintCopy.time.min);

        sprintCopy.time.sec = duration_cast<seconds>(diff).count();

        sprintCopy.state = hasOvertime ? SprintState::Overtime : SprintState::Normal;
    }

    return sprintCopy;
}

Sprint Engine::upcomingSprint() const
{
    using namespace std::chrono;

    require(hasUpcomingSprint());

    auto sprintCopy = m_ideal.sprints[m_nextSprintIndex];

    return sprintCopy;
}

bool Engine::hasUpcomingSprint() const
{
    return !m_ideal.sprints.empty() && m_nextSprintIndex < m_ideal.sprints.size();
}

void Engine::tap()
{
    // tap to affect sprint: start/pause/continue
    using namespace std::chrono;

    if (m_current.sprints.empty()) return;

    auto now = Clock::now();
    auto sprintEnd = m_current.sprints.back().finishTime;

    bool hasEnded = (now >= sprintEnd);
    if (hasEnded) {

        m_current.sprints.back().actualFinishTime = now;

        activateNextSprint(now);
    }
}

void Engine::skip()
{
    // tap to skip this sprint
    // you need to track skips in analytics too
}

Workday Engine::currentWorkday() const
{
    return m_current;
}

Workday Engine::idealWorkday() const
{
    return m_ideal;
}

size_t Engine::nextSprintIndex() const
{   
    return m_nextSprintIndex;
}

void Engine::activateNextSprint(const TimePoint& startTime)
{
    if (m_nextSprintIndex < m_ideal.sprints.size()) {

        auto sprint = m_ideal.sprints[m_nextSprintIndex];
        sprint.startTime = startTime;
        sprint.finishTime = sprint.startTime + sprint.time;

        m_nextSprintIndex += 1;

        m_current.sprints.push_back(sprint);
    }
}

