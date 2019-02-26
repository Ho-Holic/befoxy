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
  const std::vector<Sprint> finishedSprints() const;
  void cleanFinishedSprints();

private:  
  Workday m_ideal;
  Workday m_current;
  TimePoint m_sprintEnd;
  std::vector<Sprint> m_finishedSprints;
};

#endif // BEFOXY_CORE_ENGINE_HPP
