

// Arquivo tree.c
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

struct no
{
    Data data;
    struct no *esq;
    struct no *dir;
};

Tree ** cria_inicializa_Tree()
{
    Tree **novo;
    // Cria um novo endereco para a raiz da arvore
    novo = (Tree **) malloc (sizeof(Tree *));
    // Se alocacao deu certo
    if(novo != NULL)
    {
        // Inicializa a arvore (uma arvore vazia)
        *novo = NULL;
    }
}

int ehVazia_Tree(Tree **root)
{
    if(root != NULL)
    {
        if(*root == NULL)
        {
            return 1; // eh vazia
        }
        else
        {
            return 0; // nao eh vazia
        }
    }
    return -1; // nao existe
}

int insere_Tree(Tree **root, Data elem)
{
    Tree *novo_no;
    
    if(root == NULL)
    {
        return -1; // A arvore nao existe
    }
    
    novo_no = (Tree *) malloc (sizeof(Tree));
    if(novo_no == NULL)
    {
        return -1; // Alocacao falhou
    }
    // Preenchendo o novo no
    novo_no->data = elem;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    
    if(ehVazia_Tree(root) == 1)
    {
        *root = novo_no;
        return 1;
    }
    
    return insere_no_Tree(*root,novo_no);
}

int insere_no_Tree(Tree *root, Tree *novo)
{
    // evita repeticoes
    if(root->data.chave == novo->data.chave)
    {
        return 0;
    }
    // Chave do elemento < chave da raiz?
    if(novo->data.chave < root->data.chave)
    {
        //Sim? Vou para a sub-arvore esquerda
        if(root->esq == NULL)
        {
            root->esq = novo;
            return 1;
        }
        else
        {
            // Nao! Existe uma sub-arvore esquerda
            // Caminha para a sub-arvore esquerda
            return insere_no_Tree(root->esq,novo);
        }
    }
    else
    {
        // Verifica se a sub-arvore direita existe
        if(root->dir == NULL)
        {
            // Se nao existe sub-arvore direita
            root->dir = novo;
            return 1;
        }
        else
        {
            // Sim! Existe uma sub-arvore direita
            // Caminha para a sub-arvore direita
            return insere_no_Tree(root->dir,novo);
        }
    }
}

void visit(Tree *no)
{
    printf(" %d ",no->data.chave);
}

void caminha_InOrder_Tree(Tree **root)
{
    if(root != NULL)
    {
        caminha_InOrder_Tree_rec(*root);
    }
}

void caminha_InOrder_Tree_rec(Tree *root)
{
    // Criterio de parada da recursao
    if(root == NULL)
    {
        return ;
    }
    caminha_InOrder_Tree_rec(root->esq);
    visit(root);
    caminha_InOrder_Tree_rec(root->dir);
}

int busca_Tree(Tree** root, Data elem, Tree* end_no){
    Tree* aux;
    if(root==NULL || *root==NULL){ return -1; } /*caso arvore nao exista ou vazia retorna -1*/
    aux = *root;
    while(aux!=NULL){
        if(elem.chave==aux->data.chave){
            end_no = aux;
            return 1;
        }
        else if(elem.chave > aux->data.chave){
            //direita
            aux = aux->dir;
        }
        else if(elem.chave < aux->data.chave){
            //esquerda
            aux = aux->esq;
        }
    }
    end_no = NULL;
    return 0;
}

void libera_Tree(Tree **root)
{
    if(root != NULL)
    {
        libera_Tree_rec(*root);
    }
    free(root);
}

void libera_Tree_rec(Tree *root)
{
    // Criterio de parada da recursao
    if(root == NULL)
    {
        return ;
    }
    libera_Tree_rec(root->esq);
    libera_Tree_rec(root->dir);
    free(root);
}


