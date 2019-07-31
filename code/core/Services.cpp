#include "Services.hpp"

#include <core/Engine.hpp>
#include <core/DataStorage.hpp>
#include <core/Preferences.hpp>

template <>
DataStorage& service<DataStorage>()
{
    static DataStorage instance;
    return instance;
}

template <>
Engine& service<Engine>()
{
    static Engine instance;
    return instance;
}

template<>
Preferences& service<Preferences>()
{
    static Preferences instance;
    return instance;
}
