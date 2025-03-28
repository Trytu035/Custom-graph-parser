#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <array>
#include <string.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <cctype>
#include "../include/graph.h"
#include "../include/display_matrix.h"
// #include <graph.h>
// #include <display_matrix.h>

#define MAX_LINE_LENGTH 100

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;


// namespace Display_matrix
// {

	template<typename _T1, typename _T2>
	ostream& operator<<(ostream&, const pair<_T1, _T2>&);
	template<typename _T1, typename _T2=less<_T1>>
	ostream& operator<<(ostream&, const set<_T1, _T2>&);
	ostream& operator<<(ostream&, const graph::edge&);
	template<typename _T1>
	ostream& operator<<(ostream&, const vector<_T1>&);
	// ostream& operator<<(ostream&, const vector<vector<int>>&);


	template<typename _T1, typename _T2=less<_T1>>
	ostream& operator<<(ostream& stream_out, const set<_T1, _T2>& set_of_smth){
		if (set_of_smth.size() > 0){
			stream_out << *(set_of_smth.begin());
			for_each(next(set_of_smth.begin()), set_of_smth.end(), [&](_T1 val){
				stream_out << ", " << val;
			});
		}
		
		return stream_out;
	}

	template<typename _T1, typename _T2>
	ostream& operator<<(ostream& stream_out, const pair<_T1, _T2>& pair_of_smth){
		stream_out << pair_of_smth.first << "-" << pair_of_smth.second;

		return stream_out;
	}

	ostream& operator<<(ostream& stream_out, const graph::edge& edge){
		if (edge.count > 0){
			stream_out << edge.first << "-" << edge.second;
			for (int i = 1; i < edge.count; i++){
				stream_out << ", " << edge.first << "-" << edge.second;
			}
		}

		return stream_out;
	}

	ostream& operator<<(ostream& stream_out, const graph::edge_index& edge){
		if (edge.count > 0){
			stream_out << edge.first << "-" << edge.second;
			for (int i = 1; i < edge.count; i++){
				stream_out << ", " << edge.first << "-" << edge.second;
			}
		}

		return stream_out;
	}

	template<typename _T1>
	ostream& operator<<(ostream& stream_out, const vector<_T1>& vector){
		if (vector.size() > 0){
			stream_out << *(vector.begin());
			for_each(next(vector.begin()), vector.end(), [&](_T1 val){
				stream_out << ", " << val;
			});
		}

		return stream_out;
	}

	ostream& operator<<(ostream& stream_out, const vector<vector<int>>& matrix){
		for_each(matrix.begin(), matrix.end(), [&](vector<int> row){
			stream_out << "|\t";
			if (row.size() > 0){
				stream_out << row[0];
				for_each(next(row.begin()), row.end(), [&](int val){
					stream_out << "\t" << val;
				});
			}
			stream_out << "\t|";
			stream_out << endl;
		});

		return stream_out;
	}
// }


void zadanie1(char*);

// template<typename _T1>
int edge_count(set<graph::edge> edges){
	int count = 0;
	for_each(edges.begin(), edges.end(), [&](graph::edge edge){
		count += edge.count;
	});
	return count;
}

int main(int argc, char** argv) {
// int main() {
//	 cout << "hello world" << endl;
	// cout << argv[0] << endl;
	if (argc == 2){
		zadanie1(argv[1]);
	} else {
		cout << "niepoprawna liczba argumentow: " << argc << endl;
	}
	return 0;
}

