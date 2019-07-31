#ifndef BEFOXY_CORE_SERVICES_HPP
#define BEFOXY_CORE_SERVICES_HPP

class DataStorage;
class Engine;
class Preferences;

//
// TODO: write proper services with 'get/set' methods and type erasure
//
template <typename T>
inline T& service(); // Supposed to be used as specialization only

template <>
DataStorage& service<DataStorage>();

template <>
Engine& service<Engine>();

template <>
Preferences& service<Preferences>();

#endif // BEFOXY_CORE_SERVICES_HPP
