#pragma once

#include "PCH/CStd.hpp"

#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Core/CPU/Interrupts/ReservedInterrupts.hpp"

#include "spdlog/spdlog.h"

// TODO: позор партии, убрать и переделать в функцию
#define mem_ctlr_assert(expr)                                             \
  do {                                                                    \
    if (!(expr) && (!cpu || !cpu->CanExecuteInterrupts())) [[unlikely]] { \
      spdlog::error("Assertion failed: {}", #expr);                       \
      std::abort();                                                       \
    } else if (!(expr) && cpu && cpu->CanExecuteInterrupts()) {           \
      cpu->TriggerInterrupt(HyperCPU::cpu_exceptions::SEGF);              \
    } else [[likely]] {                                                   \
    }                                                                     \
  } while (false)

namespace HyperCPU {
  template <bool, typename T>
  struct LoadTypeChooser;

  template <typename T>
  struct LoadTypeChooser<false, T> {
    using type = T;
  };

  template <typename T>
  struct LoadTypeChooser<true, T> {
    using type = std::underlying_type_t<T>;
  };

  template<typename T>
  concept IntConvertable = 
    (sizeof(T) == 1 && std::is_convertible_v<typename LoadTypeChooser<std::is_enum_v<T>, T>::type, std::uint8_t>) ||
    (sizeof(T) == 2 && std::is_convertible_v<typename LoadTypeChooser<std::is_enum_v<T>, T>::type, std::uint16_t>) ||
    (sizeof(T) == 4 && std::is_convertible_v<typename LoadTypeChooser<std::is_enum_v<T>, T>::type, std::uint32_t>) ||
    (sizeof(T) == 8 && std::is_convertible_v<typename LoadTypeChooser<std::is_enum_v<T>, T>::type, std::uint64_t>);

  class MemoryControllerST final {
  public:
    explicit MemoryControllerST(std::size_t mem_size, class CPU* cpu = nullptr)
        : cpu(cpu), total_mem(mem_size) {
      memory = static_cast<char*>(calloc(total_mem, 1));
      if (!memory)
        throw std::runtime_error("Failed to allocate memory!");
    }

    template<IntConvertable T>
    inline T Fetch(std::uint64_t& ptr) {
      mem_ctlr_assert(ptr + sizeof(T) - 1 < total_mem);
      auto t = cpu->CanExecuteInterrupts();

      T data;
      std::memcpy(&data, &memory[ptr], sizeof(T));
      ptr += sizeof(T);

      return data;
    }

    template<IntConvertable T>
    inline T Read(std::uint64_t ptr) {
      mem_ctlr_assert(ptr + sizeof(T) - 1 < total_mem);

      T data;
      std::memcpy(&data, &memory[ptr], sizeof(T));

      return data;
    }

    template<IntConvertable T>
    inline void Load(std::uint64_t ptr, T data) {
      mem_ctlr_assert(ptr + sizeof(T) - 1 < total_mem);

      memcpy(&memory[ptr], &data, sizeof(std::uint8_t));
    }

    std::uint8_t* get_ptr() const noexcept {
      return reinterpret_cast<std::uint8_t*>(memory);
    }

    ~MemoryControllerST() {
      free(memory);
    }

  private:
    char* memory;
    class CPU* cpu;
    std::size_t total_mem;
  };
} // namespace HyperCPU
