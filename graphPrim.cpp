#include "graphPrim.h"

//Inicializa as estruturas que serão usadas
//Pre-condicao: id do vértice inicial
//Pos-condicao: Novo grafo inicializado e mapa de Prim inicializado
void graphPrim::initPrim(int id_ini){
	auxPrim aux;

	//Zera variavel auxiliar
	aux.id_pai = -1;
	aux.is_infinity = true;
	aux.is_start = false;
	aux.id_edge = -1;

	//Atribui a todos os elementos no mapa
	for(map<int,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		PRIM_map[it->first]  = aux;
	}

	//Inicializa o vértice inicial
	aux.distancia = 0;
	aux.is_infinity = false;
	aux.is_start = true;
	PRIM_map[id_ini] = aux;

};

//Condição para executar o relax
//Pre-condicao: id vertice 1, id vertice 2, peso da conexão
//Pos-condicao: se o relax pode ser executado
bool graphPrim::relax_validation(int id_ini, int id_dest, int weight){
	return (PRIM_map[id_dest].is_infinity) || (PRIM_map[id_dest].distancia > PRIM_map[id_ini].distancia + weight);
};

//Executa o relax
//Pre-condicao: id vertice 1, id vertice 2, id da aresta
//Pos-condicao: relax
void graphPrim::relax(int id_ini, int id_dest, int id_path){

	//Obtém todos os vizinhos do id_ini
	list <path> *edge_list = this->myGraph->getNeighbors(id_ini);

	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		//Busca pelo informado
		if(it->my_id == id_path){
			//Se possível, realiza o relax
			if( relax_validation(id_ini, id_dest, it->weight) ){
				PRIM_map[id_dest].id_pai = id_ini;
				PRIM_map[id_dest].id_edge = id_path;
				PRIM_map[id_dest].distancia = PRIM_map[id_ini].distancia + it->weight;
				PRIM_map[id_dest].is_infinity = false;
			}
		}
	}
};

//Procura o vértice não explorado com a menor distancia
//Pre-condicao: 
//Pos-condicao: id do vértice buscado, ou -1 caso não exista tal vértice
int graphPrim::naoExploradoComMenorDistancia(){

	bool isFirst = true;
	int pos = -1;
	int lower;

	//Itera no mapa
	for(map<int,auxPrim>::iterator it = this->PRIM_map.begin(); it != this->PRIM_map.end(); ++it){

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

};

//Construtor
//Pre-condicao: Grafo original 
//Pos-condicao: myGraph inicializado
graphPrim::graphPrim(graph *graph_map){
	this->myGraph = graph_map;
	this->myNewGraph.setIsOrientado(false);
};

//Verifica se o algoritmo pode ser executado
//Pre-condicao:
//Pos-condicao: is_valid atualizado
bool graphPrim::validate(){
	return !this->myGraph->getIsOrientado();
};

//Executa o algoritmo
//Pre-condicao: id que representa o vértice inicial
//Pos-condicao: Mapa de Prim gerado e novo grafo gerado
bool graphPrim::run(int id_ini){
	is_valid = this->validate();
	//Valida grafo
	if(is_valid){

		//Inicializa
		this->initPrim(id_ini);

		int node2Explore = id_ini;

		//Enquanto encontrar um vértice não explorado com distância != infinito
		while(node2Explore != -1){

			//Seta como explorado e não infinito
			PRIM_map[node2Explore].is_explorado = true;
			PRIM_map[node2Explore].is_infinity = false;

			//Obtem lista de vizinho
			list <path> *edge_list = this->myGraph->getNeighbors(node2Explore);

			//Realiza relax em todos os vizinhos
			for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
				relax(node2Explore,it->id_dest,it->my_id);
			}

			//Busca próximo vértice pra explorar
			node2Explore = naoExploradoComMenorDistancia();
		}

		//Itera no mapa e insere no novo grafo de acordo com oque estiver informado no mapa
		for (map<int,auxPrim>::iterator it = this->PRIM_map.begin(); it != this->PRIM_map.end(); ++it){
			if(it->second.is_start){
				this->myNewGraph.insertNode(it->first,(*this->myGraph->getMap())[it->first].name);
			}
			else if(it->second.id_pai != -1){
				path * p_aux = this->myGraph->getNeighbor(it->second.id_edge);

				this->myNewGraph.insertNode(it->first, (*this->myGraph->getMap())[it->first].name);
				this->myNewGraph.insertNeighbor(p_aux->id_orig, p_aux->name_path, p_aux->weight, p_aux->id_dest);
			}
		}
	}
	return is_valid;
};

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pre-condicao: Se deseja gerar a imagem
//Pos-condicao: Visualização do resultado do algoritmo
void graphPrim::printPrim(bool isImage){
	if(!is_valid){
		cout << "Grafo inválido, deve ser não orientado para rodar" << endl;
		return;
	}

	if(isImage){
		//Nome do arquivo
		string file2Generate;

		set<int> empty_int_list;
		manipulaGraphviz *Desenhador = new manipulaGraphviz(&this->myNewGraph,&empty_int_list,&empty_int_list);

		cout << "Nome do arquivo a ser gerado:" << endl;
		cin  >> file2Generate;

		//Gera o arquivo
		Desenhador->criarArquivoImagem(file2Generate);

		delete Desenhador;
	}
	else{
		//Imprime os vértices
		this->myNewGraph.printNodes();
	}


};

//Destrutor
//Pre-condicao:
//Pos-condicao: Instância deixa de existir
graphPrim::~graphPrim(){

};

