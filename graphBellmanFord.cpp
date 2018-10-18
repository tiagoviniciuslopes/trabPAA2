#include "graphBellmanFord.h"

//Inicializa as estruturas que serão usadas
//Pre-condicao: id do vértice inicial
//Pos-condicao: BellmanFord_map inicializado
void graphBellmanFord::initBellmanFord(int id_ini){
	auxBellmanFord aux;

	//Zera variavel auxiliar
	aux.id_pai = -1;
	aux.isInfinity = true;
	aux.is_start = false;
	aux.id_edge = -1;

	//Atribui a todos os elementos no mapa
	for(map<int,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		BellmanFord_map[it->first] = aux;
	}

	//Inicializa o vértice inicial
	aux.distancia = 0;
	aux.is_start = true;
	aux.isInfinity = false;
	BellmanFord_map[id_ini] = aux;
};

//Condição para executar o relax
//Pre-condicao: id vertice 1, id vertice 2, peso da conexão
//Pos-condicao: se o relax pode ser executado
bool graphBellmanFord::relax_validation(int id_ini, int id_dest, int weight){
	return (BellmanFord_map[id_dest].isInfinity) || (BellmanFord_map[id_dest].distancia > BellmanFord_map[id_ini].distancia + weight);
};

//Executa o relax
//Pre-condicao: id vertice 1, id vertice 2, id da aresta
//Pos-condicao: relax
void graphBellmanFord::relax(list<path>::iterator it){

	//Uma vez que itera sobre a lista geral (onde não existe (3,5) e (5,3) pra representar a mesma aresta)
	//A validação é feita pra ambos, caso seja um grafo não orientado
	if( relax_validation(it->id_orig, it->id_dest, it->weight) ){
		BellmanFord_map[it->id_dest].id_pai = it->id_orig;
		BellmanFord_map[it->id_dest].id_edge = it->my_id;
		BellmanFord_map[it->id_dest].distancia = BellmanFord_map[it->id_orig].distancia + it->weight;
		BellmanFord_map[it->id_dest].isInfinity = false;
	}
	if(!this->myGraph->getIsOrientado() && relax_validation(it->id_dest, it->id_orig, it->weight) ){
		BellmanFord_map[it->id_orig].id_pai = it->id_dest;
		BellmanFord_map[it->id_orig].id_edge = it->my_id;
		BellmanFord_map[it->id_orig].distancia = BellmanFord_map[it->id_dest].distancia + it->weight;
		BellmanFord_map[it->id_orig].isInfinity = false;
	}

};

	//Construtor
	//Pre-condicao: Grafo original 
	//Pos-condicao: myGraph inicializado
graphBellmanFord::graphBellmanFord(graph *graph_map){
	this->myGraph = graph_map;
};

	//Executa o algoritmo
	//Pre-condicao: id que representa o vértice inicial
	//Pos-condicao: BellmanFord_map com os valores pós-execução do algoritmo
bool graphBellmanFord::run(int id_ini){
	//Inicializa
	this->initBellmanFord(id_ini);

	//Obtem todos os vértices
	list <path> *edge_list = this->myGraph->getAllNeighbors();

	//Executa n-1 vezes o relax para todos os vértices
	for(int i = 0; i < this->myGraph->getMap()->size() - 1; i++){

		//Itera na lista de vértices
		for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
			this->relax(it);
		}

	}

	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		//Uma vez que itera sobre a lista geral (onde não existe (3,5) e (5,3) pra representar a mesma aresta)
		//A validação é feita pra ambos, caso seja um grafo não orientado

		//Caso seja possível realizar o relax em qualquer uma das situações, então o grafo contém um loop negativo
		if(relax_validation(it->id_orig, it->id_dest, it->weight)){
			BellmanFord_map.clear();
			return false;
		}
		if(!this->myGraph->getIsOrientado() && relax_validation(it->id_dest, it->id_orig, it->weight)){
			BellmanFord_map.clear();
			return false;
		}
	}
	return true;
};

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pre-condicao: Se deseja gerar a imagem
//Pos-condicao: Visualização do resultado do algoritmo
void graphBellmanFord::printBF(bool isImage){
	//Set's que contem os vértices e arestas que devem estar em destaque na imagem
	set<int> NodeHighlight;
	set<int> EdgeHighlight;

	//Imprime tabela resultante da execução do algoritmo
	cout << "*****************************************BellmanFord********************************************" << endl;
	cout << "\t" << setw(15) << left << "ID" << "\t\tPai\t\tDistancia" << endl;
	for (map<int,auxBellmanFord>::iterator it = this->BellmanFord_map.begin(); it != this->BellmanFord_map.end(); ++it){

		if(myGraph->getMap()->at(it->first).name != "")
			cout << it->first << "\t" << setw(15) << left << myGraph->getMap()->at(it->first).name << "\t\t";
		else
			cout << "\t" << setw(15) << left << it->first << "\t\t";

		cout << it->second.id_pai << "\t\t";
		cout << it->second.distancia << "\t\t" << endl;

		//Caso também venha ser gerado a imagem, a mesma repetição é utilizada para inicialiar os highlights
		if(isImage){
			if(it->second.is_start){
				NodeHighlight.insert(it->first);
			}
			else if(it->second.id_pai != -1){
				EdgeHighlight.insert(it->second.id_edge);
			}
		}
	}
	cout << "************************************************************************************************" << endl;

	if(isImage){
		//String com o nome do arquivo a ser gerado
		string file2Generate;

		manipulaGraphviz *Desenhador = new manipulaGraphviz(myGraph,&NodeHighlight,&EdgeHighlight);

		cout << "Nome do arquivo a ser gerado:" << endl;
		cin  >> file2Generate;

		//Gera o arquivo
		Desenhador->criarArquivoImagem(file2Generate);

		delete Desenhador;
	}

};

//Destrutor
//Pre-condicao:
//Pos-condicao: Instância deixa de existir
graphBellmanFord::~graphBellmanFord(){
};
