import java.io.*;
import java.util.*;
import java.lang.StringBuffer;


public class Grafo{
	
	ArrayList<No> nos;  // todos os vértices do grafo
	Boolean orientado; // true: é orientado
	int numVertex;

	//Funcao: instancia um arraylist de nos
	//Entrada: 
	//Saida: 
	//Pre-condicao: 
	//Pos-condicao: o arraylist é instanciado na memoria
	public Grafo(){
		nos = new ArrayList<No>();
	}

	//Funcao: atribui um valor ao atributo orientado
	//Entrada: o valor a ser atribuido
	//Saida: 
	//Pre-condicao: 
	//Pos-condicao: o valor eh setado no atributo orientado
	public void setOrientado(Boolean orientado){
		this.orientado = orientado;
	}

	//Funcao: retorna o valor do atributo orientado
	//Entrada: 
	//Saida: o valor do atributo orientado
	//Pre-condicao: 
	//Pos-condicao: o valor do atributo eh retornado
	public Boolean getOrientado(){
		return orientado;	
	}

	//Funcao: atribui um valor ao atributo numVertex
	//Entrada: o valor a ser atribuido
	//Saida: 
	//Pre-condicao: 
	//Pos-condicao: o valor eh setado no atributo numVertex
	public void setNumVertex(int numVertex){
		this.numVertex = numVertex;
	}

	//Funcao: retorna o valor do atributo numVertex
	//Entrada: 
	//Saida: o valor do atributo numVertex
	//Pre-condicao: 
	//Pos-condicao: o valor do atributo eh retornado
	public int getNumVertex(){
		return numVertex;	
	}

	//Funcao: seta todos os nos do grafo como nao visitados
	//Entrada: 
	//Saida: 
	//Pre-condicao: o grafo deve possuir nos
	//Pos-condicao: o atributo visitado de cada no recebe -1
	public void unvisit(){
		for(No no:nos){
			no.visitado = -1;
		}
	}

	//Funcao: adiciona um no ao grafo
	//Entrada: no a ser adicionado
	//Saida: 
	//Pre-condicao: o arraylist de nos deve estar instanciado 
	//Pos-condicao: o no eh adicionado ao arraylist
	public void add(No no){
		this.nos.add(no);
	}

	//Funcao: retorna o primeiro elemento do arraylist
	//Entrada: 
	//Saida: o primeiro no do arraylist
	//Pre-condicao: o arraylist deve estar instanciado
	//Pos-condicao: o no eh retornado
	public No head() {
		if (nos == null || nos.isEmpty())
		 return null;
	   
		return nos.get(0);
	}  
	  
	//Funcao: retorna o ultimo elemento do arraylist de nos
	//Entrada: 
	//Saida: o ultimo no do arraylist
	//Pre-condicao: o arraylist deve estar instanciado
	//Pos-condicao: o no eh retornado
	public No tail() {
		if (nos == null || nos.isEmpty())
		 return null;
	   
		return nos.get(nos.size()-1);
	}

	//Funcao: procura no arraylist um no com um determinado nome
	//Entrada: o nome a ser procurado
	//Saida: o no que possui o nome
	//Pre-condicao: 
	//Pos-condicao: o no com o nome especificado eh retornado
	public No find(String nome){
		for(No no : nos){ //Escolhe o no onde vai começar a busca 
			if(no.nome.equals(nome))
				return no;
		}
		return null;
	}

	//Funcao: procura o no inicial para iniciar a busca em profundidade
	//Entrada: o nome do no inicial
	//Saida: 
	//Pre-condicao: o grafo deve possuir um no com o nome
	//Pos-condicao: a busca em profundidade eh feita
	public void buscaProfundidade(String nome){
		No find = find(nome);
		buscaProfundidade(find);
	}

	//Funcao: faz a busca em profundidade
	//Entrada: o no inicial da busca
	//Saida: 
	//Pre-condicao: o no inicial deve existir
	//Pos-condicao: a busca em profundidade eh feita
	public void buscaProfundidade(No find){
		if(find != null && find.visitado == -1){
			find.visitado = 0;

			System.out.print("["+ find.nome + "] -> ");

			for(Incidencia in : find.incidencias){
				buscaProfundidade(in.no);
			}

			find.visitado = 1;
		}
	}

