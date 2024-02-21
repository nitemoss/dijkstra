#include <iostream>
#include <vector>
#include <map>
#include <string> 
#include <algorithm>
#include "graph.hpp"
#include "file_reader.cpp"
#define DEBUG 1
using namespace std;

int dijkstra(vertex* from, vertex* to){
    if(from == NULL || to == NULL) {cerr << "Error. Vertices not found." << endl; return -1;}
    cout << endl << endl << "Making direction from " << from->name << " to " << to->name << "..." << endl;

    vertex* current = NULL;
    vertex_queue queue;
    queue.add(from);

    while(!queue.empty()){
        current = queue.get_closest();     
        current->visited = true;   
        queue.erase_closest();

        // Vertex with a minimum distance of edge from a current vertex, which will be used as a current vertex in next iteration
        vertex* closest_neighbor = NULL;

        if(current == to || current == NULL) break;
        if(current == from) current->shortest_path = 0;

        int edges_amount = current->edges.size();

        if(edges_amount == 0) continue;
        if(DEBUG) cout << endl << "Analyzing " << edges_amount << " edges of " << current->name << endl;

        closest_neighbor = NULL;
        for (auto edges_iterator: current->edges){
            int edge_distance = edges_iterator.first;
            vertex* edge_destination = edges_iterator.second;
            
            if(DEBUG) cout << "\t"  << current->name  << " -> " << edge_destination->name  << " : "  << edge_distance  << " "  << (edge_destination->visited ? " (visited)" : "")  << endl;
            
            // 1. Update neighbors' estimates
            if((current->shortest_path + edge_distance < edge_destination->shortest_path)){
                edge_destination->shortest_path = current->shortest_path + edge_distance;
                edge_destination->previous = current;
                if(DEBUG) cout << "\t\tUpdating shortest path of " << edge_destination->name << " to " << edge_destination->shortest_path << "; " << endl;
            } 
            // 2. Choose next 'current'
            if(!(edge_destination->visited) and (closest_neighbor == NULL or edge_destination->shortest_path < closest_neighbor->shortest_path)){
                if(DEBUG) cout << "New closest neighbor: " << edge_destination->name << " " << edge_destination->shortest_path << endl;
                edge_destination->visited = true;
                closest_neighbor = edge_destination;
                queue.add(closest_neighbor);
                if(DEBUG) queue.print();
            }
        }
        if(closest_neighbor == NULL) if(DEBUG) cout << "No unvisited vertices for " << current->name << endl;
    }
    if(to->shortest_path == INF){ cerr << "Error. No path found. " << endl; return -1; }

    list<string> path = {};
    vertex* path_reversed_it = to;
    
    while(path_reversed_it != NULL){
        path.push_front(path_reversed_it->name);
        path_reversed_it = path_reversed_it->previous;
    }

    cout << "Final route: " << endl;
    for(auto &it: path) cout << " -> " << it;
    cout << " (" << to->shortest_path << " km)" << endl;
    return to->shortest_path;
}

bool reverse_path_test(graph &g, string _from, string _to){
    vertex* from = g.vertices[_from];
    vertex* to = g.vertices[_to];
    int d1 = dijkstra(from, to);
    g.reset();
    int d2 = dijkstra(to, from);        
    g.reset();
    if(d1 == d2 and d1 != -1 and d2 != -1){
        cout << endl << "TEST OK" << endl;
        return true;
    }
    else {
        cout << "TEST FAILED" << endl;
        return false;
    }
    
}
int main(int argc, char* argv[]){
    if(argc == 1){
        {
            graph g;
            string template_name = "europe";
            load_vertices("graph_templates/" + template_name + "/vertices.dat", g);
            load_edges("graph_templates/" + template_name + "/edges.dat", g, true);

            vertex* from = g.vertices["Berlin"];
            vertex* to = g.vertices["Lisbon"];
            
            // Dijkstra algorithm can be performed only once on the same graph.
            dijkstra(from, to);
            g.reset();
            dijkstra(to, from);
        }

        {
            graph g;
            string template_name = "europe";
            load_vertices("graph_templates/" + template_name + "/vertices.dat", g);
            load_edges("graph_templates/" + template_name + "/edges.dat", g, true);

            // Simple test of whether the distance of the route is the same if path is reversed.
            int fail_tests = 0;
            int ok_tests = 0;

            reverse_path_test(g, "Lisbon", "Tirana") ? ok_tests++ : fail_tests++;
            reverse_path_test(g, "Lisbon", "Rome") ? ok_tests++ : fail_tests++;
            reverse_path_test(g, "Lisbon", "Moscow") ? ok_tests++ : fail_tests++;
            reverse_path_test(g, "Lisbon", "Kyiv") ? ok_tests++ : fail_tests++;
            reverse_path_test(g, "Lisbon", "Riga") ? ok_tests++ : fail_tests++;

            cout << "Successful tests " << ok_tests << "/" << fail_tests + ok_tests << endl;
        }
    } else if(argc == 4){
        string template_name = argv[1];
        string _from = argv[2];
        string _to = argv[3];

        graph g;
        load_graph_template(template_name, g, true);
        
        vertex* from = g.vertices[_from];
        vertex* to = g.vertices[_to];
        
        dijkstra(from, to);
    } else {
        cout << "Wrong argument amount received. " << endl;
    }
    return 0;
}