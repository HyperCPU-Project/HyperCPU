#include "fixtures.hpp"

TEST_F(FULL_ASSEMBLER, MULTUPLE_INSTRUCTIONS) {
  std::string data = "_start:\n\tmov x0, 0u1;\n\tmov x1, 0u2;\n\tadd x0, x1;";
  std::uint32_t code_size;
  auto binary = compiler.Compile(data, code_size);

  {
    std::ofstream file("test", std::ios::binary);

    HCAsm::WriteResultFile(HyperCPU::FileType::Binary, binary, file, code_size, 0);
  }

  std::ifstream input("test");

  HyperCPU::GenericHeader hdr;
  input.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));
  ASSERT_EQ(hdr.magic, HyperCPU::magic);
  ASSERT_EQ(hdr.code_size, code_size);
  ASSERT_EQ(hdr.type, HyperCPU::FileType::Binary);
  ASSERT_EQ(hdr.version, HyperCPU::Version::PreRelease);
  ASSERT_EQ(std::filesystem::file_size("test"), code_size + sizeof(HyperCPU::GenericHeader));

  auto buf = new char[code_size];
  input.read(buf, code_size);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 2), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R_IMM));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 3), HyperCPU::Reg::X0);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 4), 1);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 12), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 14), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R_IMM));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 15), HyperCPU::Reg::X1);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 16), 2);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 24), HyperCPU::Opcode::ADD);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 26), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R_R));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 27), HyperCPU::Reg::X0);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 28), HyperCPU::Reg::X1);

  delete[] buf;
}

TEST_F(FULL_ASSEMBLER, IRET) {
  std::string data = "mov xbp, 0u512; mov xsp, xbp; push b64 hlt; iret; hlt: halt;";
  std::uint32_t code_size;
  auto binary = compiler.Compile(data, code_size);

  {
    std::ofstream file("test", std::ios::binary);

    HCAsm::WriteResultFile(HyperCPU::FileType::Binary, binary, file, code_size, 0);
  }

  std::ifstream input("test");

  HyperCPU::GenericHeader hdr;
  input.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));
  ASSERT_EQ(hdr.magic, HyperCPU::magic);
  ASSERT_EQ(hdr.code_size, code_size);
  ASSERT_EQ(hdr.type, HyperCPU::FileType::Binary);
  ASSERT_EQ(hdr.version, HyperCPU::Version::PreRelease);
  ASSERT_EQ(std::filesystem::file_size("test"), code_size + sizeof(HyperCPU::GenericHeader));

  auto buf = new char[code_size];
  input.read(buf, code_size);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 2), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R_IMM));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 3), HyperCPU::Reg::XBP);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 4), 512);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 12), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 14), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R_R));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 15), HyperCPU::Reg::XSP);
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 16), HyperCPU::Reg::XBP);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 17), HyperCPU::Opcode::PUSH);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 19), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::IMM));
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint64_t>(buf + 20), 30);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 28), HyperCPU::Opcode::IRET);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 30), HyperCPU::Opcode::HALT);

  delete[] buf;
}

TEST_F(FULL_ASSEMBLER, LODSB) {
  std::string data = "lodsb xll0, 0s-16; halt;";
  std::uint32_t code_size;
  auto binary = compiler.Compile(data, code_size);

  {
    std::ofstream file("test", std::ios::binary);

    HCAsm::WriteResultFile(HyperCPU::FileType::Binary, binary, file, code_size, 0);
  }

  std::ifstream input("test");

  HyperCPU::GenericHeader hdr;
  input.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));
  ASSERT_EQ(hdr.magic, HyperCPU::magic);
  ASSERT_EQ(hdr.code_size, code_size);
  ASSERT_EQ(hdr.type, HyperCPU::FileType::Binary);
  ASSERT_EQ(hdr.version, HyperCPU::Version::PreRelease);
  ASSERT_EQ(std::filesystem::file_size("test"), code_size + sizeof(HyperCPU::GenericHeader));

  auto buf = new char[code_size];
  input.read(buf, code_size);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 2), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R_IMM));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 3), HyperCPU::Reg::XFST);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::int64_t>(buf + 4), -16);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 12), HyperCPU::Opcode::LODSB);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 14), (static_cast<std::uint8_t>(HyperCPU::Mode::b16) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 15), HyperCPU::Reg::XLL0);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 16), HyperCPU::Opcode::HALT);

  delete[] buf;
}

TEST_F(FULL_ASSEMBLER, STDSB) {
  std::string data = "stdsb xll0, 0s-16; halt;";
  std::uint32_t code_size;
  auto binary = compiler.Compile(data, code_size);

  {
    std::ofstream file("test", std::ios::binary);

    HCAsm::WriteResultFile(HyperCPU::FileType::Binary, binary, file, code_size, 0);
  }

  std::ifstream input("test");

  HyperCPU::GenericHeader hdr;
  input.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));
  ASSERT_EQ(hdr.magic, HyperCPU::magic);
  ASSERT_EQ(hdr.code_size, code_size);
  ASSERT_EQ(hdr.type, HyperCPU::FileType::Binary);
  ASSERT_EQ(hdr.version, HyperCPU::Version::PreRelease);
  ASSERT_EQ(std::filesystem::file_size("test"), code_size + sizeof(HyperCPU::GenericHeader));

  auto buf = new char[code_size];
  input.read(buf, code_size);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf), HyperCPU::Opcode::MOV);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 2), (static_cast<std::uint8_t>(HyperCPU::Mode::b64) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R_IMM));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 3), HyperCPU::Reg::XFST);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::int64_t>(buf + 4), -16);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 12), HyperCPU::Opcode::STDSB);
  ASSERT_EQ(HyperCPU::bit_cast_from<std::uint8_t>(buf + 14), (static_cast<std::uint8_t>(HyperCPU::Mode::b16) << 4) | static_cast<std::uint8_t>(HyperCPU::OperandTypes::R));
  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Reg>(buf + 15), HyperCPU::Reg::XLL0);

  ASSERT_EQ(HyperCPU::bit_cast_from<HyperCPU::Opcode>(buf + 16), HyperCPU::Opcode::HALT);

  delete[] buf;
}