	//Funcao: procura o no inicial para iniciar a busca em largura
	//Entrada: o nome do no inicial
	//Saida: 
	//Pre-condicao: o grafo deve possuir um no com o nome especificado
	//Pos-condicao: a busca em largura eh feita
	public void buscaLargura(String nome) throws Exception{
		LinkedList<No> fila = new LinkedList<No>();
		fila.offer(find(nome));
		buscaLargura(fila);
	}

	//Funcao: faz a busca em largura utilizando uma fila
	//Entrada: fila com os nos que devem ser pesquisados em ordem
	//Saida: 
	//Pre-condicao: a fila deve existir
	//Pos-condicao: a busca em largura eh feita
	public void buscaLargura(LinkedList<No> fila) throws Exception{
		No aux = fila.poll();

		if(aux != null && aux.visitado == -1){
			aux.visitado = 0;
			System.out.print("["+ aux.nome + "] -> ");

			for(Incidencia in : aux.incidencias){
				if(!fila.contains(in.no)){
					fila.offer(in.no);
				}
			}
			
			
		}
		if(fila!=null && aux!=null) buscaLargura(fila);
		if (aux!=null )aux.visitado = 1;
	}

	//Funcao: inicializa os caminhos para o algoritmo de bellman ford
	//Entrada: o no inicial do algoritmo
	//Saida: 
	//Pre-condicao: o no deve existir
	//Pos-condicao: todos os caminhos recebem valor inifinito com excessao do caminho ao proprio no que recebe 0
	public void inicializaCaminhos(No src){
		for(No no : nos){	 
			src.caminhos.put(no, src.infinito);
		}
		src.caminhos.put(src, 0);
	}

	//Funcao: procura o no onde iniciar o algoritmo de bellman ford e inicia a pesquisa do menor caminho
	//Entrada: nome do no onde o algoritmo vai se iniciar
	//Saida: 
	//Pre-condicao: o no deve existir
	//Pos-condicao: o algoritmo de bellman ford eh executado
	public void bellmanFord(String nome){
		No aux = find(nome);
		LinkedList<No> fila = new LinkedList<No>();
		fila.offer(aux);
		bellmanFord(fila);

		for(No no : nos){
			//if(aux.caminhos.get(no) < 10000 && aux.caminhos.get(no) > 0)
				System.out.println("No: " + no.nome + "          Distancia: " + aux.caminhos.get(no));
		}
	}

	//Funcao: executa o algoritmo de bellman ford para encontrar os menores caminhos
	//Entrada: fila com os nos que devem ser pesquisados em ordem
	//Saida: 
	//Pre-condicao: a fila deve existir
	//Pos-condicao: o algoritmo eh executado
	private void bellmanFord(LinkedList<No> fila) {
		No aux = fila.poll();

		if(aux != null && aux.visitado == -1){
			aux.visitado = 0;
			inicializaCaminhos(aux);

			for(Incidencia incidencia : aux.incidencias){
				if(incidencia.no != null){
					aux.caminhos.put(incidencia.no,incidencia.peso);
					if(!fila.contains(incidencia.no)){
						fila.offer(incidencia.no);
					}
				}
			}
		}
		if(fila!=null && aux!=null) bellmanFord(fila);
		if(aux!=null){
			aux.visitado = 1;

			for(Incidencia incidencia : aux.incidencias){
				No inc = incidencia.no;
				for(No no : nos){
					if(inc.caminhos.get(no) != inc.infinito && !no.nome.equals(aux.nome)){
						if((aux.caminhos.get(inc) + inc.caminhos.get(no)) < aux.caminhos.get(no)){
							aux.caminhos.remove(no);
							aux.caminhos.put(no,aux.caminhos.get(inc) + inc.caminhos.get(no));
						}
					}
				}
			}
		}
	}

