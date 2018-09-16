#include <bits/stdc++.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#define min(a,b) a<b?a:b

using namespace std;

bool sortbysec(const pair<int,int> a, const pair<int,int> b) { 
    return (a.second < b.second); 
} 



vector<vector<pair<int,int>>> le_arquivo(char *file, int* qt_cidades){
	ifstream myfile;
	string line;
	myfile.open(file);
	//int qt_cidades;
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
			if(aux == "DIMENSION:"){ //DIMENSION
				buff >> aux;
				*qt_cidades = stoi(aux);
				cout << *qt_cidades << endl;
				listaAdjacencia.resize(*qt_cidades);
				//for (int i = 0; i < *qt_cidades; i ++) listaAdjacencia[i].resize(*qt_cidades);
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


			//for (int i = 0; buff >> aux; i++){
			while(buff >> aux){
				//buff >> aux;
				if (aux == "EOF" || aux == "DISPLAY_DATA_SECTION"){
						/*for (int i = 0; i < *qt_cidades; i++){
							//cout << i << " ";
							for (int j = 0; j < listaAdjacencia[i].size(); j++){
								cout << "<" <<listaAdjacencia[i][j].first <<  "," << listaAdjacencia[i][j].second << ">  ";
							}
							cout << endl;
						}*/

					return listaAdjacencia; //EOF
				}

				x = stoi(aux);	//strig to integer
							
				listaAdjacencia[id_cidade].push_back((make_pair(count_cidade, x)));
				//cout << count_cidade << endl;


				


				if (x != 0){
					count_cidade++;
					//listaAdjacencia[id_cidade].push_back((make_pair(count_cidade, x)));
					//a.first = id_cidade;
					//listaAdjacencia[count_cidade].push_back(a);
				}
				else {
					id_cidade++;// cout << endl;
					count_cidade = 0;
					//id_city = 0;

				}

				
			}
		}		
	}


	myfile.close();

	return listaAdjacencia;
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

int calcula_menor_caminho(vector < vector < pair <int,int> > > listaAdjacencia, int qt_cidades, int cidade_de_origem){
	vector <int> cidades_visitadas;
	cidades_visitadas.resize(qt_cidades);
	int aux_cidade_de_origem = cidade_de_origem;
	int caminho = 0;
	int end = 0;
	cidades_visitadas[cidade_de_origem] = 1;



	/*cout << "CIDADES VISITADAS: ";
	for ( int i = 0; i < qt_cidades; i++){
		cout << cidades_visitadas[i] << " ";
	}
	cout << endl;*/

	while(!end){
		for (int i = 0; i < qt_cidades; i++){
			//cout << "cheguei aqui" << endl;	
			if (!cidades_visitadas[listaAdjacencia[aux_cidade_de_origem][i].first] && listaAdjacencia[aux_cidade_de_origem][i].second ){

				//cout << aux_cidade_de_origem << "-> " << listaAdjacencia[aux_cidade_de_origem][i].first << ": "<<listaAdjacencia[aux_cidade_de_origem][i].second << endl;
				//cout << caminho << "-> "<< caminho + listaAdjacencia[aux_cidade_de_origem][i].second << endl << endl;
				//cout << "oi";

				cout << "Sai da cidade " << aux_cidade_de_origem << " e fui para a " << listaAdjacencia[aux_cidade_de_origem][i].first << endl;
				cout << "caminho: " << caminho << " + " << listaAdjacencia[aux_cidade_de_origem][i].second << " = " <<  caminho + listaAdjacencia[aux_cidade_de_origem][i].second << endl;
				

				cidades_visitadas[listaAdjacencia[aux_cidade_de_origem][i].first] = 1;
				caminho += listaAdjacencia[aux_cidade_de_origem][i].second;
				aux_cidade_de_origem = listaAdjacencia[aux_cidade_de_origem][i].first;
				//cidades_visitadas[listaAdjacencia[aux_cidade_de_origem][i].first ] = 1;
				break;
			}
		}

		end = 1;
		//cout << endl << "CIDADES QUE JA VISITEI : " ;

		for ( int i = 0; i < qt_cidades; i++)
			cout << cidades_visitadas[i] << " ";
		cout << endl << endl;

		for (int i = 0; i < qt_cidades; i++){
			if (!cidades_visitadas[i]) {
				//cout << "ainda nao acabou " << endl;
				//cout << cidades_visitadas[i] << " ";
				end = 0;
				break;
			}
		}
	}

	for (int i = 0; i < qt_cidades; i++){
		if (listaAdjacencia[cidade_de_origem][i].first == aux_cidade_de_origem){
			//cout << "Voltando pra casa. Da cidade " << aux_cidade_de_origem << "Para a cidade " << cidade_de_origem <<endl;
			return (caminho + listaAdjacencia[cidade_de_origem][i].second);
		}

	}
	return caminho;


}


int caminho_otimo(vector < vector < pair <int,int> > > listaAdjacencia, int qt_cidades){
	int menor = INT_MAX;

	for (int i = 0; i < qt_cidades; i++)
		menor = (min(calcula_menor_caminho(listaAdjacencia, qt_cidades, i), menor));	//calcula menor caminho saindo da cidade i
	return menor;

}



void imprime_listaAdjacencia(vector < vector < pair <int,int> > > listaAdjacencia){

	for (int i = 0; i < listaAdjacencia.size(); i++){
							//cout << i << " ";
		for (int j = 0; j < listaAdjacencia[i].size(); j++){
			cout << "<" <<listaAdjacencia[i][j].first <<  "," << listaAdjacencia[i][j].second << ">  ";
		}
		cout << endl;
	}

}


int main(int argc, char *argv[]){
	
	int i, f;
	i = time(NULL);
	int qt_cidades;

	vector < vector < pair <int,int> > > listaAdjacencia;

	listaAdjacencia = le_arquivo(argv[1], &qt_cidades);
	listaAdjacencia = copia_superior(listaAdjacencia);



	cout << endl << "SEM ORDENAÇÃO:" << endl << endl;

	imprime_listaAdjacencia(listaAdjacencia);

	cout << endl << "COM ORDENAÇÃO:" << endl << endl;


	for (int i = 0; i < listaAdjacencia.size(); i++){
		sort(listaAdjacencia[i].begin(), listaAdjacencia[i].end(), sortbysec);
	}

	imprime_listaAdjacencia(listaAdjacencia);


	//cout << endl << endl << "Menor caminho possivel: " << caminho_otimo(listaAdjacencia, qt_cidades);


	cout << endl << calcula_menor_caminho(listaAdjacencia, qt_cidades, 2);
	/*for (int i = 0; i < qt_cidades; i++){
		cout << lista[i].inicio->distancia;
	}*/

	//cout << lista[0]->inicio->distancia;



	//libera_lista(lista, qt_cidades);

	f = time(NULL);

	printf("\nTempo total = %i s\n", f-i);


	return 0;
}
