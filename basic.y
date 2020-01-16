%{
#include <stdio.h>
#include "ast.h"
#include "basic.tab.h"
extern int yylex();
extern int yyerror();
Node* top;
%}

%union{
    Node* np;  //抽象構文木
    int ival; //変数
    char* sp;
 }

%token DEFINE ARRAY WHILE IF ELSE SEMIC PLUS TIMES MINUS DEVIDE ASSIGN EQUAL LT RT REM LPAR RPAR L_BRACKET R_BRACKET L_BRACE R_BRACE
%token <sp> IDENT
%token <ival> NUMBER
%type <np> program declarations statements decl_statement array_stmt statement loop_stmt cond_stmt assignment_stmt expression term factor var condition 
%%

program : declarations statements {top = build_node2(PROGRAM_AST,$1,$2);}
;

declarations : decl_statement declarations {$$ = build_node2(DCLRS_AST,$1,$2);}
| decl_statement {$$ = build_node(DCLRS_AST,$1);}
;   

decl_statement : DEFINE IDENT SEMIC {$$ = build_ident_node(DCLR_AST,$2);}
| ARRAY array_stmt SEMIC {$$ = build_node(DCLR_AST,$2);}
; 

 array_stmt : IDENT L_BRACKET expression R_BRACKET {$$ = build_array_node(ARRAY_AST,$1,$3);}
;

statements : statement statements {$$ = build_node2(STMTS_AST,$1,$2);}
| statement {$$ = build_node(STMTS_AST,$1);}
;

statement : assignment_stmt SEMIC {$$ = build_node(STMT_AST,$1);}
| loop_stmt {$$ = build_node(STMT_AST,$1);}
| cond_stmt {$$ = build_node(STMT_AST,$1);}
;

assignment_stmt : IDENT ASSIGN expression {$$ = build_assign_node(ASSIGN_AST,$1,$3);} 
| array_stmt ASSIGN expression {$$ = build_node2(ASSIGN_AST,$1,$3);}
;

expression : expression PLUS term {$$ = build_node2(PLUS_AST,$1,$3);}
| expression MINUS term {$$ = build_node2(MINUS_AST,$1,$3);}
| expression REM term 
| term {$$ = build_node(EXPRESS_AST,$1);}
;

term : term TIMES factor {$$ = build_node2(TIMES_AST,$1,$3);}
| term DEVIDE factor {$$ = build_node2(DEVIDE_AST,$1,$3);}
| factor {$$ = build_node(TERM_AST,$1);}
;

factor : var {$$ = build_node(FACTOR_AST,$1);}
| LPAR expression RPAR {$$ = build_node(FACTOR_AST,$2);}
;

/*add_op : PLUS {$$ = build_node(PLUS_AST,$1);}
| MINUS {$$ = build_node(MINUS_AST,$1);}
;

mul_op : TIMES {$$ = build_node(TIMES_AST,$1);}
| DEVIDE {$$ = build_node(DEVIDE_AST,$1);}
;

rem_op : REM;
*/
var : IDENT {$$ = build_ident_node(IDENT_AST,$1);}
| NUMBER {$$ = build_num_node(NUM_AST,$1);}
| array_stmt {$$ = build_node(ARRAY_AST,$1);}
; 

loop_stmt : WHILE LPAR condition RPAR L_BRACE statements R_BRACE {$$ = build_node2(WHILE_AST,$3,$6);}
;

cond_stmt : IF LPAR condition RPAR L_BRACE statements R_BRACE {$$ = build_node2(IF_AST,$3,$6);}
| IF LPAR condition RPAR L_BRACE statements R_BRACE ELSE L_BRACE statements R_BRACE {$$ = build_node3(IF_AST,$3,$6,$10);}
;

condition : expression EQUAL expression {$$ = build_node2(EQUAL_AST,$1,$3);}
| expression LT expression {$$ = build_node2(LT_AST,$1,$3);}
| expression RT expression {$$ = build_node2(RT_AST,$1,$3);}
;

/*
cond_op : EQUAL 
| LT 
| RT;
*/

%% 
int main(void){
    if(yyparse()){
        fprintf(stderr, "Error\n");
        return 1;
 }else{
    printNodes(top);
 }
    return 0;
}
