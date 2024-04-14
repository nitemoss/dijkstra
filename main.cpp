#include <iostream>
#include "dijkstra.cpp"

using namespace std;


int main(int argc, char* argv[]){
    if(argc == 1){
        graph g;
        string template_name = "europe";
        load_vertices("graph_templates/" + template_name + "/vertices.dat", g);
        load_edges("graph_templates/" + template_name + "/edges.dat", g, true);
        vertex* from = g.vertices["Berlin"];
        vertex* to = g.vertices["Lisbon"];
        dijkstra(from, to);
    } else if(argc == 4){
        string template_name = argv[1];
        string _from = argv[2];
        string _to = argv[3];

        graph g;
        load_graph_template(template_name, g, true);
        
        vertex* from = g.vertices[_from];
        vertex* to = g.vertices[_to];
        
        dijkstra(from, to);
    } else cout << "Wrong argument amount received. " << endl;

    return 0;
}