#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

Node* build_node(NType t, Node* p1){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        // yyerror("out of memory");
    }
    p->type = t;
    p->child = p1;
    p->brother = NULL;
    return p;
}


Node* build_node2(NType t, Node* p1, Node* p2){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        // yyerror("out of memory");
    }
    p->type = t;
    p->child = p1;
    p1->brother = p2; // p->child->brother = p2でもよい
    p->brother = NULL;
    return p;
}


Node* build_assign_node(NType t, char* str, Node* p2){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        // yyerror("out of memory");
    }
    p->type = t;
    p->child = p2;
    p->brother = NULL;
    return p;
}


Node* build_node3(NType t, Node* p1, Node* p2, Node* p3){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        // yyerror("out of memory");
    }
    p->type = t;
    p->child = p1;
    p1->brother = p2; // p->child->brother = p2でもよい
    p2->brother = p3;
    p->brother = NULL;
    return p;
}

Node* build_num_node(NType t, int n){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        //yyerror("out of memory");
    }
    p->type = t;
    p->value = n;
    p->child = NULL;
    p->brother = NULL;
    return p;
}

Node* build_ident_node(NType t, char* str){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        yyerror("out of memory");
    }
    p->type = t;
    p->variable = (char*)malloc(sizeof(char)*strlen(str));
    if(p->variable == NULL){
        yyerror("out of memory");
    }
    strcpy(p->variable, str);
    p->child = NULL;
    p->brother = NULL;
    return p;
}

Node* build_array_node(NType t, char* str, Node* p1){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        yyerror("out of memory");
    }
    p->type = t;
    p->variable = (char*)malloc(sizeof(char)*strlen(str));

    if(p->variable == NULL){
        yyerror("out of memory");
    }
    strcpy(p->variable, str);
    p->child = NULL;
    p->brother = NULL;
    return p;
}

void printTree(Node* p)
{
    FILE *fp;
    char init_str[] = "\
    INITIAL_GP = 0x10008000		# initial value of global pointer\n\
	INITIAL_SP = 0x7ffffffc		# initial value of stack pointer\n\
	# system call service number\n\
	stop_service = 99\n\
\n\
	.text\n\
init:\n\
	# initialize $gp (global pointer) and $sp (stack pointer)\n\
	la	$gp, INITIAL_GP		# (下の2行に置き換えられる)\n\
#	lui	$gp, 0x1000		# $gp <- 0x10008000 (INITIAL_GP)\n\ 
#	ori	$gp, $gp, 0x8000\n\
	la	$sp, INITIAL_SP		# (下の2行に置き換えられる)\n\
#	lui	$sp, 0x7fff		# $sp <- 0x7ffffffc (INITIAL_SP)\n\
#	ori	$sp, $sp, 0xfffc\n\
	jal	main			# jump to `main'\n\
	nop				# (delay slot)\n\
	li	$v0, stop_service	# $v0 <- 99 (stop_service)\n\
	syscall				# stop\n\
	nop\n\
	# not reach here\n\
stop:					# if syscall return\n\
	j stop				# infinite loop...\n\
	nop				# (delay slot)\n\
\n\
	.text 	0x00001000";

    fp = fopen("program.s","w");
    
    
    if (p != NULL) {
        fprintf(fp,"%s\n",init_str);    
        switch(p->type){
        case PROGRAM_AST:
            printf("program: ");
            break;
        case DCLRS_AST:
            printf("declarations: ");
            break;
        case DCLR_AST:
            printf("declaration: ");
            break;    
            /*case DeclStmt_AST:
            printf("decl_statement: ");
            break;*/
        case ARRAY_AST:
            printf("array: ");
            break;    
        case STMTS_AST:
            printf("statements: ");
            break;  
        case STMT_AST:
            printf("statement: ");
            break;
        case ASSIGN_AST:
            printf("assigment_stmt: ");
            break;    
        case EXPRESS_AST:
            printf("expression: ");
            break; 
        case PLUS_AST:
            printf("add: ");
            break;
        case MINUS_AST:
            printf("sub: ");
            break;    
            /*case REM_AST:
            printf("rem: ");
            break;*/
        case TIMES_AST:
            printf("mul: ");
            break;
        case DEVIDE_AST:
            printf("div: ");
            break;    
        case TERM_AST:
            printf("term: ");
            break; 
        case FACTOR_AST:
            printf("factor: ");
            break;
        case IDENT_AST:
            printf("ident: ");
            break;    
        case NUM_AST:
            printf("number: ");
            break;
            /*case Var_AST:
            printf("var: ");
            break;*/
        case WHILE_AST:
            printf("loop_stmt: ");
            break;    
        case IF_AST:
            printf("cond_stmt: ");
            break; 
        case EQUAL_AST:
            printf("EQ: ");
            break;
        case LT_AST:
            printf("LT: ");
            break;    
        case RT_AST:
            printf("RT: ");
            break;    
        default:
            break;
        }

        if(p->variable != NULL){
            printf("%s\t", p->variable);
        }else{
            printf("NO IDENT\t");
        }
        
        printf("%d\t",p->value);
        
        
        /* if (p->brother != NULL) { */
        /*     printTree(p->brother);             */
        /* } */
        if (p->child != NULL) {
            printf("(");
            printTree(p->child);
            printf(")");       
        }         
         if (p->brother != NULL) {
            printTree(p->brother);            
        }
    }

}

