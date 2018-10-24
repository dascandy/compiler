#include "cpplang/lexer.hpp"
#include <unordered_map>

static std::unordered_map<Type, std::string_view> token_names = {
  { TOK_EXCL, "TOK_EXCL" },
  { TOK_KEYWORD_not, "TOK_KEYWORD_not" },
  { TOK_PERCENT, "TOK_PERCENT" },
  { TOK_CARET, "TOK_CARET" },
  { TOK_KEYWORD_xor, "TOK_KEYWORD_xor" },
  { TOK_TILDE, "TOK_TILDE" },
  { TOK_KEYWORD_compl, "TOK_KEYWORD_compl" },
  { TOK_LANGLE, "TOK_LANGLE" },
  { TOK_EQUALS, "TOK_EQUALS" },
  { TOK_RANGLE, "TOK_RANGLE" },
  { TOK_MINUS, "TOK_MINUS" },
  { TOK_COMMA, "TOK_COMMA" },
  { TOK_PIPE, "TOK_PIPE" },
  { TOK_KEYWORD_bitor, "TOK_KEYWORD_bitor" },
  { TOK_SEMICOLON, "TOK_SEMICOLON" },
  { TOK_COLON, "TOK_COLON" },
  { TOK_SCOPE, "TOK_SCOPE" },
  { TOK_QUESTION, "TOK_QUESTION" },
  { TOK_SLASH, "TOK_SLASH" },
  { TOK_SLASH_EQ, "TOK_SLASH_EQ" },
  { TOK_DOT, "TOK_DOT" },
  { TOK_DOT_STAR, "TOK_DOT_STAR" },
  { TOK_LPAREN, "TOK_LPAREN" },
  { TOK_RPAREN, "TOK_RPAREN" },
  { TOK_LBRACKET, "TOK_LBRACKET" },
  { TOK_RBRACKET, "TOK_RBRACKET" },
  { TOK_LCURLY, "TOK_LCURLY" },
  { TOK_RCURLY, "TOK_RCURLY" },
  { TOK_STAR, "TOK_STAR" },
  { TOK_AMP, "TOK_AMP" },
  { TOK_KEYWORD_bitand, "TOK_KEYWORD_bitand" },
  { TOK_PLUS, "TOK_PLUS" },
  { TOK_CARET_EQ, "TOK_CARET_EQ" },
  { TOK_KEYWORD_xor_eq, "TOK_KEYWORD_xor_eq" },
  { TOK_TILDE_EQ, "TOK_TILDE_EQ" },
  { TOK_LANGLE_EQ, "TOK_LANGLE_EQ" },
  { TOK_EQUALS_EQ, "TOK_EQUALS_EQ" },
  { TOK_RANGLE_EQ, "TOK_RANGLE_EQ" },
  { TOK_PIPE_EQ, "TOK_PIPE_EQ" },
  { TOK_KEYWORD_or_eq, "TOK_KEYWORD_or_eq" },
  { TOK_MINUS_EQ, "TOK_MINUS_EQ" },
  { TOK_EXCL_EQ, "TOK_EXCL_EQ" },
  { TOK_KEYWORD_not_eq, "TOK_KEYWORD_not_eq" },
  { TOK_STAR_EQ, "TOK_STAR_EQ" },
  { TOK_AMP_EQ, "TOK_AMP_EQ" },
  { TOK_KEYWORD_and_eq, "TOK_KEYWORD_and_eq" },
  { TOK_PERCENT_EQ, "TOK_PERCENT_EQ" },
  { TOK_PLUS_EQ, "TOK_PLUS_EQ" },
  { TOK_LEFTSHIFT, "TOK_LEFTSHIFT" },
  { TOK_LEFTSHIFT_EQ, "TOK_LEFTSHIFT_EQ" },
  { TOK_RIGHTSHIFT, "TOK_RIGHTSHIFT" },
  { TOK_RIGHTSHIFT_EQ, "TOK_RIGHTSHIFT_EQ" },
  { TOK_ARROW, "TOK_ARROW" },
  { TOK_ARROW_STAR, "TOK_ARROW_STAR" },
  { TOK_AMP_AMP, "TOK_AMP_AMP" },
  { TOK_KEYWORD_and, "TOK_KEYWORD_and" },
  { TOK_PIPE_PIPE, "TOK_PIPE_PIPE" },
  { TOK_KEYWORD_or, "TOK_KEYWORD_or" },
  { TOK_INCREMENT, "TOK_INCREMENT" },
  { TOK_DECREMENT, "TOK_DECREMENT" },
  { TOK_SPACESHIP, "TOK_SPACESHIP" },
  { TOK_STRING, "TOK_STRING" },
  { TOK_CHAR, "TOK_CHAR" },
  { TOK_NUMBER, "TOK_NUMBER" },
  { TOK_IDENTIFIER, "TOK_IDENTIFIER" },
  { TOK_KEYWORD_alignas, "TOK_KEYWORD_alignas" },
  { TOK_KEYWORD_alignof, "TOK_KEYWORD_alignof" },
  { TOK_KEYWORD_asm, "TOK_KEYWORD_asm" },
  { TOK_KEYWORD_auto, "TOK_KEYWORD_auto" },
  { TOK_KEYWORD_bool, "TOK_KEYWORD_bool" },
  { TOK_KEYWORD_break, "TOK_KEYWORD_break" },
  { TOK_KEYWORD_case, "TOK_KEYWORD_case" },
  { TOK_KEYWORD_catch, "TOK_KEYWORD_catch" },
  { TOK_KEYWORD_char, "TOK_KEYWORD_char" },
  { TOK_KEYWORD_char16_t, "TOK_KEYWORD_char16_t" },
  { TOK_KEYWORD_char32_t, "TOK_KEYWORD_char32_t" },
  { TOK_KEYWORD_class, "TOK_KEYWORD_class" },
  { TOK_KEYWORD_const, "TOK_KEYWORD_const" },
  { TOK_KEYWORD_constexpr, "TOK_KEYWORD_constexpr" },
  { TOK_KEYWORD_const_cast, "TOK_KEYWORD_const_cast" },
  { TOK_KEYWORD_continue, "TOK_KEYWORD_continue" },
  { TOK_KEYWORD_decltype, "TOK_KEYWORD_decltype" },
  { TOK_KEYWORD_default, "TOK_KEYWORD_default" },
  { TOK_KEYWORD_delete, "TOK_KEYWORD_delete" },
  { TOK_KEYWORD_do, "TOK_KEYWORD_do" },
  { TOK_KEYWORD_double, "TOK_KEYWORD_double" },
  { TOK_KEYWORD_dynamic_cast, "TOK_KEYWORD_dynamic_cast" },
  { TOK_KEYWORD_else, "TOK_KEYWORD_else" },
  { TOK_KEYWORD_enum, "TOK_KEYWORD_enum" },
  { TOK_KEYWORD_explicit, "TOK_KEYWORD_explicit" },
  { TOK_KEYWORD_extern, "TOK_KEYWORD_extern" },
  { TOK_KEYWORD_false, "TOK_KEYWORD_false" },
  { TOK_KEYWORD_float, "TOK_KEYWORD_float" },
  { TOK_KEYWORD_for, "TOK_KEYWORD_for" },
  { TOK_KEYWORD_friend, "TOK_KEYWORD_friend" },
  { TOK_KEYWORD_goto, "TOK_KEYWORD_goto" },
  { TOK_KEYWORD_if, "TOK_KEYWORD_if" },
  { TOK_KEYWORD_inline, "TOK_KEYWORD_inline" },
  { TOK_KEYWORD_int, "TOK_KEYWORD_int" },
  { TOK_KEYWORD_long, "TOK_KEYWORD_long" },
  { TOK_KEYWORD_mutable, "TOK_KEYWORD_mutable" },
  { TOK_KEYWORD_namespace, "TOK_KEYWORD_namespace" },
  { TOK_KEYWORD_new, "TOK_KEYWORD_new" },
  { TOK_KEYWORD_noexcept, "TOK_KEYWORD_noexcept" },
  { TOK_KEYWORD_nullptr, "TOK_KEYWORD_nullptr" },
  { TOK_KEYWORD_operator, "TOK_KEYWORD_operator" },
  { TOK_KEYWORD_private, "TOK_KEYWORD_private" },
  { TOK_KEYWORD_protected, "TOK_KEYWORD_protected" },
  { TOK_KEYWORD_public, "TOK_KEYWORD_public" },
  { TOK_KEYWORD_register, "TOK_KEYWORD_register" },
  { TOK_KEYWORD_reinterpret_cast, "TOK_KEYWORD_reinterpret_cast" },
  { TOK_KEYWORD_return, "TOK_KEYWORD_return" },
  { TOK_KEYWORD_short, "TOK_KEYWORD_short" },
  { TOK_KEYWORD_signed, "TOK_KEYWORD_signed" },
  { TOK_KEYWORD_sizeof, "TOK_KEYWORD_sizeof" },
  { TOK_KEYWORD_static, "TOK_KEYWORD_static" },
  { TOK_KEYWORD_static_assert, "TOK_KEYWORD_static_assert" },
  { TOK_KEYWORD_static_cast, "TOK_KEYWORD_static_cast" },
  { TOK_KEYWORD_struct, "TOK_KEYWORD_struct" },
  { TOK_KEYWORD_switch, "TOK_KEYWORD_switch" },
  { TOK_KEYWORD_template, "TOK_KEYWORD_template" },
  { TOK_KEYWORD_this, "TOK_KEYWORD_this" },
  { TOK_KEYWORD_thread_local, "TOK_KEYWORD_thread_local" },
  { TOK_KEYWORD_throw, "TOK_KEYWORD_throw" },
  { TOK_KEYWORD_true, "TOK_KEYWORD_true" },
  { TOK_KEYWORD_try, "TOK_KEYWORD_try" },
  { TOK_KEYWORD_typedef, "TOK_KEYWORD_typedef" },
  { TOK_KEYWORD_typeid, "TOK_KEYWORD_typeid" },
  { TOK_KEYWORD_typename, "TOK_KEYWORD_typename" },
  { TOK_KEYWORD_union, "TOK_KEYWORD_union" },
  { TOK_KEYWORD_unsigned, "TOK_KEYWORD_unsigned" },
  { TOK_KEYWORD_using, "TOK_KEYWORD_using" },
  { TOK_KEYWORD_virtual, "TOK_KEYWORD_virtual" },
  { TOK_KEYWORD_void, "TOK_KEYWORD_void" },
  { TOK_KEYWORD_volatile, "TOK_KEYWORD_volatile" },
  { TOK_KEYWORD_wchar_t, "TOK_KEYWORD_wchar_t" },
  { TOK_KEYWORD_while, "TOK_KEYWORD_while" },
  { TOK_KEYWORD_override, "TOK_KEYWORD_override" },
  { TOK_KEYWORD_final, "TOK_KEYWORD_final" },
  { TOK_KEYWORD_transaction_safe, "TOK_KEYWORD_transaction_safe" },
  { TOK_KEYWORD_transaction_safe_dynamic, "TOK_KEYWORD_transaction_safe_dynamic" },
  { TOK_KEYWORD_synchronized, "TOK_KEYWORD_synchronized" },
  { TOK_KEYWORD_requires, "TOK_KEYWORD_requires" },
  { TOK_KEYWORD_export, "TOK_KEYWORD_export" },
  { TOK_KEYWORD_import, "TOK_KEYWORD_import" },
  { TOK_KEYWORD_atomic_cancel, "TOK_KEYWORD_atomic_cancel" },
  { TOK_KEYWORD_atomic_commit, "TOK_KEYWORD_atomic_commit" },
  { TOK_KEYWORD_atomic_noexcept, "TOK_KEYWORD_atomic_noexcept" },
  { TOK_KEYWORD_concept, "TOK_KEYWORD_concept" },
  { TOK_KEYWORD_co_await, "TOK_KEYWORD_co_await" },
  { TOK_KEYWORD_co_return, "TOK_KEYWORD_co_return" },
  { TOK_KEYWORD_co_yield, "TOK_KEYWORD_co_yield" },
  { TOK_KEYWORD_module, "TOK_KEYWORD_module" },
  { TOK_COMMENT_EOL, "TOK_COMMENT_EOL" },
  { TOK_COMMENT_COMPOUND, "TOK_COMMENT_COMPOUND" },
};

