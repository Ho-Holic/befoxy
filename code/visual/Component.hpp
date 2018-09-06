#ifndef BEFOXY_VISUAL_COMPONENT
#define BEFOXY_VISUAL_COMPONENT

#include <string>

enum class PinType
{
    Unknown,
    Main,
    SubMain,
};

struct Pin
{
    PinType type;
};

#endif // BEFOXY_VISUAL_COMPONENT

