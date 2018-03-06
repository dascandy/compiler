
namespace Language {

struct Declaration {
  virtual ~Declaration() {}
  enum Accessibility {
    Public,
    Protected,
    Private,
  } accessor = Public;
};

struct Type {};

struct Namespace : Declaration {
  std::string name;
  std::unordered_map<std::string, std::shared_ptr<Type>> types;
  std::unordered_map<std::string, std::unique_ptr<Declaration>> declarations;
  std::vector<Declaration*> friends;
};

struct Class : Namespace, Type {
  bool isUnion;
};

struct Variable : Declaration {
  bool isStatic;
  std::shared_ptr<Type> type;
  std::string name;
  std::unique_ptr<Expression> initial_value;
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
  std::vector<Variable> argumentlist;
  std::unique_ptr<Scope> body;
};
 
struct Structor : Function {
  std::unordered_map<std::string, std::unique_ptr<Expression>> initializerlist;
  bool constructor;
};

struct Scope {
  std::vector<std::unique_ptr<Declaration>> declarations;
};

struct NamedReference : Type {
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

struct Expression {
};

struct UnaryPostfixExpression : Expression {
  std::unique_ptr<Expression> lhs;
  std::string operatorname;
};

struct UnaryPrefixExpression : Expression {
  std::unique_ptr<Expression> rhs;
  std::string operatorname;
};

struct BinaryExpression : Expression {
  std::unique_ptr<Expression> lhs, rhs;
  std::string operatorname;
};

struct TernaryExpression : Expression {
  std::unique_ptr<Expression> lhs, rhs;
  std::string operatorname;
};

expression ::= name [ ( '(' expression { ',' expression } ')' | '{' expression { ',' expression } '}' ) ]
             | immediate_value
             | expression binary_op expression
             | unary_prefix_op expression
             | expression unary_postfix_op
             | name '(' [ expression { ',' expression } ] ')'
             | name '{' [ expression { ',' expression } ] '}'
             | variable_declaration
             | unary_operator expression

struct Statement : Declaration {};

struct ExpressionStatement : Statement {
  std::unique_ptr<Expression> value;
};

struct ReturnStatement : Statement {
  std::unique_ptr<Expression> value;
};

struct Loop : Statement {
  std::unique_ptr<Expression> loopCondition;
  Scope body;
};

struct Conditional : Statement {
  std::unique_ptr<Expression> condition;
  Scope positive;
  Scope negative;
};


