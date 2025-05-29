#pragma once

#include "PCH/CStd.hpp"

#include "Common/LanguageSpec/Flags.hpp"
#include "Common/LanguageSpec/Opcodes.hpp"
#include "Emulator/Core/CPU/Decoders/IDecoder.hpp"
#include "Emulator/Core/MemoryController/IMemoryController.hpp"
#include "Emulator/Misc/bit_cast.hpp"

namespace HyperCPU {
  enum class AddrExtensionStatus {
    Disabled = 0b00,
    EnabledOp1 = 0b10,
    EnabledOp2 = 0b11
  };

  struct OperandContainer {
  public:
    OperandContainer()
        : value(0) {
    }
    OperandContainer(std::nullptr_t)
        : value(0) {
    }
    explicit OperandContainer(std::uint64_t value)
        : value(value) {
    }
    template <typename T>
    explicit OperandContainer(T* ptr)
        : value(HyperCPU::bit_cast<std::uint64_t>(ptr)) {
    } // Supposed to be executed from GetRegister()

    operator std::uint8_t() const noexcept {
      return HyperCPU::bit_cast<std::uint8_t>(value);
    }
    operator std::uint16_t() const noexcept {
      return HyperCPU::bit_cast<std::uint16_t>(value);
    }
    operator std::uint32_t() const noexcept {
      return HyperCPU::bit_cast<std::uint32_t>(value);
    }
    operator std::uint64_t() const noexcept {
      return value;
    }

    std::uint64_t& ref() noexcept {
      return value;
    }

    template <typename T>
    operator T*() const noexcept {
      return HyperCPU::bit_cast<T*>(value);
    }

    template <typename T>
    T& deref() const noexcept {
      return *static_cast<T*>(*this);
    }

    template <typename T>
    T* ptr() const noexcept {
      return static_cast<T*>(*this);
    }

    ~OperandContainer() {
    }

  private:
    std::uint64_t value;
  };

  struct IInstruction {
    Opcode m_opcode;
    ModePack m_opcode_mode;
    OperandTypes m_op_types;
    OperandContainer m_op1, m_op2;
    AddrExtensionStatus addr_extension_status;
    std::uint8_t extension;
  };

  class CPU;

  class Decoder final : public IDecoder {
  private:
    IMemoryController* mem_controller;
    std::uint64_t* xip;
    class CPU* cpu;
    bool decoder_halted;

    bool CheckSupportedOperandSize(std::uint8_t byte, Mode mode) const noexcept;
    void RaiseException(bool expr) noexcept;

  public:
    explicit Decoder() = default; // For testing purposes - causes UB if used incorrectly
    explicit Decoder(IMemoryController* mc, std::uint64_t* counter, class CPU* cpu)
        : mem_controller(mc), xip(counter), cpu(cpu), decoder_halted(false) {
    }

    IInstruction FetchAndDecode() override;
    bool IsHalted() const noexcept override;

    ~Decoder() = default;
  };
}; // namespace HyperCPU
