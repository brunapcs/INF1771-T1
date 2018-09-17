//#include <bits/stdc++.h>

#include "/Users/brunaparacat1/stdc++.h"

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ListaAdjacencia.h"
#define min(a,b) a<b?a:b

using namespace std;


double busca_gulosa(vector < vector < pair <int,int> > > listaAdjacencia, int qt_cidades, int cidade_de_origem, vector <int> solucao){
	vector <int> cidades_visitadas;
	cidades_visitadas.resize(qt_cidades);
    
	int aux_cidade_de_origem = cidade_de_origem;
	int caminho = 0;
	int end = 0;
    double latencia =0;
    solucao.push_back(cidade_de_origem);
	cidades_visitadas[cidade_de_origem] = 1;

    double latenciaTotal = 0.0 ;
	while(!end){
		for (int i = 0; i < qt_cidades; i++){
			if (!cidades_visitadas[listaAdjacencia[aux_cidade_de_origem][i].first] && listaAdjacencia[aux_cidade_de_origem][i].second ){
			   solucao.push_back(listaAdjacencia[aux_cidade_de_origem][i].first);
                
//               cout << aux_cidade_de_origem << "---> " << listaAdjacencia[aux_cidade_de_origem][i].first << endl;
//               cout<< "custo entre cidades: "<<listaAdjacencia[aux_cidade_de_origem][i].second <<endl;
                
                latencia = caminho + listaAdjacencia[aux_cidade_de_origem][i].second;
				
                latenciaTotal += latencia;
				cidades_visitadas[listaAdjacencia[aux_cidade_de_origem][i].first] = 1;
				caminho += listaAdjacencia[aux_cidade_de_origem][i].second ;
				aux_cidade_de_origem = listaAdjacencia[aux_cidade_de_origem][i].first;
				break;
			}
		}
		end = 1;

		for (int i = 0; i < qt_cidades; i++){
			if (!cidades_visitadas[i]) {
				end = 0;
				break;
			}
		}
	}
    
    cout << latenciaTotal << endl;
	return latenciaTotal;
}


int caminho_otimo(vector < vector < pair <int,int> > > listaAdjacencia, int qt_cidades){
	int menor = INT_MAX;
    vector <int> solucao;

	for (int i = 0; i < qt_cidades; i++)
		menor = (min(busca_gulosa(listaAdjacencia, qt_cidades, i, solucao), menor));	//calcula menor caminho saindo da cidade i
	
    return menor;
}


int main(int argc, char *argv[]){
	
    clock_t tStart;
	int qt_cidades;

	vector < vector < pair <int,int> > > listaAdjacencia;

    //leitura do arquivo
	listaAdjacencia = le_arquivo(argv[1], &qt_cidades);
    
    //inicio contagem de tempo de execucao
    tStart= clock();
    
    // Ordenacao de listaAdjacencia
    listaAdjacencia = copia_superior(listaAdjacencia);
    for (int i = 0; i < listaAdjacencia.size(); i++){
		sort(listaAdjacencia[i].begin(), listaAdjacencia[i].end(), sortbysec);
	}

    //Calculo de Latencia Minima Utilizando Algoritmo Guloso
    double latenciaTotal = caminho_otimo(listaAdjacencia, qt_cidades);
    cout << endl << endl << "Menor caminho possivel: " << latenciaTotal;


    printf("\nTempo de execucao: %.2fs\n ms", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}
