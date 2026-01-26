#include "Tokenizer.hpp"
#include <stdexcept>

#include "mapbox/eternal.hpp"

static constexpr auto ident_assoc = mapbox::eternal::map<mapbox::eternal::string, HCAsm::TokenType>({
      {"adc", HCAsm::TokenType::ADC},
      {"add", HCAsm::TokenType::ADD},
      {"and", HCAsm::TokenType::AND},
      {"andn", HCAsm::TokenType::ANDN},
      {"bswap", HCAsm::TokenType::BSWAP},
      {"call", HCAsm::TokenType::CALL},
      {"ccrf", HCAsm::TokenType::CCRF},
      {"covf", HCAsm::TokenType::COVF},
      {"cudf", HCAsm::TokenType::CUDF},
      {"hid", HCAsm::TokenType::HID},
      {"inc", HCAsm::TokenType::INC},
      {"dec", HCAsm::TokenType::DEC},
      {"div", HCAsm::TokenType::DIV},
      {"mul", HCAsm::TokenType::MUL},
      {"sub", HCAsm::TokenType::SUB},
      {"shfr", HCAsm::TokenType::SHFR},
      {"shfl", HCAsm::TokenType::SHFL},
      {"or", HCAsm::TokenType::OR},
      {"halt", HCAsm::TokenType::HALT},
      {"loivt", HCAsm::TokenType::LOIVT},
      {"intr", HCAsm::TokenType::INTR},
      //{"ret", HCAsm::TokenType::RET},
      {"iret", HCAsm::TokenType::IRET},
      {"mov", HCAsm::TokenType::MOV},
      {"read", HCAsm::TokenType::READ},
      {"write", HCAsm::TokenType::WRITE},
      {"jmp", HCAsm::TokenType::JMP},
      {"push", HCAsm::TokenType::PUSH},
      {"pop", HCAsm::TokenType::POP},
      {"calle", HCAsm::TokenType::CALLE},
      {"callgr", HCAsm::TokenType::CALLGR},
      {"calll", HCAsm::TokenType::CALLL},
      {"jme", HCAsm::TokenType::JME},
      {"jmgr", HCAsm::TokenType::JMGR},
      {"jml", HCAsm::TokenType::JML},
      {"cmp", HCAsm::TokenType::CMP},
      {"lodsb", HCAsm::TokenType::LODSB},
      {"stdsb", HCAsm::TokenType::STDSB},
      {"attr", HCAsm::TokenType::ATTR},
      {"x0",   HCAsm::TokenType::X0},
      {"x1",   HCAsm::TokenType::X1},
      {"x2",   HCAsm::TokenType::X2},
      {"x3",   HCAsm::TokenType::X3},
      {"x4",   HCAsm::TokenType::X4},
      {"x5",   HCAsm::TokenType::X5},
      {"x6",   HCAsm::TokenType::X6},
      {"x7",   HCAsm::TokenType::X7},
      {"xh0",  HCAsm::TokenType::XH0},
      {"xh1",  HCAsm::TokenType::XH1},
      {"xh2",  HCAsm::TokenType::XH2},
      {"xh3",  HCAsm::TokenType::XH3},
      {"xh4",  HCAsm::TokenType::XH4},
      {"xh5",  HCAsm::TokenType::XH5},
      {"xh6",  HCAsm::TokenType::XH6},
      {"xh7",  HCAsm::TokenType::XH7},
      {"xl0",  HCAsm::TokenType::XL0},
      {"xl1",  HCAsm::TokenType::XL1},
      {"xl2",  HCAsm::TokenType::XL2},
      {"xl3",  HCAsm::TokenType::XL3},
      {"xl4",  HCAsm::TokenType::XL4},
      {"xl5",  HCAsm::TokenType::XL5},
      {"xl6",  HCAsm::TokenType::XL6},
      {"xl7",  HCAsm::TokenType::XL7},
      {"xll0",  HCAsm::TokenType::XLL0},
      {"xll1",  HCAsm::TokenType::XLL1},
      {"xll2",  HCAsm::TokenType::XLL2},
      {"xll3",  HCAsm::TokenType::XLL3},
      {"xllh0", HCAsm::TokenType::XLLH0},
      {"xllh1", HCAsm::TokenType::XLLH1},
      {"xllh2", HCAsm::TokenType::XLLH2},
      {"xllh3", HCAsm::TokenType::XLLH3},
      {"xlll0", HCAsm::TokenType::XLLL0},
      {"xlll1", HCAsm::TokenType::XLLL1},
      {"xlll2", HCAsm::TokenType::XLLL2},
      {"xlll3", HCAsm::TokenType::XLLL3},
      {"xbp",  HCAsm::TokenType::XBP},
      {"xsp",  HCAsm::TokenType::XSP},
      {"xip",  HCAsm::TokenType::XIP},
      {"xgdp", HCAsm::TokenType::XGDP},
      {"xivt", HCAsm::TokenType::XIVT},
      {"xfst", HCAsm::TokenType::XFST}
});

char HCAsm::Tokenizer::Peek(std::uint8_t offset) {
  if (cur_raw_offset + offset > source.size()) {
    return '\0';
  }
  return source[cur_raw_offset + offset];
}

void HCAsm::Tokenizer::Advance() {
  char ch = Peek();
  if (source[cur_raw_offset++] == '\n') {
    ++cur_line;
    cur_offset = 0;
  } else {
    ++cur_offset;
  }
}

bool HCAsm::Tokenizer::SkipWhitespace() {
  bool has_effect = false;
  while (true) {
    switch (Peek(0)) {
    case '\n':
    case ' ':
    case '\t':
      Advance();
      has_effect = true;
      continue;
    case '\0':
    default:
      break;
    }
    break;
  }
  return has_effect;
}

