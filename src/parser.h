#pragma once

class Parser {
public:
  Parser(Lexer& lexer)
  : lexer(lexer)
  {
  }
  Lexer lexer;
  
};


struct 


toplevel_statement ::= variable_declaration ';'
                     | function

function ::= [ 'static' | 'virtual' ] type function_prototype cv_qualifier [ 'noexcept' ] [ 'override' ] ( scope_body | ';' )
constructor ::= function_prototype ( ';' | [ initializer_list ] scope_body )

initializer_list ::= ':' initializer_list_entry { ',' initializer_list_entry }
initializer_list_entry ::= name '(' expression ')'

function_prototype ::= name '(' [ variable_declaration { ',' variable_declaration } ] ')' 

variable_declaration ::= type [ name ] [ '=' expression ]

type ::= cv_qualifier ( 'auto' | enum_type | struct_type | name ) cv_qualifier { '*' cv_qualifier } [ '&' | '&&' ]

enum_type ::= 'enum' [ name ] [ '{' enum_value { ',' enum_value } [ ',' ] '}' ]
enum_value ::= name [ '=' expression ]

struct_type ::= ( 'struct' | 'class' | 'union' ) [ name ] [ '{' { struct_member_declaration } '}' ]

// Friend variables are for friend types (classes). Having an instance in a friend statement makes no logical sense.
struct_member_declaration ::= variable_declaration ';'
                            | 'friend' ( type ';' | function )
                            | function
                            | [ '~' ] constructor
                            | access_modifier ':'

scope_body ::= '{' { statement } '}'

statement ::= expression ';'
            | 'return' expression ';'
            | 'if' '(' expression ')' scope_body [ 'else' scope_body ]
            | 'while' '(' expression ')' scope_body
            | 'for' '(' [ variable_declaration ] ( ':' expression | ';' [ expression ] ';' [ expression ] ) ')'
            | 'do' scope_body 'while' '(' expression ')' ';'

expression ::= name [ ( '(' expression { ',' expression } ')' | '{' expression { ',' expression } '}' ) ]
             | immediate_value
             | expression binary_op expression
             | unary_prefix_op expression
             | expression unary_postfix_op
             | name '(' [ expression { ',' expression } ] ')'
             | name '{' [ expression { ',' expression } ] '}'
             | variable_declaration
             | unary_operator expression

name ::= 'operator' ( any_overloadable_operator | 'new' [ '[' ']' ] | 'delete' [ '[' ']' ] | '"' '"' name | type )
       | string_literal

access_modifier ::= 'public' | 'private' | 'protected'
any_overloadable_operator ::= '+' | '-' | '*' | '/' | '%' | '^' | '&' | '|' | '~' | '!' | '=' | '<' | '>' | '+=' | '-=' | '*=' | '/=' | '%=' | '^=' | '&=' | '|=' | '<<' | '>>' | '>>=' | '<<=' | '==' | '!=' | '<=' | '>=' | '<=>' | '&&' | '||' | '++' | '--' | ',' | '->*' | '->' | '(' ')' | '[' ']' 


