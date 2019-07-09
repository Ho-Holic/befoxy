#include "Engine.hpp"
#include <style/Guidelines.hpp>
#include <algorithm>
#include <core/Methods.hpp>

Engine::Engine()
:   m_ideal()
,   m_current()
{
    //
}

void Engine::init(const Workday& idealWorkday)
{
    Workday currentWorkday;
    currentWorkday.day = idealWorkday.day;

    init(idealWorkday, currentWorkday);
}

void Engine::init(const Workday& idealWorkday, const Workday& currentWorkday)
{
    // clean up
    m_ideal.sprints.clear();
    m_current.sprints.clear();    

    //
    // TODO: make index based non destructive sprint advancing
    //

    // make a stack from ideal workday
    m_ideal = idealWorkday;
    std::reverse(m_ideal.sprints.begin(), m_ideal.sprints.end());

    m_current = currentWorkday;

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
    auto workdayCopy = m_ideal;
    std::reverse(workdayCopy.sprints.begin(), workdayCopy.sprints.end());
    return workdayCopy;
}

WorkProgress Engine::workProgress() const
{
    auto left = std::count_if(m_ideal.sprints.begin(), m_ideal.sprints.end(), &isImportantSprint);
    auto done = std::count_if(m_current.sprints.begin(), m_current.sprints.end(), &isImportantSprint);

    require(done <= (left + done));
    require(left >= 0);
    require(done >= 0);

    return { done, left + done};
}

void Engine::activateNextSprint(const TimePoint& startTime)
{
    if (m_ideal.sprints.empty()) return;

    auto sprint = m_ideal.sprints.back();
    sprint.startTime = startTime;
    sprint.finishTime = sprint.startTime + sprint.time;

    m_ideal.sprints.pop_back();
    m_current.sprints.push_back(sprint);
}
