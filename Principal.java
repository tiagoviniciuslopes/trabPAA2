import java.io.*;
import java.util.*;

public class Principal{

    public static void main(String args[]) throws Exception{

        Grafo teste = new Grafo();
        teste = carregar_grafo("inputs/grafo1.txt");

        Grafo grafo = new Grafo();
        No a = new No();
        No b = new No();
        No c = new No();
        No d = new No();

        a.nome = "a";
        b.nome = "b";
        c.nome = "c";
        d.nome = "d";

        Incidencia emA = new Incidencia();
        emA.no = a;
        emA.peso = 0;
        Incidencia emC = new Incidencia();
        emC.no = c;
        emC.peso = 0;
        Incidencia emD = new Incidencia();
        emD.no = d;
        emD.peso = 0;

        b.incidencias.add(emC);
        b.incidencias.add(emD);
        c.incidencias.add(emA);

        grafo.add(a);
        grafo.add(b);
        grafo.add(c);
        grafo.add(d);
        
        grafo.buscaProfundidade("b");

        System.out.println("------------------------");
        grafo.unvisit();
        grafo.buscaLargura("b");
    }

    public static Grafo carregar_grafo(String arquivo) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader(arquivo));
        
        Grafo grafo = new Grafo();
        
        try {
            String line = null;

            line = br.readLine();            
            Boolean isOrientado = line.contains("sim");
            grafo.setOrientado(isOrientado);

            line = br.readLine();
            int numVertex = 0;

            if(line.contains("{")){

            }else{
                String myString = "asd1234";
                int foo = Integer.parseInt(myString);
                System.out.println(foo);
            }
            System.out.println(line);

            /*
            //percorre todos os vertices
            while (line != null) {
                System.out.println(line);
                line = br.readLine();

            }
            */
        } catch (Exception e){
            System.out.println(e.getMessage());
        } finally {
            br.close(); 
            return grafo; 
        }
    }
}