	//Funcao: gera um arquivo .dot com as propriedades do grafo e depois gera uma imagem que represente graficamente o grafo
	//Entrada: 
	//Saida: 
	//Pre-condicao: o grafo deve existir
	//Pos-condicao: os arquivos devem ser criados
	public void geraDot() throws Exception{
		StringBuffer dot;
		String seta;

		if(orientado){
			dot  = new StringBuffer("digraph G {\n");
			seta = new String(" -> ");
		}else{
			dot  = new StringBuffer("graph G {\n");
			seta = new String(" -- ");
		}

		dot.append("rankdir=LR\n");

		for(No no : nos){
			for(Incidencia incidencia : no.incidencias){
				if(!incidencia.duplicate){
					dot.append("\t");
					dot.append(no.nome.replaceAll("\\s",""));
					dot.append(seta);
					dot.append(incidencia.no.nome.replaceAll("\\s",""));
					dot.append(" [label=\"");
					dot.append(incidencia.peso);
					dot.append("\n");
					if(!incidencia.label.isEmpty()){
						dot.append("'"+incidencia.label+"'");
					}
					dot.append("\"];\n");
				}
			}
		}
		dot.append("}\n");

		Writer writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("G.dot"), "utf-8"));
		writer.write(dot.toString());
		writer.close();

		Runtime rt = Runtime.getRuntime();
		Process proc = rt.exec("dot -T png G.dot -o G.png");

		rt.exec("clear");
		rt.exec("xdg-open G.png");
	}

	//Funcao: printa os vertices e pesos de uma lista de adjacencias que representa um grafo
	//Entrada: lista de adjacencias
	//Saida: 
	//Pre-condicao: lista de adjacencias populada e válida
	//Pos-condicao: 
	public void printGraph(ArrayList<Edge> edges){
		int acum = 0;
		for (int i = 0; i <edges.size() ; i++) {
			Edge edge = edges.get(i);
			System.out.println(edge.source +" --- "+ edge.destination +" = "+ edge.weight);
			acum += edge.weight;
		}
		System.out.println("___________");
		System.out.println("TOTAL:   "+acum);
	}

	//Funcao: procura o set de um vertice de baixo pra cima até o elemento que o pai seja ele mesmo
	//Entrada: cadeia de ponteiros pai, vertice a ser procurado
	//Saida: ponteiro pro elemento, se achado
	//Pre-condicao: 
	//Pos-condicao: 
	public int findMST(int[] parent, int vertex){
		if(parent[vertex]!=vertex){
			return findMST(parent, parent[vertex]);
		}
		return vertex;
	}

	//Funcao: faz a união de dois sets x e y
	//Entrada: o vetor de sets pai, set x e set y
	//Saida: 
	//Pre-condicao: 
	//Pos-condicao: 
	public void union(int[] parent, int x, int y){
		int x_set_parent = findMST(parent, x);
		int y_set_parent = findMST(parent, y);

		parent[y_set_parent] = x_set_parent;
	}

	//Funcao: calcula a arvore minima geradora(MST) utilizando o algoritmo de kruskal
	//Entrada: nenhuma
	//Saida: nenhuma
	//Pre-condicao: grafo não orientado e populado
	//Pos-condicao: deve ser printado os vertices que compoe a arvore minima geradora(MST) e o total dos pesos
	public void kruskalMST(){
		ArrayList<Edge> mst = new ArrayList<>();

		if(!orientado){

			ArrayList<Edge> edges = new ArrayList<>();

			for(int i=0;i<numVertex;i++){
				for(int j=0;j<nos.get(i).incidencias.size();j++){
					Edge edge = new Edge(nos.get(i).nome, nos.get(i).incidencias.get(j).no.nome, nos.get(i).incidencias.get(j).peso);
					if(!nos.get(i).incidencias.get(j).duplicate){
						edges.add(edge);
					}
				}
			}

			PriorityQueue<Edge> pq = new PriorityQueue<>(edges.size(), Comparator.comparingInt(o -> o.weight));
			
			for (int i = 0; i <edges.size() ; i++) {
				pq.add(edges.get(i));
			}
			
			//inicializa um vetor de ponteiros com os proprios indices
			int[] parent = new int[numVertex];
			for (int i = 0; i <numVertex ; i++) {
				parent[i] = i;
			}

			int index = 0;
			while(index<numVertex-1){
				Edge edge = pq.remove();
				
				// checa se cria ciclo
				int x = findMST(parent, Integer.parseInt(edge.source));
				int y = findMST(parent, Integer.parseInt(edge.destination));

				if(x!=y){
					mst.add(edge);
					index++;
					union(parent,x,y);
				}
			}

			printGraph(mst);

		}else{
			System.out.println("Erro, o grafo precisa ser não orientado!");
		}
	}
}
