#include <iostream>
#include <vector>
#include <map>
#include <string> 
#include "graph.hpp"
#include "file_reader.cpp"
#define DEBUG 1
using namespace std;

int dijkstra(vertex* from, vertex* to){
    cout << endl << endl << "Making direction from " << from->name << " to " << to->name << "..." << endl;

    vertex* current = from;
    vertex_queue queue;
    queue.add(current);

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
            
            // 1. Update estimates
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
        if(closest_neighbor == NULL){
            if(DEBUG) cout << "No unvisited vertices for " << current->name << endl;
        }
    }
    if(to->shortest_path == INF){ cout << "Error. No path found. " << endl; return -1; }

    list<string> path = {};
    vertex* path_reversed_it = to;
    
    while(path_reversed_it != NULL){
        path.push_front(path_reversed_it->name);
        path_reversed_it = path_reversed_it->previous;
    }

    cout << "Final route: " << endl;
    for(auto &it: path){
        cout << " -> " << it;
    }
    cout << " (" << to->shortest_path << " km)" << endl;
    return to->shortest_path;
}

int main(){
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


    // g.print();

    return 0;
}