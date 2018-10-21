import java.util.ArrayList;
import java.util.Hashtable;

public class No{
	String nome = new String();
	ArrayList<Incidencia> incidencias = new ArrayList<Incidencia>();
	int visitado = -1; // -1 nao visitado, 0 visitado, 1 visitado e todas incidencias visitadas 
	final int infinito = Integer.MAX_VALUE;
	Hashtable<No, Integer> caminhos = new Hashtable<No, Integer>();

	public void add(Incidencia incidencia){
		this.incidencias.add(incidencia);
	}
}
