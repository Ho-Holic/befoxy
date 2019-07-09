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

//
// TODO: write proper services with 'get/set' methods and type erasure
//
template <typename T>
inline T& service(); // Supposed to be used as specialization now and link error if not

template <>
inline DataStorage& service<DataStorage>()
{
    return services().dataStorage();
}

template <>
inline Engine& service<Engine>()
{
    return services().engine();
}

#endif // BEFOXY_CORE_SERVICES_HPP
