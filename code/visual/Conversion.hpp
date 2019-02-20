#ifndef BEFOXY_VISUAL_CONVERSION_HPP
#define BEFOXY_VISUAL_CONVERSION_HPP

#include <QString>
#include "core/Component.hpp"
#include "core/utility/MirrorMap.hpp"

static auto sprintIconPathMap()
{
    static auto cache = makeMirrorMap<SprintType, QString>({
        { SprintType:: Unknown, ":/white.png" },
        { SprintType:: NoTracking, ":/gray.png" },
        { SprintType:: WorkdayStart, ":/blue.png" },
        { SprintType:: WorkdayEnd, ":/cyan.png" },
        { SprintType:: Work, ":/red.png" },
        { SprintType:: Rest, ":/green.png" },
    });
    return cache;
}

#endif // BEFOXY_VISUAL_CONVERSION_HPP
