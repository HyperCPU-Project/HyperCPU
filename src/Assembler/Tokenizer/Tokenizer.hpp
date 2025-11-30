#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace HCAsm {
    enum class TokenType : std::uint16_t {
        /* Keywords */
        ATTR = 1,

        /* Instructions */
        ADC = 10,
        ADD = 11,
        AND = 12,
        ANDN = 13,
        BSWAP = 14,
        CALL = 15,
        CCRF = 16,
        COVF = 17,
        CUDF = 18,
        HID = 19,
        INC = 20,
        DEC = 21,
        DIV = 22,
        MUL = 23,
        SUB = 24,
        SHFR = 25,
        SHFL = 26,
        OR = 27,
        HALT = 28,
        LOIVT = 29,
        INTR = 30,
        MOV = 31,
        READ = 32,
        WRITE = 33,
        JMP = 34,
        PUSH = 35,
        POP = 36,
        CALLE = 37,
        CALLGR = 38,
        CALLL = 39,
        JME = 40,
        JMGR = 41,
        JML = 42,
        CMP = 43,
        LODSB = 44,
        STDSB = 45,
        IRET = 46,

        /* Registers */
        X0 = 400,
        X1 = 401,
        X2 = 402,
        X3 = 403,
        X4 = 404,
        X5 = 405,
        X6 = 406,
        X7 = 407,
        XH0 = 408,
        XH1 = 409,
        XH2 = 410,
        XH3 = 411,
        XH4 = 412,
        XH5 = 413,
        XH6 = 414,
        XH7 = 415,
        XL0 = 416,
        XL1 = 417,
        XL2 = 418,
        XL3 = 419,
        XL4 = 420,
        XL5 = 421,
        XL6 = 422,
        XL7 = 423,
        XLL0 = 424,
        XLL1 = 425,
        XLL2 = 426,
        XLL3 = 427,
        XLLH0 = 428,
        XLLH1 = 429,
        XLLH2 = 430,
        XLLH3 = 431,
        XLLL0 = 432,
        XLLL1 = 433,
        XLLL2 = 434,
        XLLL3 = 435,
        XBP = 436,
        XSP = 437,
        XIP = 438,
        XGDP = 439,
        XIVT = 440,
        XFST = 441,


        /* Characters */
        SEMICOLON = ';',
        COLON = ':',
        OPEN_PARENTHESIS = '(',
        CLOSE_PARENTHESIS = ')',
        BACKSLASH = '\\',
        DOT = '.',
        COMMA = ',',
        EQUAL = '=',
        SINGLE_QUOTE = '\'',
        DOUBLE_QUOTE = '"',
        END_OF_FILE = 201,

        IDENTIFIER = 202,
        INT_LITERAL = 203,
        FLOAT_LITERAL = 204,
        STRING_LITERAL = 205,
    };

    enum class TokenizerState {
      START,
      END_OF_FILE,
      IDENT,
      STRING_LIT,
      INT_LIT,
      FLOAT_LIT
    };

    struct SourceLocation {
    public:
      SourceLocation()
        : line(0)
        , offset(0)
        , raw_offset(0) {}
      SourceLocation(std::uint32_t _line, std::uint32_t _offset, std::uint64_t _raw_offset)
        : line(_line)
        , offset(_offset)
        , raw_offset(_raw_offset) {}
      std::uint32_t GetLine();
      std::uint32_t GetOffset();
      std::uint64_t GetRawOffset();

    private:
      std::uint32_t line;
      std::uint32_t offset;
      std::uint64_t raw_offset;
    };

    struct Token {
        TokenType type;
        SourceLocation source_loc;
        std::string lexeme;
    };

    class Tokenizer {
    public:
        Tokenizer(std::string& str) : source(str) {}
        std::vector<Token> Tokenize();
    private:
        Token GetNextToken();
        Token CreateToken(TokenType type, std::string lexeme);
        SourceLocation CreateSourceLocation();
        bool SkipWhitespace();
        bool SkipComments();

        char Peek(std::uint8_t offset = 1);
        void Advance();
        std::uint64_t GetCurOffset();

        std::string& source;
        std::uint64_t cur_raw_offset = 0;
        std::uint32_t cur_line = 1;
        std::uint32_t cur_offset = 0;
    };
};
