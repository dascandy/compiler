#include "lexer.h"
#include <unordered_map>

static std::unordered_map<std::string_view, Type> keywords = {
  { "alignas", TOK_KEYWORD_alignas },
  { "alignof", TOK_KEYWORD_alignof },
  { "asm", TOK_KEYWORD_asm },
  { "auto", TOK_KEYWORD_auto },
  { "bool", TOK_KEYWORD_bool },
  { "break", TOK_KEYWORD_break },
  { "case", TOK_KEYWORD_case },
  { "catch", TOK_KEYWORD_catch },
  { "char", TOK_KEYWORD_char },
  { "char16_t", TOK_KEYWORD_char16_t },
  { "char32_t", TOK_KEYWORD_char32_t },
  { "class", TOK_KEYWORD_class },
  { "const", TOK_KEYWORD_const },
  { "constexpr", TOK_KEYWORD_constexpr },
  { "const_cast", TOK_KEYWORD_const_cast },
  { "continue", TOK_KEYWORD_continue },
  { "decltype", TOK_KEYWORD_decltype },
  { "default", TOK_KEYWORD_default },
  { "delete", TOK_KEYWORD_delete },
  { "do", TOK_KEYWORD_do },
  { "double", TOK_KEYWORD_double },
  { "dynamic_cast", TOK_KEYWORD_dynamic_cast },
  { "else", TOK_KEYWORD_else },
  { "enum", TOK_KEYWORD_enum },
  { "explicit", TOK_KEYWORD_explicit },
  { "extern", TOK_KEYWORD_extern },
  { "false", TOK_KEYWORD_false },
  { "float", TOK_KEYWORD_float },
  { "for", TOK_KEYWORD_for },
  { "friend", TOK_KEYWORD_friend },
  { "goto", TOK_KEYWORD_goto },
  { "if", TOK_KEYWORD_if },
  { "inline", TOK_KEYWORD_inline },
  { "int", TOK_KEYWORD_int },
  { "long", TOK_KEYWORD_long },
  { "mutable", TOK_KEYWORD_mutable },
  { "namespace", TOK_KEYWORD_namespace },
  { "new", TOK_KEYWORD_new },
  { "noexcept", TOK_KEYWORD_noexcept },
  { "nullptr", TOK_KEYWORD_nullptr },
  { "operator", TOK_KEYWORD_operator },
  { "private", TOK_KEYWORD_private },
  { "protected", TOK_KEYWORD_protected },
  { "public", TOK_KEYWORD_public },
  { "register", TOK_KEYWORD_register },
  { "reinterpret_cast", TOK_KEYWORD_reinterpret_cast },
  { "return", TOK_KEYWORD_return },
  { "short", TOK_KEYWORD_short },
  { "signed", TOK_KEYWORD_signed },
  { "sizeof", TOK_KEYWORD_sizeof },
  { "static", TOK_KEYWORD_static },
  { "static_assert", TOK_KEYWORD_static_assert },
  { "static_cast", TOK_KEYWORD_static_cast },
  { "struct", TOK_KEYWORD_struct },
  { "switch", TOK_KEYWORD_switch },
  { "template", TOK_KEYWORD_template },
  { "this", TOK_KEYWORD_this },
  { "thread_local", TOK_KEYWORD_thread_local },
  { "throw", TOK_KEYWORD_throw },
  { "true", TOK_KEYWORD_true },
  { "try", TOK_KEYWORD_try },
  { "typedef", TOK_KEYWORD_typedef },
  { "typeid", TOK_KEYWORD_typeid },
  { "typename", TOK_KEYWORD_typename },
  { "union", TOK_KEYWORD_union },
  { "unsigned", TOK_KEYWORD_unsigned },
  { "using", TOK_KEYWORD_using },
  { "virtual", TOK_KEYWORD_virtual },
  { "void", TOK_KEYWORD_void },
  { "volatile", TOK_KEYWORD_volatile },
  { "wchar_t", TOK_KEYWORD_wchar_t },
  { "while", TOK_KEYWORD_while },
  { "override", TOK_KEYWORD_override },
  { "final", TOK_KEYWORD_final },
};

