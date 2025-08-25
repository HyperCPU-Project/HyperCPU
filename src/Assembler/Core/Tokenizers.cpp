#include "Assembler/Core/Compiler.hpp"
#include "PCH/CStd.hpp"
#include "Pog/Pog.hpp"

using HCAsm::Value;

[[gnu::visibility("hidden")]]
std::uint64_t BinaryStrToUint64(std::string_view& binary_str) {
  binary_str.remove_prefix(2);
  if (binary_str.length() > 64) {
    throw std::invalid_argument("Binary string is too long to fit in a uint64_t");
  }

  std::uint64_t result = 0;
  for (char c : binary_str) {
    if (c != '0' && c != '1') {
      if (c == 'b') {
        break;
      }
      throw std::invalid_argument("Invalid character in binary string");
    }
    result = (result << 1) | (c - '0');
  }
  return result;
}

Value HCAsm::TokenizeSignedInt(std::string_view str) {
  return {std::stol(str.begin() + 2)};
}

Value HCAsm::TokenizeUnsignedInt(std::string_view str) {
  return {std::stoull(str.begin() + 2)};
}

Value HCAsm::TokenizeString(std::string_view str) {
  std::string res;
  res.reserve(str.length());

  bool escape = false;
  for (char c : str.substr(1, str.length() - 2)) {
    if (!escape) {
      if (c == '\\') {
        escape = true;
      } else {
        res.push_back(c);
      }
    } else {
      switch (c) {
      case 'n':
        res.push_back('\n');
        break;
      case 'r':
        res.push_back('\r');
        break;
      case '\\':
        res.push_back('\\');
        break;
      case '0':
        res.push_back('\0');
        break;
      case 'e':
        res.push_back(0x1B);
        break;
      case 'b':
        res.push_back('\b');
        break;
      case 't':
        res.push_back('\t');
        break;
      case '\n':
        break;
      default:
        res.push_back(c);
        break;
      }
      escape = false;
    }
  }
  return {res};
}

Value HCAsm::TokenizeIdentifier(std::string_view str) {
  return {std::string{str}};
}

Value HCAsm::TokenizeChar(std::string_view str) {
  return {static_cast<std::uint64_t>(str[1])};
}

Value HCAsm::TokenizeHexadecimal(std::string_view str) {
  std::uint64_t x = 0;
  std::stringstream ss;
  ss << std::hex << str.begin() + 2;
  ss >> x;
  return {x};
}

Value HCAsm::TokenizeBinary(std::string_view str) {
  return {BinaryStrToUint64(str)};
}
