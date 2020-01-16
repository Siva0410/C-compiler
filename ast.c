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


/* Node の表示*/
void printNodes(Node *obj){
  if (obj != NULL) {
    if (obj->child != NULL) {
      printNodes(obj->child);
    }

    printf("%d\t", obj->value);
    if(obj->value == 0)
    printf("%s\t", obj->variable);

    if (obj->brother != NULL) {
      printNodes(obj->brother);
    }
  }

}

/*
int main(int argc, char *argv[]){
    Node *n1,*n2,*n3,*n4,*n5,*n6;
    n1=build_ident_node(IDENT_AST,"xx");
    n2=build_num_node(NUM_AST,2);
    n3=build_num_node(NUM_AST,3);
    n4=build_num_node(NUM_AST,4);
    n5=build_node3(NUM_AST,n1,n2,n3);
    n6=build_node2(NUM_AST,n5,n4);
    
    printNodes(n6);
    printf("\n");

  return 0;
}
*/
