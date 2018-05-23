%{
#include "parser.tab.h"
%}

%option bison-bridge

%%

"+"     { return T_PLUS; }
"-"     { return T_MINUS; }
"*"     { return T_STAR; }
"="     { return T_EQUALS; }
"<="    { return T_LESS_EQUALS; }
"&&"    { return T_AMPERSANDS; }
"!"     { return T_BANG; }
";"     { return T_SEMICOLON; }
"("     { return T_LPAREN; }
")"     { return T_RPAREN; }
"{"     { return T_LBRACE; }
"}"     { return T_RBRACE; }
":="    { return T_COLON_EQUALS; }
"true"  { return T_TRUE; }
"false" { return T_FALSE; }
"if"    { return T_IF; }
"else"  { return T_ELSE; }
"while" { return T_WHILE; }
[0-9]+  { yylval->val = atoi(yytext); return T_NUMBER; }
[a-zA-Z][a-zA-Z0-9]* { yylval->id = strdup(yytext); return T_VAR; }
[ \t\n] { /* ignore */ }
.       { fprintf(stderr, "Unrecognized character %c\n", *yytext); }
