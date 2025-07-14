#include "PCH/CStd.hpp"

#include "Emulator/Core/CPU/Assert.hpp"
#include "Emulator/Core/CPU/CPU.hpp"
#include "Emulator/Core/MemoryController/MemoryControllerST.hpp"

void HyperCPU::CPU::StackPush8(std::uint8_t val) noexcept {
  h_assert(*xsp > 1, { std::cout << "Stack pointer too low!\n"; exit(1); });

  *xsp -= 1;
  mem_controller->Load(*xsp, val);
}

void HyperCPU::CPU::StackPush16(std::uint16_t val) noexcept {
  h_assert(*xsp > 2, { std::cout << "Stack pointer too low!\n"; exit(1); });

  *xsp -= 2;
  mem_controller->Load(*xsp, val);
}

void HyperCPU::CPU::StackPush32(std::uint32_t val) noexcept {
  h_assert(*xsp > 4, { std::cout << "Stack pointer too low!\n"; exit(1); });

  *xsp -= 4;
  mem_controller->Load(*xsp, val);
}

void HyperCPU::CPU::StackPush64(std::uint64_t val) noexcept {
  h_assert(*xsp > 8, { std::cout << "Stack pointer too low!\n"; exit(1); });

  *xsp -= 8;
  mem_controller->Load(*xsp, val);
}

std::uint8_t HyperCPU::CPU::StackPop8() noexcept {
  h_assert((*xsp + 1) <= *xbp, { std::cout << "Stack pointer too high!\n"; exit(1); });

  std::uint8_t val = mem_controller->Read<std::uint8_t>(*xsp);
  *xsp += 1;
  return val;
}

std::uint16_t HyperCPU::CPU::StackPop16() noexcept {
  h_assert((*xsp + 2) <= *xbp, { std::cout << "Stack pointer too high!\n"; exit(1); });

  std::uint16_t val = mem_controller->Read<std::uint16_t>(*xsp);
  *xsp += 2;
  return val;
}

std::uint32_t HyperCPU::CPU::StackPop32() noexcept {
  h_assert((*xsp + 4) <= *xbp, { std::cout << "Stack pointer too high!\n"; exit(1); });

  std::uint32_t val = mem_controller->Read<std::uint32_t>(*xsp);
  *xsp += 4;
  return val;
}

std::uint64_t HyperCPU::CPU::StackPop64() noexcept {
  h_assert((*xsp + 8) <= *xbp, { std::cout << "Stack pointer too high!\n"; exit(1); });

  std::uint64_t val = mem_controller->Read<std::uint64_t>(*xsp);
  *xsp += 8;
  return val;
}
