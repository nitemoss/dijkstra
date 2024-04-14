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

    vertex* current = NULL;
    vertex_queue queue;
    queue.add(from);
    while(!queue.empty()){
        current = queue.get_closest();     
        queue.erase_closest();
        vertex* closest_neighbor = NULL;

        if(current == from) current->shortest_path = 0;
        if(current == to || current == NULL) break;

        if(current->edges.size() == 0) continue; // Current vertex has no edges
        for (auto edges_iterator: current->edges){
            int edge_distance = edges_iterator.first;
            vertex* edge_destination = edges_iterator.second;            
            if((current->shortest_path + edge_distance < edge_destination->shortest_path)){
                edge_destination->shortest_path = current->shortest_path + edge_distance;
                edge_destination->previous = current;
            } 
            if(!(edge_destination->visited) and (closest_neighbor == NULL or edge_destination->shortest_path < closest_neighbor->shortest_path)){
                if(DEBUG) cout << "New closest neighbor: " << edge_destination->name << " " << edge_destination->shortest_path << endl;
                edge_destination->visited = true;
                closest_neighbor = edge_destination;
                queue.add(closest_neighbor);
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
