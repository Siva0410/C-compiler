%{
#include "ast.h"
#include "basic.tab.h"
#include <math.h>
%}

%%
"define"       { return DEFINE;}
"array"        { return ARRAY; }
"while"        { return WHILE; }
"for"          { return FOR; }
"if"           { return IF; }
"else"         { return ELSE; }
";"            { return SEMIC; }
"++"           { return INCREMENT;}
"+"            { return PLUS; }
"*"            { return TIMES; }
"-"            { return MINUS; }
"/"            { return DEVIDE; }
"="            { return ASSIGN; }
"=="           { return EQUAL; }
"<"            { return LT; }
"<="           { return LTE; }
">"            { return RT; }
">="           { return RTE; }
"%"            { return REM; }

"("            { return LPAR; }
")"            { return RPAR; }
"["            { return L_BRACKET; } 
"]"            { return R_BRACKET; } 
"{"            { return L_BRACE; } 
"}"            { return R_BRACE; }

[0-9]+         { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z][0-9a-zA-Z]*     { yylval.sp = strdup(yytext); return IDENT; }
[\t\n ] ; /* ignore whitespace */
%%
