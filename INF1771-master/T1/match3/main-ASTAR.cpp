#include <stdio.h>
#include "Graphics.h"
#include <time.h>
#include <stdlib.h>
#include "Audio.h"
#include <cstdlib> 
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "MAPA.h"
#include "SA.h"

using namespace std;
Graphics graphics;

const int n=41; // Limite horizontal do mapa
const int m=41; // Limite vertical do mapa
static int map[n][m];
static int closed_nodes_map[n][m]; // mapa de nós fechados (tentados) 
static int open_nodes_map[n][m]; // mapa de nós abertos (não tentados ainda) 
static int dir_map[n][m]; // mapa de direções
const int dir=4; // numero de direcoes posicoes a partir de qualquer posicao
static int dx[dir]={1, 0, -1, 0};
static int dy[dir]={0, 1, 0, -1};

int board[m][m];
int xx, yy, b1, b2;
int w = 1, x3, x4, y3, y4;
int mov = 25, cmov = 0;
int pontos = 0, cpontos;
int b, k = 2;
int cc = 0;
int dd;
bool t_inicial = true;
bool gmove = false;
bool g_over = false;
bool semcredito = false;

/* novas declarações */
static int dificuldadeClareira[10] = {150, 140, 130, 120, 110, 100, 95, 90, 85, 80};
static double fatorApreciacao[5] = {1.5, 1.4, 1.3, 1.2, 1.1};
static int qtdDoce[5] = {5,5,5,5,5};
char ** combDoces;
int clareira_atual = 0;
double custoClareiraAtual = 0;

int xA=36, yA=4, xB=36, yB=36; // A é a origem e B é o destino
int visitado[41][41];
int posicao[2] = {0,0}; // posição x e y da chapeuzinho
int direcao = 0; // FRENTE
string route; // esse caminho tem tamanho numPassos
unsigned int numPassos = 0;
double custoTotal = 0;

static int open_nodes[n][m]; // mapa de nós abertos para impressão
int numPassosTeste = 0;
int diferenca = 0;

Image chapeuzinho[4];
Image background, btn_iniciar, btn_sair;
Image casa_chapeu, casa_vovo, grama, galho, clareira, denso; // itens iniciais do mapa
Image grama_visitada, clareira_visitada, galho_visitado; // itens visitados pela chapeuzinho
Image grama_aberta, galho_aberto, denso_aberto; // itens em aberto para chapeuzinho
/* fim novas declarações */

Audio Musica, boom;

// Calcula o custo da clareira com a combinação de doces da matriz de combinações, na linha de mesmo indice
double custoClareira(){
    int i;
    double tempo, denominador;

	tempo = denominador = 0.;
    for(i=0; i<5; i++){
        denominador += (combDoces[clareira_atual][i]*fatorApreciacao[i]); // nesse caso, as linhas são as clareiras e as colunas os doces
		qtdDoce[i] -= combDoces[clareira_atual][i];
	}

    tempo += ((double)dificuldadeClareira[clareira_atual]/denominador);
	clareira_atual++;

	printf("%f\n", tempo);
    return tempo;
}

// Incrementa o custo total do percurso
void incrementarCusto(){
	switch(map[posicao[0]][posicao[1]]){
		case 'C':
			/* usa a combinação */
			custoClareiraAtual = custoClareira();
			custoTotal += custoClareiraAtual;
			break;
		case 'D':
			/* incrementa o custo em 200 */
			custoTotal += 200;
			break;
		case 'G':
			/* incrementa o custo em 5 */
			custoTotal += 5;
			break;
		case '.':
			/* incrementa o custo em 1 */
			custoTotal += 1;
			break;
	}
}

// Obtem a proxima coordenada e insere na posição da chapeuzinho
void darUmPasso(){
	int j;
	char c;

	if(numPassos<route.length()){
		int x_ant, y_ant;
		
		x_ant = posicao[0];
		y_ant = posicao[1];

		c =route.at(numPassos);
		j=atoi(&c); 
		
		posicao[0]+=dx[j];
		posicao[1]+=dy[j];

		/* muda a direção que a chapeuzinho tá virada */
		if(dx[j]==1 && !dy[j]) // (1,0) DIREITA
			direcao = 1;
		else
		if(!dx[j] && dy[j]==1) // (0,1) COSTAS
			direcao = 3;
		else
		if(dx[j]==-1 && !dy[j]) // (-1,0) ESQUERDA
			direcao = 2;
		else // (0, -1) FRENTE
			direcao = 0;

		/* cria uma trilha apos chapeuzinho se deslocar */
		if(map[x_ant][y_ant]!='I')
			visitado[x_ant][y_ant] = 1; 

		numPassos++;
	}
	else{ /* terminar jogo */
		//g_over = true;
	}

}

