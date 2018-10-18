#ifndef GRAPHDBELLMANFORD_H
#define GRAPHDBELLMANFORD_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include <set>
#include "graph.h"

#include "manipulaGraphviz.h"

using namespace std;

struct auxBellmanFord{
	int id_pai;
	int distancia = -1;

	//Id da aresta que leva até este vertice
	int id_edge;
	//Indica se é vértice inicial
	bool is_start;

	//Indica que um vértice tem peso infinito
	bool isInfinity = true;

};

class graphBellmanFord{
private:
	//Grafo original
	graph *myGraph;
	//Mapa de estruturas que representam os vertices, de acordo com a chave
	map <int,auxBellmanFord> BellmanFord_map;

	//Inicializa as estruturas que serão usadas
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: BellmanFord_map inicializado
	void initBellmanFord(int id_ini);

	//Condição para executar o relax
	//Pre-condicao: id vertice 1, id vertice 2, peso da conexão
	//Pos-condicao: se o relax pode ser executado
	bool relax_validation(int id_ini, int id_dest, int weight);

	//Executa o relax
	//Pre-condicao: id vertice 1, id vertice 2, id da aresta
	//Pos-condicao: relax
	void relax(list<path>::iterator it);

public:

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
	graphBellmanFord(graph *graph_map);

	//Executa o algoritmo
	//Pre-condicao: id que representa o vértice inicial
	//Pos-condicao: BellmanFord_map com os valores pós-execução do algoritmo
	bool run(int id_ini);

	//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
	//Pre-condicao: Se deseja gerar a imagem
	//Pos-condicao: Visualização do resultado do algoritmo
	void printBF(bool isImage);

	//Destrutor
	//Pre-condicao:
	//Pos-condicao: Instância deixa de existir
	~graphBellmanFord();
	
};

#endif //GRAPHDBELLMANFORD_H