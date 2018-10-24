#include "cpplang/lexer.h"
#include <iostream>

int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "rb");
  fseek(f, 0, SEEK_END);
  size_t s = ftell(f);
  fseek(f, 0, SEEK_SET);
  char* buffer = (char*)malloc(s);
  fread(buffer, s, 1, f);
  fclose(f);
  Lexer l(std::string_view(buffer, s));
  for (auto& token : l) {
    std::cout << token.t << ": " << token.text << "\n";
  }
}
