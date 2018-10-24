#pragma once

#include <string_view>
#include <ostream>

enum Type {
  TOK_NONE = 0,
  TOK_HASH = '#',
  TOK_EXCL = '!',
  TOK_KEYWORD_not = TOK_EXCL,
  TOK_PERCENT = '%',
  TOK_CARET = '^',
  TOK_KEYWORD_xor = TOK_CARET,
  TOK_TILDE = '~',
  TOK_KEYWORD_compl = TOK_TILDE,
  TOK_LANGLE = '<',
  TOK_EQUALS = '=',
  TOK_RANGLE = '>',
  TOK_MINUS = '-',
  TOK_COMMA = ',',
  TOK_PIPE = '|',
  TOK_KEYWORD_bitor = TOK_PIPE,
  TOK_SEMICOLON = ';',
  TOK_COLON = ':',
  TOK_SCOPE = ':' | 0x80,
  TOK_QUESTION = '?',
  TOK_SLASH = '/',
  TOK_SLASH_EQ = 0x80 | '/',
  TOK_DOT = '.',
  TOK_DOT_STAR = '.' | 0x80,
  TOK_LPAREN = '(',
  TOK_RPAREN = ')',
  TOK_LBRACKET = '[',
  TOK_RBRACKET = ']',
  TOK_LCURLY = '{',
  TOK_RCURLY = '}',
  TOK_STAR = '*',
  TOK_AMP = '&',
  TOK_KEYWORD_bitand = TOK_AMP,
  TOK_PLUS = '+',
  TOK_CARET_EQ = 0x80 | '^',
  TOK_KEYWORD_xor_eq = TOK_CARET_EQ,
  TOK_TILDE_EQ = 0x80 | '~',
  TOK_LANGLE_EQ = 0x80 | '<',
  TOK_EQUALS_EQ = 0x80 | '=',
  TOK_RANGLE_EQ = 0x80 | '>',
  TOK_PIPE_EQ = 0x80 | '|',
  TOK_KEYWORD_or_eq = TOK_PIPE_EQ,
  TOK_MINUS_EQ = 0x80 | '-',
  TOK_EXCL_EQ = 0x80 | '!',
  TOK_KEYWORD_not_eq = TOK_EXCL_EQ,
  TOK_STAR_EQ = 0x80 | '*',
  TOK_AMP_EQ = 0x80 | '&',
  TOK_KEYWORD_and_eq = TOK_AMP_EQ,
  TOK_PERCENT_EQ = 0x80 | '%',
  TOK_PLUS_EQ = 0x80 | '+',
  TOK_LEFTSHIFT = 0x100,
  TOK_LEFTSHIFT_EQ,
  TOK_RIGHTSHIFT,
  TOK_RIGHTSHIFT_EQ,
  TOK_ARROW,
  TOK_ARROW_STAR,
  TOK_AMP_AMP,
  TOK_KEYWORD_and = TOK_AMP_AMP,
  TOK_PIPE_PIPE,
  TOK_KEYWORD_or = TOK_PIPE_PIPE,
  TOK_INCREMENT,
  TOK_DECREMENT,
  TOK_SPACESHIP,
  TOK_STRING,
  TOK_CHAR,
  TOK_NUMBER,
  TOK_IDENTIFIER,
  TOK_KEYWORD_alignas,
  TOK_KEYWORD_alignof,
  TOK_KEYWORD_asm,
  TOK_KEYWORD_auto,
  TOK_KEYWORD_bool,
  TOK_KEYWORD_break,
  TOK_KEYWORD_case,
  TOK_KEYWORD_catch,
  TOK_KEYWORD_char,
  TOK_KEYWORD_char16_t,
  TOK_KEYWORD_char32_t,
  TOK_KEYWORD_class,
  TOK_KEYWORD_const,
  TOK_KEYWORD_constexpr,
  TOK_KEYWORD_const_cast,
  TOK_KEYWORD_continue,
  TOK_KEYWORD_decltype,
  TOK_KEYWORD_default,
  TOK_KEYWORD_delete,
  TOK_KEYWORD_do,
  TOK_KEYWORD_double,
  TOK_KEYWORD_dynamic_cast,
  TOK_KEYWORD_else,
  TOK_KEYWORD_enum,
  TOK_KEYWORD_explicit,
  TOK_KEYWORD_extern,
  TOK_KEYWORD_false,
  TOK_KEYWORD_float,
  TOK_KEYWORD_for,
  TOK_KEYWORD_friend,
  TOK_KEYWORD_goto,
  TOK_KEYWORD_if,
  TOK_KEYWORD_inline,
  TOK_KEYWORD_int,
  TOK_KEYWORD_long,
  TOK_KEYWORD_mutable,
  TOK_KEYWORD_namespace,
  TOK_KEYWORD_new,
  TOK_KEYWORD_noexcept,
  TOK_KEYWORD_nullptr,
  TOK_KEYWORD_operator,
  TOK_KEYWORD_private,
  TOK_KEYWORD_protected,
  TOK_KEYWORD_public,
  TOK_KEYWORD_register,
  TOK_KEYWORD_reinterpret_cast,
  TOK_KEYWORD_return,
  TOK_KEYWORD_short,
  TOK_KEYWORD_signed,
  TOK_KEYWORD_sizeof,
  TOK_KEYWORD_static,
  TOK_KEYWORD_static_assert,
  TOK_KEYWORD_static_cast,
  TOK_KEYWORD_struct,
  TOK_KEYWORD_switch,
  TOK_KEYWORD_template,
  TOK_KEYWORD_this,
  TOK_KEYWORD_thread_local,
  TOK_KEYWORD_throw,
  TOK_KEYWORD_true,
  TOK_KEYWORD_try,
  TOK_KEYWORD_typedef,
  TOK_KEYWORD_typeid,
  TOK_KEYWORD_typename,
  TOK_KEYWORD_union,
  TOK_KEYWORD_unsigned,
  TOK_KEYWORD_using,
  TOK_KEYWORD_virtual,
  TOK_KEYWORD_void,
  TOK_KEYWORD_volatile,
  TOK_KEYWORD_wchar_t,
  TOK_KEYWORD_while,
  TOK_KEYWORD_override,
  TOK_KEYWORD_final,


