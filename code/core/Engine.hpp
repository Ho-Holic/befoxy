#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <chrono>

#include "core/Component.hpp"

class Engine
{
public:
    using TimePoint = std::chrono::system_clock::time_point;
    using Clock = std::chrono::system_clock;
public:
  Engine();
public:
  void init(const Workday& workday);
public:
  Sprint sprint();
  void tap();
  void skip();
  void update();
  const Workday& workday() const;

private:  
  Workday m_ideal;
  Workday m_current;
  TimePoint m_sprintEnd;
};

#endif // ENGINE_HPP
