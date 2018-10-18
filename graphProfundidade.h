#ifndef GRAPHPROFUNDIDADE_H
#define GRAPHPROFUNDIDADE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include "graph.h"

#include "manipulaGraphviz.h"

using namespace std;

struct auxProfundidade{
	//0 == branco, 1 == cinza, 2 == preto
	int cor;
	
	int id_pai;

	//Id da aresta que leva até este vertice
	int id_edge;

	//Indica se é vértice inicial
	bool is_start;
	
	unsigned int  timestamp_descoberta;
	unsigned int  timestamp_fim;
};

class graphProfundidade{

private:
	//Grafo original
	graph *myGraph;
	//Mapa de estruturas que representam os vertices, de acordo com a chave
	map <int,auxProfundidade> DFS;
	//Variavel 'global' pra guardar timestamp atual
	unsigned int timestamp = 0;

	//Converte o id da cor para a palavra
	//Pre-condicao: id da cor
	//Pos-condicao: string com o nome da cor
	string getCor(int idCor);

	//Faz a recursão de visitas ao vértice e seus vizinhos, atualizando seus timestamps e cores
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: todas as visitas realizadas na arvore em questão
	void visit(int id);

	//Inicializa as estruturas que serão usadas
	//Pre-condicao: id do vértice inicial
	//Pos-condicao: DFS inicializado
	void initDFS();

public:

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
	graphProfundidade(graph *graph_map);;

	//Executa o algoritmo
	//Pre-condicao: id que representa o vértice inicial
	//Pos-condicao: DFS com os valores pós-execução do algoritmo
	void run(int start);

	//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
	//Pre-condicao: Se deseja gerar a imagem
	//Pos-condicao: Visualização do resultado do algoritmo
	void printDFS(bool isImage);

	//Destrutor
	//Pre-condicao:
	//Pos-condicao: Instância deixa de existir
	~graphProfundidade();;
	
};

#endif //GRAPHPROFUNDIDADE_H