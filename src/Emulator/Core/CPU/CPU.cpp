#include "Common/LanguageSpec/Opcodes.hpp"
#include "PCH/CStd.hpp"

#include "Common/LanguageSpec/Opcodes.hpp"
#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Core/CPU/Decoders/StdDecoder.hpp"
#include "Emulator/Core/MemoryController/MemoryControllerST.hpp"

HyperCPU::CPU::CPU(std::uint16_t core_count, std::uint64_t mem_size, char* binary, std::uint64_t binary_size)
    : mem_controller(dynamic_cast<IMemoryController*>(new MemoryControllerST(mem_size, this))),
      core_count(core_count),
      total_mem(mem_size),
      binary_size(binary_size),
      halted(false),
      ivt_initialized(false),
      io_ctl(std::make_unique<SimpleIOImpl>()) {
  // Initializing all register pointers
  std::memset(&data, 0, sizeof(data));
  x0 = &data[0];
  x1 = &data[1];
  x2 = &data[2];
  x3 = &data[3];
  x4 = &data[4];
  x5 = &data[5];
  x6 = &data[6];
  x7 = &data[7];

  xl0 = reinterpret_cast<std::uint32_t*>(&data[0]);
  xl1 = reinterpret_cast<std::uint32_t*>(&data[1]);
  xl2 = reinterpret_cast<std::uint32_t*>(&data[2]);
  xl3 = reinterpret_cast<std::uint32_t*>(&data[3]);
  xl4 = reinterpret_cast<std::uint32_t*>(&data[4]);
  xl5 = reinterpret_cast<std::uint32_t*>(&data[5]);
  xl6 = reinterpret_cast<std::uint32_t*>(&data[6]);
  xl7 = reinterpret_cast<std::uint32_t*>(&data[7]);

  xh0 = reinterpret_cast<std::uint32_t*>(&data[0]) + 1;
  xh1 = reinterpret_cast<std::uint32_t*>(&data[1]) + 1;
  xh2 = reinterpret_cast<std::uint32_t*>(&data[2]) + 1;
  xh3 = reinterpret_cast<std::uint32_t*>(&data[3]) + 1;
  xh4 = reinterpret_cast<std::uint32_t*>(&data[4]) + 1;
  xh5 = reinterpret_cast<std::uint32_t*>(&data[5]) + 1;
  xh6 = reinterpret_cast<std::uint32_t*>(&data[6]) + 1;
  xh7 = reinterpret_cast<std::uint32_t*>(&data[7]) + 1;

  xll0 = reinterpret_cast<std::uint16_t*>(&data[0]);
  xll1 = reinterpret_cast<std::uint16_t*>(&data[1]);
  xll2 = reinterpret_cast<std::uint16_t*>(&data[2]);
  xll3 = reinterpret_cast<std::uint16_t*>(&data[3]);

  xllh0 = reinterpret_cast<std::uint8_t*>(&data[0]) + 1;
  xllh1 = reinterpret_cast<std::uint8_t*>(&data[1]) + 1;
  xllh2 = reinterpret_cast<std::uint8_t*>(&data[2]) + 1;
  xllh3 = reinterpret_cast<std::uint8_t*>(&data[3]) + 1;

  xlll0 = reinterpret_cast<std::uint8_t*>(&data[0]);
  xlll1 = reinterpret_cast<std::uint8_t*>(&data[1]);
  xlll2 = reinterpret_cast<std::uint8_t*>(&data[2]);
  xlll3 = reinterpret_cast<std::uint8_t*>(&data[3]);

  xbp = &data[8];
  xsp = &data[9];
  xip = &data[10];
  xgdp = &data[11];
  xivt = &data[12];

  crf = false;
  ovf = false;
  udf = false;
  zrf = false;

  // TODO: Use std::bind instead of lambdas
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::HALT)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecHALT(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::ADD)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecADD(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::ADC)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecADC(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::AND)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecAND(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::ANDN)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecANDN(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::BSWAP)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecBSWAP(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CALL)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCALL(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CCRF)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCCRF(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::COVF)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCOVF(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CUDF)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCUDF(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::INC)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecINC(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::DEC)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecDEC(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::HID)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecHID(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::MUL)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecMUL(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::OR)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecOR(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::SUB)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecSUB(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::SHFL)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecSHFL(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::SHFR)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecSHFR(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::DIV)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecDIV(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::LOIVT)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecLOIVT(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::INTR)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecINTR(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::MOV)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecMOV(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::READ)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecREAD(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::WRITE)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecWRITE(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::JMP)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecJMP(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::PUSH)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecPUSH(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::POP)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecPOP(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CALLE)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCALLE(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CALLGR)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCALLGR(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CALLL)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCALLL(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::JME)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecJME(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::JMGR)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecJMGR(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::JML)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecJML(instr, op1, op2); };
  opcode_handler_assoc[static_cast<std::uint16_t>(HyperCPU::Opcode::CMP)] =
      [this](const IInstruction& instr, OperandContainer op1, OperandContainer op2) -> void { this->ExecCMP(instr, op1, op2); };

  read_io_handlers[0] = io_ctl->GetGetchar();

  write_io_handlers[0] = io_ctl->GetPutchar();

  m_decoder = std::make_unique<Decoder>(mem_controller, xip, this);
  if (binary) {
    std::memcpy(mem_controller->get_ptr(), binary, binary_size);
  }
}

