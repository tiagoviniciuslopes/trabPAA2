#ifndef MANIPULAGRAPHVIZ_H
#define MANIPULAGRAPHVIZ_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include <set>
#include "graph.h"
using namespace std;

//Responsável por manipular o grafo para desenho numa imagem png, utilizando o Graphviz
class manipulaGraphviz
{

private:
	graph *myGraph; // grafo resultado dos codigos passados
	bool isOrientado; //se é grafo orientado ou não
	set<int> *nodesHighlight; //lista dos nos que tem que haver destaque
	set<int> *edgesHighlight; //lista das arestas com destaques
	string conteudoArquivo; //conteudo para ser inserido dentro do arquivo .dot
	
	//Descricao: testa se uma aresta esta na lista de aresta para se destacar
	//Pre-condição: possuir uma lista de aresta para destaque, != null
	//Pos-condição: retorna verdadeiro se e para destacar, false para nao destacar
	bool isBrilhaAresta(int idAresta); 


	//Descricao: testa se um no esta na lista de nos para se destacar
	//Pre-condição: possuir uma lista de nos para destaque, != null
	//Pos-condição: retorna verdadeiro se e para destacar, false para nao destacar
	bool isBrilhaNo(int idNo);


public:
	//Descricao: Construtor passando o grafo a ser impresso, lista de nos e arestas para destaque
	//Pre-condição: grafo nao nulo, lista de nos e arestas nao nulas
	//Pos-condição: retorna verdadeiro se e para destacar, false para nao destacar
	manipulaGraphviz(graph *myGraph, set<int> *nodesHighlight, set<int> *edgesHighlight);

	//Descricao: Converte um no, em dados texto (string)
	//Pre-condição: id, nome validos.
	//Pos-condição: retorna string em linguagem dot para o no
	string criarNo(int idNo, string nomeNo, bool isBrilhaNo);

	//Descricao: Converte uma aresta, em dados texto (string)
	//Pre-condição: origem, destino, caminhoPeso nao nulos
	//Pos-condição: retorna string em linguagem dot para a aresta
	string criarLigacao(string origem, string destino, string nomeCaminhoPeso, bool isBrilhaCaminho);

	//Descricao: Utiliza as funcoes anteriores para criacao do arquivo, apartir das string retornadas, ele cria um arquivo .dot
	//Pre-condição: grafo, lista de nos e arestas para destaque nao nulos
	//Pos-condição: cria uma imagem.png do grafo
	void criarArquivoImagem(string nomeArquivoImagem);

	//Destrutor
	~manipulaGraphviz();
	
};

#endif //MANIPULAGRAPHVIZ_H