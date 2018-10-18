#ifndef GRAPHLARGURA_H
#define GRAPHLARGURA_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include <queue>
#include "graph.h"

#include "manipulaGraphviz.h"

using namespace std;

struct auxLargura{
	//0 == branco, 1 == cinza, 2 == preto
	int cor;
	
	int id_pai;

	//Id da aresta que leva até este vertice
	int id_edge;
	
	//Indica se é vértice inicial
	bool is_start;
	
	int distancia = -1;
};

class graphLargura{
private:
	//Grafo original
	graph *myGraph;
	//Mapa de estruturas que representam os vertices, de acordo com a chave
	map <int,auxLargura> BFS_map;
	//Lista de prioridade
	queue <int> BFS_queue;

	//Converte o id da cor para a palavra
	//Pre-condicao: id da cor
	//Pos-condicao: string com o nome da cor
	string getCor(int idCor);
	
	//Inicializa as estruturas que serão usadas
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: BFS_map inicializado
	void initBFS(int id_ini);

public:

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
	graphLargura(graph *graph_map);

	//Executa o algoritmo
	//Pre-condicao: id que representa o vértice inicial
	//Pos-condicao: BFS_map com os valores pós-execução do algoritmo
	void run(int id_ini);

	//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
	//Pre-condicao: Se deseja gerar a imagem
	//Pos-condicao: Visualização do resultado do algoritmo
	void printBFS(bool isImage);

	//Destrutor
	//Pre-condicao:
	//Pos-condicao: Instância deixa de existir
	~graphLargura();
	
};

#endif //GRAPHLARGURA_H