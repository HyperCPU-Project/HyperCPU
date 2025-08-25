#include <argparse/argparse.hpp>
#include <mapbox/eternal.hpp>
#include <spdlog/spdlog.h>

#include "Assembler/Core/Compiler.hpp"
#include "Common/NotImplemented.hpp"
#include "PCH/CStd.hpp"
#include "Pog/Pog.hpp"

#ifdef HCPU_ENABLE_LIBUNWIND
#include "BacktraceProvider/BacktraceProvider.hpp"
#endif

std::string CreateObjectFilename(std::string str) {
  std::size_t lastDotPos = str.rfind('.');
  if (lastDotPos != std::string::npos) {
    str.replace(lastDotPos + 1, str.length() - lastDotPos - 1, "o");
  }
  return str;
}

int main(int argc, char** argv) {
#ifdef HCPU_ENABLE_LIBUNWIND
  global_bt_controller = BacktraceController(argv[0]);

  std::signal(SIGSEGV, SignalHandler);
  std::signal(SIGFPE, SignalHandler);
#endif
  argparse::ArgumentParser program("hcasm");
  program.add_argument("source")
      .help("source file to be assembled")
      .required();
  program.add_argument("-o")
      .help("name of the binary file");
  program.add_argument("-c")
      .help("compile to object file")
      .default_value(false)
      .implicit_value(true);
  program.add_argument("-V")
      .default_value(std::string{"warning"})
      .help("set verbosity level. possible modes:\n- debug\n- info\n- warning\n- error");

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& err) {
    std::cerr << err.what() << '\n';
    return 1;
  }

  auto source = program.get<std::string>("source");
  std::string result;
  if (program.present("-o")) {
    result = program.get<std::string>("-o");
  } else {
    result = CreateObjectFilename(source);
    if (result == source) {
      result += ".o";
    }
  }

  if (program["-c"] == true) {
    HyperCPU::PrintUnsupported("Compilation to object files is not implemented!");
  }

  HCAsm::HCAsmCompiler compiler;

  // Verify that files are available
  if (!std::filesystem::is_regular_file(source)) {
    spdlog::error("Source file \"{}\" is not a regular file!", source);
    return 1;
  }

  std::ifstream src(source);
  std::ofstream dst(result, std::ios::binary | std::ios::ate);
  if (!src.is_open()) {
    spdlog::error("Failed to open source file!");
    return 1;
  }

  spdlog::error("Source and destination files handles acquired");
  HyperCPU::GenericHeader hdr{};
  src.read(reinterpret_cast<char*>(&hdr), sizeof(hdr));
  if (hdr.magic == HyperCPU::magic) {
    HyperCPU::PrintUnsupported("Linking object files is not implemented!");
  }
  src.close();
  src.open(source);

  std::string contents(
      (std::istreambuf_iterator<char>(src)),
      std::istreambuf_iterator<char>());

  std::uint32_t code_size = 0;

  auto binary = compiler.Compile(contents, code_size);

  HCAsm::WriteResultFile(HyperCPU::FileType::Binary, binary, dst, code_size, binary.entry_point);
}