// Configura o botão de inicio de jogo para iniciar o jogo/percurso
void ClickButtonPlay(int button, int state, int x, int y){
	t_inicial = false;
}

// Configura o botão sair para sair da tela do jogo
void ClickButtonSair(int button, int state, int x, int y){
	exit(0);
}

// Habilita o clique do mouse na tela do jogo
void MouseClickInput ( int button, int state, int x, int y){
	int xw = ((graphics.GetScreenWidth() / 2) - (256));	
	int yw = ((graphics.GetScreenHeight() / 2) - (256));

	if ((!t_inicial)&&(!g_over))
	{
		if (w == 1)
		{
			if ((button == MOUSE_LEFT_BUTTON)&&(state == MOUSE_STATE_DOWN))
			{
				x3 = (int)((x-xw)/64); 
				y3 = (int)((y-yw)/64);
				w = 2;
			}
		}
		else if (w == 2)
		{
			if ((button == MOUSE_LEFT_BUTTON)&&(state == MOUSE_STATE_DOWN))
			{
				x4 = (int)((x-xw)/64); 
				y4 = (int)((y-yw)/64);
				w = 1;

				if ((x3 == (x4 + 1) || x3 == (x4 -1)) && y3 == y4 )
				{
					int memoria = board[x3][y3];
					board[x3][y3] = board[x4][y3];
					board[x4][y3] = memoria; 
					cmov=1;
				}
				if ((y3 == (y4 +1) || y3 == (y4 - 1)) && x3 == x4 )			
				{
					int memoria = board[x3][y3];
					board[x3][y3] = board[x3][y4];
					board[x3][y4] = memoria;
					cmov=1;
				}
			}
		}	
	}
}

/* loop infinito, então basta alterar informações na matriz para que seja modificado os blocos no mapa */
void MainLoop()
{		
	int Xw = ((graphics.GetScreenWidth() / 2) - (292));
	int Yw = ((graphics.GetScreenHeight() / 2) - (200));
	int xb = ((graphics.GetScreenWidth() / 2) - (90));	
	int yb = ((graphics.GetScreenHeight() / 2) - (16));

	if (t_inicial == true){
		mov = 25;
		pontos = 0;
		cpontos=0;
		graphics.DrawImage2D(0,0, graphics.GetScreenWidth(),graphics.GetScreenHeight(), background);
		graphics.DrawImage2D(btn_iniciar);
		btn_iniciar.SetPosition(xb,yb + 20,200,52);
		g_over = false;
	}
	else if (g_over == true){
		int cx, cy;
		cx = cy = graphics.GetScreenWidth()/2;

		graphics.DrawImage2D(0,0, graphics.GetScreenWidth(),graphics.GetScreenHeight(), background);
		graphics.DrawImage2D(btn_sair);
		btn_sair.SetPosition(xb,yb,200,52);

		graphics.DrawText2D(cx-140,cy+80,"Chapeuzinho deu %d passos.", numPassos);
		graphics.DrawText2D(cx-260,cy+60,"O custo total de sua ida a vovozinha foi de %.2fmin.", custoTotal);
	} 
	else
	{
		int xw = (0 /*(graphics.GetScreenWidth() / 2) - (256)*/);	
		int yw = (0 /*(graphics.GetScreenHeight() / 2) - (256)*/);

		/* tudo certo aqui */
		for (xx = 0 ; xx < 41 ; xx ++){
			for(yy = 0; yy < 41; yy ++){
				if (map[xx][yy] == 'C'){
					graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, clareira);
				}
				if (map[xx][yy] == 'D'){
					graphics.DrawImage2D(xw + xx*16, yw + yy*16,16, 16, denso);
				}
				if (map[xx][yy] == 'G'){
					graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, galho);
				}
				if (map[xx][yy] == '.'){
					graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, grama);
				}
				if (map[xx][yy] == 'F'){
					graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, casa_vovo);
					
				}
				if (map[xx][yy] == 'I'){
					graphics.DrawImage2D(xw + xx*16, yw + yy*16,16, 16, casa_chapeu);
				}
			}
		}

		/* sobrepõe o mapa com os nós abertos */
		for (xx = 0 ; xx < 41 ; xx ++)
			for(yy = 0; yy < 41; yy ++)
				if(open_nodes[xx][yy]!=0 && open_nodes[xx][yy]<(numPassos+1))
					switch(map[xx][yy]){
						case '.':
							graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, grama_aberta);
							break;
						case 'D':
							graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, denso_aberto);
							break;
						case 'G':
							graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, galho_aberto);
							break;
					}

		/* sobrepõe o mapa com a trilha até então feita */
		for (xx = 0 ; xx < 41 ; xx ++)
			for(yy = 0; yy < 41; yy ++)
				if(visitado[xx][yy])
					switch(map[xx][yy]){
						case '.':
							graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, grama_visitada);
							break;
						case 'C':
							graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, clareira_visitada);
							break;
						case 'G':
							graphics.DrawImage2D(xw + xx*16, yw + yy*16, 16, 16, galho_visitado);
							break;
					}

		/* sobrepõe o mapa com a chapeuzinho virada pra sua direção atual */
		graphics.DrawImage2D(xw + 16*posicao[0], yw + 16*posicao[1], 16, 16, chapeuzinho[direcao]);

		/* itens e custos */
		graphics.SetTextFont("Arial", 24, false, false, false);
		graphics.DrawText2D(10,620,"Passos: %d", numPassos);
		graphics.DrawText2D(10,600,"Custo: %.2fmin", custoTotal);
		graphics.DrawText2D(10,28,"TortaDeAmoras:%d CupcakesDeMarshmallow:%d BoloDeChocolate:%d", qtdDoce[0], qtdDoce[1], qtdDoce[2]);
		graphics.DrawText2D(10,8,"Brigadeiro:%d DoceDeCoco:%d", qtdDoce[3], qtdDoce[4]);

		Sleep(150);

		/* dar um passo e incrementar os custos */
		darUmPasso();

		if(custoClareiraAtual){ // MAIOR QUE ZERO
			Sleep(200);
			graphics.DrawText2D(graphics.GetScreenWidth()/2-50,graphics.GetScreenHeight()/2,"+%.2fmin", custoClareiraAtual);
			Sleep(300); /* pra dar uma sensação de esforço */
			custoClareiraAtual=0;
		}

		incrementarCusto();

	}
}

