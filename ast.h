typedef enum {
    PROGRAM_AST, //プログラムのノード型
    DCLRS_AST, //宣言のzentaiのノード型
    DCLR_AST, //宣言のノード型
    DEFINE_AST, //define str node
    DEF_ARRAY_AST,
    DEF_WARRAY_AST,
    STMTS_AST, //構文の集合のノード型
    STMT_AST, //構文のノード型
    ASSIGN_AST, //代入文のノード型
    ASSIGN_ARRAY_NUM_AST,
    ASSIGN_ARRAY_IDENT_AST,
    ASSIGN_WARRAY_NUM_AST,
    ASSIGN_WARRAY_IDENT_AST,
    EXPRESS_AST, //式のノード型
    IDENT_AST, //変数のノード型
    ARRAY_NUM_AST,
    ARRAY_IDENT_AST,
    WARRAY_NUM_AST,
    WARRAY_IDENT_AST,
    NUM_AST,   //整数のノード型
    FACTOR_AST, //因子のノード型
    TERM_AST, //項のノード型
    PLUS_AST, //加算演算子のノード型
    MINUS_AST, //減算演算子のノード型
    TIMES_AST, //乗算演算子のノード型
    DEVIDE_AST, //除算演算子のノード型
    EQUAL_AST,
    LT_AST,
    RT_AST,
    LTE_AST,
    RTE_AST,
    REM_AST,
    WHILE_AST,  // whileのノード型
    IF_AST,     // ifのノード型
    IFELSE_AST,     // ifelse
    INCREMENT_AST,
    FOR_AST,
} NType;

typedef enum {
    GROBAL,
    LOCAL,
} SScope;

typedef struct node{
    NType type;
    int value;
    int value2;
    char* variable; 
    char* ident;
    char* ident2;
    struct node *child;
    struct node *brother;
} Node;

typedef struct symbols{
    int symno; //変数番号．ユニークになるようにつけること 
    char *symbolname; //変数名
    struct symbols* next; //次の変数へのリンク
} Symbols;

typedef struct array{
    int symno; //変数番号．ユニークになるようにつけること 
    struct array* next; //次の変数へのリンク
} Array;

#define SIMNAMELEN 64
#define MAXSIMENTRIES 100

typedef struct simTableEntry {
    char name[SIMNAMELEN];
    //SType type;
    //SScope scope;
    int wide, height;
    //SValue value;
} SimTableEntry;

SimTableEntry simTable[MAXSIMENTRIES];

Node* build_node(NType t, Node* p1);
Node* build_node2(NType t, Node* p1, Node* p2);
Node* build_node3(NType t, Node* p1, Node* p2, Node* p3);
Node* build_node4(NType t, Node* p1, Node* p2, Node* p3, Node* p4);
Node* build_num_node(NType t, int n);
Node* build_ident_node(NType t, char* str);
Node* build_ident_node2(NType t, char* str,Node* p1, Node* p2);
Node* build_array_num_node(NType t, char* str, int num);
Node* build_array_ident_node(NType t, char* str, char* ident);
Node* build_array_num_node2(NType t, char* str, int num, Node* p1);
Node* build_array_ident_node2(NType t, char* str, char* ident, Node* p1);
Node* build_warray_num_node(NType t, char* str, int num1, int num2);
Node* build_warray_ident_node(NType t, char* str, char* ident1, char* ident2);
Node* build_warray_num_node2(NType t, char* str, int num1, int num2, Node* p1);
Node* build_warray_ident_node2(NType t, char* str, char* ident1, char* ident2, Node* p1);
void printTree(Node *obj,FILE *fp1,FILE *fp2);

