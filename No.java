import java.util.ArrayList;

public class No{
	String nome = new String();
	ArrayList<Incidencia> incidencias = new ArrayList<Incidencia>();
	int visitado = -1; // -1 nao visitado, 0 visitado, 1 visitado e todas incidencias visitadas 

	public void add(Incidencia incidencia){
		this.incidencias.add(incidencia);
	}
}
