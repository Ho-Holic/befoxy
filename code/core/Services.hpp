#ifndef SERVICES_HPP
#define SERVICES_HPP

#include <core/Engine.hpp>

class Services
{
public:
    Services();
public:
    Engine& engine();
private:
    Engine m_engine;
};

Services& services();

#endif // SERVICES_HPP
