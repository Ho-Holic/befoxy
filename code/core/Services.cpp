#include "Services.hpp"

Engine& Services::engine()
{
    return m_engine;
}

DataStorage& Services::dataStorage()
{
    return m_dataStorage;
}

Services& services()
{
    static Services servicesInstance;
    return servicesInstance;
}
