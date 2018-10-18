#include "manipulaGraphviz.h"

//Descricao: testa se uma aresta esta na lista de aresta para se destacar
//Pre-condição: possuir uma lista de aresta para destaque, != null
//Pos-condição: retorna verdadeiro se e para destacar, false para nao destacar
bool manipulaGraphviz::isBrilhaAresta(int idAresta)
{
	return (bool) this->edgesHighlight->count(idAresta);
}

//Descricao: testa se um no esta na lista de nos para se destacar
//Pre-condição: possuir uma lista de nos para destaque, != null
//Pos-condição: retorna verdadeiro se e para destacar, false para nao destacar
bool manipulaGraphviz::isBrilhaNo(int idNo)
{
	return (bool) this->nodesHighlight->count(idNo);
}

//Descricao: Construtor passando o grafo a ser impresso, lista de nos e arestas para destaque
//Pre-condição: grafo nao nulo, lista de nos e arestas nao nulas
//Pos-condição: retorna verdadeiro se e para destacar, false para nao destacar
manipulaGraphviz::manipulaGraphviz(graph *myGraph, set<int> *nodesHighlight, set<int> *edgesHighlight)
{
	this->myGraph = myGraph;
	this->nodesHighlight = nodesHighlight;
	this->edgesHighlight = edgesHighlight;
	this->isOrientado = myGraph->getIsOrientado();
};


//Descricao: Converte um no, em dados texto (string)
//Pre-condição: id, nome validos.
//Pos-condição: retorna string em linguagem dot para o no
string manipulaGraphviz::criarNo(int idNo, string nomeNo, bool isBrilhaNo)
{
	string conteudo = ""; //conteudo da string para retorno
	string aux = ""; //auxiliar string para valores que podem ou nao ser retornados junto
	if(isBrilhaNo) aux = "fontcolor=red"; //se é para destacar adiciona
	//coloca em linguagem dot
	conteudo += to_string(idNo) + " [shape=ellipse label=\""+ (nomeNo!=""? nomeNo: to_string(idNo)) + "\" "+aux+"];\n";
	return conteudo; //retorna o conteudo string, no formatado
}

//Descricao: Converte uma aresta, em dados texto (string)
//Pre-condição: origem, destino, caminhoPeso nao nulos
//Pos-condição: retorna string em linguagem dot para a aresta
string manipulaGraphviz::criarLigacao(string origem, string destino, string nomeCaminhoPeso, bool isBrilhaCaminho)
{
	string conteudo = ""; //conteudo para ser retornado
	conteudo += origem + " -> " + destino + " "; //linguagem dot
	string aux = "[label="+nomeCaminhoPeso; //label
	if(!this->isOrientado) aux += " dir = none"; //se for orientado ha uma flexa, se nao, so linha
	if(isBrilhaCaminho) aux += " color=red";//se for pra destacar
	aux += "]\n";
	
	conteudo += aux;

	return conteudo;  //aresta criada na linguagem dot
}


//Descricao: Utiliza as funcoes anteriores para criacao do arquivo, apartir das string retornadas, ele cria um arquivo .dot
//Pre-condição: grafo, lista de nos e arestas para destaque nao nulos
//Pos-condição: cria uma imagem.png do grafo
void manipulaGraphviz::criarArquivoImagem(string nomeArquivoImagem)
{		
	//conteudo para ser salvo no arquivo
	conteudoArquivo = "digraph G { \n";

	//converte todos os nos em linguagem dot, colocando na string para arquivo
	for(map<int,node>::iterator it = this->myGraph->getMap()->begin(); it != this->myGraph->getMap()->end(); ++it){
		conteudoArquivo += " " + this->criarNo(it->second.my_id, it->second.name, this->isBrilhaNo(it->second.my_id)) + " ";
	}

	//converte todas as arestas para linguagem dot, e coloca na string para o arquivo
	list <path> *edge_list = this->myGraph->getAllNeighbors();
	for(list<path>::iterator it = edge_list->begin(); it != edge_list->end(); ++it){
		string aux = "\"" + (it->name_path==""?"": it->name_path + "\n") + to_string(it->weight) + "\"";
		conteudoArquivo += " " + this->criarLigacao(to_string(it->id_orig), to_string(it->id_dest), aux , this->isBrilhaAresta(it->my_id));
	}

	conteudoArquivo += " }";

	FILE *arq; //arquivo para ser criado

	string openType = "w";
	string fileNameDot = nomeArquivoImagem+".dot";

	arq = fopen(fileNameDot.c_str(), openType.c_str());  // Cria um arquivo texto para gravação
	if (arq == NULL) // Se não conseguiu criar
	{
		cout << "Problemas na CRIACAO do arquivo\n";
		return;
	}

	int flag = fputs(conteudoArquivo.c_str(), arq); //escrevendo no arquivo
	if (flag == EOF)
		cout << "Erro na Gravacao\n";
	fclose(arq);

	string execute;
	
	//comando para chamar a execucao da conversao do arquivo criado, para a imagem png no grafo
	execute = "dot -Tpng "+fileNameDot+" -o "+nomeArquivoImagem+".png";
	system(execute.c_str());

	execute = "rm " + fileNameDot; //apaga arquivo .dot
	system(execute.c_str()); 
	
	execute = "xdg-open " + nomeArquivoImagem+".png"; //abre a imagem
	system(execute.c_str()); //executa

}


manipulaGraphviz::~manipulaGraphviz(){};