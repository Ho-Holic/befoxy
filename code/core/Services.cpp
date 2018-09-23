#include "Services.hpp"

namespace {
    Workday fakeWorkday()
    {
        std::vector<Sprint> w = {
            { SprintType::WorkdayStart, SprintState::Normal, {0, 0, 0} },

            { SprintType::Work,  SprintState::Normal, {0, 0, 15} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5} },
            { SprintType::Work,  SprintState::Normal, {0, 0, 15} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5} },

            { SprintType::WorkdayEnd,  SprintState::Normal, {0, 0, 0} },
        };
        return Workday { {}, w };
    }
}

Services::Services()
{
    //
}

void Services::init()
{
    m_engine.init(fakeWorkday());
}

Engine& Services::engine()
{
    return m_engine;
}

DataStorage& Services::dataStorage()
{
    return m_dataStorage;
}


Services& services()
{
    static Services servicesInstance;
    return servicesInstance;
}
