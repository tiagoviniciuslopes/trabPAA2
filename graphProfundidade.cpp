#include "graphProfundidade.h"

//Converte o id da cor para a palavra
//Pre-condicao: id da cor
//Pos-condicao: string com o nome da cor
string graphProfundidade::getCor(int idCor){
	if(idCor == 0) return "Branco";
	else if(idCor == 1) return "Cinza";
	else if(idCor == 2) return "Preto";
}

//Faz a recursão de visitas ao vértice e seus vizinhos, atualizando seus timestamps e cores
//Pre-condicao: id do vértice inicial
//Pos-condicao: todas as visitas realizadas na arvore em questão
void graphProfundidade::visit(int id){

	this->DFS[id].cor = 1;
	this->DFS[id].timestamp_descoberta = ++timestamp;

	list<path> *vizinhos = myGraph->getNeighbors(id);

	for(list<path>::iterator it = vizinhos->begin(); it != vizinhos->end(); ++it){

		if(this->DFS[it->id_dest].cor == 0){
			this->DFS[it->id_dest].id_pai = id;
			this->DFS[it->id_dest].id_edge = it->my_id;
			visit(it->id_dest);
		}

	}

	this->DFS[id].cor = 2;
	this->DFS[id].timestamp_fim = ++timestamp;
	
}

//Inicializa as estruturas que serão usadas
//Pre-condicao: id do vértice inicial
//Pos-condicao: DFS inicializado
void graphProfundidade::initDFS(){
	auxProfundidade emptyAux;

	//Zera struct auxiliar
	emptyAux.cor = emptyAux.timestamp_fim = emptyAux.timestamp_descoberta = 0;
	emptyAux.id_pai = -1;
	emptyAux.is_start = false;

	//Inicializa DFS
	for (map<int,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		DFS[it->first] = emptyAux;
	}

}

//Executa o algoritmo
//Pre-condicao: id que representa o vértice inicial
//Pos-condicao: DFS com os valores pós-execução do algoritmo
void graphProfundidade::run(int start){

	//Inicializa o DFS
	initDFS();

	//Define o vértice inicial
	DFS[start].is_start = true;

	visit(start);

	//Itera em todos os vértices branco a operação visit
	for (map<int,auxProfundidade>::iterator it = this->DFS.begin(); it != this->DFS.end(); ++it){

		if (it->second.cor == 0){
			visit(it->first);
		}

	}

}

//Imprime o resultado do algoritmo, seja como imagem png ou textualmente
//Pre-condicao: Se deseja gerar a imagem
//Pos-condicao: Visualização do resultado do algoritmo
void graphProfundidade::printDFS(bool isImage){
	//Set's que contem os vértices e arestas que devem estar em destaque na imagem
	set<int> NodeHighlight;
	set<int> EdgeHighlight;

	//Imprime tabela resultante da execução do algoritmo
	cout << "******************************************Profundidade******************************************" << endl;
	cout << "\t" << setw(15) << left << "ID" << "\t\tCor\t\tPai\t\tTSD\t\tTSF" << endl;
	for (map<int,auxProfundidade>::iterator it = this->DFS.begin(); it != this->DFS.end(); ++it){

		if(myGraph->getMap()->at(it->first).name != "")
			cout << it->first << "\t" << setw(15) << left << myGraph->getMap()->at(it->first).name << "\t\t";
		else
			cout << "\t" << setw(15) << left << it->first << "\t\t";

		cout << getCor(it->second.cor) << "\t\t";
		cout << it->second.id_pai << "\t\t";
		cout << it->second.timestamp_descoberta << "\t\t";
		cout << it->second.timestamp_fim << "\t\t" << endl;

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

//Construtor
//Pre-condicao: Grafo original 
//Pos-condicao: myGraph inicializado
graphProfundidade::graphProfundidade(graph *graph_map){
	this->myGraph = graph_map;
};

//Destrutor
//Pre-condicao:
//Pos-condicao: Intância deixa de existir
graphProfundidade::~graphProfundidade(){
};
