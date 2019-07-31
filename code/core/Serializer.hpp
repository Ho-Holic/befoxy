#ifndef BEFOXY_CORE_SERIALIZER_HPP
#define BEFOXY_CORE_SERIALIZER_HPP

#include <core/Component.hpp>
#include <core/Engine.hpp>
#include <core/Conversion.hpp>
#include <core/Preferences.hpp>
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
struct Serializer<Preferences>
{
    static void write(const Preferences& value, QJsonObject& root)
    {
        root["workdayScheme"] = writeObject(value.workdayScheme());
    }

    static void read(const QJsonObject& root, Preferences& value)
    {
        auto scheme = readObject<WorkdayScheme>(root["workdayScheme"].toObject());
        value.setWorkdayScheme(scheme);
    }
};

template <>
struct Serializer<Engine>
{
    static void write(const Engine& value, QJsonObject& root)
    {
        root["idealWorkday"] = writeObject(value.idealWorkday());
        root["currentWorkday"] = writeObject(value.currentWorkday());
        root["nextSprintIndex"] = static_cast<int>(value.nextSprintIndex());
    }

    static void read(const QJsonObject& root, Engine& value)
    {        
        auto idealWorkday = readObject<Workday>(root["idealWorkday"].toObject());
        auto currentWorkday = readObject<Workday>(root["currentWorkday"].toObject());
        auto nextSprintIndex = root["nextSprintIndex"].toInt();

        value.init(idealWorkday, currentWorkday, static_cast<size_t>(nextSprintIndex));
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
        value.type = sprintTypeMap()(root["type"].toString());
        value.time = sprintTimeMap(root["time"].toString());
        value.startTime = timePointMap(root["startTime"].toString());
        value.finishTime = timePointMap(root["finishTime"].toString());
        value.actualFinishTime = timePointMap(root["actualFinishTime"].toString());
    }
};

template <>
struct Serializer<Workday>
{
    static void write(const Workday& value, QJsonObject& root)
    {
        root["day"] = timePointMap(value.day);
        root["sprints"] = writeObject(value.sprints);
    }

    static void read(const QJsonObject& root, Workday& value)
    {
        value.day = timePointMap(root["day"].toString());
        value.sprints = readObject<std::vector<Sprint>>(root["sprints"].toObject());
    }
};

template <>
struct Serializer<WorkdayScheme>
{
    static void write(const WorkdayScheme& value, QJsonObject& root)
    {
        root["sprints"] = sprintSchemeMap(value.sprints);
    }

    static void read(const QJsonObject& root, WorkdayScheme& value)
    {
        value.sprints = sprintSchemeMap(root["sprints"].toString());
    }
};

#endif // BEFOXY_CORE_SERIALIZER_HPP

