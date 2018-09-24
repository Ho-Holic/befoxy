#include "DataStorage.hpp"

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

void DataStorage::setStoragePath(const QString& storagePath)
{
    m_storagePath = storagePath;
}

void DataStorage::serialize()
{
    //
}

void DataStorage::deserialize()
{
    // fake
    m_idealWorkday = fakeWorkday();
}

Workday& DataStorage::idealWorkday()
{
    return m_idealWorkday;
}