// ALGORITMO A-ESTRELA
class node{
    // posicao atual
    int xPos;
    int yPos;
    //level = peso de cada nó
    int level;
    // priority = level + heuristica
    int priority;  //quanto menor, maior é a prioridade

    public:
        node(int xp, int yp, int d, int p) 
            {xPos=xp; yPos=yp; level=d; priority=p;}
    
        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        void nextLevel(const int & i) 
        {
			 level+=calcula_custo(map[xPos][yPos]);        
        }
        
        //Distancia de Manhattan aproximada do destino
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;         

            // distancia de Manhattan
            d=abs(xd)+abs(yd);
            
            return(d);
        }
};

// Determinação de prioriade (na fila de prioridade)
bool operator<(const node & a, const node & b){
  return a.getPriority() > b.getPriority();
}

//A rota é retornada como uma string de direçoes a serem percorridas no melhor caminho
string pathFind( const int & xStart, const int & yStart, const int & xFinish, const int & yFinish ){
    static priority_queue<node> pq[2]; // lista de nós abertos (não tentads)
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset do mapa de nós
    for(y=0;y<m;y++)
    {
        for(x=0;x<n;x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
			open_nodes[x][y]=0;
        }
    }

    // cria o nó inicial e da push na lista de nós abertos 
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->getPriority(); // marca o nó no mapeamento de nós abertos 

    // BUSCA A* 
    while(!pq[pqi].empty())
    {
        // Obtem o nó corrente com a prioridade mais alta
		// na lista de nós abertos
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), 
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove o nó da lista de nós abertos
        open_nodes_map[x][y]=0;
        // marca o nó na lista de nós fechados 
        closed_nodes_map[x][y]=1;

		numPassosTeste++;
		
        // Sai da busca quando o estado da busca é atingido (Fim da rota)
        if(x==xFinish && y==yFinish) 
        {
            // Gera o caminho do fim para o início
            // seguindo as direções
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            
            delete n0;
            // esvazia nós que sobraram
            while(!pq[pqi].empty()) pq[pqi].pop();           
            return path;
        }

        // gera 'movimentos' (child nodes) em todas as possíveis direções
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx][ydy]==1
                || closed_nodes_map[xdx][ydy]==1))
            {
                // cria um novo child node
                m0=new node( xdx, ydy, n0->getLevel(), 
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                //adiciona a lista de nós abertos, caso ainda não esteja lá
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    //  marca a direção do nó pai 
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

					open_nodes[xdx][ydy] = numPassosTeste;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // atualiza prioridade
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // atualiza informacao de parentalidade (dir)
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // substitui o nó
                    // esvaziado um pq por outro nó
                    // exceto o nó a ser substituido, esse deve ser ignorado
                    // e o novo nó deve ser posto em seu lugar
                    while(!(pq[pqi].top().getxPos()==xdx && 
                           pq[pqi].top().getyPos()==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // remove  o nó desejado
                    
                    // esvazia o maior lador de pq para o outro lado
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // adiciona  o melhor nó

					diferenca = numPassosTeste - open_nodes[m0->getxPos()][m0->getyPos()];
					numPassosTeste -= diferenca;
					
                }
                else{
					delete m0; //libera nó
					numPassosTeste--;
				}
            }
        }
        delete n0; // libera o nó (garbage collection)
    } 
    return ""; // nenhuma rota encontrada
}

