#ifndef BEFOXY_CORE_SERIALIZER_HPP
#define BEFOXY_CORE_SERIALIZER_HPP

#include "core/Component.hpp"
#include "core/Engine.hpp"
#include "core/Conversion.hpp"
#include <QJsonObject>
#include <QJsonArray>

template <typename T>
struct Serializer
{
    static void write(const T&, QJsonObject&);
    static void read(const QJsonObject&, T&);
};

template <typename T>
inline QJsonObject writeObject(const T& value)
{
    QJsonObject object;
    Serializer<T>::write(value, object);
    return object;
}

template <typename T>
inline T readObject(const QJsonObject& object)
{
    T value;
    Serializer<T>::read(object, value);
    return value;
}

template <>
struct Serializer<Engine>
{
    static void write(const Engine& value, QJsonObject& root)
    {
        root["currentSprints"] = writeObject(value.currentSprints());
    }

    static void read(const QJsonObject&, Engine&)
    {
        // some body
    }
};

template <typename T>
struct Serializer<std::vector<T>>
{
    static void write(const std::vector<T>& value, QJsonObject& root)
    {
        for (size_t i = 0; i < value.size(); ++i) {

            QString key = QString("key_%1").arg(i);
            root[key] = writeObject(value[i]);
        }
    }

    static void read(const QJsonObject&, std::vector<T>&)
    {
        // some body
    }
};

template <>
struct Serializer<Sprint>
{
    static void write(const Sprint& value, QJsonObject& root)
    {
        root["type"] = sprintTypeMap()(value.type);        
        root["time"] = sprintTimeMap(value.time);
        root["startTime"] = timePointMap(value.startTime);
        root["finishTime"] = timePointMap(value.finishTime);
        root["actualFinishTime"] = timePointMap(value.actualFinishTime);
    }

    static void read(const QJsonObject&, Sprint&)
    {
        // some body
    }
};

template <>
struct Serializer<Workday>
{
    static void write(const Workday&, QJsonObject&)
    {
        // some body
    }

    static void read(const QJsonObject&, Workday&)
    {
        // some body
    }
};

Workday parseWorkday(const QString&)
{
    // parse format '(+35m -10m) * 4 -1h + (+35m -10m) * 4'
    return {};
}

#endif // BEFOXY_CORE_SERIALIZER_HPP