HyperCPU::CPU::~CPU() {
  delete mem_controller;
}

/*
void HyperCPU::CPU::DecodingThread() {
  bool skip_decoding_cycle = false;
  bool current = false;
  while (!halted) {
    if (skip_decoding_cycle) {
      skip_decoding_cycle = false;

      // Wait for executor thread to execute instruction
      current = buffer_used.load(std::memory_order_acquire);
      while (current) {
        buffer_used.wait(current, std::memory_order_acquire);
        current = buffer_used.load(std::memory_order_acquire);
      }
      continue;
    }

    if (pending_interrupt.has_value()) {
      while (current) {
        buffer_used.wait(current, std::memory_order_acquire);
        current = buffer_used.load(std::memory_order_acquire);
      }
      StackPush64(*xip);
      *xip = pending_interrupt.value();
      pending_interrupt.reset();
      continue;
    }

    _buffer = m_decoder->FetchAndDecode();

    switch (_buffer.m_opcode) {
      case CALL:
      case JMP:
      case HALT:
        skip_decoding_cycle = true;
        break;
      case _CONT:
        continue;
      default:
        break;
    }

    if (interrupt_active.load(std::memory_order_acquire)) {
      skip_decoding_cycle = false;
      continue;
    } else if (buffer_used.load(std::memory_order_acquire)) {
      current = buffer_used.load(std::memory_order_acquire);
      while (current) {
        buffer_used.wait(current, std::memory_order_acquire);
        current = buffer_used.load(std::memory_order_acquire);
      }
    }

    std::swap(buffer, _buffer);

    buffer_used.store(true, std::memory_order_release);
    buffer_used.notify_one();
  }
}

void HyperCPU::CPU::ExecutingThread() {
  while (!halted) {
    bool current = buffer_used.load(std::memory_order_acquire);
    while (!current) {
      buffer_used.wait(current, std::memory_order_acquire);
      current = buffer_used.load(std::memory_order_acquire);
    }

    std::pair<OperandContainer, OperandContainer> operands = GetOperands(buffer.m_op_types, buffer.m_opcode_mode, buffer.m_op1, buffer.m_op2);
    opcode_handler_assoc[static_cast<std::uint16_t>(buffer.m_opcode)](buffer, operands.first, operands.second);

    buffer_used.store(false, std::memory_order_release);
    buffer_used.notify_one();
  }
}
*/

void HyperCPU::CPU::Run() {
  /*
  std::thread decoder_thread(std::bind(&CPU::DecodingThread, this));
  std::thread executor_thread(std::bind(&CPU::ExecutingThread, this));

  decoder_thread.join();
  executor_thread.join();
  */

  bool skip_decoding_cycle = false;
  while (!halted) {
    if (skip_decoding_cycle) {
      skip_decoding_cycle = false;
      continue;
    }

    if (pending_interrupt.has_value()) {
      StackPush64(*xip);
      *xip = pending_interrupt.value();
      pending_interrupt.reset();
      continue;
    }
    
    if ((*xip) >= binary_size) {
      halted = true;
      break;
    }

    buffer = m_decoder->FetchAndDecode();

    switch (buffer.m_opcode) {
    case HyperCPU::Opcode::_CONT:
      continue;
    case HyperCPU::Opcode::IRET:
      *xip = StackPop64();
      continue;
    default:
      break;
    }

    std::pair<OperandContainer, OperandContainer> operands = GetOperands(buffer.m_op_types, buffer.m_opcode_mode, buffer.m_op1, buffer.m_op2);
    opcode_handler_assoc[static_cast<std::uint16_t>(buffer.m_opcode)](buffer, operands.first, operands.second);
  }
}

bool HyperCPU::CPU::CanExecuteInterrupts() {
  return *xivt != 0;
}

void HyperCPU::CPU::SetEntryPoint(std::uint32_t entry_point) {
  *xip = entry_point;
}
