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
            Integer numVertex = 0;

            if(line.contains("{")){
                line = line.replace("V={","");
                line = line.replace("}","");

                String[] parts = line.split(",");
                
                for (String part: parts) {
                    // aqui eu pego os label dos vertices
                    // pegaralbel
                    numVertex++;          
                }
            }else{
                line = line.replace("V=","");
                numVertex = Integer.parseInt(line);
            }

            grafo.setNumVertex(numVertex);

            line = br.readLine();
            while (line != null) {
                String[] half = line.split(":");

                String caminho = half[0];
                String peso = half[1];

                caminho = caminho.replace("(","");
                caminho = caminho.replace(")","");

                String[] fromTo = caminho.split(",");

                Integer from = Integer.parseInt(fromTo[0]);
                Integer to = Integer.parseInt(fromTo[1]);
                System.out.println("from:"+from);
                System.out.println("to:"+to);
                

                line = br.readLine();
            }

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
        

        Grafo teste = new Grafo();
                    
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String opcao,vertex;
            
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

                    System.out.println("Entre com o nome do arquivo: ");
                    String arq = reader.readLine().trim();
                        
                    // so pra n ter q escrever o nome toda hr                
                    if(arq.isEmpty()){
                        arq = "grafo1.txt";//entrar com o teste
                    }

                    teste = carregar_grafo("inputs/"+arq);

                    System.out.println("É orientado? "+teste.getOrientado());
                    System.out.println("Num Vertices: "+teste.getNumVertex());

                    System.out.println("\nGrafo carregado!");
                    reader.readLine();

                    break;

                case "2":

                    // https://www.youtube.com/watch?v=_0zQh_jtIsE&list=PLSVAhOzzve5Irl93Oa35RIYtcMD6ilNSz&index=1
                    break;

                case "3":

                    System.out.println("Qual vertice?");
                    vertex = reader.readLine().trim();

                    System.out.println("\n|- BUSCA EM PROFUNDIDADE -|\n");
                    grafo.buscaProfundidade(vertex);
                    
                    System.out.println("\n\nPressione qualquer tecla para continuar...");
                    reader.readLine();

                    break;

                case "4":

                    System.out.println("Qual vertice?");
                    vertex = reader.readLine().trim();

                    System.out.println("\n|- BUSCA EM LARGURA -|\n");
                    grafo.buscaLargura(vertex);
                    
                    System.out.println("\n\nPressione qualquer tecla para continuar...");
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