void zadanie1(char *filename){
	ifstream plik(filename);
	if (plik.is_open()){
		graph::Graph g(plik);
		set<graph::edge> edges;
		g.edges(edges);
		graph::Matrix<int> incidency_matrix(g.vertices.size(), edge_count(edges));
		g.incidencies(incidency_matrix);

		cout << "Liczba wierzcholkow grafu G wynosi " << g.vertices.size() << endl;
		cout << "Zbior wierzcholkow V = {" << g.vertices << "} " << endl;
		cout << "Liczba krawedzi grafu G wynosi " << edge_count(edges) << endl;
		cout << "Zbior krawedzi K = {" << edges << "}" << endl;
		cout << "Maciez sasiedztwa:" << endl << g.neighborhood_matrix << endl;
		cout << "Maciez incydencji:" << endl << incidency_matrix << endl;

		plik.close();
	}
/* 
	// set<vertex_name, (vertex_name a, vertex_name b){ return strcmp(a, b)}> vertex_list;	// set of vertex in plain text
	auto vertex_compare_function = [](vertex_name a, vertex_name b){ return (strcmp(a, b) < 0) ? true : false; };

	set<vertex_name, decltype(vertex_compare_function)> vertex_list(vertex_compare_function);	// set of vertex in plain text
	// set<edge, decltype(edge_compare_function)> neighbor_list(edge_compare_function);	// set of pair of vertex (from vertex_list) and pointer to name of other vertex
	// set<edge, decltype(edge_compare_function)> edge_list(edge_compare_function);	// set of pair of vertex (from vertex_list) and other vertex (from vertex_list) equivalent to the name from neighbors set
	set<edge> neighbor_list;	// set of pair of vertex (from vertex_list) and pointer to name of other vertex
	set<edge> edge_list;	// set of pair of vertex (from vertex_list) and other vertex (from vertex_list) equivalent to the name from neighbors set
	set<edge_index> edge_indeces_list;	// -,,-
	vector<vector<int>> neighborhood_matrix;
	vector<vector<int>> incidency_matrix;
	
	vector<char*> file;
	
	if (plik.is_open()){
		char line[MAX_LINE_LENGTH];
	
		while (plik.getline(line, MAX_LINE_LENGTH)){
			file.push_back(strdup(line));
		}
	}else{
		cout << "Nie otwarto" << endl;
	}
	
	for (vector<char*>::iterator i=file.begin(); i!=file.end(); i++){
		char *context = NULL;
		char* ptr = NULL;
		char* vertex_ptr = NULL;

		ptr = strtok_r(*i, ":", &context);	// pierwszy token
		if (ptr == NULL){ continue; }
		vertex_ptr = ptr;
		vertex_list.insert(vertex_ptr);
		ptr = strtok_r(NULL, ",", &context);

		while (ptr != NULL){	// TODO: ensure, vertex exist at the end
			edge new_edge(vertex_ptr, ptr + strspn(ptr, " \n\t"));

			pair<set<edge>::iterator, bool> edge_found = neighbor_list.insert(new_edge);
			
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
		set<vertex_name>::iterator result1 = vertex_list.find(edge_val.first);
		
		if (result1 != vertex_list.end()){
			int index1 = distance(vertex_list.begin(), result1);
			set<vertex_name>::iterator result2 = vertex_list.find(edge_val.second);
			
			if (result2 != vertex_list.end()){
				int index2 = distance(vertex_list.begin(), result2);

				if (edge_val.direction != 0){
                    cout << "Krawedz " << index1 << "-" << index2 << " jest niedomknieta w pliku zrodlowym.";
				}
				edge_indeces_list.insert(edge_index(index1, index2, edge_val));
				edge_list.insert(edge(*result1, *result2, edge_val.count, edge_val.direction));
			}else {
				cout << index1 << "-X ta krawedz nie istnieje" << endl;
			}
		}else {
			cout << "X-X ta krawedz nie istnieje" << endl;
		}
	}); */
/* 
	cout << "Liczba wierzcholkow grafu G wynosi " << vertex_list.size() << endl;
	cout << "Zbior wierzcholkow V = {" << vertex_list << "} " << endl;
	cout << "Liczba krawedzi grafu G wynosi " << edge_count(edge_list) << endl;
	cout << "Zbior krawedzi K = {" << edge_list << "}" << endl;

	cout << edge_list << endl;
	cout << edge_indeces_list << endl;
	
	neighborhood_matrix.resize(vertex_list.size());
	incidency_matrix.resize(vertex_list.size());
	for (int i = 0; i < vertex_list.size(); i++){
		neighborhood_matrix[i] = vector<int>(vertex_list.size(), 0);
		incidency_matrix[i] = vector<int>(edge_count(edge_list), 0);
	}

	for_each(edge_indeces_list.begin(), edge_indeces_list.end(), [&](edge_index edge){
		neighborhood_matrix[edge.first][edge.second] = edge.count;
		if (edge.first != edge.second){
			neighborhood_matrix[edge.second][edge.first] += edge.count;	// comment for directional edges
		}
	});

	for_each(edge_list.begin(), edge_list.end(), [&](edge edge_val){
		int incidency_i = -1;
		int incidency_j = distance(edge_list.begin(), edge_list.find(edge_val));
		int sum_of_edges = 0;
		for_each(edge_list.begin(), edge_list.find(edge_val), [&sum_of_edges](edge edge_val){
			sum_of_edges += edge_val.count - 1;
		});
		incidency_j += sum_of_edges;
		
		for (int i=0; i < edge_val.count; i++){	//	TODO: check for directions
			incidency_i = distance(vertex_list.begin(), vertex_list.find(edge_val.first));
			incidency_matrix[incidency_i][incidency_j + i] = 1;
			incidency_i = distance(vertex_list.begin(), vertex_list.find(edge_val.second));
			incidency_matrix[incidency_i][incidency_j + i] = 1;
		}
	});

	cout << neighborhood_matrix << endl << endl;

	cout << incidency_matrix << endl; */
	
	plik.close();
}