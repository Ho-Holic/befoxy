#ifndef BEFOXY_CORE_DATASTORAGE_HPP
#define BEFOXY_CORE_DATASTORAGE_HPP

#include <QString>
#include <core/Component.hpp>

class DataStorage
{
public:
    void save();
public:
  void setStoragePath(const QString& storagePath);
  QString serialize();
  void deserialize();
  Workday& idealWorkday();
private:
  QString m_storagePath;
  Workday m_idealWorkday;  
  Config m_config;
};

#endif // BEFOXY_CORE_DATASTORAGE_HPP
