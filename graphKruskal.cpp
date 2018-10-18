#include "graphKruskal.h"

//Inicializa as estruturas que serão usadas
//Pre-condicao: id do vértice inicial
//Pos-condicao: Mapa Kruskal inicializado, NewGraph inicializado e lista de pesos inicializado
void graphKruskal::initKruskal(){
	//Inicializa o mapa kruskal
	for(int i = 0; i < myGraph->getMap()->size(); ++i){
		Kruskal[i] = -1;
	}

	//Insere os nós no novo grafo
	for(map<int,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		this->myNewGraph.insertNode(it->first,it->second.name);
	}

	//Insere os pesos de todos os na lista
	list <path> *edge_list = this->myGraph->getAllNeighbors();
	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		edges.insert(pair<int,path>(it->weight,*it));
	}
};

//Verifica a qual arvore um vértice pertence
//Pre-condicao: id vértice
//Pos-condicao: id da arvore
int graphKruskal::find(int id){
	if(Kruskal[id] <= -1) return id;
	else return find(Kruskal[id]);
}

//Simula a inserção de uma aresta no mapa Kruskal
//Pre-condicao: id vértice 1, id vértice 2
//Pos-condicao: Mapa Kruskal atualizado
bool graphKruskal::insertEdge(int e1, int e2){
	int tree_e1 = find(e1);
	int tree_e2 = find(e2);

	//Caso pertençam a árvore diferentes, faz a união de ambas
	if(tree_e1 != tree_e2){
		//Sempre diminui a menor
		if(Kruskal[tree_e1] >= Kruskal[tree_e2]){
			Kruskal[tree_e2]--;
			Kruskal[tree_e1] = tree_e2;
		}
		else{
			Kruskal[tree_e1]--;
			Kruskal[tree_e2] = tree_e1;
		}
		return true;
	}
	else{
		return false;
	}

}

//Construtor
//Pre-condicao: Grafo original 
//Pos-condicao: myGraph inicializado
graphKruskal::graphKruskal(graph *graph_map){
	this->myGraph = graph_map;
	this->myNewGraph.setIsOrientado(this->myGraph->getIsOrientado());
};

//Valida se o algoritmo pode ser executado
//Pre-condicao: 
//Pos-condicao: is_valid atualizado
bool graphKruskal::validate(){
	return !this->myGraph->getIsOrientado();
}

//Executa o algoritmo
//Pre-condicao:
//Pos-condicao: Mapa Kruskal com os valores pós-execução do algoritmo
bool graphKruskal::run(){
	//Verifica se o algoritmo pode executar no grafo
	is_valid = this->validate();
	if(is_valid){

		initKruskal();

		multimap<int,path>::iterator it;

		//Percore mapa de pesos
		while(!edges.empty()){
			//Obtém a cabeça
			it = edges.begin();

			//Se o vértice foi inserido no mapa
			if(insertEdge(it->second.id_orig,it->second.id_dest)){
				//Também o insere no novografo
				this->myNewGraph.insertNeighbor(it->second.id_orig,it->second.name_path,it->second.weight,it->second.id_dest);
			}

			//Remove a cabeça
			edges.erase(it);
		}
	}

	return is_valid;
};

//Retorna o novo grafo
//Pre-condicao:
//Pos-condicao: Mapa Kruskal com os valores pós-execução do algoritmo
graph *graphKruskal::getNewGraph(){
	return &this->myNewGraph;
}

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pre-condicao: Se deseja gerar a imagem
//Pos-condicao: Visualização do resultado do algoritmo
void graphKruskal::printKruskal(bool isImage){

	if(isImage){
		//Nome do arquivo
		string file2Generate;

		set<int> empty_int_list;
		manipulaGraphviz *Desenhador = new manipulaGraphviz(&this->myNewGraph,&empty_int_list,&empty_int_list);

		cout << "Nome do arquivo a ser gerado:" << endl;
		cin  >> file2Generate;

		//Gera arquivo
		Desenhador->criarArquivoImagem(file2Generate);

		delete Desenhador;
	}
	else{
		//Imprime os nós do grafo
		this->myNewGraph.printNodes();
	}

};

//Destrutor
//Pre-condicao:
//Pos-condicao: Instância deixa de existir
graphKruskal::~graphKruskal(){
};
