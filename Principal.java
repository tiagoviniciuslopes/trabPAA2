import java.io.*;
import java.util.*;

public class Principal{

    //Funcao: carrega um grafo que esta dentro de um arquivo
	//Entrada: o nome do arquivo onde o grafo esta armazenado
	//Saida: o grafo gerado com base no arquivo
	//Pre-condicao: o arquivo deve existir
	//Pos-condicao: o grafo deve ser gerado
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

            ArrayList<String> labels = new ArrayList<String>();

            // teste se tem label ou se é só um int os vertices
            if(line.contains("{")){
                line = line.replace("V={","");
                line = line.replace("}","");

                String[] parts = line.split(",");
                
                for (String part: parts) {

                    No no = new No();
                    no.nome = part;
                    grafo.add(no);
                    labels.add(part);

                    numVertex++;          
                }
            }else{
                line = line.replace("V=","");
                numVertex = Integer.parseInt(line);

                for(int i = 0; i < numVertex ; i++){
                   No no = new No();
                   no.nome = String.valueOf(i);
                   grafo.add(no);
                   labels.add(String.valueOf(i));
                }
            }

            grafo.setNumVertex(numVertex);

            line = br.readLine();
            while (line != null) {
                String[] half = line.split(":");

                String caminho = half[0];
                String descricao = half[1];

                caminho = caminho.replace("(","");
                caminho = caminho.replace(")","");

                String[] fromTo = caminho.split(",");          
                
                int from = Integer.parseInt(fromTo[0]);
                int to = Integer.parseInt(fromTo[1]);
                
                int peso;
                String label = "";

                if(descricao.contains(",")){
                    String[] desc = descricao.split(",");
                    peso = Integer.parseInt(desc[0]);
                    label = desc[1];
                }else{
                    peso = Integer.parseInt(descricao);
                }
                
                // adiciona incidencia
                Incidencia incid = new Incidencia();
                incid.no = grafo.find(labels.get(to));
                incid.peso = peso;
                incid.label = label;
                incid.duplicate = false;

                No no = grafo.find(labels.get(from));
                no.incidencias.add(incid);
                
                // grafo n orientado, deve ter duas incidencias
                if(!isOrientado){
                    Incidencia incid2 = new Incidencia();
                    incid2.no = grafo.find(labels.get(from));
                    incid2.peso = peso;
                    incid2.label = label;
                    incid2.duplicate = true;

                    No no2 = grafo.find(labels.get(to));
                    no2.incidencias.add(incid2);
                }

                line = br.readLine();
            }

        } catch (Exception e){
            System.out.println(e.getMessage());
        } finally {
            br.close();
        }
        return grafo; 
    }

    //Funcao: apresenta um menu inicial ao usuario
	//Entrada: 
	//Saida: 
	//Pre-condicao: 
	//Pos-condicao: o menu eh exibido
    private static void menu() throws Exception{ 

        Grafo grafo = new Grafo();
                    
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
                        arq = "grafo9.txt";//entrar com o teste
                    }

                    grafo = new Grafo();
                    grafo = carregar_grafo("inputs/"+arq);
                    
                    System.out.println("\nGrafo carregado!");
                    reader.readLine();

                    break;

                case "2":
                    grafo.geraDot();
                    System.out.println("Grafo gerado!");
                    reader.readLine();
                    break;

                case "3":

                    System.out.println("Qual vertice?");
                    vertex = reader.readLine().trim();

                    System.out.println("\n|- BUSCA EM PROFUNDIDADE -|\n");
                    grafo.buscaProfundidade(vertex);
                    
                    grafo.unvisit();
                    System.out.println("\n\nPressione qualquer tecla para continuar...");
                    reader.readLine();

                    break;

                case "4":

                    System.out.println("Qual vertice?");
                    vertex = reader.readLine().trim();

                    System.out.println("\n|- BUSCA EM LARGURA -|\n");
                    grafo.buscaLargura(vertex);
                    
                    grafo.unvisit();
                    System.out.println("\n\nPressione qualquer tecla para continuar...");
                    reader.readLine();
                    
                    break;

                case "5":

                    System.out.println("Qual vertice?");
                    vertex = reader.readLine().trim();

                    System.out.println("\n|- BELLMAN FORD -|\n");
                    grafo.bellmanFord(vertex);
                    
                    System.out.println("\n\nPressione qualquer tecla para continuar...");
                    reader.readLine();
                    
                    break;

                case "6":
                    
                    System.out.println("\n|- KRUSKAL MST-|\n");
                    
                    grafo.kruskalMST();

                    System.out.println("\n\nPressione qualquer tecla para continuar...");
                    reader.readLine();
                    break;

                case "7":

                    System.out.println("\n\nPressione qualquer tecla para continuar...");
                    reader.readLine();
                    break;

                case "0":

                    System.out.println("Até logo...");
                    System.exit(0);

                default:
                    System.out.println("Opção Inválida!\n");
            }
        }
    }

    //Funcao: inicia o programa
	//Entrada: 
	//Saida: 
	//Pre-condicao: 
	//Pos-condicao: o programa eh iniciado 
    public static void main(String args[]) throws Exception{
        menu();
    }
}
