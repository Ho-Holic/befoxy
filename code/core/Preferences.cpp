#include "Preferences.hpp"

namespace {
    std::vector<Sprint> defaultSprintConfiguration()
    {
        std::vector<Sprint> w = {
            { SprintType::WorkdayStart, SprintState::Normal, {0, 0, 0}, {}, {}, {} },

            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {}, {} },
            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {}, {} },

            { SprintType::WorkdayEnd,  SprintState::Normal, {0, 0, 0}, {}, {}, {} },
        };

        return w;
    }
}

Preferences::Preferences()
{    
    m_workdayScheme.sprints = defaultSprintConfiguration();
}

void Preferences::setWorkdayScheme(const WorkdayScheme& scheme)
{
    m_workdayScheme = scheme;
}

const WorkdayScheme& Preferences::workdayScheme() const
{
    return m_workdayScheme;
}
