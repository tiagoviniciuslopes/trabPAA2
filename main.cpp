#include <iostream>
#include <iomanip>
#include <string>
#include "graph.h"
#include "graphProfundidade.h"
#include "graphLargura.h"
#include "graphDijkstra.h"
#include "graphBellmanFord.h"
#include "graphKruskal.h"
#include "graphPrim.h"

#include "manipulaGraphviz.h"

using namespace std;

bool is_printImage(){
	string resposta;

	cout << "Deseja gerar imagem de resultado (s/n)?" << endl;
	cin  >> resposta;

	return (resposta[0] == 's' || resposta[0] == 'S');
}

int selectNode(graph *myGraph){
	int selection = -3;

	myGraph->printNodes();

	cout << "Indique um id para ser o vértice inicial (-1 para cancelar):" << endl;
	cin >> selection;

	if( (selection >= -1) && (selection < myGraph->getMap()->size()) ){
		return selection;
	}
	else{
		cout << "Valor inválido" << endl;
	}	

	return selection;
}

int main(int argc, char const *argv[]) {

	graph *myGraph = new graph;

	while (1){
		int op, selectedNode ;

		system("clear");

		cout << "-------------------------------" << endl;
		cout << "|" << setw(3) << 0 << "\t" << setw(22) << std::right << "Carregar grafo" << "|" << endl;
		cout << "|" << "-----------------------------" << "|" <<endl;
		cout << "|" << setw(3) << 1 << "\t" << setw(22) << std::right << "Executar DFS" << "|" << endl;
		cout << "|" << setw(3) << 2 << "\t" << setw(22) << std::right << "Executar BFS" << "|" << endl;
		cout << "|" << "-----------------------------" << "|" <<endl;
		cout << "|" << setw(3) << 3 << "\t" << setw(22) << std::right << "Executar Dijkstra" << "|" << endl;
		cout << "|" << setw(3) << 4 << "\t" << setw(22) << std::right << "Executar Bellman-Ford" << "|" << endl;
		cout << "|" << "-----------------------------" << "|" <<endl;
		cout << "|" << setw(3) << 5 << "\t" << setw(22) << std::right << "Executar Kruskal" << "|" << endl;
		cout << "|" << setw(3) << 6 << "\t" << setw(22) << std::right << "Executar Prim" << "|" << endl;
		cout << "|" << "-----------------------------" << "|" <<endl;
		cout << "|" << setw(3) << 7 << "\t" << setw(22) << std::right << "Imprimir Grafo" << "|" << endl;
		cout << "|" << "-----------------------------" << "|" <<endl;
		cout << "|" << setw(3) << -1 << "\t" << setw(22) << std::right << "Sair" << "|" << endl;
		cout << "-------------------------------" << endl << endl;
		
		cout << "Selecione uma opcao: ";
		cin  >> op;

		if (op == 0){

			myGraph->clear();

			string input = "";
			cout << "Insira o nome do arquivo a ser lido:" << endl;
			cin  >> input;

			if(myGraph->readInput(input))
				cout << "Arquivo lido com sucesso!" << endl;
			else
				cout << "Falha na leitura do arquivo!" << endl;


		}
		else if (op == 1){

			//Busca em profundidade
			graphProfundidade *DFS = new graphProfundidade(myGraph);

			selectedNode = selectNode(myGraph);
			if(selectedNode != -1){

				DFS->run(selectedNode);
				DFS->printDFS(is_printImage());

			}
			delete DFS;

		}
		else if (op == 2){

			//Busca em largura
			graphLargura *BFS = new graphLargura(myGraph);

			selectedNode = selectNode(myGraph);
			if(selectedNode != -1){

				BFS->run(selectedNode);
				BFS->printBFS(is_printImage());

			}

			delete BFS;

		}
		else if (op == 3){

			//Dijkstra
			graphDijkstra *DJK = new graphDijkstra(myGraph);

			selectedNode = selectNode(myGraph);
			if(selectedNode != -1){

				DJK->run(selectedNode);
				DJK->printDJK(is_printImage());

			}

			delete DJK;

		}
		else if (op == 4){

			//Bellman-Ford
			graphBellmanFord *BellmanFord = new graphBellmanFord(myGraph);

			selectedNode = selectNode(myGraph);
			if(selectedNode != -1){

				if(BellmanFord->run(selectedNode)){
					BellmanFord->printBF(is_printImage());
				}
				else{
					cout << "Loop negativo identificado" << endl;
				}

			}
			delete BellmanFord;


		}
		else if (op == 5){

			//Kruskal
			graphKruskal *Kruskal = new graphKruskal(myGraph);

			if(Kruskal->run()){
				Kruskal->printKruskal(is_printImage());
			}
			else{
				cout << "Grafo deve ser não orientado" << endl;
			}

			delete Kruskal;


		}
		else if (op == 6){

			//Prim
			graphPrim *Prim = new graphPrim(myGraph);

			selectedNode = selectNode(myGraph);
			if(selectedNode != -1){

				if(Prim->run(selectedNode)){
					Prim->printPrim(is_printImage());
				}
				else{
					cout << "Grafo deve ser não orientado" << endl;
				}

			}
			delete Prim;

		}
		else if (op == 7){

			if(is_printImage()){

				string file2Generate;
				set<int> empty_int_list;
				manipulaGraphviz *Desenhador = new manipulaGraphviz(myGraph,&empty_int_list,&empty_int_list);

				cout << "Nome do arquivo a ser gerado:" << endl;
				cin  >> file2Generate;

				Desenhador->criarArquivoImagem(file2Generate);

				delete Desenhador;
			}
			else{
				myGraph->printNodes();
			}

		}


		cout << "<Pressione ENTER p/ continuar>" << endl;
		cin.get();
		cin.get();


		if(op == -1) break;

	};



	delete myGraph;

	return 0;
}