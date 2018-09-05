#include "Services.hpp"

Services::Services()
{

}

Engine& Services::engine()
{
    return m_engine;
}


Services& services()
{
    static Services servicesInstance;
    return servicesInstance;
}
