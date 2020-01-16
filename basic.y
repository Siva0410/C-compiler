%{
#include <stdio.h>
#include "basic.tab.h"
extern int yylex();
extern int yyerror();
double vbltable[26];
%}

%token DEFINE ARRAY WHILE IF ELSE SEMIC PLUS TIMES MINUS DEVIDE ASSIGN EQUAL LT RT REM LPAR RPAR L_BRACKET R_BRACKET L_BRACE R_BRACE NUMBER IDENT 

%%
main_program : program main_program | program; 

program : declarations statements;

declarations : decl_statement declarations | decl_statement;   

decl_statement : DEFINE IDENT SEMIC | 
ARRAY array_stmt SEMIC ; 

array_stmt : IDENT L_BRACKET expression R_BRACKET ;

statements : statement statements  | statement;

statement : assignment_stmt SEMIC| loop_stmt | cond_stmt;

assignment_stmt : IDENT ASSIGN expression | 
                  IDENT L_BRACKET NUMBER R_BRACKET ASSIGN expression | 
                  IDENT L_BRACKET IDENT R_BRACKET ASSIGN expression;  

expression : expression  add_op term | expression rem_op term | term ;

term : term mul_op factor |factor;

factor : var | LPAR expression RPAR;

add_op : PLUS | MINUS;

mul_op : TIMES | DEVIDE;

rem_op : REM;

var : IDENT | NUMBER | IDENT L_BRACKET NUMBER R_BRACKET; 

loop_stmt : WHILE LPAR condition RPAR L_BRACE statements R_BRACE;

cond_stmt : IF LPAR condition RPAR L_BRACE statements R_BRACE | IF LPAR condition RPAR L_BRACE statements R_BRACE ELSE L_BRACE statements R_BRACE;

condition : expression cond_op expression;

cond_op : EQUAL | LT | RT;


%% 
int main(void){
    if(yyparse()){
        fprintf(stderr, "Error\n");
        return 1;
    }
    return 0;
}
