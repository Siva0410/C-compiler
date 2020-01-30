#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int stack_num = 0;
int loop_num = 0;
int loop_rec = 0;
int if_num = 0;
int if_else_num = 0;
int if_else_rec = 0;
int eq_num = 0;
int leq_num = 0;
int req_num = 0;

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

Node* build_node4(NType t, Node* p1, Node* p2, Node* p3, Node* p4){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        // yyerror("out of memory");
    }
    p->type = t;
    p->child = p1;
    p1->brother = p2; // p->child->brother = p2でもよい
    p2->brother = p3;
    p3->brother = p4;
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

Node* build_array_num_node(NType t, char* str, int num){
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
    p->value = num;
    p->child = NULL;
    p->brother = NULL;
    return p;
}

Node* build_array_num_node2(NType t, char* str, int num, Node* p1){
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
    p->value = num;
    p->child = p1;
    p->brother = NULL;
    return p;
}


Node* build_array_ident_node(NType t, char* str, char* ident){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        yyerror("out of memory");
    }
    p->type = t;
    p->variable = (char*)malloc(sizeof(char)*strlen(str));
    if(p->variable == NULL){
        yyerror("out of memory");
    }

    p->ident = (char*)malloc(sizeof(char)*strlen(str));
    if(p->ident == NULL){
        yyerror("out of memory");
    }

    strcpy(p->variable, str);
    strcpy(p->ident, ident);

    p->child = NULL;
    p->brother = NULL;
    return p;
}

Node* build_array_ident_node2(NType t, char* str, char* ident, Node* p1){
    Node *p;
    if((p = (Node *)malloc(sizeof(Node))) == NULL){
        yyerror("out of memory");
    }
    p->type = t;
    p->variable = (char*)malloc(sizeof(char)*strlen(str));
    if(p->variable == NULL){
        yyerror("out of memory");
    }

    p->ident = (char*)malloc(sizeof(char)*strlen(str));
    if(p->ident == NULL){
        yyerror("out of memory");
    }

    strcpy(p->variable, str);
    strcpy(p->ident, ident);

    p->child = p1;
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
    fprintf(text_fp,"\taddi  $sp, $sp, -32\n\tsw  $ra, 28($sp)\n");
}

void tail_print(FILE* text_fp){
    fprintf(text_fp,"end:\n\tlw  $ra, 28($sp)\n\taddi  $sp, $sp, 32\n");
    fprintf(text_fp,"\tjr $ra\n\n");
}

