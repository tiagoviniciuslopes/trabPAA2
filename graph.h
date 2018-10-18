#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <string>
#include <list>
#include <map>

using namespace std;

typedef struct {
	int my_id;
	int id_orig;
	int id_dest;
	int weight;
	string name_path;
} path;

typedef struct {
	int my_id;
	string name;
	list <path> neighbors;
} node;


class graph{

	private:
		map <int,node> graph_map;

		list <path> edge_list;

		bool is_orientado = false;

		list <string>tokenizeStr(string txt, string delimiter);


	public:
		graph();
		
		void insertNode(int pos, string name);
		void insertNeighbor(int node, string name, int weight, int id_neighbor);

		bool readInput(string fileName);
		
		map <int,node> * getMap();

		path *getNeighbor(int id);

		list <path> * getNeighbors(int id);

		list <path> * getAllNeighbors();

		void setIsOrientado(bool option);
		bool getIsOrientado();

		void clear();

		void printNodes();

		~graph();
	
};

#endif //GRAPH_H