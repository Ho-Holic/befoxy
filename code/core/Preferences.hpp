#ifndef BEFOXY_CORE_PREFERENCES_HPP
#define BEFOXY_CORE_PREFERENCES_HPP

#include "core/Component.hpp"

class Preferences
{
public:
    Preferences();
public:
    void setWorkdayScheme(const WorkdayScheme& scheme);
    const WorkdayScheme& workdayScheme() const;
private:
    WorkdayScheme m_workdayScheme;
};

#endif // BEFOXY_CORE_PREFERENCES_HPP
