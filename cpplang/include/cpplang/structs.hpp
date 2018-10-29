#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstddef>
#include <cstdint>

namespace Language {

struct Declaration {
  virtual ~Declaration() {}
  enum Accessibility {
    Public,
    Protected,
    Private,
  } accessor = Public;
  std::string name;
  std::string mangling = "CXX";
  bool external = false;
};

struct Scope {
  // TODO: make this a variant?
  std::vector<std::unique_ptr<Declaration>> declarations;
};

struct Type {};
struct Expression {};
struct Statement : Declaration {};

struct Namespace : Declaration, Type {
  bool isUnion;
  std::unordered_map<std::string, std::shared_ptr<Type>> types;
  std::unordered_map<std::string, std::unique_ptr<Declaration>> declarations;
  std::vector<Declaration*> friends;
};

struct Variable : Declaration {
  bool isStatic;
  std::shared_ptr<Type> type;
  std::shared_ptr<Expression> initial_value;
};

struct Function : Declaration {
  std::shared_ptr<Type> returnType;
  std::string_view name;
  bool isVirtual;
  bool isStatic;
  bool isNoexcept;
  bool isOverride;
  bool isConst;
  bool isVolatile;
  std::vector<Variable> argumentList;
  std::unordered_map<std::string, std::shared_ptr<Expression>> initializerlist;
  std::unique_ptr<Scope> body;
};
 
struct NamedType : Type {
  std::string name;
};

struct PointerIndirection : Type {
  std::shared_ptr<Type> baseType;
};

struct CVQualifiedType : Type {
  std::shared_ptr<Type> baseType;
  bool isConst;
  bool isVolatile;
};

struct Reference : Type {
  std::shared_ptr<Type> baseType;
  bool isRighthandReference = false;
};

struct Enum : Type, Declaration {
  std::unordered_map<std::string, size_t> values;
};

struct UnaryPostfixExpression : Expression {
  std::shared_ptr<Expression> lhs;
  std::string operatorname;
};

struct UnaryPrefixExpression : Expression {
  std::shared_ptr<Expression> rhs;
  std::string operatorname;
};

struct BinaryExpression : Expression {
  std::shared_ptr<Expression> lhs, rhs;
  std::string operatorname;
};

struct TernaryExpression : Expression {
  std::shared_ptr<Expression> lhs, rhs;
  std::string operatorname;
};

struct FunctionCall : Expression {
  std::vector<std::shared_ptr<Expression>> arguments;
};

struct NamedExpression : Expression {
  std::string name;
};

struct ImmediateValue : Expression {
  std::string value;
}; 

struct ExpressionStatement : Statement {
  std::shared_ptr<Expression> value;
};

struct ReturnStatement : Statement {
  std::shared_ptr<Expression> value;
};

struct Loop : Statement {
  std::shared_ptr<Expression> loopCondition;
  Scope body;
};

struct Conditional : Statement {
  std::shared_ptr<Expression> condition;
  Scope positive;
  Scope negative;
};

}


