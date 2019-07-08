#include "DataStorage.hpp"
#include "Services.hpp"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <core/Serializer.hpp>
#include <QDebug>

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
        return Workday { {}, w };
    }
}

void DataStorage::setStoragePath(const QString& storagePath)
{
    m_storagePath = storagePath;
}

QString DataStorage::sprintHistoryFilePath()
{
    return m_storagePath + "sprintHistory.json";
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
        Serializer<Engine>::write(services().engine(), object);

        QJsonDocument document(object);
        sprintHistory.write(document.toJson());
    }    

    sprintHistory.close();
}


void DataStorage::load()
{
    QFile sprintHistory(sprintHistoryFilePath());

    if ( ! sprintHistory.open(QIODevice::ReadOnly | QIODevice::Text)) {

        services().engine().init(firstRunWorkday());
        return;
    }

    QByteArray saveData = sprintHistory.readAll();
    QJsonParseError parseError;
    QJsonDocument document(QJsonDocument::fromJson(saveData, &parseError));

    if (parseError.error != QJsonParseError::NoError) {

        qDebug() << parseError.errorString();
        services().engine().init(firstRunWorkday());
        return;
    }

    Serializer<Engine>::read(document.object(), services().engine());
}




