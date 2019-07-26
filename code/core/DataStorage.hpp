#ifndef BEFOXY_CORE_DATASTORAGE_HPP
#define BEFOXY_CORE_DATASTORAGE_HPP

#include <QString>
#include <core/Component.hpp>

class DataStorage
{
public:    
    void load();
    void save();
public:
  void setStoragePath(const QString& storagePath);      
  QString sprintHistoryFilePath();
  QString settingsFilePath();
private:
  Workday firstRunWorkday();
  void saveDefaultSettings();
  // void loadSettings(); // TODO: later, now this is too much
  // void saveSettings(); // TODO: later, now this is too much
private:
  QString m_storagePath;    
  QString m_sprintHistoryFileName;
};

#endif // BEFOXY_CORE_DATASTORAGE_HPP
