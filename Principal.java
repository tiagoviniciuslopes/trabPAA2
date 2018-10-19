public class Principal{

    public static void main(String args[]) throws Exception{
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

}