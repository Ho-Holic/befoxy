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
        root["idealWorkday"] = writeObject(value.idealSprints());
        root["currentWorkday"] = writeObject(value.currentSprints());
    }

    static void read(const QJsonObject& root, Engine& value)
    {
        // TODO: implement Workday serialization
        auto idealWorkday = readObject<std::vector<Sprint>>(root["idealWorkday"].toObject());
        auto currentWorkday = readObject<std::vector<Sprint>>(root["currentWorkday"].toObject());

        value.init(Workday{{}, idealWorkday}, Workday{{}, currentWorkday});
    }
};

template <typename T>
struct Serializer<std::vector<T>>
{
    static QString key(size_t index) {
        return QString("key_%1").arg(index);
    }

    static void write(const std::vector<T>& value, QJsonObject& root)
    {
        for (size_t i = 0; i < value.size(); ++i) {

            root[key(i)] = writeObject(value[i]);
        }
        root["size"] = static_cast<int>(value.size());
    }

    static void read(const QJsonObject& root, std::vector<T>& value)
    {
        int maybeSize = root["size"].toInt();
        if (maybeSize > 0) {

            for (size_t i = 0; i < static_cast<size_t>(maybeSize); ++i) {

                auto object = root[key(i)].toObject();
                value.push_back(readObject<T>(object));
            }
        }
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

    static void read(const QJsonObject& root, Sprint& value)
    {
        value.type= sprintTypeMap()(root["type"].toString());
        value.time = sprintTimeMap(root["time"].toString());
        value.startTime = timePointMap(root["startTime"].toString());
        value.finishTime = timePointMap(root["finishTime"].toString());
        value.actualFinishTime = timePointMap(root["actualFinishTime"].toString());
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

