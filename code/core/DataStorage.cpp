#include "DataStorage.hpp"
#include "Services.hpp"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <core/Serializer.hpp>

namespace {
    Workday fakeWorkday()
    {
        std::vector<Sprint> w = {
            { SprintType::WorkdayStart, SprintState::Normal, {0, 0, 0}, {}, {}, {} },

            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {}, {} },
            { SprintType::Work,  SprintState::Normal, {0, 0, 15}, {}, {}, {} },
            { SprintType::Rest,  SprintState::Normal, {0, 0, 5}, {}, {}, {} },

            { SprintType::WorkdayEnd,  SprintState::Normal, {0, 0, 0}, {}, {}, {} },
        };
        return Workday { {}, w };
    }
}

void DataStorage::save()
{
    QString sprintHistoryFileName = "sprintHistory.json";

    QFile sprintHistory(m_storagePath + "/" + sprintHistoryFileName);
    if ( ! sprintHistory.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        // TODO: Somehow take care of unsaved sprints
        return;
    }    

    {        
        QJsonObject object;
        Serializer<Engine>::write(services().engine(), object);

        QJsonDocument document(object);
        sprintHistory.write(document.toJson());
    }    

    sprintHistory.close();
}

void DataStorage::setStoragePath(const QString& storagePath)
{
    m_storagePath = storagePath;
}

void DataStorage::load()
{
    // fake
    m_idealWorkday = fakeWorkday();
    services().engine().init(m_idealWorkday);
}

Workday& DataStorage::idealWorkday()
{
    return m_idealWorkday;
}

