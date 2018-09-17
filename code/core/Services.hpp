#ifndef SERVICES_HPP
#define SERVICES_HPP

#include <core/Engine.hpp>
#include <core/DataStorage.hpp>
#include <memory>

class Services
{
public:
    Services();
public:
    void init();
public:
    DataStorage& dataStorage();
    Engine& engine();
private:    
    DataStorage m_dataStorage;
    Engine m_engine;
};

Services& services();

#endif // SERVICES_HPP
