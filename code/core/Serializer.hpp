#ifndef BEFOXY_CORE_SERIALIZER_HPP
#define BEFOXY_CORE_SERIALIZER_HPP

#include "core/Component.hpp"
#include <QJsonObject>

template <typename T>
struct Serializer
{
    static QJsonObject serialize(const T&);
    static T deserialize(const QJsonObject&);
};

template <>
struct Serializer<Workday>
{
    static QJsonObject serialize(const Workday&) {
        // some body
    }

    static Workday deserialize(const QJsonObject&)
    {
        // some body
    }
};

Workday parseWorkday(const QString& data)
{
    // parse format '(+35m -10m) * 4 -1h + (+35m -10m) * 4'
    return {};
}

#endif // BEFOXY_CORE_SERIALIZER_HPP

