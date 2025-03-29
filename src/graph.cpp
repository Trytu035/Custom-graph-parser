// #include "graph.h"
#include "../include/graph.h"
// #include "../include/display_matrix.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

//TODO: make line below consistent for entire filesystem
#define MAX_LINE_LENGTH 100

using namespace std;

graph::Graph::Graph(ifstream& source){
    vector<char*> file;
    set<edge> neighbor_list;	// set of pair of vertex (from vertex_list) and pointer to name of other vertex
	set<edge> edge_list;	// set of pair of vertex (from vertex_list) and other vertex (from vertex_list) equivalent to the name from neighbors set
	set<edge_index> edge_indeces_list;	// -,,-

	
	if (source.is_open()){  //caller should do that, not me
		char line[MAX_LINE_LENGTH];
	
		while (source.getline(line, MAX_LINE_LENGTH)){
			file.push_back(strdup(line));
		}
	}else{
		cout << "Niepoprawna nazwa pliku" << endl;
        return;
	}

    for (vector<char*>::iterator i=file.begin(); i!=file.end(); i++){
		char *context = NULL;
		char* ptr = NULL;
		char* vertex_ptr = NULL;

		ptr = strtok_r(*i, ":", &context);	// pierwszy token
		if (ptr == NULL){ continue; }
		vertex_ptr = ptr;
		// this->vertices.insert(Node(vertex_ptr));
		this->vertices.insert(strdup(vertex_ptr));
		ptr = strtok_r(NULL, ",", &context);

		while (ptr != NULL){	// TODO: ensure, vertex exist at the end
			edge new_edge(vertex_ptr, ptr + strspn(ptr, " \n\t"));

			pair<set<edge>::iterator, bool> edge_found = neighbor_list.insert(new_edge);
            // cout << "inserted: " << *(edge_found.first->first) << "-" << *(edge_found.first->second) << endl;
			
			if (edge_found.second == false){	//TODO: check if new_edge has count higher than 1 or it's own full_edges
				int full_edges = edge_found.first->count - abs(edge_found.first->direction);
				int new_full_edges = 0;

				if ((edge_found.first->direction < 0) != (new_edge.direction < 0)){	// value of subtracted direction
					new_full_edges = min(abs(edge_found.first->direction), abs(new_edge.direction));
				}else if (edge_found.first->direction == 0 && new_edge.direction == 0){	// it's full edge (probably edge to self)
					new_full_edges += 1;
				}
				edge_found.first->direction += new_edge.direction;
				edge_found.first->count = full_edges + new_full_edges + abs(edge_found.first->direction);
			}
			ptr = strtok_r(NULL, ",", &context);
		}
	}

    for_each(neighbor_list.begin(), neighbor_list.end(), [&](edge edge_val){
        set<Node>::iterator result1 = this->vertices.find(graph::Node(edge_val.first));
		
		if (result1 != this->vertices.end()){
			int index1 = distance(this->vertices.begin(), result1);
			set<Node>::iterator result2 = this->vertices.find(graph::Node(edge_val.second));
			
			if (result2 != this->vertices.end()){
				int index2 = distance(this->vertices.begin(), result2);

				if (edge_val.direction != 0){
                    throw runtime_error(string("Krawedz ") + to_string(index1) + string("-") + to_string(index2) + string(" jest niedomknieta w pliku zrodlowym."));
				}
				edge_indeces_list.insert(edge_index(index1, index2, edge_val));
				edge_list.insert(edge(*result1, *result2, edge_val.count, edge_val.direction));
                // cout << index1 << "-" << index2 << endl;
			}else {
				cout << index1 << "-X ta krawedz nie istnieje" << endl;
			}
		}else {
			cout << "X-X ta krawedz nie istnieje" << endl;
		}
	});

    this->neighborhood_matrix = Matrix<int>(this->vertices.size(), this->vertices.size());
	// incidency_matrix.resize(this->vertices.size());
	// for (int i = 0; i < this->vertices.size(); i++){
		// neighborhood_matrix[i] = new vector<int>(this->vertices.size(), 0);
		// incidency_matrix[i] = vector<int>(edge_count(edge_list), 0);
	// }
    
	for_each(edge_indeces_list.begin(), edge_indeces_list.end(), [&](edge_index edge){
		this->neighborhood_matrix(edge.first, edge.second) += edge.count;
		if (edge.first != edge.second){
			this->neighborhood_matrix(edge.second, edge.first) += edge.count;	// comment for directional edges
		}
	});
}

graph::Graph::Graph(){
    this->vertices = std::set<Node>();
    this->neighborhood_matrix = Matrix<int>(0, 0);
}

void graph::Graph::edges(set<edge>& resulting_set){
    this->neighborhood_matrix.for_each<set<edge>, Graph>([](int& value, int& i, int& j, set<edge>& result, Graph* self){
        if (value > 0){
            result.insert(edge(
                *next(self->vertices.begin(), i),
                *next(self->vertices.begin(), j),
                value
            ));
        }
    }, resulting_set, this);
}

void graph::Graph::incidencies(Matrix<int>& result_matrix){
    int a;
    result_matrix.for_each<int, int>([](int& val, int& i, int& j, int& result, int* self){
        val = 0;
    }, a, &a);

    set<graph::edge> g_edges;
    this->edges(g_edges);
    int i = 0;
    for_each(g_edges.begin(), g_edges.end(), [&](graph::edge edge_val){
        int index1 = distance(this->vertices.begin(), this->vertices.find(edge_val.first));
        int index2 = distance(this->vertices.begin(), this->vertices.find(edge_val.second));
        for (int j = 0; j < edge_val.count; j++){
            result_matrix(index1,i) = 1;
            result_matrix(index2,i) = 1;
            cout << i << "-" << index1 << endl;
            i++;
        }
    });
    
    cout << endl;
}

int graph::Graph::rank(){
    return this->vertices.size();
}

int graph::Graph::size(){
    set<graph::edge> edges;
    int count = 0;

    this->edges(edges);
	for_each(edges.begin(), edges.end(), [&](graph::edge edge){
		count += edge.count;
	});

    return count;
}

// -1 if node doesn't exist. Degree otherwise
int graph::Graph::degree(const Node& vertex){
    set<Node>::iterator result = this->vertices.find(vertex);
    int degree = 0;

    if (result != this->vertices.end()){
        int index = distance(this->vertices.begin(), result);

        for (int i=0; i < this->rank(); i++){
            if (i == index){
                degree += 2 * this->neighborhood_matrix(index, i);
            }else{
                degree += this->neighborhood_matrix(index, i);
            }
        }
        return degree;
    }
    return -1;
}

bool graph::Graph::is_simple(){
    bool result = true;

    this->neighborhood_matrix.for_each<bool, bool>([](int& val, int& i, int& j, bool& result, bool* self){
        if (val > 1){
            result = false;
        }
    }, result, &result);
    return result;
}

bool graph::Graph::is_full(){
    bool result = true;

    this->neighborhood_matrix.for_each<bool, bool>([](int& val, int& i, int& j, bool& result, bool* self){
        if (val < 1){
            result = false;
        }
    }, result, &result);
    return result;
}

void graph::Graph::compliment_edges(set<edge>& result){
    this->neighborhood_matrix.for_each<set<edge>, Graph>([](int& val, int& i, int& j, set<edge>& result, Graph* self){
        if (val < 1){
            result.insert(edge(
                *next(self->vertices.begin(), i),
                *next(self->vertices.begin(), j),
                1,
                false,
                0
            ));
        }
    }, result, this);
}