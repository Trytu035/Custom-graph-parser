#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <utility>
#include <set>
#include <string.h>
#include <assert.h>
#include <fstream>
#include <algorithm>

using namespace std;
namespace graph
{

    typedef char* vertex_name;

    typedef struct edge{
        char* first;
        char* second;
        mutable int count;	// number of full edges (both direction) + disproported edges
        mutable int direction;	// x < 0 from higher to lower, x > 0 from lower to higher, x == 0 no disproportion between lower and higher

        edge(vertex_name first, vertex_name second, int count = 1, bool auto_direction = true, int new_direction = 0){
            if (strcmp(first, second) < 0){
                this->first = first;
                this->second = second;
                this->direction = auto_direction ? -1 : new_direction;
            }else{
                this->first = second;
                this->second = first;
                if (strcmp(first, second) == 0){
                    this->direction = 0;
                }else {
                    this->direction = auto_direction ? 1 : new_direction;
                }
            }
            this->count = count;
        }
        
        edge(){
            this->first = NULL;
            this->second = NULL;
            this->count = 0;
            this->direction = 0;
        }

        edge& operator=(const edge& other){
            if (this != &other){
                this->first = other.first;
                this->second = other.second;
                this->count = other.count;
                this->direction = other.direction;
            }

            return *this;
        }

        bool operator==(const edge& other){
            if (this->first == other.first && this->second == other.second){
                return true;
            }
            return false;
        }
        
        bool operator<(const edge& other) const {
            if (strcmp(this->first, other.first) == 0 && strcmp(this->second, other.second) == 0){
                return false;	// a equals b, so a not less b
            }else if (strcmp(this->second, other.second) != 0){
                return strcmp(this->second, other.second) < 0;
            }else {
                return strcmp(this->first, other.first) < 0;
            }
        }
    } edge;

    typedef struct edge_index{
        int first;
        int second;
        mutable int count;	// number of full edges (both direction) + disproported edges
        mutable int direction;	// x < 0 from higher to lower, x > 0 from lower to higher, x == 0 no disproportion between lower and higher

        edge_index(int first, int second, edge& edge){
            assert(first <= second);
            this->first = first;	// don't need to check but if it's needed fix
            this->second = second;
            this->direction = edge.direction;
            this->count = edge.count;
        }

        bool operator==(const edge_index& other){
            if (this->first == other.first && this->second == other.second){
                return true;
            }
            return false;
        }
        
        bool operator<(const edge_index& other) const {
            if (this->first == other.first && this->second == other.second){
                return false;	// a equals b, so a not less b
            }else if (this->second != other.second){
                return this->second < other.second;
            }else {
                return this->first < other.first;
            }
        }
    } edge_index;

    class Node{
    public:
        char* name;
        // int index = 0;

        Node(char* name){
            this->name = name;
        }

        // operator const char*() const{
        //     return this->name;
        // }
        
        operator char*() const{
            return this->name;
        }

        // operator const int() const{
        //     return this->index;
        // }

        bool operator<(const Node& other) const{
            return strcmp(this->name, other.name) < 0;
        }

        bool operator<(const char*& other) const{
            return strcmp(this->name, other) < 0;
        }

        bool operator==(const Node& other) const{
            return strcmp(this->name, other.name) == 0;
        }
        bool operator==(const char*& other) const{
            return strcmp(this->name, other) == 0;
        }
    };

    class Edge{
        // pair<Node, Node> vertices; // ensure set.size() is always 2;

        Node& other();
    };

    template<class T>
    class Matrix{
    private:
        size_t rows, cols;
        std::vector<T> data;
    public:
        Matrix(size_t rows, size_t cols){
            this->rows = rows;
            this->cols = cols;
            this->data.resize(rows * cols, 0);
        }

        // void resize(size_t rows, size_t cols){
        //     this->rows = rows;
        //     this->cols = cols;
        //     this->data.resize(rows * cols);
        // }

        T& operator()(size_t row, size_t col){
            assert(row < this->rows);
            assert(col < this->cols);
            return this->data[row * this->rows + col];
        }

        const T& operator()(size_t row, size_t col) const{
            assert(row > 0 && row < this->rows);
            assert(col > 0 && col < this->cols);
            return this->data[row * this->rows + col];
        }

        friend ostream& operator<<(ostream& stream_out, const Matrix& matrix){
            for (int i = 0; i < matrix.rows; i++){
                stream_out << "|\t";
                if (matrix.cols > 0){
                    stream_out << matrix.data[i * matrix.rows];
                    for (int j = 1; j < matrix.cols; j++){
                        stream_out << "\t" << matrix.data[i * matrix.rows + j];
                    }
                }
                stream_out << "\t|" << endl;
            }
        
            return stream_out;
        }

        int row_count(){
            return this->rows;
        }

        int col_count(){
            return this->cols;
        }


        template<typename T_result, typename T_self>
        void for_each(void (*iterate)(T&, int, int, T_result&, T_self*), T_result& result, T_self* self){
        // void for_each(void (*iterate)(T& value, int i, int j, T_self* self), T_self* self){
        // void for_each(void (*iterate)(T& value)){
        // void for_each(lambda [](int value, int &i, int &j)->void iterate){
            for (int i = 0; i < this->rows; i++){
                for (int j = 0; j < this->cols; j++){
                    iterate(this->data[i * this->rows + j], i, j, result, self);
                }
            }
        }
    };
    /* 
    template<typename T>
    ostream& operator<<(ostream& stream_out, const Matrix<T>& matrix){
        for (int i = 0; i < matrix.rows; i++){
            stream_out << "|\t";
            if (matrix.cols > 0){
                stream_out << matrix.data[i * matrix.rows];
                for (int j = 0; j < matrix.cols; j++){
                    stream_out << "\t" << matrix.data[i * matrix.rows + j];
                }
            }
            stream_out << "\t|" << endl;
        }

        return stream_out;
    } */

    // auto vertex_compare_function = [](Node a, Node b){ return (strcmp(a, b) < 0) ? true : false; };

    class Graph{
        public:

        // set<vertex_name, decltype(vertex_compare_function)> vertex_list(vertex_compare_function);	// set of vertex in plain text

        set<Node> vertices;
        // set<char*> vertices;
        Matrix<int> neighborhood_matrix = Matrix<int>(0, 0);
        //// vector<pair<Node>> edges;

        Graph(ifstream& source);
        Graph();
        // ~Graph(){
        //     for_each(this->vertices.begin(), this->vertices.end(), [](Node& vertex){
        //         free(vertex.name);
        //     });
        // }

        void edges(set<edge>& result);
        void incidencies(Matrix<int>& result);
    };
}
#endif