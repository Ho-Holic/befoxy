#ifndef BEFOXY_CORE_CONVERSION_HPP
#define BEFOXY_CORE_CONVERSION_HPP

#include <string>
#include "core/Component.hpp"
#include "core/utility/MirrorMap.hpp"

static auto sprintTypeMap()
{
    static auto cache = makeMirrorMap<SprintType, std::string>({
        { SprintType:: Unknown, "Unknown" },
        { SprintType:: NoTracking, "NoTracking" },
        { SprintType:: WorkdayStart, "WorkdayStart" },
        { SprintType:: WorkdayEnd, "WorkdayEnd" },
        { SprintType:: Work, "Work" },
        { SprintType:: Rest, "Rest" },
    });
    return cache;
}

#endif // BEFOXY_CORE_CONVERSION_HPP