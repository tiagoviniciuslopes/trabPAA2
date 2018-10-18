#ifndef GRAPHKRUSKAL_H
#define GRAPHKRUSKAL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include "graph.h"

#include "manipulaGraphviz.h"

using namespace std;

class graphKruskal{
private:
	graph *myGraph;
	
	//Novo grafo gerado
	graph myNewGraph;
	//Mapa para executar o algoritmo
	map <int,int> Kruskal;

	//Mapa ordenado de pesos de vértices
	multimap <int,path> edges;

	//Indica se é um grafo valido
	bool is_valid;

	//Inicializa as estruturas que serão usadas
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: Mapa Kruskal inicializado, NewGraph inicializado e lista de pesos inicializado
	void initKruskal();

	//Verifica a qual arvore um vértice pertence
	//Pre-condicao: id vértice
	//Pos-condicao: id da arvore
	int find(int id);

	//Simula a inserção de uma aresta no mapa Kruskal
	//Pre-condicao: id vértice 1, id vértice 2
	//Pos-condicao: Mapa Kruskal atualizado
	bool insertEdge(int e1, int e2);

public:

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
	graphKruskal(graph *graph_map);

	//Valida se o algoritmo pode ser executado
	//Pre-condicao: 
	//Pos-condicao: is_valid atualizado
	bool validate();

	//Executa o algoritmo
	//Pre-condicao:
	//Pos-condicao: Mapa Kruskal com os valores pós-execução do algoritmo
	bool run();

	//Retorna o novo grafo
	//Pre-condicao:
	//Pos-condicao: Mapa Kruskal com os valores pós-execução do algoritmo
	graph *getNewGraph();

	//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
	//Pre-condicao: Se deseja gerar a imagem
	//Pos-condicao: Visualização do resultado do algoritmo
	void printKruskal(bool isImage);

	//Destrutor
	//Pre-condicao:
	//Pos-condicao: Instância deixa de existir
	~graphKruskal();
	
};

#endif //GRAPHKRUSKAL_H