void Lexer::readToken() {
  size_t s = cur, e = cur;
  Type state = TOK_NONE;
  while (e != str.size()) {
    switch(state) {
      case TOK_NONE:
        switch(str[e]) {
          case '!': state = TOK_EXCL; break;
          case '%': state = TOK_PERCENT; break;
          case '^': state = TOK_CARET; break;
          case '~': state = TOK_TILDE; break;
          case '<': state = TOK_LANGLE; break;
          case '=': state = TOK_EQUALS; break;
          case '>': state = TOK_RANGLE; break;
          case '-': state = TOK_MINUS; break;
          case ',': e++; token = Token(TOK_COMMA, std::string_view(str.data() + s, e - s)); break;
          case '|': state = TOK_PIPE; break;
          case ';': e++; token = Token(TOK_SEMICOLON, std::string_view(str.data() + s, e - s)); break;
          case ':': e++; token = Token(TOK_COLON, std::string_view(str.data() + s, e - s)); break;
          case '?': e++; token = Token(TOK_QUESTION, std::string_view(str.data() + s, e - s)); break;
          case '/': state = TOK_SLASH; break;
          case '.': e++; token = Token(TOK_DOT, std::string_view(str.data() + s, e - s)); break;
          case '(': e++; token = Token(TOK_LPAREN, std::string_view(str.data() + s, e - s)); break;
          case ')': e++; token = Token(TOK_RPAREN, std::string_view(str.data() + s, e - s)); break;
          case '[': e++; token = Token(TOK_LBRACKET, std::string_view(str.data() + s, e - s)); break;
          case ']': e++; token = Token(TOK_RBRACKET, std::string_view(str.data() + s, e - s)); break;
          case '{': e++; token = Token(TOK_LCURLY, std::string_view(str.data() + s, e - s)); break;
          case '}': e++; token = Token(TOK_RCURLY, std::string_view(str.data() + s, e - s)); break;
          case '*': state = TOK_TIMES; break;
          case '&': state = TOK_AMP; break;
          case '+': state = TOK_PLUS; break;
          case '"': state = TOK_STRING; break;
          case '\'': state = TOK_CHAR; break;
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': state = TOK_NUMBER; break;
          case ' ': case '\t': case '\r': case '\n': state = TOK_NONE; break;
          default: state = TOK_IDENTIFIER; break;
        }
        break;
      case TOK_AMP:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_AMP_EQ, std::string_view(str.data() + s, e - s)); break;
          case '&': e++; token = Token(TOK_AMP_AMP, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_AMP, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_CARET:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_CARET_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_CARET, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_EQUALS:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_EQUALS_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_EQUALS, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_EXCL:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_EXCL_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_EXCL, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_LANGLE:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_LANGLE_EQ, std::string_view(str.data() + s, e - s)); break;
          case '<': e++; token = Token(TOK_LEFTSHIFT, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_LANGLE, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_RANGLE:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_RANGLE_EQ, std::string_view(str.data() + s, e - s)); break;
          case '>': e++; token = Token(TOK_RIGHTSHIFT, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_RANGLE, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_MINUS:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_MINUS_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_MINUS, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_PIPE:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_PIPE_EQ, std::string_view(str.data() + s, e - s)); break;
          case '|': e++; token = Token(TOK_PIPE_PIPE, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_PIPE, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_PLUS:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_PLUS_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_PLUS, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_PERCENT:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_PERCENT_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_PERCENT, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_SLASH:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_SLASH_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_SLASH, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_TILDE:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_TILDE_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_TILDE, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_TIMES:
        switch(str[e]) {
          case '=': e++; token = Token(TOK_TIMES_EQ, std::string_view(str.data() + s, e - s)); break;
          default: token = Token(TOK_TIMES, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_NUMBER:
        switch(str[e]) {
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': state = TOK_NUMBER; break;
          default: token = Token(TOK_NUMBER, std::string_view(str.data() + s, e - s)); break;
        }
        break;
      case TOK_CHAR:
        switch(str[e]) {
          case '\'':
            e++; token = Token(TOK_CHAR, std::string_view(str.data() + s, e - s)); break;
            default: break;
        }
        break;
      case TOK_STRING:
        switch(str[e]) {
          case '\"':
            e++; token = Token(TOK_STRING, std::string_view(str.data() + s, e - s)); break;
            default: break;
        }
        break;
      case TOK_IDENTIFIER:
        if ((str[e] >= 'a' && str[e] <= 'z') || (str[e] >= 'A' && str[e] <= 'Z') || (str[e] >= '0' && str[e] <= '9') || str[e] == '_') {
        } else {
          std::string_view v(str.data() + s, e - s);
          Type type = TOK_IDENTIFIER;
          auto it = keywords.find(v);
          if (it != keywords.end()) type = it->second;
          token = Token(type, v); break;
        }
        break;
    }
  }
}


