#pragma once

#include <limits>


namespace HyperCPU {
  template <typename T>
  constexpr bool AdditionWillOverflow(T& a, T& b) {
    return (b > 0 && a > std::numeric_limits<T>::max() - b);
  }

  template<typename T>
  constexpr bool multiplication_will_overflow(T& a, T& b) {
    return (a != 0 && (static_cast<T>(a * b)) / a != b);
  }
}
