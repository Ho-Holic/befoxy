#include "DataStorage.hpp"
#include "Services.hpp"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <core/Serializer.hpp>
#include <QDebug>
#include <style/Backport.hpp>

namespace {
    Workday firstRunWorkday()
    {
        std::vector<Sprint> w = {
            { SprintType::WorkdayStart, SprintState::Normal, {0, 0, 0}, {}, {}, {} },

            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {}, {} },
            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {}, {} },

            { SprintType::WorkdayEnd,  SprintState::Normal, {0, 0, 0}, {}, {}, {} },
        };

        auto now = Clock::now();
        auto startOfTheDay = std::chrono::time_point_cast<backport::std::chrono::days>(now);

        return Workday { startOfTheDay, w };
    }
}

void DataStorage::setStoragePath(const QString& storagePath)
{
    m_storagePath = storagePath;
}

QString DataStorage::sprintHistoryFilePath()
{    
    auto now = Clock::now();
    auto startOfTheDay = std::chrono::time_point_cast<backport::std::chrono::days>(now);
    auto currentDay = timePointMap(startOfTheDay);
    return m_storagePath + QString("sprintHistory_%1.json").arg(currentDay);
}

void DataStorage::load()
{
    QFile sprintHistory(sprintHistoryFilePath());

    if ( ! sprintHistory.open(QIODevice::ReadOnly | QIODevice::Text)) {

        service<Engine>().init(firstRunWorkday());
        return;
    }

    QByteArray saveData = sprintHistory.readAll();
    QJsonParseError parseError;
    QJsonDocument document(QJsonDocument::fromJson(saveData, &parseError));

    if (parseError.error != QJsonParseError::NoError) {

        qDebug() << parseError.errorString();
        service<Engine>().init(firstRunWorkday());
        return;
    }

    Serializer<Engine>::read(document.object(), service<Engine>());
}

void DataStorage::save()
{
    QFile sprintHistory(sprintHistoryFilePath());
    if ( ! sprintHistory.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        // TODO: Somehow take care of unsaved sprints
        return;
    }

    {
        QJsonObject object;
        Serializer<Engine>::write(service<Engine>(), object);

        QJsonDocument document(object);
        sprintHistory.write(document.toJson());
    }

    sprintHistory.close();
}
