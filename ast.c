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
    strcpy(p->variable, str);
    p->child = NULL;
    p->brother = NULL;
    return p;
}

void printTree(Node* p)
{
    // printf("(");
    if (p != NULL) {
        
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

