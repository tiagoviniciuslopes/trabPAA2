import java.io.*;
import java.util.*;

public class Principal{

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
                line = line.replace("V={","");
                line = line.replace("}","");

                String[] parts = line.split(",");
                
                for (String part: parts) {
                    // aqui eu pego os label dos vertices
                    numVertex++;          
                }
            }else{
                line = line.replace("V=","");
                numVertex = Integer.parseInt(line);
            }

            grafo.setNumVertex(numVertex);

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

    private static void menu() throws Exception{ 

        //isso vai sair daqui
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
        


        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String opcao;
            
        while(true){
            System.out.println("         *---------------------------*");
            System.out.println("         |         MENU DE PAA       |");
            System.out.println("         *---------------------------*");
            System.out.println("*--------------------------------------------*");
            System.out.println("| |01| - Carregar Grafo                      |");
            System.out.println("| |02| - Desenhar Grafo                      |");
            System.out.println("*--------------------------------------------*");
            System.out.println("| |03| - Busca em Profundidade               |");
            System.out.println("| |04| - Busca em Largura                    |");
            System.out.println("*--------------------------------------------*");
            System.out.println("| |05| - Bellman-Ford                        |");
            System.out.println("| |06| - Kruskal                             |");
            System.out.println("| |07| - Ford-Fulkerson                      |");
            System.out.println("*--------------------------------------------*");
            System.out.println("| |00| - Sair                                |");
            System.out.println("*--------------------------------------------*");
            System.out.println("ESCOLHA: \n");
            
            opcao = reader.readLine().trim();
            
            System.out.println("");
            
            switch(opcao){
                case "1":

                    Grafo teste = new Grafo();
                    teste = carregar_grafo("inputs/grafo3.txt");
                    System.out.println("É orientado? "+teste.getOrientado());
                    System.out.println("Num Vertices: "+teste.getNumVertex());

                    break;

                case "2":


                    break;

                case "3":

                    System.out.println("|- BUSCA EM PROFUNDIDADE -|\n");
                    grafo.buscaProfundidade("b");
                    
                    System.out.println();
                    reader.readLine();

                    break;

                case "4":
                    
                    System.out.println("|- BUSCA EM LARGURA -|\n");
                    grafo.buscaLargura("b");
                    
                    System.out.println();
                    reader.readLine();
                    
                    break;

                case "5":
                    break;

                case "6":
                    break;

                case "7":
                    break;

                case "0":

                    System.out.println("Até logo...");
                    System.exit(0);

                default:
                    System.out.println("Opção Inválida!\n");
            }

            grafo.unvisit();
        }
    }

    public static void main(String args[]) throws Exception{
        menu();
    }
}