std::ostream& operator<<(std::ostream& os, Type t) {
  os << token_names[t];
  return os;
}

static std::unordered_map<std::string_view, Type> keywords = {
  { "alignas", TOK_KEYWORD_alignas },
  { "alignof", TOK_KEYWORD_alignof },
  { "and_eq", TOK_KEYWORD_and_eq },
  { "and", TOK_KEYWORD_and },
  { "asm", TOK_KEYWORD_asm },
  { "auto", TOK_KEYWORD_auto },
  { "bitand", TOK_KEYWORD_bitand },
  { "bitor", TOK_KEYWORD_bitor },
  { "bool", TOK_KEYWORD_bool },
  { "break", TOK_KEYWORD_break },
  { "case", TOK_KEYWORD_case },
  { "catch", TOK_KEYWORD_catch },
  { "char16_t", TOK_KEYWORD_char16_t },
  { "char32_t", TOK_KEYWORD_char32_t },
  { "char", TOK_KEYWORD_char },
  { "class", TOK_KEYWORD_class },
  { "compl", TOK_KEYWORD_compl },
  { "const_cast", TOK_KEYWORD_const_cast },
  { "constexpr", TOK_KEYWORD_constexpr },
  { "const", TOK_KEYWORD_const },
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
  { "final", TOK_KEYWORD_final },
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
  { "not_eq", TOK_KEYWORD_not_eq },
  { "not", TOK_KEYWORD_not },
  { "nullptr", TOK_KEYWORD_nullptr },
  { "operator", TOK_KEYWORD_operator },
  { "or_eq", TOK_KEYWORD_or_eq },
  { "or", TOK_KEYWORD_or },
  { "override", TOK_KEYWORD_override },
  { "private", TOK_KEYWORD_private },
  { "protected", TOK_KEYWORD_protected },
  { "public", TOK_KEYWORD_public },
  { "register", TOK_KEYWORD_register },
  { "reinterpret_cast", TOK_KEYWORD_reinterpret_cast },
  { "return", TOK_KEYWORD_return },
  { "short", TOK_KEYWORD_short },
  { "signed", TOK_KEYWORD_signed },
  { "sizeof", TOK_KEYWORD_sizeof },
  { "static_assert", TOK_KEYWORD_static_assert },
  { "static_cast", TOK_KEYWORD_static_cast },
  { "static", TOK_KEYWORD_static },
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
  { "xor_eq", TOK_KEYWORD_xor_eq },
  { "xor", TOK_KEYWORD_xor },
};

