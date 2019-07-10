#ifndef BEFOXY_CORE_CONVERSION_HPP
#define BEFOXY_CORE_CONVERSION_HPP

#include <QString>
#include <QStringList>
#include "core/Component.hpp"
#include "core/utility/MirrorMap.hpp"

static auto sprintTypeMap()
{
    static auto cache = makeMirrorMap<SprintType, QString>({
        { SprintType:: Unknown, "Unknown" },
        { SprintType:: NoTracking, "NoTracking" },
        { SprintType:: WorkdayStart, "WorkdayStart" },
        { SprintType:: WorkdayEnd, "WorkdayEnd" },
        { SprintType:: Work, "Work" },
        { SprintType:: Rest, "Rest" },
    });
    return cache;
}

static auto sprintStateMap()
{
    static auto cache = makeMirrorMap<SprintState, QString>({
        { SprintState:: Unknown, "Unknown" },
        { SprintState:: Normal, "Normal" },
        { SprintState:: Paused, "Paused" },
        { SprintState:: Overtime, "Overtime" },
    });
    return cache;
}

QString sprintTimeMap(const SprintTime& time);
SprintTime sprintTimeMap(const QString& time);

QString timePointMap(const TimePoint& timePoint);
TimePoint timePointMap(const QString& timePoint);

QString sprintSchemeMap(const std::vector<Sprint>& scheme);
std::vector<Sprint> sprintSchemeMap(const QString& scheme);

#endif // BEFOXY_CORE_CONVERSION_HPP