bool HCAsm::Tokenizer::SkipComments() {
  char ch = Peek(0);
  bool has_effect = false;
  bool comment = true;

  if (!ch) {
    return false;
  }
  if (ch == '/' && Peek() == '*') {
    Advance();
    Advance();

    while (comment) {
      switch (Peek(0)) {
      case '*':
        if (Peek() == '/' || Peek() == '\0') {
          Advance();
          Advance();
          comment = false;
        }
        break;
      case '\0':
        comment = false;
        break;
      default:
        Advance();
        has_effect = true;
        continue;
      }
    }
    return true;
  } else if (ch == '/' && Peek() == '/') {
    Advance();
    Advance();

    while (comment) {
      switch (Peek(0)) {
      case '\0':
        comment = false;
        break;
      case '\n':
        Advance();
        comment = false;
        break;
      default:
        Advance();
        has_effect = true;
        continue;
      }
      break;
    }
  }
  return false;
}

HCAsm::Token HCAsm::Tokenizer::GetNextToken() {
  TokenizerState state = TokenizerState::START;
  std::string lexeme;
  bool running = true;

  while (SkipComments() || SkipWhitespace());

  while (running) {
    char ch = Peek(0);
    switch (state) {
    case TokenizerState::START:
      if (std::isalpha(ch)) {
        state = TokenizerState::IDENT;
        lexeme.push_back(ch);
        Advance();
        continue;
      }
      if (ch == '0') {
        state = TokenizerState::START_INT_LIT;
        lexeme.push_back(ch);
        Advance();
        continue;
      }
      switch (ch) {
      case '"':
        state = TokenizerState::STRING_LIT;
        Advance();
        continue;
      case '\'':
        state = TokenizerState::CHAR_LIT;
        Advance();
        continue;
      case '\0':
        Advance();
        return CreateToken(TokenType::END_OF_FILE, {});
      default:
        Advance();
        return CreateToken(static_cast<TokenType>(ch), {});
      }
      break;
    case TokenizerState::IDENT:
      if (ch == '_' || std::isalnum(ch)) {
        lexeme.push_back(ch);
        Advance();
      } else {
        if (ident_assoc.contains(lexeme.c_str())) {
          return CreateToken(ident_assoc.at(lexeme.c_str()), lexeme);
        }
        return CreateToken(TokenType::IDENTIFIER, lexeme);
      }
      break;
    case TokenizerState::STRING_LIT:
      if (ch != '"') {
        lexeme.push_back(ch);
        Advance();
      } else {
        Advance();
        return CreateToken(TokenType::STRING_LITERAL, lexeme);
      }
      break;
    case TokenizerState::START_INT_LIT:
      switch (ch) {
      case '.':
        lexeme.push_back(ch);
        state = TokenizerState::FLOAT_LIT;
        break;
      case 's':
        lexeme.clear();
        state = TokenizerState::SINT_LIT;
        break;
      case 'u':
        lexeme.clear();
        state = TokenizerState::UINT_LIT;
        break;
      case 'x':
        lexeme.clear();
        state = TokenizerState::HEX_LIT;
        break;
      case 'b':
        lexeme.clear();
        state = TokenizerState::BINARY_LIT;
        break;
      default:
        //TODO: handle error
        std::abort();
      }
      break;
    case TokenizerState::FLOAT_LIT:
      if (ch == '.') {
        throw std::runtime_error("Multiple dots in a float literal");
      }
      if (std::isdigit(ch)) {
        lexeme.push_back(ch);
        Advance();
      } else {
        return CreateToken(TokenType::FLOAT_LITERAL, lexeme);
      }
      break;
    case TokenizerState::SINT_LIT:
      if (std::isdigit(ch)) {
        lexeme.push_back(ch);
        Advance();
      } else {
        return CreateToken(TokenType::SINT_LITERAL, lexeme);
      }
      break;
    case TokenizerState::UINT_LIT:
      if (std::isdigit(ch)) {
        lexeme.push_back(ch);
        Advance();
      } else {
        return CreateToken(TokenType::UINT_LITERAL, lexeme);
      }
      break;
    case TokenizerState::BINARY_LIT:
      if (std::isdigit(ch)) {
        lexeme.push_back(ch);
        Advance();
      } else {
        return CreateToken(TokenType::UINT_LITERAL, std::string {
          std::to_string(std::stoul(lexeme, nullptr, 2))
        });
      }
      break;
    case TokenizerState::HEX_LIT:
      if (std::isdigit(ch)) {
        lexeme.push_back(ch);
        Advance();
      } else {
        return CreateToken(TokenType::UINT_LITERAL, std::string {
          std::to_string(std::stoul(lexeme, nullptr, 16))
        });
      }
      break;
    case TokenizerState::CHAR_LIT:
      lexeme.push_back(ch);
      if (Peek() != '\'') {
        throw std::runtime_error{"Not closed char lit"};
      }
      Advance();
      return CreateToken(TokenType::CHAR_LITERAL, lexeme);
    default:
      std::abort();
    }
  }
}

HCAsm::Token HCAsm::Tokenizer::CreateToken(TokenType type, std::string lexeme) {
  return Token{type, CreateSourceLocation(), std::move(lexeme)};
}

HCAsm::SourceLocation HCAsm::Tokenizer::CreateSourceLocation() {
  return SourceLocation{cur_line, cur_offset, cur_raw_offset};
}

std::vector<HCAsm::Token> HCAsm::Tokenizer::Tokenize() {
  std::vector<Token> tokens;
  Token tok;
  do {
    tok = GetNextToken();
    tokens.emplace_back(std::move(tok));
  } while (tok.type != TokenType::END_OF_FILE);
  return tokens;
}