  TOK_KEYWORD_transaction_safe,
  TOK_KEYWORD_transaction_safe_dynamic,
  TOK_KEYWORD_synchronized,
  TOK_KEYWORD_requires,
  TOK_KEYWORD_export,
  TOK_KEYWORD_import,
  TOK_KEYWORD_atomic_cancel,
  TOK_KEYWORD_atomic_commit,
  TOK_KEYWORD_atomic_noexcept,
  TOK_KEYWORD_concept,
  TOK_KEYWORD_co_await,
  TOK_KEYWORD_co_return,
  TOK_KEYWORD_co_yield,
  TOK_KEYWORD_module,
  TOK_COMMENT_EOL,
  TOK_COMMENT_COMPOUND,
};

std::ostream& operator<<(std::ostream& os, Type t);
struct Token {
  Token(Type t, std::string_view text) : t(t), text(text) {}
  Token() {}
  std::string_view text;
  Type t;
};

class Lexer {
public:
  Lexer(std::string_view str) 
  : str(str)
  { 
    readToken(); 
  }
  std::string_view str;
  size_t cur = 0;
  Token token;
  void operator++() {
    readToken();
  }
  void readToken();
  Lexer& begin() { return *this; }
  struct sentinel {};
  sentinel end() { return sentinel{}; }
  Token& operator*() 
  { 
    return token; 
  }
  bool operator==(const sentinel&) { return cur > str.size(); }
  bool operator!=(const sentinel&) { return cur <= str.size(); }
};

