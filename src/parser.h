#pragma once

class Parser {
public:
  Parser(std::string_view str)
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


