#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void load_vertices(const string& filename, graph &g) {
    vector<string> vertices = {};
    ifstream file(filename);
    if (file.is_open()) {
        string vertex;
        while (file >> vertex) {
            g.add_vertex(vertex);
        }
        file.close();
    } 
    else cerr << "Unable to open file: " << filename << endl;
}

void load_edges(const string& filename, graph &g) {
    vector<string> edges = {};
    ifstream file(filename);
    if (file.is_open()) {
        string from, to;
        int distance;
        while( file >> from >> to >> distance){
            cout << from << " " << to << " " << distance  << endl;
            g.add_edge(from, to, distance);
        }
        file.close();
    } 
    else cerr << "Unable to open file: " << filename << endl;
    
    
}

// int main(){
//     graph g;
    
//     load_vertices("vertices.dat", g);
//     load_edges("edges.dat", g);
//     g.print();

    
// }