void assign_print(Node* p,FILE* text_fp){
    fprintf(text_fp,"\tli   $t0, %s\n",p->variable);
    fprintf(text_fp,"\tsw   $v0, 0($t0)\n");        
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
            fprintf(data_fp,"%s:\t.word   0x0000\n",p->variable);
            switchNode(p,text_fp,data_fp);
            break;    

        case DEF_ARRAY_AST:
            fprintf(data_fp,"%s:\t.space  %d\n",p->variable,p->value*4);
            switchNode(p,text_fp,data_fp);
            break;    

        case ARRAY_NUM_AST:
            fprintf(text_fp,"\tli  $t0, %s\n\tlw  $v0, %d($t0)\n\tnop\n",p->variable,p->value*4);
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;  

        case ARRAY_IDENT_AST:
            fprintf(text_fp,"\tli  $t0, %s\n",p->variable);
            fprintf(text_fp,"\tli  $t1, %s\n\tlw  $t2, 0($t1)\n\tnop\n",p->ident);
            fprintf(text_fp,"\tsll  $t2, $t2, 2\n");
            fprintf(text_fp,"\tadd  $t0, $t0, $t2\n\tlw  $v0, 0($t0)\n\tnop\n");
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;

        case STMTS_AST:
            switchNode(p,text_fp,data_fp);
            break;  

        case STMT_AST:
            switchNode(p,text_fp,data_fp);
            break;

        case ASSIGN_AST:
            switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tli   $t0, %s\n",p->variable);
            fprintf(text_fp,"\tsw   $v0, 0($t0)\n");
            stack_num = 0;
            break;    

        case ASSIGN_ARRAY_NUM_AST:
            switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tli   $t0, %s\n",p->variable);
            fprintf(text_fp,"\tsw   $v0, %d($t0)\n",p->value*4);
            stack_num = 0;
            break;  

        case ASSIGN_ARRAY_IDENT_AST:
            switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tli  $t0, %s\n",p->variable);
            fprintf(text_fp,"\tli  $t1, %s\n\tlw  $t2, 0($t1)\n\tnop\n",p->ident);
            fprintf(text_fp,"\tsll  $t2, $t2, 2\n\tnop\n");
            fprintf(text_fp,"\tadd  $t0, $t0, $t2\n\tnop\n\tsw  $v0, 0($t0)\n\tnop\n");
            stack_num = 0;
            break; 

        case EXPRESS_AST:
            switchNode(p,text_fp,data_fp);
            //p->value = p->child->value;
            break; 

        case PLUS_AST:
            /*switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tlw  $t0, 0($sp)\n");
            fprintf(text_fp,"\tlw  $t1, 4($sp)\n\tnop\n");
            fprintf(text_fp,"\tadd  $v0, $t0, $t1\n");*/

            switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tlw  $t0, %d($sp)\n",(stack_num-2)*4);
            fprintf(text_fp,"\tlw  $t1, %d($sp)\n\tnop\n",(stack_num-1)*4);
            fprintf(text_fp,"\tadd  $v0, $t0, $t1\n\tnop\n");
            stack_num=stack_num-2;
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;

        case MINUS_AST:
            switchNode(p,text_fp,data_fp);
            break;    

        case REM_AST:
            switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tlw  $t0, %d($sp)\n",(stack_num-2)*4);
            fprintf(text_fp,"\tlw  $t1, %d($sp)\n\tnop\n",(stack_num-1)*4);
            fprintf(text_fp,"\tdiv  $t0, $t1\n");
            fprintf(text_fp,"\tmfhi  $v0\n");
            stack_num=stack_num-2;
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;

        case TIMES_AST:
            switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tlw  $t0, %d($sp)\n",(stack_num-2)*4);
            fprintf(text_fp,"\tlw  $t1, %d($sp)\n\tnop\n",(stack_num-1)*4);
            fprintf(text_fp,"\tmult  $t0, $t1\n");
            fprintf(text_fp,"\tmflo  $v0\n");
            stack_num=stack_num-2;
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;

        case DEVIDE_AST:
            switchNode(p,text_fp,data_fp);
            fprintf(text_fp,"\tlw  $t0, %d($sp)\n",(stack_num-2)*4);
            fprintf(text_fp,"\tlw  $t1, %d($sp)\n\tnop\n",(stack_num-1)*4);
            fprintf(text_fp,"\tdiv  $t0, $t1\n");
            fprintf(text_fp,"\tmflo  $v0\n");
            stack_num=stack_num-2;
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;    

        case TERM_AST:
            switchNode(p,text_fp,data_fp);
            //p->value = p->child->value;
            break; 

        case FACTOR_AST:
            switchNode(p,text_fp,data_fp);
            //p->value = p->child->value;
            break;

        case INCREMENT_AST:
            fprintf(text_fp,"\tli  $t0, %s\n\tlw  $v0, 0($t0)\n\tnop\n",p->variable);
            fprintf(text_fp,"\taddi  $v0, $v0, 1\n\tnop\n");
            fprintf(text_fp,"\tsw  $v0, 0($t0)\n");
            break;  

        case IDENT_AST:
            fprintf(text_fp,"\tli  $t0, %s\n\tlw  $v0, 0($t0)\n\tnop\n",p->variable);
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;    

        case NUM_AST:
            fprintf(text_fp,"\tli  $v0, %d\n",p->value);
            fprintf(text_fp,"\tsw  $v0, %d($sp)\n",stack_num*4);
            stack_num++;
            break;

        case WHILE_AST:
            fprintf(text_fp,"L%d_%d:\n",loop_rec,loop_num);
            printTree(p->child,text_fp,data_fp);
            fprintf(text_fp,"\tbeq  $v0, $zero, L%d_%d\n",loop_rec,loop_num+1);
            loop_rec++;
            printTree(p->child->brother,text_fp,data_fp);  
            loop_rec--;
            fprintf(text_fp,"\tj  L%d_%d\n",loop_rec,loop_num);
            fprintf(text_fp,"L%d_%d:\n",loop_rec,loop_num+1);
            if(loop_rec==0) loop_num=loop_num+2;
            break;

        case IF_AST:
            printTree(p->child,text_fp,data_fp);
            fprintf(text_fp,"\tbeq  $v0, $zero, C%d\n",if_num);
            printTree(p->child->brother,text_fp,data_fp);  
            fprintf(text_fp,"C%d:\n",if_num);
            if_num = if_num+1;
            break; 

        case IFELSE_AST:
            printTree(p->child,text_fp,data_fp);
            fprintf(text_fp,"\tbeq  $v0, $zero, CE%d_%d\n",if_else_rec,if_else_num);
            printTree(p->child->brother->brother,text_fp,data_fp);  
            fprintf(text_fp,"\tj  CE%d_%d\n",if_else_rec,if_else_num+1);
            //else
            p->child->brother->brother = NULL;
            fprintf(text_fp,"CE%d_%d:\n",if_else_rec,if_else_num);
            if_else_rec++;
            printTree(p->child->brother,text_fp,data_fp);  
            if_else_rec--;
            fprintf(text_fp,"CE%d_%d:\n",if_else_rec,if_else_num+1);
            break; 
            
        case FOR_AST:
            fprintf(text_fp,"L%d_%d:\n",loop_rec,loop_num);
            printTree(p->child,text_fp,data_fp);
            fprintf(text_fp,"\tbeq  $v0, $zero, L%d_%d\n",loop_rec,loop_num+1);
            loop_rec++;
            printTree(p->child->brother,text_fp,data_fp);  
            loop_rec--;
            fprintf(text_fp,"\tj  L%d_%d\n",loop_rec,loop_num);
            fprintf(text_fp,"L%d_%d:\n",loop_rec,loop_num+1);
            if(loop_rec==0) loop_num=loop_num+2;
            break;

        case EQUAL_AST:
            printTree(p->child,text_fp,data_fp); 
            fprintf(text_fp,"\tlw  $t0, %d($sp)\n",(stack_num-2)*4);
            fprintf(text_fp,"\tlw  $t1, %d($sp)\n",(stack_num-1)*4);
            fprintf(text_fp,"\tli $v0, 0\n");
            fprintf(text_fp,"\tbne  $t0, $t1, EQ%d\n\tnop\n",eq_num);
            fprintf(text_fp,"\tli  $v0, 1\n");
            fprintf(text_fp,"EQ%d:\n",eq_num++);
            stack_num = 0;
            break;
  
        case LT_AST:
            printTree(p->child,text_fp,data_fp); 
            fprintf(text_fp,"\tlw $t0, 0($sp)\n");
            fprintf(text_fp,"\tlw $t1, 4($sp)\n\tnop\n");
            fprintf(text_fp,"\tslt  $v0, $t0, $t1\n");
            stack_num = 0;
            break;    

        case LTE_AST:
            printTree(p->child,text_fp,data_fp); 
            fprintf(text_fp,"\tlw  $t0, %d($sp)\n",(stack_num-2)*4);
            fprintf(text_fp,"\tlw  $t1, %d($sp)\n",(stack_num-1)*4);
            fprintf(text_fp,"\tli $v0, 1\n");
            fprintf(text_fp,"\tbeq  $t0, $t1, LEQ%d\n\tnop\n",leq_num);

            fprintf(text_fp,"\tslt  $v0, $t0, $t1\n");
            fprintf(text_fp,"LEQ%d:\n",leq_num++);
            stack_num = 0;
            break;    
        case RT_AST:
            printTree(p->child,text_fp,data_fp); 
            fprintf(text_fp,"\tlw $t0, 0($sp)\n\n");
            fprintf(text_fp,"\tlw $t1, 4($sp)\n\tnop\n");
            fprintf(text_fp,"\tslt  $v0, $t1, $t0\n");
            stack_num = 0;
            break;    
        case RTE_AST:
            printTree(p->child,text_fp,data_fp); 
            fprintf(text_fp,"\tlw  $t0, %d($sp)\n",(stack_num-2)*4);
            fprintf(text_fp,"\tlw  $t1, %d($sp)\n",(stack_num-1)*4);
            fprintf(text_fp,"\tli $v0, 1\n");
            fprintf(text_fp,"\tbeq  $t0, $t1, REQ%d\n\tnop\n",req_num);

            fprintf(text_fp,"\tslt  $v0, $t1, $t0\n");
            fprintf(text_fp,"REQ%d:\n",req_num++);
            stack_num = 0;
            break;    
        default:
            fprintf(stderr,"error!");
            break;
        }
    }
}

