import java.util.ArrayList;
import java.util.Hashtable;

public class No{
	String nome = new String();
	ArrayList<Incidencia> incidencias;
	int visitado = -1; // -1 nao visitado, 0 visitado, 1 visitado e todas incidencias visitadas 
	final int infinito = 1000000;
	Hashtable<No, Integer> caminhos;

	public No(){
		incidencias = new ArrayList<Incidencia>();
		caminhos = new Hashtable<No, Integer>();
	}

	public void add(Incidencia incidencia){
		this.incidencias.add(incidencia);
	}
}
