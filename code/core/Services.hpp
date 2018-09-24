#ifndef BEFOXY_CORE_SERVICES_HPP
#define BEFOXY_CORE_SERVICES_HPP

#include <core/Engine.hpp>
#include <core/DataStorage.hpp>
#include <memory>

class Services
{
public:
    DataStorage& dataStorage();
    Engine& engine();
private:    
    DataStorage m_dataStorage;
    Engine m_engine;
};

Services& services();

#endif // BEFOXY_CORE_SERVICES_HPP
