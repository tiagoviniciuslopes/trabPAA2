import java.io.*;
import java.util.*;


public class Grafo{
	ArrayList<No> nos;  // todos os vértices do grafo

	public Grafo(){
		nos = new ArrayList<No>();
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

	public No inicio(String nome){
		for(No no : nos){ //Escolhe o no onde vai começar a busca 
			if(no.nome.equals(nome))
				return no;
		}
		return null;
	}

	public void buscaProfundidade(String nome){
		No inicio = inicio(nome);
		buscaProfundidade(inicio);
	}

	public void buscaProfundidade(No inicio){
		if(inicio != null && inicio.visitado == -1){
			inicio.visitado = 0;

			System.out.println(inicio.nome);

			for(Incidencia in : inicio.incidencias){
				buscaProfundidade(in.no);
			}

			inicio.visitado = 1;
		}
	}

	public void buscaLargura(String nome) throws Exception{
		LinkedList<No> fila = new LinkedList<No>();
		fila.offer(inicio(nome));
		buscaLargura(fila);
	}

	public void buscaLargura(LinkedList<No> fila) throws Exception{
		No aux = fila.poll();
		
		if(aux != null && aux.visitado == -1){
			aux.visitado = 0;
	
			System.out.println(aux.nome);

			for(Incidencia in : aux.incidencias){
				if(in.no != null) fila.offer(in.no);
			}

			buscaLargura(fila);
			aux.visitado = 1;
		}
	}
}
