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
private:
  QString sprintHistoryFilePath();
private:
  QString m_storagePath;  
  Config m_config;
  QString m_sprintHistoryFileName;
};

#endif // BEFOXY_CORE_DATASTORAGE_HPP
