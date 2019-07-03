#ifndef BACKPORT_HPP
#define BACKPORT_HPP

#include <style/Guidelines.hpp>
#include <functional>

// backport of std::clamp from C++17

namespace backport {

  namespace std {

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
