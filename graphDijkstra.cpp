#include "graphDijkstra.h"

//Inicializa as estruturas que serão usadas
//Pre-condicao: id do vértice inicial
//Pos-condicao: DIJKSTRA_map inicializado
void graphDijkstra::initDIJKSTRA(int id_ini){
	auxDijkstra aux;

	//Zera variavel auxiliar
	aux.id_pai = -1;
	aux.is_infinity = true;
	aux.is_start = false;
	aux.id_edge = -1;

	//Atribui a todos os elementos no mapa
	for(map<int,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		DIJKSTRA_map[it->first]  = aux;
	}

	//Inicializa o vértice inicial
	aux.distancia = 0;
	aux.is_infinity = false;
	aux.is_start = true;
	DIJKSTRA_map[id_ini] = aux;
};

//Condição para executar o relax
//Pre-condicao: id vertice 1, id vertice 2, peso da conexão
//Pos-condicao: se o relax pode ser executado
bool graphDijkstra::relax_validation(int id_ini, int id_dest, int weight){
	return (DIJKSTRA_map[id_dest].is_infinity) || (DIJKSTRA_map[id_dest].distancia > DIJKSTRA_map[id_ini].distancia + weight);
}

//Executa o relax
//Pre-condicao: id vertice 1, id vertice 2, id da aresta
//Pos-condicao: relax
void graphDijkstra::relax(int id_ini, int id_dest, int id_path){

	//Obtém todos os vizinhos do id_ini
	list <path> *edge_list = this->myGraph->getNeighbors(id_ini);

	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		//Busca pelo informado
		if(it->my_id == id_path){
			//Se possível, realiza o relax
			if( relax_validation(id_ini, id_dest, it->weight) ){
				DIJKSTRA_map[id_dest].id_pai = id_ini;
				DIJKSTRA_map[id_dest].id_edge = id_path;
				DIJKSTRA_map[id_dest].distancia = DIJKSTRA_map[id_ini].distancia + it->weight;
				DIJKSTRA_map[id_dest].is_infinity = false;
			}
		}
	}
}

//Procura o vértice não explorado com a menor distancia
//Pre-condicao: 
//Pos-condicao: id do vértice buscado, ou -1 caso não exista tal vértice
int graphDijkstra::naoExploradoComMenorDistancia(){

	bool isFirst = true;
	int pos = -1;
	int lower;

	//Itera no mapa
	for(map<int,auxDijkstra>::iterator it = this->DIJKSTRA_map.begin(); it != this->DIJKSTRA_map.end(); ++it){

		if(it->second.is_explorado == false && it->second.id_pai != -1){
			if(isFirst){
				pos = it->first;
				lower = it->second.distancia;
				isFirst = false;
			}
			else{
				if( it->second.distancia < lower ){
					pos = it->first;
					lower = it->second.distancia;
				}
			}
		}

	}

	return pos;
}

//Construtor
//Pre-condicao: Grafo original 
//Pos-condicao: myGraph inicializado
graphDijkstra::graphDijkstra(graph *graph_map){
	this->myGraph = graph_map;
};

//Verifica se o algoritmo pode ser executado
//Pre-condicao:
//Pos-condicao: is_valid atualizado
bool graphDijkstra::validate(){
	//Obtem todos as arestas
	list <path> *edge_list = this->myGraph->getAllNeighbors();

	//Verifica se existe alguma negativa
	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		if ( it->weight < 0 ) return false;
	}

	return true;
};

//Executa o algoritmo
//Pre-condicao: id que representa o vértice inicial
//Pos-condicao: DIJKSTRA_map com os valores pós-execução do algoritmo
bool graphDijkstra::run(int id_ini){
	is_valid = this->validate();
	//Valida grafo
	if(is_valid){

		//Inicializa
		this->initDIJKSTRA(id_ini);

		int node2Explore = id_ini;

		//Enquanto encontrar um vértice não explorado com distância != infinito
		while(node2Explore != -1){

			//Seta como explorado e não infinito
			DIJKSTRA_map[node2Explore].is_explorado = true;
			DIJKSTRA_map[node2Explore].is_infinity = false;

			//Obtem lista de vizinho
			list <path> *edge_list = this->myGraph->getNeighbors(node2Explore);

			//Realiza relax em todos os vizinhos
			for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
				relax(node2Explore,it->id_dest,it->my_id);
			}

			//Busca próximo vértice pra explorar
			node2Explore = naoExploradoComMenorDistancia();
		}

	}
	return is_valid;
};

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pre-condicao: Se deseja gerar a imagem
//Pos-condicao: Visualização do resultado do algoritmo
void graphDijkstra::printDJK(bool isImage){
	if(!is_valid){
		cout << "Grafo inválido, contém arrestas negativas" << endl;
		return;
	}

	//Set's que contem os vértices e arestas que devem estar em destaque na imagem
	set<int> NodeHighlight;
	set<int> EdgeHighlight;

	//Imprime tabela resultante da execução do algoritmo
	cout << "*******************************************DIJKSTRA*********************************************" << endl;
	cout << "\t" << setw(15) << left << "ID" << "\t\tPai\t\tDistancia\tExplorado?" << endl;
	for (map<int,auxDijkstra>::iterator it = this->DIJKSTRA_map.begin(); it != this->DIJKSTRA_map.end(); ++it){

		if(myGraph->getMap()->at(it->first).name != "")
			cout << it->first << "\t" << setw(15) << left << myGraph->getMap()->at(it->first).name << "\t\t";
		else
			cout << "\t" << setw(15) << left << it->first << "\t\t";

		cout << it->second.id_pai << "\t\t";
		cout << it->second.distancia << "\t\t";
		cout << (it->second.is_explorado?"Sim":"Não") << "\t\t" << endl;

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

}

//Destrutor
//Pre-condicao:
//Pos-condicao: Instância deixa de existir
graphDijkstra::~graphDijkstra(){

};
