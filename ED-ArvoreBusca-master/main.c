

// Arquivo main.c
#include <stdio.h>
#include "tree.h"

int main()
{
    Tree **root;
    Data info;
    Tree* node = NULL;
    
    root = cria_inicializa_Tree();
    // Inserindo o elemento de chave 8
    info.chave = 8;
    insere_Tree(root,info);
    // Inserindo o elemento de chave 3
    info.chave = 3;
    insere_Tree(root,info);
    // Inserindo o elemento de chave 0
    info.chave = 0;
    insere_Tree(root,info);
    // Inserindo o elemento de chave 15
    info.chave = 15;
    insere_Tree(root,info);
    // Inserindo o elemento de chave -4
    info.chave = -4;
    insere_Tree(root,info);
    // Inserindo o elemento de chave 6
    info.chave = 6;
    insere_Tree(root,info);
    // Inserindo o elemento de chave 1
    info.chave = 1;
    insere_Tree(root,info);
    // Inserindo o elemento de chave 10
    info.chave = 10;
    insere_Tree(root,info);
    // Inserindo o elemento de chave 4
    info.chave = 4;
    insere_Tree(root,info);
    
    caminha_InOrder_Tree(root);
    printf("\n");
    libera_Tree(root);
    
    return 0;
}
