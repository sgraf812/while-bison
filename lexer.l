%{
    typedef enum yytokentype {
        T_EOF,
        T_NUMBER,
        T_TRUE,
        T_FALSE,
        T_VAR,
        T_PLUS,
        T_MINUS,
        T_STAR,
        T_EQUALS,
        T_LESS_EQUALS,
        T_AMPERSANDS,
        T_BANG,
        T_SEMICOLON,
        T_IF,
        T_THEN,
        T_ELSE,
        T_WHILE,
        T_DO,
        T_COLON_EQUALS,
        T_N_TOKEN_TYPE
    } token_type_t;

    int yyval;
    const char *yyvar;
%}

%%

\EOF    { return T_EOF; }
"+"     { return T_PLUS; }
"-"     { return T_MINUS; }
"*"     { return T_STAR; }
"="     { return T_EQUALS; }
"<="    { return T_LESS_EQUALS; }
"&&"    { return T_AMPERSANDS; }
"!"     { return T_BANG; }
";"     { return T_SEMICOLON; }
"true"  { return T_TRUE; }
"false" { return T_FALSE; }
"if"    { return T_IF; }
"then"  { return T_THEN; }
"else"  { return T_ELSE; }
"while" { return T_WHILE; }
"do"    { return T_DO; }
":="    { return T_COLON_EQUALS; }
[0-9]+  { yyval = atoi(yytext); return T_NUMBER; }
[a-zA-Z][a-zA-Z0-9]* { yyvar = strdup(yytext); return T_VAR; }
[ \t\n] { /* ignore */ }
.       { printf("Unrecognized character %c\n", *yytext); }

%%

int main() {
    int tok;
    while (tok = yylex()) {
        printf("%d", tok);
        if (tok == T_NUMBER) printf(" %d", yyval);
        if (tok == T_VAR) printf(" %s", yyvar);
        printf("\n");
    }
}
