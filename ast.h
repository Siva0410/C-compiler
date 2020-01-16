typedef enum {
    IDENT_AST, //変数のノード型
    NUM_AST,   //整数のノード型
    ASSIGN_AST,//代入文の=のノード型
    PLUS_AST, //加算演算子のノード型
    MINUS_AST, //減算演算子のノード型
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
