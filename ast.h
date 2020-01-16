typedef enum {
    PROGRAM_AST, //プログラムのノード型
    DCLRS_AST, //宣言の集合のノード型
    DCLR_AST, //宣言のノード型
    STMTS_AST, //構文の集合のノード型
    STMT_AST, //構文のノード型
    ASSIGN_AST, //代入文のノード型
    EXPRESS_AST, //式のノード型
    IDENT_AST, //変数のノード型
    ARRAY_AST, //配列のノード型
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
    WHILE_AST,  // whileのノード型
    IF_AST,     // ifのノード型
} NType;

typedef struct node{
    NType type;
    int value;
    char* variable; 
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

Node* build_node(NType t, Node* p1);
Node* build_node2(NType t, Node* p1, Node* p2);
Node* build_node3(NType t, Node* p1, Node* p2, Node* p3);
Node* build_assign_node(NType t, char* str, Node* p1);
Node* build_num_node(NType t, int n);
Node* build_ident_node(NType t, char* str);
Node* build_array_node(NType t, char* str, Node* p1);
