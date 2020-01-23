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

Node* build_ident_node2(NType t, char *str,Node*p1, Node* p2){
    Node *p;
    
    p = (Node *)malloc(sizeof(Node));
    if(p == NULL){
        yyerror("out of memory");
    }
    p->type = t;
    
    p->variable = (char *)malloc(sizeof(char)*strlen(str));
    if(p->variable == NULL){
        yyerror("out of memory");
    }
    
    strncpy(p->variable, str, sizeof(char)*strlen(str));
    p->child = p1;
    p1->brother = p2; // p->child->brother = p2でもよい
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

/***************************************************************************************/
void initial_print(FILE* text_fp){
    char init_str[] = "\
\tINITIAL_GP = 0x10008000		# initial value of global pointer\n \
	INITIAL_SP = 0x7ffffffc		# initial value of stack pointer\n\
\t# system call service number\n\
\tstop_service = 99\n\
\n\
\t.text\n\
init:\n\
\t# initialize $gp (global pointer) and $sp (stack pointer)\n\
\tla	$gp, INITIAL_GP\n\
\tla	$sp, INITIAL_SP\n\
\tjal	main			# jump to `main'\n\
\tnop				# (delay slot)\n\
\tli	$v0, stop_service	# $v0 <- 99 (stop_service)\n\
\tsyscall				# stop\n\
\tnop\n\
\t# not reach here\n\
stop:					# if syscall return\n\
\tj stop				# infinite loop...\n\
\tnop				# (delay slot)\n\
\n\
\t.text 	0x00001000\n\
main:\n";
    

    fprintf(text_fp,"%s",init_str);
    fprintf(text_fp,"\tsubu  $sp, $sp, 32\n\tsw  $ra, 28($sp)\n");
}

void tail_print(FILE* text_fp){
    fprintf(text_fp,"end:\n\tlw  $ra, 28($sp)\n\taddu  $sp, $sp, 32\n");
    fprintf(text_fp,"\tjr $ra\n");
}

void assign_print(Node* p,FILE* text_fp){
    fprintf(text_fp,"\tli   $t0, %s\n",p->child->variable);
    //if(staNum == 0 && regNum == 1){
    fprintf(text_fp,"\tsw   $v0, 0($t0)\n");        
    //}else if(staNum != 0){
    //  fprintf(fp, "\tlw   $v0, %d($sp)\n",staNum-4);
    //  fprintf(fp,"\tsw   $v0, 0($t4)\n");      
    //}
}
/*
void assign_print(Node* p,FILE* sata_fp){

}

void assign_print(Node* p,FILE* sata_fp){

}

void assign_print(Node* p,FILE* sata_fp){

}
*/
/***************************************************************************************/

void switchNode(Node *p,FILE *text_fp,FILE *data_fp){

        if (p->child != NULL) {
            printTree(p->child,text_fp,data_fp);      
        }         
        if (p->brother != NULL) {
            printTree(p->brother,text_fp,data_fp);            
        }
}

void printTree(Node* p,FILE *text_fp,FILE *data_fp){

    if (p != NULL) {
        switch(p->type){

        case PROGRAM_AST:
            initial_print(text_fp);
            switchNode(p,text_fp,data_fp);
            tail_print(text_fp);
            break;
        case DCLRS_AST:
            fprintf(data_fp,"\t.data   0x10004000\n");
            switchNode(p,text_fp,data_fp);
            break;
        case DCLR_AST:
            switchNode(p,text_fp,data_fp);
            break;
        case DEFINE_AST:
            fprintf(data_fp,"%s:\t.word   0x00000000\n",p->variable);
            switchNode(p,text_fp,data_fp);
            break;    
        case ARRAY_AST:
            switchNode(p,text_fp,data_fp);
            //printf("array: ");
            break;    
        case STMTS_AST:
            switchNode(p,text_fp,data_fp);
            //printf("statements: ");
            break;  
        case STMT_AST:
            switchNode(p,text_fp,data_fp);
            printf("a\n");
            break;
        case ASSIGN_AST:
            printf("b\n");
            switchNode(p,text_fp,data_fp);
            printf("b-2\n");
            assign_print(p,text_fp);
            break;    
        case EXPRESS_AST:
            printf("c\n");
            switchNode(p,text_fp,data_fp);
            p->value = p->child->value;
            //fprintf(text_fp,"    add  $v0, $v0, $zero\n");
            break; 
        case PLUS_AST:
            switchNode(p,text_fp,data_fp);
            break;
        case MINUS_AST:
            switchNode(p,text_fp,data_fp);
            //printf("sub: ");
            break;    
            /*case REM_AST:
              printf("rem: ");
              break;*/
        case TIMES_AST:
            switchNode(p,text_fp,data_fp);
            //printf("mul: ");
            break;
        case DEVIDE_AST:
            switchNode(p,text_fp,data_fp);
            //printf("div: ");
            break;    
        case TERM_AST:
            printf("d\n");
            switchNode(p,text_fp,data_fp);
            p->value = p->child->value;
            //fprintf(text_fp,"    add  $v0, $v0, $zero\n");
            break; 
        case FACTOR_AST:
            printf("e\n");
            switchNode(p,text_fp,data_fp);
            p->value = p->child->value;
            fprintf(text_fp,"%d\n",p->child->value);
            //fprintf(text_fp,"    add  $v0, $v0, $zero\n");
            break;
        case IDENT_AST:
            printf("f\n");
            //fprintf(text_fp,"\tli  $v0, %d\n",p->value);
            //fprintf(text_fp,"\tli  $t0, %s\n\tlw  $v0, 0($t0)\n",p->variable);
            break;    
        case NUM_AST:
            printf("g\n");
            fprintf(text_fp,"\tli  $v0, %d\n",p->value);
            break;
            /*case Var_AST:
              printf("var: ");
              break;*/
        case WHILE_AST:
            switchNode(p,text_fp,data_fp);
            //printf("loop_stmt: ");
            break;    
        case IF_AST:
            switchNode(p,text_fp,data_fp);
            //printf("cond_stmt: ");
            break; 
        case EQUAL_AST:
            switchNode(p,text_fp,data_fp);
//        fprintf(text_fp,"    %s = %d\n",p->child->variable,p->child->brother->value);
            break;
        case LT_AST:
            switchNode(p,text_fp,data_fp);
            //printf("LT: ");
            break;    
        case RT_AST:
            switchNode(p,text_fp,data_fp);
            //printf("RT: ");
            break;    
        default:
            fprintf(stderr,"error!");
            break;
        }
    }
}

