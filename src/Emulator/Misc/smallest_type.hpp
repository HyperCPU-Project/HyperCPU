#include <type_traits>

namespace HyperCPU {
  template<typename T, typename U>
  using smallest_type = std::conditional_t<
    (sizeof(T) <= sizeof(U)),
    T,
    U
  >;
}