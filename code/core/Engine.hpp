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
  void init(const Workday& idealWorkday, const Workday& currentWorkday, size_t nextSprintIndex);

public:
  Sprint sprint() const;
  Sprint upcomingSprint() const;
  bool hasUpcomingSprint() const;
  void tap();
  void skip();    
  Workday currentWorkday() const;
  Workday idealWorkday() const;
  size_t nextSprintIndex() const;

private:
  void activateNextSprint(const TimePoint& startTime);  

private:  
  Workday m_ideal;
  Workday m_current;  
  size_t m_nextSprintIndex;
};

#endif // BEFOXY_CORE_ENGINE_HPP
