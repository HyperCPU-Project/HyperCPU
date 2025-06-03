#pragma once

#include "PCH/CStd.hpp"

#include "Common/LanguageSpec/Flags.hpp"
#include "Emulator/Core/CPU/Decoders/StdDecoder.hpp"
#include "Emulator/Core/CPU/IO/Simple.hpp"
#include "Emulator/Core/CPU/Interrupts/ReservedInterrupts.hpp"
#include "Emulator/Core/MemoryController/IMemoryController.hpp"

#define DECLARE_INSTR(name) void Exec##name(const IInstruction& instr, OperandContainer op1, OperandContainer op2)

namespace HyperCPU {
  class MemoryControllerST;

  class CPU {
  private:
    friend class Decoder;
    friend class MemoryControllerST;

    using opcode_handler = std::function<void(const IInstruction& instr, OperandContainer op1, OperandContainer op2)>;
    using read_operation_handler = std::function<std::uint8_t()>;
    using write_operation_handler = std::function<void(std::uint8_t)>;

    // Components
    IMemoryController* mem_controller;
    std::unique_ptr<Decoder> m_decoder;

    // Data
    std::uint16_t core_count;
    std::uint64_t total_mem;
    bool halted;

    // General space for registers
    std::uint64_t data[13];

    // GP Registers
    std::uint64_t *x0, *x1, *x2, *x3, *x4, *x5, *x6, *x7;
    std::uint32_t *xh0, *xh1, *xh2, *xh3, *xh4, *xh5, *xh6, *xh7;
    std::uint32_t *xl0, *xl1, *xl2, *xl3, *xl4, *xl5, *xl6, *xl7;
    std::uint16_t *xll0, *xll1, *xll2, *xll3;
    std::uint8_t *xllh0, *xllh1, *xllh2, *xllh3;
    std::uint8_t *xlll0, *xlll1, *xlll2, *xlll3;

    // Specific registers
    std::uint64_t *xbp, *xsp, *xip, *xgdp, *xivt;
    bool ivt_initialized;

    // Flags
    bool crf, ovf, udf, zrf;

    std::array<opcode_handler, 128> opcode_handler_assoc;

    std::pair<OperandContainer, OperandContainer> GetOperands(OperandTypes op_types, ModePack md, OperandContainer& op1, OperandContainer& op2);
    OperandContainer GetRegister(OperandContainer& op1);

    // Stack
    void StackPush8(std::uint8_t) noexcept;
    void StackPush16(std::uint16_t) noexcept;
    void StackPush32(std::uint32_t) noexcept;
    void StackPush64(std::uint64_t) noexcept;

    std::uint8_t StackPop8() noexcept;
    std::uint16_t StackPop16() noexcept;
    std::uint32_t StackPop32() noexcept;
    std::uint64_t StackPop64() noexcept;

    // Interrupts
    void TriggerInterrupt(HyperCPU::cpu_exceptions exception);
    void RunInterruptSubroutine();

    // Pipeline implementation
    std::atomic<bool> buffer_used, interrupt_active;
    IInstruction buffer, _buffer;
    std::optional<std::uint64_t> pending_interrupt;
    void DecodingThread();
    void ExecutingThread();

    // All instructions
    DECLARE_INSTR(ADD);
    DECLARE_INSTR(ADC);
    DECLARE_INSTR(AND);
    DECLARE_INSTR(ANDN);
    DECLARE_INSTR(BSWAP);
    DECLARE_INSTR(CALL);
    DECLARE_INSTR(CALLE);
    DECLARE_INSTR(CALLGR);
    DECLARE_INSTR(CALLL);
    DECLARE_INSTR(CCRF);
    DECLARE_INSTR(CMP);
    DECLARE_INSTR(COVF);
    DECLARE_INSTR(CUDF);
    DECLARE_INSTR(INC);
    DECLARE_INSTR(DEC);
    DECLARE_INSTR(HID);
    DECLARE_INSTR(MUL);
    DECLARE_INSTR(OR);
    DECLARE_INSTR(SUB);
    DECLARE_INSTR(SHFL);
    DECLARE_INSTR(SHFR);
    DECLARE_INSTR(DIV);
    DECLARE_INSTR(HALT);
    DECLARE_INSTR(MOV);
    DECLARE_INSTR(LOIVT);
    DECLARE_INSTR(INTR);
    DECLARE_INSTR(READ);
    DECLARE_INSTR(WRITE);
    DECLARE_INSTR(JMP);
    DECLARE_INSTR(JME);
    DECLARE_INSTR(JMGR);
    DECLARE_INSTR(JML);
    DECLARE_INSTR(PUSH);
    DECLARE_INSTR(POP);
    DECLARE_INSTR(LODSB);
    DECLARE_INSTR(STDSB);

    // I/O
    std::array<read_operation_handler, 256> read_io_handlers;
    std::array<write_operation_handler, 256> write_io_handlers;
    std::unique_ptr<SimpleIOImpl> io_ctl;
    
    class CPU_InstrImpl;

  public:
    CPU(std::uint16_t core_count, std::uint64_t mem_size, char* binary = nullptr, std::uint64_t binary_size = 0);

    void Run();

    bool CanExecuteInterrupts();
    void SetEntryPoint(std::uint32_t entry_point);

    ~CPU();
  };
} // namespace HyperCPU
