#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <assert.h>
#include "LISTA.h"



/***********************************************************************
 *  Tipo de dados
 ***********************************************************************/
typedef struct no_lista_cidades{
    
    struct no_lista_cidades *pAnt;
    /*ponteiro para o no anterior da lista*/
    
    struct no_lista_cidades *pProx;
    /*ponteiro para proxima cidade*/
    
    int linha;
    /*numero da cidade na matriz*/
    
    int col;
    /*numero da proxima cidade na matriz*/
    
    int dist;
    /*distancia entre as duas cidades em questao*/
}noCidade;


struct lista_cidades {
    
    noCidade *pCabeca;
    /*ponteiro para primeira cidade da lista*/
    
    noCidade *pCorr;
    /*ponteiro para no corrente da lista */
    
 } ;

typedef struct lista_cidades listaCidades;

/***************************************************************************
*
*  Funcao: Criar lista
***************************************************************************/
pListaCid CriaLista()
{
    pListaCid pLista = (listaCidades *)malloc(sizeof(listaCidades));
    if ( pLista == NULL )
    {
        puts(" erro ao criar lista de cidades");
        exit(1);
    }
    return pLista ;
} /* Fim */


/***************************************************************************
 * Funcao: Insere elemento na lista de Cidades e o inicializa com os
    valores passados nos parametros.
    Ponteiro de pCorr da lista apontara para o no inserido.
    Se lista estiver vazia o no sera a cabeca.
 **********************************************************************/

void insereLista(pListaCid pLista, int dist, int linha, int col)
{
    noCidade *no = (noCidade *)malloc(sizeof(noCidade));
    if (no == NULL)
    {
        puts( "erro ao criar no de cidade");
        exit(1);
    }
    
    no->pProx = NULL;
    no->linha = linha;
    no->col = col;
    no->dist = dist;
    
    if(pLista == NULL){ //se lista estiver vazia
        pLista->pCabeca = no;
        no->pAnt = NULL;
    
    }
    else{
        no->pAnt = pLista->pCorr;
        pLista->pCorr->pProx = no ;
    }
     pLista->pCorr = no;
}
/***************************************************************************
 *
 * Funcao: Imprime Lista , mantem ponteiro de pCorr no atual
 **********************************************************************/

void imprimeLista(pListaCid pLista){
    noCidade *hold = pLista->pCorr;
    printf(" /n/n " ); 
    pLista->pCorr = pLista->pCabeca;
    while(pLista->pCorr!= NULL){
        printf("%d  -----> " , pLista->pCorr->linha);
    }
    pLista->pCorr = hold;
}

/***************************************************************************
 *
 * Funcao: SWAP
            troca de lugar dois nós selecionados da lista e reorganiza
            valores da lista (distancias)
            move ponteiro de no corrente para o no b
 *
 **********************************************************************/

pListaCid SWAP(pListaCid pLista,  noCidade* a, noCidade* b)
{
    noCidade *hold = b->pProx;
    
    a->pAnt->pProx = b;
    b->pAnt = a->pAnt;
    b->pProx = a;
    a->pProx = hold;
    
    pLista->pCorr = b;
    return pLista;
}


/***************************************************************************
 *
 * Funcao: Ir X : move o ponteiro pCorr para o no de numero X partindo
                    do no cabeca da lista
 *
 **********************************************************************/

pListaCid ir_no(pListaCid pLista, int x){
    pLista->pCorr = pLista->pCabeca;
    for(int i=0; i<x ; i++){
        pLista->pCorr = pLista->pCorr->pProx;
    }
    return pLista;
}
