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
void zadanie2(char*);
void zadanie3(char*);
void zadanie4(char*);
void zadanie5(char*);
void (*zadania[])(char*) = {zadanie1, zadanie2, zadanie3, zadanie4, zadanie5};

int main(int argc, char** argv) {
	if (argc == 3){
		int task_index = atoi(argv[1]);
		cout << task_index << endl;
		if (task_index > 0 && task_index <= sizeof(zadania)/sizeof(*zadania)){
			zadania[task_index - 1](argv[2]);
		}else{
			cout << "Niepoprawny pierwszy argument." << endl;
			cout << "Skladnia: \n my_project.exe [1-4] nazwa_pliku \n na przyklad ./my_project.exe 1 ../graf.txt" << endl;
		}
	} else {
		cout << "niepoprawna liczba argumentow: " << argc << endl;
		cout << "Skladnia: \n my_project.exe [1-4] nazwa_pliku \n na przyklad ./my_project.exe 1 ../graf.txt" << endl;
	}
	return 0;
}

void zadanie1(char *filename){
	ifstream plik(filename);
	if (plik.is_open()){
		graph::Graph g(plik);
		set<graph::edge> edges;
		g.edges(edges);
		graph::Matrix<int> incidency_matrix(g.vertices.size(), g.size());
		g.incidencies(incidency_matrix);

		cout << "Liczba wierzcholkow grafu G wynosi " << g.vertices.size() << endl;
		cout << "Zbior wierzcholkow V = {" << g.vertices << "} " << endl;
		cout << "Liczba krawedzi grafu G wynosi " << g.size() << endl;
		cout << "Zbior krawedzi K = {" << edges << "}" << endl;
		cout << "Maciez sasiedztwa:" << endl << g.neighborhood_matrix << endl;
		cout << "Maciez incydencji:" << endl << incidency_matrix << endl;

		// for_each(g.vertices.begin(), g.vertices.end(), [](graph::Node vertex){

		// });

		plik.close();
	}
	plik.close();
}

void zadanie2(char* filename){
	ifstream plik(filename);
	if (plik.is_open()){
		graph::Graph g(plik);
		cout << "Rzad grafu G wynosi " << g.rank() << endl;
		cout << "Rozmiar grafu G wynosi " << g.size() << endl;
		cout << "Stopnie wierzcholkow:" << endl;
		for_each(g.vertices.begin(), g.vertices.end(), [&](graph::Node vertex){
			cout << "deg(" << vertex.name << ") = " << g.degree(vertex) << endl;
		});
		plik.close();
	}
}


void zadanie3(char* filename){
	ifstream plik(filename);
	if (plik.is_open()){
		graph::Graph g(plik);
		cout << "Graf G jest grafem " << (g.is_simple() ? "prostym" : "ogolnym") << endl;
		plik.close();
	}
}

void zadanie4(char* filename){
	ifstream plik(filename);
	if (plik.is_open()){
		graph::Graph g(plik);
		bool is_g_full = g.is_full();

		if (is_g_full){
			cout << "Graf G jest grafem pelnym" << endl;
		}else{
			std::set<graph::edge> compliment;

			g.compliment_edges(compliment);
			cout << "Graf G nie jest grafem pelnym" << endl;
			cout << "Krawedzie dopelnienia grafu G: " << compliment << endl;
		}
		plik.close();
	}
}

void zadanie5(char* filename){
	ifstream plik(filename);
	if (plik.is_open()){
		graph::Graph g(plik);
		set<graph::edge> edges;

		g.edges(edges);
		for_each(g.vertices.begin(), g.vertices.end(), [&](graph::Node vertex){
			set<graph::Node> neighbors;
			for_each(edges.begin(), edges.end(), [&](graph::edge edge){
				if (edge.first == vertex){
					neighbors.insert(graph::Node(edge.second));
				}else if (edge.second == vertex){
					neighbors.insert(graph::Node(edge.first));
				}
			});
			cout << vertex << " -> " << neighbors << endl;
		});

		plik.close();
	}
}