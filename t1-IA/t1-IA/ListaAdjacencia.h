#ifndef LISTAADJ_C
#define LISTAADJ_C
using namespace std;

    bool sortbysec(const pair<int,int> a, const pair<int,int> b);
	vector<vector<pair<int,int> > > le_arquivo(char *file, int* qt_cidades); 
	vector<vector<pair<int,int> > > copia_superior( vector < vector < pair <int,int> > > listaAdjacencia);
	void imprime_listaAdjacencia(vector < vector < pair <int,int> > > listaAdjacencia); 

#endif
