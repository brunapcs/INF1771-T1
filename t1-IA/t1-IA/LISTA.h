

/****************************************************
 
TIPOS DE DADOS EXPORTADOS PELO MODULO
 
 **************************************************/
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
typedef struct lista_cidades* pListaCid;
typedef struct no_lista_cidades *pNoCid;

/**************************************************
 
 FUNCOES EXPORTADAS PELO MODULO
 
 *************************************************/

pListaCid CriaLista(); 
void insereLista(pListaCid pLista, int dist, int linha, int col);
void imprimeLista(pListaCid pLista);
pListaCid ir_no(pListaCid pLista, int x);
pListaCid SWAP(pListaCid pLista,  noCidade* a, noCidade* b); 


