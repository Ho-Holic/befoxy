#include "Services.hpp"

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
