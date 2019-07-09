#ifndef BACKPORT_HPP
#define BACKPORT_HPP

#include <style/Guidelines.hpp>
#include <functional>
#include <chrono>

// backport of std::clamp from C++17
// backport of std::chrono::days from C++20

namespace backport {

  namespace std {

    namespace chrono {
      using days = ::std::chrono::duration<int, ::std::ratio<86400>>;
    }

    template<class T, class Compare>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp) {

      return require(!comp(hi, lo)),
             comp(v, lo) ? lo : comp(hi, v) ? hi : v;
    }

    template<class T>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
      return clamp(v, lo, hi, ::std::less<>());
    }

  }
}

#endif // BACKPORT_HPP
