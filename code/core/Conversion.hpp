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

static auto sprintTimeMap(const SprintTime& time)
{
    return QString("%1:%2:%3").arg(time.hour).arg(time.min).arg(time.sec);
}

static auto sprintTimeMap(const QString& time)
{

    auto splitted = time.split(":");

    Q_ASSERT(splitted.size() == 3);

    // TODO: add error handling
    auto h = splitted[0].toInt();
    auto m = splitted[1].toInt();
    auto s = splitted[2].toInt();

    return SprintTime{h, m, s};
}

static auto timePointMap(const TimePoint& timePoint)
{
    return QString("%1").arg(timePoint.time_since_epoch().count());
}

static auto timePointMap(const QString& timePoint)
{
    static_assert (std::is_same<Clock::duration::rep, long long>::value, "Clock precision loss!");

    Clock::duration::rep ns = timePoint.toLongLong();
    TimePoint::duration duration(ns);

    return TimePoint(duration);
}

#endif // BEFOXY_CORE_CONVERSION_HPP
