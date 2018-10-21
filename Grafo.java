import java.io.*;
import java.util.*;


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
}
