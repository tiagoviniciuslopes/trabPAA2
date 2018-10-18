#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include "graph.h"

graph::graph(){
};

graph::~graph(){
	for (map<int,node>::iterator it = this->graph_map.begin(); it != this->graph_map.end(); ++it){
		it->second.neighbors.clear();
	}
	this->edge_list.clear();
};

void graph::insertNode(int pos, string name){
	this->graph_map[pos].my_id = pos;
	this->graph_map[pos].name = name;
}

path *graph::getNeighbor(int id){

	for(list<path>::iterator it = this->edge_list.begin(); it != this->edge_list.end(); ++it){
		if(it->my_id == id) return &(*it);
	}

	return NULL;
}

void graph::insertNeighbor(int id_node, string name, int weight, int id_neighbor){
	path nPath;

	nPath.my_id = edge_list.size();
	nPath.id_orig = id_node;
	nPath.id_dest = id_neighbor;
	nPath.weight = weight;
	nPath.name_path = name;

	this->graph_map[id_node].neighbors.push_back(nPath);

	this->edge_list.push_back(nPath);

	if(! this->is_orientado){
		nPath.id_orig = id_neighbor;
		nPath.id_dest = id_node;
		this->graph_map[id_neighbor].neighbors.push_back(nPath);
	}
}

void graph::printNodes(){
	for (map<int,node>::iterator it_map = this->graph_map.begin(); it_map != this->graph_map.end(); ++it_map){
		cout << "Id: " << it_map->first << endl;
		cout << "Name: " << it_map->second.name << endl;
		cout << "Neighbors: " << endl;

		for (list<path>::iterator it_list = it_map->second.neighbors.begin(); it_list != it_map->second.neighbors.end(); ++it_list){
			cout << "\t" << it_list->my_id << " | " << it_list->id_dest << " | " << it_list->weight << " | " << it_list->name_path << endl;
		}

		cout << endl << endl;

	}
}


list <string> graph::tokenizeStr(string txt, string delimiter){
	int n = 0, pos;
	string token;
	list <string> myList;

	while ((pos = txt.find(delimiter)) != string::npos) {
		token = txt.substr(0, pos);
		myList.push_back(token);
		txt.erase(0, pos + delimiter.length());
	}
	myList.push_back(txt);

	return myList;
}

bool graph::readInput(string fileName){

	try{
		this->clear();

		ifstream fin;

		fin.open(fileName,std::ifstream::in);

		if( fin.is_open() ) {
			string read_str;

			while( ! fin.eof() ) {
				getline(fin,read_str);

				if( read_str.find("=") != string::npos ) {

					string tag = read_str.substr(0,read_str.find("="));
					if( tag == "orientado" ) {
						//Set is_orientado
						is_orientado = read_str.substr(10,read_str.length()) == "sim"; 
					}
					else if ( tag == "V") {
						string result = read_str.substr(2,read_str.length());

						if(result.at(0) == '{'){

							//Remove os {} para fazer um split por ','
							result = result.substr(1, result.length() - 2);

							list <string> resultList = tokenizeStr(result,",");

							//Set names
							int counter = 0;
							for (list<string>::iterator it = resultList.begin(); it != resultList.end(); ++it){
								this->insertNode(counter++,(*it));
							}

						}
						else{

							//Insert Node
							for (int i = 0; i < stoi(result); ++i){
								this->insertNode(i,"");
							}

						}

					}

				}
				else{
					//Faz a separação de tokens para 
					if( read_str.at(0) == '(' ){

						list <string> tokenList = tokenizeStr(read_str,":");

						int a1,a2;
						int weight;
						string name = "";

						string auxNodes = tokenList.front().substr(1,tokenList.front().length() - 2);
						string auxInfo = tokenList.back();

						tokenList.clear();
						tokenList = tokenizeStr(auxNodes,",");
						a1 = stoi(tokenList.front());
						a2 = stoi(tokenList.back());

						tokenList.clear();
						tokenList = tokenizeStr(auxInfo,",");
						weight = stoi(tokenList.front());

						name = tokenList.size() == 2? tokenList.back(): "";

						this->insertNeighbor(a1,name,weight,a2);

						tokenList.clear();
					}
				}
			}

			fin.close();
			return true;
		}
		return false;
	}
	catch(exception& e){
		return false;
	}
}

map <int,node> * graph::getMap(){
	return &this->graph_map;
}

list <path> * graph::getNeighbors(int id){
	return &this->graph_map[id].neighbors;
}

list <path> * graph::getAllNeighbors(){
	return &this->edge_list;
}

void graph::setIsOrientado(bool option){
	this->is_orientado = option;
}

void graph::clear(){
	this->graph_map.clear();
	this->edge_list.clear();
}

bool graph::getIsOrientado(){
	return is_orientado;
}
