#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>

#include "core/Component.hpp"

class Engine
{
public:
  Engine();
public:
  Sprint sprint();
  void update();
  void setWorkday(const Workday& workday);
  const Workday& workday() const;
};

#endif // ENGINE_HPP
