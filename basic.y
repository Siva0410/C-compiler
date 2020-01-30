%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "basic.tab.h"
extern int yylex();
extern int yyerror();
Node* top,*tmp;
%}

%union{
    Node* np;  //抽象構文木
    int ival; //変数
    char* sp;
 }

%token DEFINE ARRAY WHILE IF ELSE SEMIC PLUS TIMES MINUS DEVIDE ASSIGN EQUAL LT  LTE RT RTE REM LPAR RPAR L_BRACKET R_BRACKET L_BRACE R_BRACE INCREMENT FOR
%token <sp> IDENT
%token <ival> NUMBER
%type <np> program declarations declaration statements decl_statement statement loop_stmt cond_stmt assignment_stmt expression term factor var condition increment_stmt for_stmt
%%

program : declarations statements {
    $$ = build_node2(PROGRAM_AST,$1,$2);
    top = $$;
 }
;

declarations : declaration {$$ = build_node(DCLRS_AST,$1);}

declaration : decl_statement declaration {$$ = build_node2(DCLR_AST,$1,$2);}
| decl_statement {$$ = build_node(DCLR_AST,$1);}
;   

decl_statement : DEFINE IDENT SEMIC {$$ = build_ident_node(DEFINE_AST,$2);}
| ARRAY IDENT L_BRACKET NUMBER R_BRACKET SEMIC {$$ = build_array_num_node(DEF_ARRAY_AST,$2,$4);}
;

statements : statement statements {$$ = build_node2(STMTS_AST,$1,$2);}
| statement {$$ = build_node(STMTS_AST,$1);}
;

statement : assignment_stmt SEMIC {$$ = build_node(STMT_AST,$1);}
| increment_stmt {$$ = build_node(STMT_AST,$1);}
| loop_stmt {$$ = build_node(STMT_AST,$1);}
| cond_stmt {$$ = build_node(STMT_AST,$1);}
| for_stmt {$$ = build_node(STMT_AST,$1);}
;

assignment_stmt : IDENT ASSIGN expression {$$=build_ident_node2(ASSIGN_AST, $1, $3, NULL); } 
| IDENT L_BRACKET NUMBER R_BRACKET ASSIGN expression {$$ = build_array_num_node2(ASSIGN_ARRAY_NUM_AST,$1,$3,$6);}
| IDENT L_BRACKET IDENT R_BRACKET ASSIGN expression {$$ = build_array_ident_node2(ASSIGN_ARRAY_IDENT_AST,$1,$3,$6);}
;

increment_stmt : INCREMENT IDENT SEMIC {$$=build_ident_node(INCREMENT_AST, $2);}
| IDENT INCREMENT SEMIC {$$=build_ident_node(INCREMENT_AST, $1);}
;

expression : expression PLUS term {$$ = build_node2(PLUS_AST,$1,$3);}
| expression MINUS term {$$ = build_node2(MINUS_AST,$1,$3);}
| expression REM term {$$ = build_node2(REM_AST,$1,$3);}
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
| IDENT L_BRACKET NUMBER R_BRACKET {$$ = build_array_num_node(ARRAY_NUM_AST,$1,$3);}
| IDENT L_BRACKET IDENT R_BRACKET {$$ = build_array_ident_node(ARRAY_IDENT_AST,$1,$3);}
; 

loop_stmt : WHILE LPAR condition RPAR L_BRACE statements R_BRACE {$$ = build_node2(WHILE_AST,$3,$6);}
;

cond_stmt : IF LPAR condition RPAR L_BRACE statements R_BRACE {$$ = build_node2(IF_AST,$3,$6);}
| IF LPAR condition RPAR L_BRACE statements R_BRACE ELSE L_BRACE statements R_BRACE {$$ = build_node3(IFELSE_AST,$3,$10,$6);}
| IF LPAR condition RPAR L_BRACE statements R_BRACE ELSE cond_stmt {$$ = build_node3(IFELSE_AST,$3,$9,$6);}
;

for_stmt : FOR LPAR assignment_stmt SEMIC condition SEMIC statement RPAR L_BRACE statements R_BRACE
;

condition : expression EQUAL expression {$$ = build_node2(EQUAL_AST,$1,$3);}
| expression LT expression {$$ = build_node2(LT_AST,$1,$3);}
| expression RT expression {$$ = build_node2(RT_AST,$1,$3);}
| expression LTE expression {$$ = build_node2(LTE_AST,$1,$3);}
| expression RTE expression {$$ = build_node2(RTE_AST,$1,$3);}
;

/*
cond_op : EQUAL 
| LT 
| RT;
*/

%% 



int main(void){
    int result;
    Node *parse_result = NULL;
    FILE *text_fp, *data_fp, *fp;
    char c;
    result =yyparse();
    parse_result = top;
    if(!result){
        text_fp = fopen("text.s","w");
        data_fp = fopen("data.s","w");
        fp = fopen("program.s","w");

        printTree(parse_result,text_fp,data_fp);

        fclose(text_fp);
        fclose(data_fp);

        text_fp = fopen("text.s","r");
        data_fp = fopen("data.s","r");
        
        while ((c=fgetc(text_fp)) != EOF) {
            fputc(c, fp);
        }
        while ((c=fgetc(data_fp)) != EOF) {
            fputc(c, fp);
        }
        
        fclose(text_fp);
        fclose(data_fp);
        fclose(fp);
    }
    return 0;
}
