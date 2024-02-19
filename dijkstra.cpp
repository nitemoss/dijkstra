#include <iostream>
#include <vector>
#include <map>
#include <string> 
#include "graph.hpp"
#include "file_reader.cpp"

using namespace std;

void dijkstra(vertex* from, vertex* to){
    cout << "Making direction from " << from->name << " to " << to->name << "..." << endl;
    
    vertex* current = from;
    vertex_queue queue;
    queue.add(current);

    while(!queue.empty()){
        current = queue.get_closest();     
        current->visited = true;   
        queue.erase_closest();

        // Vertex with a minimum distance of edge from a current vertex, which will be used as a current vertex in next iteration
        vertex* closest_neighbor = NULL;

        if(current == to) break;
        if(current == from){
            cout << "Start vertex found, distance = 0." << endl;
            current->shortest_path = 0;
        }
        if(current == NULL) {
            cout << "Error, got NULL current vertex" << endl;
            break;
        }

        int edges_amount = current->edges.size();

        if(edges_amount == 0) {
            cout << "No edges for " << current->name << endl;
            continue;
        }
        cout << endl << "Analyzing " << edges_amount << " edges of " << current->name << endl;
        // Analyze neigbours of 'current'
        closest_neighbor = NULL;
        int edge_distance = INF;
        for (auto edges_iterator: current->edges){
            edge_distance = edges_iterator.first;
            vertex* edge_destination = edges_iterator.second;
            
            cout << "\t"  << current->name  << " -> " << edge_destination->name  << " : "  << edge_distance  << " "  << (edge_destination->visited ? " (visited)" : "")  << endl;
            
            // 1. Update estimates
            if((current->shortest_path + edge_distance < edge_destination->shortest_path)){
                
                edge_destination->shortest_path = current->shortest_path + edge_distance;
                edge_destination->previous = current;

                cout << "\t\tUpdating shortest path of " << edge_destination->name << " to " << edge_destination->shortest_path << "; " << endl;
            } 
            // 2. Choose next 'current'
            if(!(edge_destination->visited) and (closest_neighbor == NULL or edge_destination->shortest_path < closest_neighbor->shortest_path)){
                cout << "New closest neighbor: " << edge_destination->name << " " << edge_destination->shortest_path << endl;
                edge_destination->visited = true;
                closest_neighbor = edge_destination;
                
                queue.add(closest_neighbor);
                queue.print();
            }
        }
        if(closest_neighbor == NULL){
            cout << "No unvisited vertices for " << current->name << endl;
            break;
        }
        cout << "Closest neighbor, visited: " << closest_neighbor->name << endl;
    }

    list<string> path = {};
    vertex* path_reversed_it = to;
    
    if(to->shortest_path == INF){ cout << "Error. No path found. " << endl; return; }

    while(path_reversed_it != NULL){
        path.push_front(path_reversed_it->name);
        path_reversed_it = path_reversed_it->previous;
    }

    cout << endl << endl << "Final route: " << endl;
    for(auto &it: path){
        cout << " -> " << it;
    }
    cout << " (" << to->shortest_path << " km)";
    cout << endl;
}

int main(){
    // {
    //     graph g;
    //     string template_name = "europe_north";
    //     load_vertices("graph_templates/" + template_name + "/vertices.dat", g);
    //     load_edges("graph_templates/" + template_name + "/edges.dat", g, true);

    //     vertex* from = g.vertices["Vilnius"];
    //     vertex* to = g.vertices["Helsinki"];
        
    //     // Dijkstra algorithm can be performed only once on the same graph.
    //     dijkstra(from, to);
    //     // dijkstra(to, from);
    // }
    {
        graph g;
        string template_name = "europe";
        load_vertices("graph_templates/" + template_name + "/vertices.dat", g);
        load_edges("graph_templates/" + template_name + "/edges.dat", g, true);

        vertex* from = g.vertices["Lisbon"];
        vertex* to = g.vertices["Berlin"];
        
        // Dijkstra algorithm can be performed only once on the same graph.
        dijkstra(from, to);
        // dijkstra(to, from);
    }

    // g.print();

    return 0;
}