void Lexer::readToken() {
  size_t s = cur;
  Type state = TOK_NONE;
  bool escaped = false;
  while (cur != str.size()) {
    switch(state) {
      case TOK_NONE:
        switch(str[cur]) {
          case '!': state = TOK_EXCL; break;
          case '%': state = TOK_PERCENT; break;
          case '^': state = TOK_CARET; break;
          case '~': state = TOK_TILDE; break;
          case '<': state = TOK_LANGLE; break;
          case '=': state = TOK_EQUALS; break;
          case '>': state = TOK_RANGLE; break;
          case '-': state = TOK_MINUS; break;
          case '#': state = TOK_COMMENT_EOL; break;
          case ',': cur++; token = Token(TOK_COMMA, std::string_view(str.data() + s, cur - s)); return;
          case '|': state = TOK_PIPE; break;
          case ';': cur++; token = Token(TOK_SEMICOLON, std::string_view(str.data() + s, cur - s)); return;
          case ':': state = TOK_COLON; break;
          case '?': cur++; token = Token(TOK_QUESTION, std::string_view(str.data() + s, cur - s)); return;
          case '/': state = TOK_SLASH; break;
          case '.': cur++; token = Token(TOK_DOT, std::string_view(str.data() + s, cur - s)); return;
          case '(': cur++; token = Token(TOK_LPAREN, std::string_view(str.data() + s, cur - s)); return;
          case ')': cur++; token = Token(TOK_RPAREN, std::string_view(str.data() + s, cur - s)); return;
          case '[': cur++; token = Token(TOK_LBRACKET, std::string_view(str.data() + s, cur - s)); return;
          case ']': cur++; token = Token(TOK_RBRACKET, std::string_view(str.data() + s, cur - s)); return;
          case '{': cur++; token = Token(TOK_LCURLY, std::string_view(str.data() + s, cur - s)); return;
          case '}': cur++; token = Token(TOK_RCURLY, std::string_view(str.data() + s, cur - s)); return;
          case '*': state = TOK_STAR; break;
          case '&': state = TOK_AMP; break;
          case '+': state = TOK_PLUS; break;
          case '"': state = TOK_STRING; break;
          case '\'': state = TOK_CHAR; break;
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': state = TOK_NUMBER; break;
          case ' ': case '\t': case '\r': case '\n': s++; break;
          default: state = TOK_IDENTIFIER; break;
        }
        break;
      case TOK_AMP:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_AMP_EQ, std::string_view(str.data() + s, cur - s)); return;
          case '&': cur++; token = Token(TOK_AMP_AMP, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_AMP, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_CARET:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_CARET_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_CARET, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_COLON:
        switch(str[cur]) {
          case ':': cur++; token = Token(TOK_SCOPE, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_COLON, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_EQUALS:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_EQUALS_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_EQUALS, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_EXCL:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_EXCL_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_EXCL, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_LANGLE:
        switch(str[cur]) {
          case '=': state = TOK_LANGLE_EQ; break;
          case '<': state = TOK_LEFTSHIFT; break;
          default: token = Token(TOK_LANGLE, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_LEFTSHIFT:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_LEFTSHIFT_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_LEFTSHIFT, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_LANGLE_EQ:
        switch(str[cur]) {
          case '>': cur++; token = Token(TOK_SPACESHIP, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_LANGLE_EQ, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_RANGLE:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_RANGLE_EQ, std::string_view(str.data() + s, cur - s)); return;
          case '>': state = TOK_RIGHTSHIFT; break;
          default: token = Token(TOK_RANGLE, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_RIGHTSHIFT:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_RIGHTSHIFT_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_RIGHTSHIFT, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_MINUS:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_MINUS_EQ, std::string_view(str.data() + s, cur - s)); return;
          case '-': cur++; token = Token(TOK_DECREMENT, std::string_view(str.data() + s, cur - s)); return;
          case '>': state = TOK_ARROW; break;
          default: token = Token(TOK_MINUS, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_DOT:
        switch(str[cur]) {
          case '*': cur++; token = Token(TOK_DOT_STAR, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_DOT, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_ARROW:
        switch(str[cur]) {
          case '*': cur++; token = Token(TOK_ARROW_STAR, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_ARROW, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_PIPE:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_PIPE_EQ, std::string_view(str.data() + s, cur - s)); return;
          case '|': cur++; token = Token(TOK_PIPE_PIPE, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_PIPE, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_PLUS:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_PLUS_EQ, std::string_view(str.data() + s, cur - s)); return;
          case '+': cur++; token = Token(TOK_INCREMENT, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_PLUS, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_PERCENT:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_PERCENT_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_PERCENT, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_SLASH:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_SLASH_EQ, std::string_view(str.data() + s, cur - s)); return;
          case '/': state = TOK_COMMENT_EOL; break;
          default: token = Token(TOK_SLASH, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_TILDE:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_TILDE_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_TILDE, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_STAR:
        switch(str[cur]) {
          case '=': cur++; token = Token(TOK_STAR_EQ, std::string_view(str.data() + s, cur - s)); return;
          default: token = Token(TOK_STAR, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_NUMBER:
        switch(str[cur]) {
          case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': 
          case 'x': case 'X': case 'b': case 'B': case '\'': break;
          default: token = Token(TOK_NUMBER, std::string_view(str.data() + s, cur - s)); return;
        }
        break;
      case TOK_CHAR:
        switch(str[cur]) {
          case '\\': if (!escaped) { escaped = true; } else { escaped = false; } break;
          case '\'': if (!escaped) { cur++; token = Token(TOK_CHAR, std::string_view(str.data() + s, cur - s)); return; }
          default: escaped = false; break;
        }
        break;
      case TOK_STRING:
        switch(str[cur]) {
          case '\\': if (!escaped) { escaped = true; } else { escaped = false; } break;
          case '\"': if (!escaped) { cur++; token = Token(TOK_STRING, std::string_view(str.data() + s, cur - s)); return; }
          default: escaped = false; break;
        }
        break;
      case TOK_IDENTIFIER:
        if ((str[cur] >= 'a' && str[cur] <= 'z') || (str[cur] >= 'A' && str[cur] <= 'Z') || (str[cur] >= '0' && str[cur] <= '9') || str[cur] == '_') {
        } else {
          std::string_view v(str.data() + s, cur - s);
          Type type = TOK_IDENTIFIER;
          auto it = keywords.find(v);
          if (it != keywords.end()) type = it->second;
          token = Token(type, v); return;
        }
        break;
      case TOK_COMMENT_EOL:
        if (str[cur] == '\n') {
          state = TOK_NONE; 
          s = cur + 1;
        }
        break;
      case TOK_COMMENT_COMPOUND:
        break;
    }
    cur++;
  }
  cur++;
}


