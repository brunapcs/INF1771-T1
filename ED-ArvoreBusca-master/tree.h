
// Arquivo tree.h
struct info
{
    int chave;
};

typedef struct info Data;

typedef struct no Tree;

// Prototipo das funcoes
Tree ** cria_inicializa_Tree();

int ehVazia_Tree(Tree **root);

int insere_Tree(Tree **root, Data elem);

int insere_no_Tree(Tree *root, Tree *novo);

void visit(Tree *no);

void caminha_InOrder_Tree(Tree **root);

void caminha_InOrder_Tree_rec(Tree *root);

int busca_Tree(Tree** root, Data elem, Tree* end_no);
void libera_Tree(Tree **root);
void libera_Tree_rec(Tree *root);












