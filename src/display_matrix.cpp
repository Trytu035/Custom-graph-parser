/* #include "graph.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include "display_matrix.h"

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

template<typename _T1, typename _T2=less<_T1>>
ostream& operator<<(ostream& stream_out, const pair<_T1, _T2>& pair_of_smth){
	stream_out << pair_of_smth.first << "-" << pair_of_smth.second;

	return stream_out;
}

ostream& operator<<(ostream& stream_out, const edge& edge){
	if (edge.count > 0){
		stream_out << edge.first << "-" << edge.second;
		for (int i = 1; i < edge.count; i++){
			stream_out << ", " << edge.first << "-" << edge.second;
		}
	}

	return stream_out;
}

ostream& operator<<(ostream& stream_out, const edge_index& edge){
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
} */