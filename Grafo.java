import java.io.*;
import java.util.*;
import java.lang.StringBuffer;


public class Grafo{
	
	ArrayList<No> nos;  // todos os vértices do grafo
	Boolean orientado; // true: é orientado
	int numVertex;

	public Grafo(){
		nos = new ArrayList<No>();
	}

	public void setOrientado(Boolean orientado){
		this.orientado = orientado;
	}

	public Boolean getOrientado(){
		return orientado;	
	}

	public void setNumVertex(int numVertex){
		this.numVertex = numVertex;
	}

	public int getNumVertex(){
		return numVertex;	
	}

	public void unvisit(){
		for(No no:nos){
			no.visitado = -1;
		}
	}

	public void add(No no){
		this.nos.add(no);
	}

	public No head() {
		if (nos == null || nos.isEmpty())
		 return null;
	   
		return nos.get(0);
	}  
	  
	public No tail() {
		if (nos == null || nos.isEmpty())
		 return null;
	   
		return nos.get(nos.size()-1);
	}

	public No find(String nome){
		for(No no : nos){ //Escolhe o no onde vai começar a busca 
			if(no.nome.equals(nome))
				return no;
		}
		return null;
	}

	public void buscaProfundidade(String nome){
		No find = find(nome);
		buscaProfundidade(find);
	}

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

	public void buscaLargura(String nome) throws Exception{
		LinkedList<No> fila = new LinkedList<No>();
		fila.offer(find(nome));
		buscaLargura(fila);
	}

	public void buscaLargura(LinkedList<No> fila) throws Exception{
		No aux = fila.poll();

		if(aux != null && aux.visitado == -1){
			aux.visitado = 0;
	
			System.out.print("["+ aux.nome + "] -> ");

			for(Incidencia in : aux.incidencias){
				if(in.no != null && !fila.contains(in.no)){
					fila.offer(in.no);
				}
			}
			
			buscaLargura(fila);
		}
		aux.visitado = 1;
	}

	public void inicializaCaminhos(No src){
		for(No no : nos){	 
			src.caminhos.put(no, src.infinito);
		}
		src.caminhos.put(src, 0);
	}

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
			bellmanFord(fila);
		}
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
		rt.exec("dot -T png G.dot -o G.png");

		rt.exec("clear");
		rt.exec("xdg-open G.png");
	}

	public void printGraph(ArrayList<Edge> edges){
		for (int i = 0; i <edges.size() ; i++) {
			Edge edge = edges.get(i);
			System.out.println(edge.source +" --- "+ edge.destination +" = "+ edge.weight);
		}
	}

	public int findMST(int [] parent, int vertex){
		//chain of parent pointers from x upwards through the tree
		// until an element is reached whose parent is itself
		if(parent[vertex]!=vertex)
			return findMST(parent, parent[vertex]);;
		return vertex;
	}

	public void union(int [] parent, int x, int y){
		int x_set_parent = findMST(parent, x);
		int y_set_parent = findMST(parent, y);
		//make x as parent of y
		parent[y_set_parent] = x_set_parent;
	}

	public void kruskalMST(){

		ArrayList<Edge> edges = new ArrayList<>();
		ArrayList<Edge> mst = new ArrayList<>();

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
		
		int [] parent = new int[numVertex];
		for (int i = 0; i <numVertex ; i++) {
			parent[i] = i;
		}

		int index = 0;
		while(index<numVertex-1){
			Edge edge = pq.remove();
			//check if adding this edge creates a cycle
			int x_set = findMST(parent, Integer.parseInt(edge.source));
			int y_set = findMST(parent, Integer.parseInt(edge.destination));

			if(x_set==y_set){
				//ignore, will create cycle
			}else {
				//add it to our final result
				mst.add(edge);
				index++;
				union(parent,x_set,y_set);
			}
		}

		System.out.println("before");
		printGraph(edges);

		System.out.println("after");
		printGraph(mst);

	}
}
