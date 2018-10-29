#include "cpplang/Parser.hpp"
#include <optional>

using namespace Language;

class Parser {
public:
  Parser(Lexer& lexer)
  : lexer(lexer)
  {
  }
  void Parse();
  std::unique_ptr<Declaration> parseDeclaration();
  std::unique_ptr<Declaration> parseFunctionOrVariable();
  std::unique_ptr<Function> parseFunction();
  std::unique_ptr<Function> parseStructor();
  std::unique_ptr<Variable> parseVariable();
  std::unique_ptr<Statement> parseStatement();
  std::shared_ptr<Expression> parseExpression();
  Scope parseScope();
  std::pair<std::string, std::shared_ptr<Expression>> parseInitlistEntry();
  std::shared_ptr<Language::Type> parseType();
  std::shared_ptr<Language::Type> parseEnum();
  std::shared_ptr<Language::Type> parseStruct();
  std::string parseName();
  Lexer lexer;
  Namespace global;
};

Namespace Parse(Lexer lexer) {
  Parser p(lexer);
  p.Parse();
  return std::move(p.global);
}

void Parser::Parse() {
  while (lexer != lexer.end()) {
    auto decl = parseFunctionOrVariable();
    std::string name = decl->name;
    global.declarations[name] = std::move(decl);
  }
}

Scope Parser::parseScope() {
  if (lexer.token.t != TOK_LCURLY) throw std::runtime_error("No scope in place that should have one");
  ++lexer;
  Scope scope;
  while (lexer.token.t != TOK_RCURLY) {
    scope.declarations.push_back(parseDeclaration());
  }
  ++lexer;
  return scope;
}

std::unique_ptr<Declaration> Parser::parseFunctionOrVariable() {
  std::unique_ptr<Function> f = parseFunction();
  if (f) return f;
  return parseVariable();
}

std::unique_ptr<Declaration> Parser::parseDeclaration() {
  bool external = false;
  std::string mangling = "CXX";
  if (lexer.token.t == TOK_KEYWORD_extern) {
    ++lexer;
    if (lexer.token.t == TOK_STRING) {
      mangling = lexer.token.text;
      ++lexer;
    }
  }
  std::unique_ptr<Declaration> decl = parseFunctionOrVariable();
  decl->external = external;
  decl->mangling = mangling;
  return decl;
}

//initializer_list_entry ::= name '(' expression ')'
std::pair<std::string, std::shared_ptr<Expression>> Parser::parseInitlistEntry() {

}

// function ::= [ 'static' | 'virtual' ] [ type ] name '(' [ variable_declaration { ',' variable_declaration } ] ')' cv_qualifier [ 'noexcept' ] [ 'override' ] ( ';' | [ initializer_list ] scope_body )
std::unique_ptr<Function> Parser::parseFunction() {
  std::unique_ptr<Function> f = std::make_unique<Function>();
  if (lexer.token.t == TOK_KEYWORD_static) {
    f->isStatic = true;
    ++lexer;
  } else if (lexer.token.t == TOK_KEYWORD_virtual) {
    f->isVirtual = true;
    ++lexer;
  }
  try {
    f->returnType = parseType();
  } catch (...) {}
  f->name = parseName(); // no scoped names? Need to fix
  if (lexer.token.t != TOK_LPAREN) {
    throw std::runtime_error("Not a function");
  }
  ++lexer;
  while (lexer.token.t != TOK_RPAREN) {
    f->argumentList.push_back(std::move(*parseVariable().get()));
    if (lexer.token.t == TOK_COMMA) 
      ++lexer; 
    else if (lexer.token.t != TOK_RPAREN) 
      throw std::runtime_error("Could not parse argument list");
  }
  if (lexer.token.t == TOK_KEYWORD_const) {
    f->isConst = true;
    ++lexer;
  }
  if (lexer.token.t == TOK_KEYWORD_noexcept) {
    f->isNoexcept = true;
    ++lexer;
  }
  if (lexer.token.t == TOK_KEYWORD_override) {
    f->isOverride = true;
    ++lexer;
  }
  if (lexer.token.t == TOK_SEMICOLON) {
    return f;
  }
  if (lexer.token.t == TOK_COLON) {
    // parse init list

  }
  f->body.reset(new Language::Scope(parseScope()));
  return f;
}

std::unique_ptr<Variable> Parser::parseVariable() {

}

std::unique_ptr<Statement> Parser::parseStatement() {

}

std::shared_ptr<Expression> Parser::parseExpression() {

}

std::shared_ptr<Type> Parser::parseType() {

}

std::shared_ptr<Type> Parser::parseEnum() {

}

std::shared_ptr<Type> Parser::parseStruct() {

}

std::string Parser::parseName() {

}


