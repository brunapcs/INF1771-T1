//#include "bits/stdc++.h"

//configuracao para mac da lib
#include "/Users/brunaparacat1/stdc++.h"

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ListaAdjacencia.h"
#include "LISTA.h"

using namespace std;

/***** VARIAVEIS GLOBAIS ********/
 int qt_cidades=0;
/********************************/

//retorna indice j ou seja cidade que ainda nao foi visitada, partindo dos pares <j, dist> de uma dada cidade "i"
int check_visitados(vector <int> v ,  vector < vector < pair <int,int> > > listaAdjacencia , int i )
{
    int j =0;
    while(1){
        if( any_of(v.begin(), v.end(), listaAdjacencia[i][j].first))
            j++;
        else
            break;
    }
    return j;
}

//constroi lista encadeada baseada nas informacoes contidas no vetor listaAdjacencia
pListaCid constroi_solucao(pListaCid pLista, vector < vector < pair <int,int> > > listaAdjacencia , int custoTotal)
{
    vector <int> visitados; //vetor com indices das cidades que ja foram visitadas
    visitados.push_back(0); //inicializacao na cidade 0, ponto de partida
    
    int count =0;
    int i=0;
    int indice=0;
    
    while(count < 10 ){
        indice = check_visitados(visitados, listaAdjacencia, i , qt_cidades);
        insereLista( pLista , listaAdjacencia[i].second, i , listaAdjacencia.first);
        i = listaAdjacencia[i].first; //proximo ponto de partida
        custoTotal += listaAdjacencia.second();
        visitados.push_back(i);
        count++;
    }
    return pLista;
}



//dada uma determinada solucao representada em uma listaEncadeada
//utiliza vizinhanca de swap em uma determinada area ao redor do ponto x   (2 cidades anteriores e 2 cidades posteriores ou outros *verificar*)
//verificas se a cada operacao a troca produz uma solucao com custoTotal < custoTotalInicial se sim, aceita nova solucao
// so aceita solucoes de melhora!
/*
pLista hillClimb (pListaCid pLista, int x, int custoTotal, vector < vector < pair <int,int> > > listaAdjacencia )
{
    pLista nova = CriaLista(); //lista copia da original para efeturar operacoes
    nova = pLista;
            for (long i = 0; i < ite_hillClimb ;  ++i)
            {
                SWAP( nova , x+i , custoTotalInicial);
                calcula_custo(nova);
                if( custo < custoTotal)
                    custoTotal = custo;
                    pLista = nova;
            }
 return pLista;
}
*/
int main(int argc, char *argv[]){
    int i, f;
    
    //lista encadeada representando solucao
    pListaCid solucao = CriaLista();
    
    vector < vector < pair <int,int> > > listaAdjacencia;
    
    //custo de latencia total da viajem na solucao em vigor
    int custoTotal;
                                                          \\
    
    //Leitura do arquivo.tsp
    listaAdjacencia = le_arquivo(argv[1], &qt_cidades);
    
    //inicializa contagem de tempo
    i = time(NULL);
    
    //ordena lista de adjacencia
    listaAdjacencia = copia_superior(listaAdjacencia);
    for (int i = 0; i < listaAdjacencia.size(); i++){
        sort(listaAdjacencia[i].begin(), listaAdjacencia[i].end(), sortbysec);
    }
    imprime_listaAdjacencia(listaAdjacencia);
    
    //constroi solucao inicial
    solucao = constroi_solucao(solucao, listaAdjacencia, &custoTotal );
    imprimeLista(solucao);
    
    //constroi solucao utilizando algoritmo guloso (?) (colocar em outro arquivo main.cpp depois)
    
    //utiliza algoritmo hillclimb a partir da solucao inicial
    
    
    
    
    f = time(NULL);
    printf("\nTempo total = %i s\n", f-i);
    return 0;
}