int main(void){
	srand((unsigned)time(NULL));

	Mapa &mapa_aux = cria_mapa("mapa.txt");

	for(int x=0;x<41;x++){
        for(int y=0;y<41;y++){
            map[x][y] = mapa_aux[x][y];  // exibe o elemento corrente no array 
			visitado[x][y] = 0;
			cout<<(char)map[x][y];
        }
		cout<<endl;  // nova linha
	}

    cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
    cout<<"Start: "<<xA<<","<<yA<<endl; 
    cout<<"Finish: "<<xB<<","<<yB<<endl;

    // Obter a rota
	printf("\nObtendo a rota via A*...\n");
    clock_t start = clock();
    route=pathFind(xA, yA, xB, yB);
    if(route=="") cout<<"Rota não encontrada!\n"<<endl;
    clock_t end = clock();

    double time_elapsed = double(end - start);
    cout<<"Rota encontrada, no tempo de "<<time_elapsed<<"ms."<<endl;
    cout<<"PASSOS:"<<numPassosTeste<<endl;
    cout<<endl;

	if(route.length()>0){
		// iniciando a chapeuzinho na origem
		posicao[0]=xA;
		posicao[1]=yA;

		printf("Combinando doces...\n");
		combDoces = criarCombDoces();
		printf("Combinacao terminada!\nIniciando o jogo...\n");

		/* inicializa o playlib */
		graphics.CreateMainWindow(650,650,"INF1771_T1");
		
		background.LoadPNGImage("img/background.png");	
		btn_iniciar.LoadPNGImage("img/btn_iniciar.png");
		btn_sair.LoadPNGImage("img/btn_sair.png");
		btn_iniciar.SetOnClick(ClickButtonPlay);
		btn_sair.SetOnClick(ClickButtonSair);

		chapeuzinho[0].LoadPNGImage("img/red/frente.png");
		chapeuzinho[1].LoadPNGImage("img/red/direita.png");
		chapeuzinho[2].LoadPNGImage("img/red/esquerda.png");
		chapeuzinho[3].LoadPNGImage("img/red/costas.png");
				
		casa_chapeu.LoadPNGImage("img/inicio.png");
		casa_vovo.LoadPNGImage("img/fim.png");
		grama.LoadPNGImage("img/grama.png");
		galho.LoadPNGImage("img/galho.png");
		clareira.LoadPNGImage("img/clareira-lobo.png");
		denso.LoadPNGImage("img/denso.png");

		grama_visitada.LoadPNGImage("img/grama-visitada.png");
		galho_visitado.LoadPNGImage("img/galho-visitado.png");
		clareira_visitada.LoadPNGImage("img/clareira-visitada.png");

		grama_aberta.LoadPNGImage("img/grama-aberta.png");
		galho_aberto.LoadPNGImage("img/galho-aberto.png");
		denso_aberto.LoadPNGImage("img/denso-aberto.png");

		//Musica.LoadAudio("Data\\incriveis.mp3");
		//Musica.Play();
		//boom.LoadAudio("Data\\boom.mp3");

		graphics.SetTextFont("Courier Regular", 36, FONT_WEIGHT_NORMAL, false, false);
		graphics.SetMouseClickInput(MouseClickInput);
		graphics.SetMainLoop(MainLoop);
		graphics.StartMainLoop();

		printf("Jogo finalizado!\n");
	}
	else
		cout<<"ROTA NÃO ENCONTRADA!"<<endl;
	
	getchar();
	return 0;
}
