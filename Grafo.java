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
				if(in.no != null) fila.offer(in.no);
			}

			buscaLargura(fila);
			aux.visitado = 1;
		}
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
			if(aux.caminhos.get(no) < 10000 && aux.caminhos.get(no) > 0)
				System.out.println("No: " + no.nome + "          Distancia: " + aux.caminhos.get(no));
		}
	}

	private void bellmanFord(LinkedList<No> fila) {
		No aux = fila.poll();

		if(aux != null && aux.visitado == -1){
			aux.visitado = 0;
			inicializaCaminhos(aux);

			for(Incidencia incidencia : aux.incidencias){
				aux.caminhos.put(incidencia.no,incidencia.peso);
				fila.offer(incidencia.no);
			}
			bellmanFord(fila);
			aux.visitado = 1;
		}

		for(Incidencia incidencia : aux.incidencias){
			No inc = incidencia.no;
			for(No no : nos){
				if(!inc.nome.equals(no.nome) && ((inc.caminhos.get(no)+aux.caminhos.get(inc)) < aux.caminhos.get(no)))
					aux.caminhos.put(no,inc.caminhos.get(no)+aux.caminhos.get(inc));
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
}
