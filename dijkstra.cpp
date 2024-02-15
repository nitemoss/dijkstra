#include <iostream>
#include <vector>
#include <map>
#include <string> 
#include "graph.hpp"

using namespace std;

void dijkstra(vertex* from, vertex* to){
    cout << "Making direction from " << from->name << " to " << to->name << "..." << endl;
    
    vertex* current = from;
    vertex_queue queue;
    queue.add(current);

    while(!queue.empty()){
        current = queue.get_closest();        
        queue.erase_closest();

        // Vertex with a minimum distance of edge from a current vertex, which will be used as a current vertex in next iteration
        vertex* closest_neighbor = NULL;

        if(current == from){
            cout << "Start vertex found, set as visited, distance = 0." << endl;
            current->shortest_path = 0;
        }    
        if(current == to) break;    

        int edges_amount = current->edges.size();
        cout << endl << endl << "Analyzing " << edges_amount << " edges of " << current->name << endl;

        if(edges_amount == 0) {
            cout << "No edges for " << current->name;
            continue;
        }
        // Analyze neigbours
        for (auto edges_iterator: current->edges){
            int edge_distance = edges_iterator.first;
            vertex* edge_destination = edges_iterator.second;
            
            cout << "\t" << current->name << " -> " << edge_destination->name << " : " << edge_distance << " " << endl;
            
            // Update vertex distance if shorter path was found, store the closest vertex to use it in the next iteration.
            if(closest_neighbor == NULL or current->shortest_path + edge_distance < edge_destination->shortest_path){
                closest_neighbor = edge_destination;
                closest_neighbor->shortest_path = current->shortest_path + edge_distance;
                closest_neighbor->previous = current;
                
                cout << "\t\tUpdating distance of " << closest_neighbor->name << " to " << closest_neighbor->shortest_path << "; " << endl;
                queue.add(closest_neighbor);
            }
        }
        current = closest_neighbor;
    }
    list<string> path = {};
    vertex* path_reversed_it = to;

    while(path_reversed_it != NULL){
        path.push_front(path_reversed_it->name);
        path_reversed_it = path_reversed_it->previous;
    }
    cout << endl;
    for(auto &it: path){
        cout << " -> " << it;
    }
    cout << endl;
}

int main(){
    graph g;
    g.add_vertex("Riga");
    g.add_vertex("Olaine");
    g.add_vertex("Kekava");
    g.add_vertex("Jurmala");
    g.add_vertex("Tukums");
    g.add_vertex("Jelgava");
    g.add_vertex("Ventspils");

    g.add_edge("Riga", "Jurmala", 10);
    g.add_edge("Riga", "Olaine", 11);
    g.add_edge("Riga", "Kekava", 13);
    g.add_edge("Riga", "Jelgava", 80);
    
    g.add_edge("Jurmala", "Jelgava", 30);
    g.add_edge("Jurmala", "Tukums", 20);

    g.add_edge("Jelgava", "Ventspils", 50);
    g.add_edge("Tukums", "Ventspils", 10);

    g.add_edge("Olaine", "Ventspils", 10);
    g.add_edge("Kekava", "Ventspils", 10);

    // g.print();

    vertex* from = g.vertices["Riga"];
    vertex* to = g.vertices["Ventspils"];
    
    dijkstra(from, to);

    return 0;
}