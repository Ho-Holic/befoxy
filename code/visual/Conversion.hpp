#ifndef BEFOXY_VISUAL_CONVERSION_HPP
#define BEFOXY_VISUAL_CONVERSION_HPP

#include <QString>
#include <QColor>
#include "core/Component.hpp"
#include "core/utility/MirrorMap.hpp"

static auto sprintIconColorMap()
{
    static auto cache = makeMirrorMap<SprintType, QColor>({
        { SprintType:: Unknown, Qt::white },
        { SprintType:: NoTracking, Qt::gray },
        { SprintType:: WorkdayStart, Qt::blue },
        { SprintType:: WorkdayEnd, Qt::cyan },
        { SprintType:: Work, Qt::red },
        { SprintType:: Rest, Qt::green },
    });
    return cache;
}

#endif // BEFOXY_VISUAL_CONVERSION_HPP
