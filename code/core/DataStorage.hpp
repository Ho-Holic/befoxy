#ifndef BEFOXY_CORE_DATASTORAGE_HPP
#define BEFOXY_CORE_DATASTORAGE_HPP

#include <QString>
#include <core/Component.hpp>

class DataStorage
{
public:    
    void loadEngine();
    void saveEngine();
    void loadPreferences();
    void savePreferences();
public:
  void setStoragePath(const QString& storagePath);      
  QString sprintHistoryFilePath();
  QString preferencesFilePath();
private:
  Workday firstRunWorkday();  
private:
  QString m_storagePath;    
  QString m_sprintHistoryFileName;
};

#endif // BEFOXY_CORE_DATASTORAGE_HPP
