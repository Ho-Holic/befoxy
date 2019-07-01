#ifndef BEFOXY_CORE_ENGINE_HPP
#define BEFOXY_CORE_ENGINE_HPP

#include <vector>

#include "core/Component.hpp"

class Engine
{
public:
  Engine();
public:
  void init(const Workday& idealWorkday);

public:
  Sprint sprint() const;
  void tap();
  void skip();    
  const std::vector<Sprint> currentSprints() const;

private:
  void activateNextSprint(const TimePoint& startTime);

private:  
  Workday m_ideal;
  Workday m_current;  
};

#endif // BEFOXY_CORE_ENGINE_HPP
