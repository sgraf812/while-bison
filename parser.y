%{
#include <stdio.h>
#include "ast.h"

int yylex();
void yyerror(const command_t **, const char*);
%}

%define api.pure full
%parse-param {const struct command_t **out}

%token       T_EOF          0      "end of file"
%token <val> T_NUMBER
%token <id>  T_VAR
%token       T_TRUE         "true"
%token       T_FALSE        "false"
%token       T_PLUS         "+"
%token       T_MINUS        "-"
%token       T_STAR         "*"
%token       T_EQUALS       "="
%token       T_LESS_EQUALS  "<="
%token       T_AMPERSANDS   "&&"
%token       T_BANG         "!"
%token       T_LPAREN       "("
%token       T_RPAREN       ")"
%token       T_SEMICOLON    ";"
%token       T_COLON_EQUALS ":="
%token       T_LBRACE       "{"
%token       T_RBRACE       "}"
%token       T_IF           "if"
%token       T_ELSE         "else"
%token       T_WHILE        "while"

%union {
  int val;
  const char *id;
  const struct expression_t *expr;
  const struct command_t *cmd;
};

%type <cmd> cmds
%type <cmd> cmd
%type <cmd> block
%type <expr> expr

%nonassoc ":="
%left "&&"
%left "<=" "="
%left "+" "-"
%left "*" 
%nonassoc "!"

%%

program
  : cmds { *out = $1; }
  ;

cmds
  : cmd cmds                      { $$ = new_sequence($1, $2); }
  | %empty                        { $$ = new_skip(); }
  ;

cmd
  : "if" expr block "else" block  { $$ = new_if($2, $3, $5); }
  | "while" expr block            { $$ = new_while($2, $3); }
  | T_VAR ":=" expr               { $$ = new_assignment($1, $3); }
  ;

block
  : "{" cmds "}"                   { $$ = $2; }
  ;

expr
  : "true"                                    { $$ = new_literal(1); }
  | "false"                                   { $$ = new_literal(0); }
  | T_NUMBER                                  { $$ = new_literal($1); }
  | T_VAR                                     { $$ = new_identifier($1); }
  | "(" expr ")"                              { $$ = $2; }
  | "!" expr                                  { $$ = new_unop(NOT, $2); }
  | expr "*" expr                             { $$ = new_binop(MUL, $1, $3); }
  | expr "+" expr                             { $$ = new_binop(ADD, $1, $3); }
  | expr "-" expr                             { $$ = new_binop(SUB, $1, $3); }
  | expr "<=" expr                            { $$ = new_binop(LEQ, $1, $3); }
  | expr "=" expr                             { $$ = new_binop(EQ, $1, $3); }
  | expr "&&" expr                            { $$ = new_binop(AND, $1, $3); }
  ;

%%

void yyerror(const command_t **out, const char *err) {
  fprintf(stderr, "%s\n", err);
}
