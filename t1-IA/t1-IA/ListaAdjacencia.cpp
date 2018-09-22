//#include "/Users/brunaparacat1/stdc++.h"
#include <bits/stdc++.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ListaAdjacencia.h"


bool sortbysec(const pair<int,int> a, const pair<int,int> b) {
    return (a.second < b.second);
}

vector<vector<pair<int,int> > > le_arquivo(char *file, int* qt_cidades){
    ifstream myfile;
    string line;
    myfile.open(file);
    
    int seed = time(NULL);
    srand(seed);
    printf("Seed %d\n", seed);
    bool lower = true;
    bool cabecalho = true;
    int count_cidade = 0;
    int id_cidade = 0;
    
    vector < vector <pair<int,int> > > listaAdjacencia;
    
    while(getline(myfile, line)){
        istringstream buff(line);
        string aux;
        
        if (cabecalho){
            buff >> aux;
            if(aux == "DIMENSION:"){
                buff >> aux;
                *qt_cidades = stoi(aux);
                cout << *qt_cidades << endl;
                listaAdjacencia.resize(*qt_cidades);
            }
            
            else if(aux == "EDGE_WEIGHT_FORMAT:"){
                buff >> aux;
                if(aux == "LOWER_DIAG_ROW")
                    lower = true;
                else
                    lower = false;
            }
            
            else if (aux == "EDGE_WEIGHT_SECTION")
                cabecalho = false;
        }
        else{
            int x;
            while(buff >> aux){
                if (aux == "EOF" || aux == "DISPLAY_DATA_SECTION"){
                    return listaAdjacencia; //EOF
                }
                
                x = stoi(aux);    //strig to integer
                if (lower){
                    listaAdjacencia[id_cidade].push_back((make_pair(count_cidade, x)));
                    
                    if (x != 0)
                        count_cidade++;
                    
                    else {
                        id_cidade++;
                        count_cidade = 0;
                    }
                }
                else{
                    if(id_cidade == count_cidade){
                        listaAdjacencia[id_cidade].push_back(make_pair(id_cidade, 0));
                        id_cidade++;
                        listaAdjacencia[id_cidade].push_back(make_pair(count_cidade, x));
                    }
                    else{
                        listaAdjacencia[id_cidade].push_back(make_pair(count_cidade,x));
                    }
                    
                    id_cidade++;
                    
                    if(id_cidade == *qt_cidades){
                        count_cidade++;
                        id_cidade = count_cidade;
                    }
                    
                }
            }
        }
    }
    
    myfile.close();
    return listaAdjacencia;
}

void imprime_vet(vector <int> v){
    for(int i =0; i<v.size(); i++ )
        cout << v[i] << " --> ";
}

vector<vector<pair<int,int> > > copia_superior( vector < vector < pair <int,int> > > listaAdjacencia){
    for( int i = 0; i< listaAdjacencia.size() ; i++ ){
        for(int j=i; j<listaAdjacencia.size(); j++){
            if(i != j)
                listaAdjacencia[i].push_back(make_pair(j , listaAdjacencia[j][i].second));
        }
    }
    return listaAdjacencia;
}


void imprime_listaAdjacencia(vector < vector < pair <int,int> > > listaAdjacencia){
    for (int i = 0; i < listaAdjacencia.size(); i++){
        for (int j = 0; j < listaAdjacencia[i].size(); j++){
            cout << "<" <<listaAdjacencia[i][j].first <<  "," << listaAdjacencia[i][j].second << ">  ";
        }
        cout << endl;
    }
}



