#ifndef GRAPHPRIM_H
#define GRAPHPRIM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include <set>
#include "graph.h"

#include "manipulaGraphviz.h"

using namespace std;

struct auxPrim{
	int id_pai;
	int distancia = -1;

	//Id da aresta que leva até este vertice
	int id_edge;
	//Indica se é vértice inicial
	bool is_start;

	//Indica se um vértice já foi explorado
	bool is_explorado = false;
	//Indica que um vértice tem peso infinito
	bool is_infinity;
};

class graphPrim{
private:
	//Grafo original
	graph *myGraph;
	//Novo grafo gerado
	graph myNewGraph;
	//Mapa de estruturas que representam os vertices, de acordo com a chave
	map <int,auxPrim> PRIM_map;

	//Indica se o algoritmo é valido para o grafo indicado
	bool is_valid;

	//Inicializa as estruturas que serão usadas
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: Novo grafo inicializado e mapa de Prim inicializado
	void initPrim(int id_ini);

	//Condição para executar o relax
	//Pre-condicao: id vertice 1, id vertice 2, peso da conexão
	//Pos-condicao: se o relax pode ser executado
	bool relax_validation(int id_ini, int id_dest, int weight);

	//Executa o relax
	//Pre-condicao: id vertice 1, id vertice 2, id da aresta
	//Pos-condicao: relax
	void relax(int id_ini, int id_dest, int id_path);

	//Procura o vértice não explorado com a menor distancia
	//Pre-condicao: 
	//Pos-condicao: id do vértice buscado, ou -1 caso não exista tal vértice
	int naoExploradoComMenorDistancia();

public:

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
	graphPrim(graph *graph_map);

	//Verifica se o algoritmo pode ser executado
	//Pre-condicao:
	//Pos-condicao: is_valid atualizado
	bool validate();

	//Executa o algoritmo
	//Pre-condicao: id que representa o vértice inicial
	//Pos-condicao: Mapa de Prim gerado e novo grafo gerado
	bool run(int id_ini);

	//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
	//Pre-condicao: Se deseja gerar a imagem
	//Pos-condicao: Visualização do resultado do algoritmo
	void printPrim(bool isImage);

	//Destrutor
	//Pre-condicao:
	//Pos-condicao: Instância deixa de existir
	~graphPrim();
	
};

#endif //GRAPHPRIM_H