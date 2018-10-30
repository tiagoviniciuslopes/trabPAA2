import java.util.ArrayList;
import java.util.Hashtable;

public class No{
	String nome = new String();
	ArrayList<Incidencia> incidencias = new ArrayList<Incidencia>();
	int visitado = -1; // -1 nao visitado, 0 visitado, 1 visitado e todas incidencias visitadas 
	final int infinito = 1000000;
	Hashtable<No, Integer> caminhos = new Hashtable<No, Integer>();

	//Funcao: adiciona uma incidencia ao no
	//Entrada: incidencia a ser adicionada
	//Saida: 
	//Pre-condicao: um array list de incidencias deve existir
	//Pos-condicao: a incidencia deve estar incerida no arraylist
	public void add(Incidencia incidencia){
		this.incidencias.add(incidencia);
	}
}
