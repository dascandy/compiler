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

translationunit ::= { declaration }
declaration ::= [ template_decl ] ( var_decl | func_decl | class_decl | enum_decl | using_decl)
class_decl ::= 'class' <name> [ inheritance_decl ] '{' { ( accessor | declaration ) } '}' ';'
var_decl ::= type_decl <name> { ',' <name> } ';'
func_decl ::= type_decl <name> '(' arg_decl { ',' arg_decl } '{' { statement } '}'
template_decl ::= 'template' '<' template_arg { ',' template_arg } '>'

using_decl ::= 'using' <name> '=' type_decl ';'

statement ::= declaration
            | 

template_arg ::= ( 'typename' | 'class' ) [ <name> ] [ '=' type_decl ]
               | integral_type [ <name> ] [ '=' default_value ]


float_type ::= 'float' | [ 'long' ] 'double'
integral_type ::= [ 'unsigned' | 'signed' ] 'int' | 'short' | 'char' | 'long' | 'long' 'long'
inheritance_decl ::= ':' access_specifier <name> { ',' access_specifier <name> } 
accessor ::= access_specifier ':'
access_specifier ::= 'public' | 'private' | 'protected'

