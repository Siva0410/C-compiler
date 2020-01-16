%{
#include "basic.tab.h"
#include <math.h>
extern double vbltable[26];
%}

%%
"define"       { return DEFINE;}
"array"        { return ARRAY; }
"while"        { return WHILE; }
"if"           { return IF; }
"else"         { return ELSE; }
";"            { return SEMIC; }

"+"            { return PLUS; }
"*"            { return TIMES; }
"-"            { return MINUS; }
"/"            { return DEVIDE; }
"="            { return ASSIGN; }
"=="            { return EQUAL; }
"<"            { return LT; }
">"            { return RT; }
"%"            { return REM; }

"("            { return LPAR; }
")"            { return RPAR; }
"["            { return L_BRACKET; } 
"]"            { return R_BRACKET; } 
"{"            { return L_BRACE; } 
"}"            { return R_BRACE; }

[0-9]+         { return NUMBER; }
[a-zA-Z][0-9a-zA-Z]*     { return IDENT; }
[\t ] ; /* ignore whitespace */
%%
