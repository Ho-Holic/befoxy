#include "DataStorage.hpp"
#include "Services.hpp"
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <core/Serializer.hpp>
#include <QDebug>
#include <style/Backport.hpp>

Workday DataStorage::firstRunWorkday()
{
    auto now = Clock::now();
    auto startOfTheDay = std::chrono::time_point_cast<backport::std::chrono::days>(now);

    return Workday { startOfTheDay, service<Preferences>().workdayScheme().sprints };
}

void DataStorage::loadPreferences()
{
    QFile preferences(preferencesFilePath());

    if ( ! preferences.open(QIODevice::ReadOnly | QIODevice::Text)) {

        savePreferences();
        return;
    }

    QByteArray saveData = preferences.readAll();
    QJsonParseError parseError;
    QJsonDocument document(QJsonDocument::fromJson(saveData, &parseError));

    if (parseError.error != QJsonParseError::NoError) {

        qDebug() << parseError.errorString();
        return; // message user about it?
    }

    QJsonObject object = document.object();
    auto scheme = readObject<WorkdayScheme>(object["workdayScheme"].toObject());

    Serializer<Preferences>::read(document.object(), service<Preferences>());

    preferences.close();
}

void DataStorage::savePreferences()
{
    QFile preferences(preferencesFilePath());
    if ( ! preferences.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {

        // we don't care here if user don't get our default settings
        return;
    }

    {                
        QJsonObject object;
        Serializer<Preferences>::write(service<Preferences>(), object);

        QJsonDocument document(object);
        preferences.write(document.toJson());
    }

    preferences.close();
}

void DataStorage::loadEngine()
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

    sprintHistory.close();
}

void DataStorage::saveEngine()
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

void DataStorage::setStoragePath(const QString& storagePath)
{
    m_storagePath = storagePath;
}

QString DataStorage::sprintHistoryFilePath()
{
    //
    // TODO: use ideal sprint time as a part of file signature
    //
    auto now = Clock::now() + std::chrono::hours(3); // UTC+3 for Moscow
    auto startOfTheDay = std::chrono::time_point_cast<backport::std::chrono::days>(now);
    auto currentDay = timePointMap(startOfTheDay);
    return m_storagePath + QString("sprintHistory_%1.json").arg(currentDay);
}

QString DataStorage::preferencesFilePath()
{
    return m_storagePath + "befoxyPreferences.json";
}
