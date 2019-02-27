#include "DataStorage.hpp"
#include "Services.hpp"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>

namespace {
    Workday fakeWorkday()
    {
        std::vector<Sprint> w = {
            { SprintType::WorkdayStart, SprintState::Normal, {0, 0, 0}, {}, {} },

            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {} },
            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {} },

            { SprintType::WorkdayEnd,  SprintState::Normal, {0, 0, 0}, {}, {} },
        };
        return Workday { {}, w };
    }
}

void DataStorage::save()
{
    QString sprintHistoryFileName = "sprintHistory.json";

    QFile sprintHistory(m_storagePath + "/" + sprintHistoryFileName);
    if ( ! sprintHistory.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // TODO: Somehow take care of unsaved sprints
        return;
    }

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(sprintHistory.readAll(), &error);
    sprintHistory.close();


    {
        auto finishedSprints = services().engine().finishedSprints();
        services().engine().cleanFinishedSprints();
        // TODO: Write data here
    }

    QFile newSprintHistory(m_storagePath + "/" + sprintHistoryFileName);
    newSprintHistory.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    newSprintHistory.write(document.toJson());
    newSprintHistory.close();
}

void DataStorage::setStoragePath(const QString& storagePath)
{
    m_storagePath = storagePath;
}

void DataStorage::load()
{
    // fake
    m_idealWorkday = fakeWorkday();
}

Workday& DataStorage::idealWorkday()
{
    return m_idealWorkday;
}

