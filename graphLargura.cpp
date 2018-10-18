#include "graphLargura.h"

//Converte o id da cor para a palavra
//Pre-condicao: id da cor
//Pos-condicao: string com o nome da cor
string graphLargura::getCor(int idCor){
	if(idCor == 0) return "Branco";
	else if(idCor == 1) return "Cinza";
	else if(idCor == 2) return "Preto";
};

//Inicializa as estruturas que serão usadas
//Pre-condicao: id do vértice inicial
//Pos-condicao: BFS_map inicializado
void graphLargura::initBFS(int id_ini){
	auxLargura emptyAux;

	//Zera struct auxiliar
	emptyAux.cor = 0;
	emptyAux.id_pai = -1;
	emptyAux.distancia = 0;
	emptyAux.is_start = false;
	emptyAux.id_edge = -1;

	//Inicializa mapa
	for (map<int,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		BFS_map[it->first] = emptyAux;
	}

	this->BFS_map[id_ini].cor = 1;
	this->BFS_map[id_ini].distancia = 0;
	this->BFS_map[id_ini].is_start = true;
};

//Construtor
//Pre-condicao: Grafo original 
//Pos-condicao: myGraph inicializado
graphLargura::graphLargura(graph *graph_map){
	this->myGraph = graph_map;
};

//Executa o algoritmo
//Pre-condicao: id que representa o vértice inicial
//Pos-condicao: BFS_map com os valores pós-execução do algoritmo
void graphLargura::run(int id_ini){
	initBFS(id_ini);

	//Adiciona o vértice inicial da fila
	BFS_queue.push(id_ini);

	//Em quanto tiver algum elemento na fila
	while(!BFS_queue.empty()){
		//Recebe a cabeça
		int head = BFS_queue.front();

		//Busca todos os vizinhos da cabeça
		list<path> *vizinhos = myGraph->getNeighbors(head);

		for(list<path>::iterator it = vizinhos->begin(); it != vizinhos->end(); ++it){

			//Caso o vizinho não tenha sido visitado, seta a cor como cinza e atualiza suas informações
			if(this->BFS_map[it->id_dest].cor == 0){
				this->BFS_map[it->id_dest].cor = 1;
				this->BFS_map[it->id_dest].id_pai = head;
				this->BFS_map[it->id_dest].id_edge = it->my_id;
				// this->BFS_map[it->id_dest].distancia = BFS_map[head].distancia + 1;
				this->BFS_map[it->id_dest].distancia = BFS_map[head].distancia + it->weight;

				//Insere o vizinho na fila
				BFS_queue.push(it->id_dest);
			}

		}

		//Remove a cabeça e atualiza sua cor para preto
		BFS_queue.pop();
		BFS_map[head].cor = 2;

	}
}

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pre-condicao: Se deseja gerar a imagem
//Pos-condicao: Visualização do resultado do algoritmo
void graphLargura::printBFS(bool isImage){
	//Set's que contem os vértices e arestas que devem estar em destaque na imagem
	set<int> NodeHighlight;
	set<int> EdgeHighlight;

	//Imprime tabela resultante da execução do algoritmo
	cout << "*********************************************Largura********************************************" << endl;
	cout << "\t" << setw(15) << left << "ID" << "\t\tCor\t\tPai\t\tDistancia" << endl;
	for (map<int,auxLargura>::iterator it = this->BFS_map.begin(); it != this->BFS_map.end(); ++it){

		if(myGraph->getMap()->at(it->first).name != "")
			cout << it->first << "\t" << setw(15) << left << myGraph->getMap()->at(it->first).name << "\t\t";
		else
			cout << "\t" << setw(15) << left << it->first << "\t\t";

		cout << getCor(it->second.cor) << "\t\t";
		cout << it->second.id_pai << "\t\t";
		cout << it->second.distancia << "\t\t" << endl;

		//Caso também venha ser gerado a imagem, a mesma repetição é utilizada para inicialiar os highlights
		if(isImage){
			if(it->second.is_start){
				NodeHighlight.insert(it->first);
			}
			else if(it->second.id_pai != -1){
				cout << it->second.id_edge;
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
//Pos-condicao: Intância deixa de existir
graphLargura::~graphLargura(){

};
