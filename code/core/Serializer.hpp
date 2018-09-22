#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
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

Workday parseWorkday(const std::string& data)
{
    // parse format '(+35m -10m) * 4 -1h + (+35m -10m) * 4'
    return;
}

#endif // SERIALIZER_HPP
