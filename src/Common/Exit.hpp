#include <cstdlib>

namespace HyperCPU {
  /*
    Some dynamic functions.
    When the program was compiled on debug profile, any exit must be easy to catch by debugger - same thing with unreachable call,
    as using this can cause serious bugs. When we are on release profile - allow these things to behave how they were intented.
  */

  [[noreturn]] constexpr void exit([[maybe_unused]] int code) {
#ifdef NDEBUG
    std::abort();
#else
    std::exit(code);
#endif
  }

  constexpr void unreachable() {
#ifdef NDEBUG
    std::abort();
#else
    __builtin_unreachable();
#endif
  }
} // namespace HyperCPU