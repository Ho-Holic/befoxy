#ifndef BEFOXY_CORE_DATASTORAGE_HPP
#define BEFOXY_CORE_DATASTORAGE_HPP

#include <QString>
#include <core/Component.hpp>

class DataStorage
{
public:
    void save();
    void load();
public:
  void setStoragePath(const QString& storagePath);    
  Workday& idealWorkday();
private:
  QString m_storagePath;
  Workday m_idealWorkday;  
  Config m_config;
};

#endif // BEFOXY_CORE_DATASTORAGE_HPP
