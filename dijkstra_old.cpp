#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct vertex {
    
    typedef pair<int, vertex*> edge; // <distance, destination>
    
    // Dijkstra attributes
    bool visited = false; // visited = false => shortest time = infinity
    int shortest_time = 0;
    
    vector<edge> edges;
    string name;
    
    vertex(string _name) : name(_name) {}
    vertex(string _name, bool visited) : name(_name) {}
    
    void print_edges();
};

void vertex::print_edges(){
    for (auto it : edges){
        cout << "\t" << it.first << " to " << it.second->name << ", " << endl;
    }
}


class graph {
public:
    typedef map<string, vertex*> vertex_map;
    vertex_map vertices;

    void add_vertex(const string&);
    void add_edge(const string& from, const string& to, double cost);
    
    void dijkstra(graph, vertex* from, vertex* to);

    void print();
};

void graph::add_vertex(const string &name){
    // Iterate through vertices, if no vertex with specified name was found, create new vertex
    vertex_map::iterator it = vertices.find(name);
    if (it == vertices.end())
    {
        vertex *v;
        v = new vertex(name);
        vertices[name] = v;
        return;
    }
    cout << "Vertex already exists!" << endl;
}

void graph::add_edge(const string& from, const string& to, double cost)
{
    vertex *f = (vertices.find(from)->second);
    vertex *t = (vertices.find(to)->second);
    pair<int, vertex *> edge = make_pair(cost, t);
    f->edges.push_back(edge);
}

void graph::print(){
    cout << endl;
    cout << "Graph information: " << endl;
    for (vertex_map::iterator it = vertices.begin(); it != vertices.end(); it++){
        cout << it->first << ": " << endl;
        it->second->print_edges();
        cout << endl;
    }
}

void graph::dijkstra(graph, vertex* from, vertex* to){
    cout << "Making direction from " << from->name << " to " << to->name << "..." << endl;

    for (vertex_map::iterator vertex_iterator = vertices.begin(); vertex_iterator != vertices.end(); vertex_iterator++){
        
        string current_vertex_name = vertex_iterator->first;
        vertex* current_vertex = vertex_iterator->second;
        
        if(current_vertex->name == from->name){
            cout << "Start vertex found, set as visited, distance = 0." << endl;
            from->visited = true;
            from->shortest_time = 0;
        } else {
            cout << endl << endl << "Analyzing " << current_vertex->name << " edges" << endl;
            for (auto edges_iterator : current_vertex->edges){
                int edge_distance = edges_iterator.first;
                vertex* edge_destination = edges_iterator.second;
                // cout << "\t" << edge_distance << " to " << edge_destination->name << endl;
                cout << "\t" << current_vertex->name << " -> " << edge_destination->name << " : " << edge_distance << endl;
                cout << "Comparing edge (" << edge_distance << ") and stored shortest time (" << edge_destination->shortest_time << ")" << endl;
                if(edge_distance < edge_destination->shortest_time and edge_destination->visited){
                    cout << "Found new shortest time from " << current_vertex_name << " to " << edge_destination->name;
                } else {
                    cout << edge_destination->name << " already has shortest time route of " << edge_destination->shortest_time;
                }
            }
            
        }
        
    }
}

int main(){
    graph g;
    g.add_vertex("Riga");
    g.add_vertex("Jurmala");
    g.add_vertex("Tukums");
    g.add_vertex("Jelgava");

    g.add_edge("Riga", "Jurmala", 10);
    g.add_edge("Jurmala", "Tukums", 20);
    g.add_edge("Tukums", "Jelgava", 10);
    
    g.add_edge("Riga", "Jelgava", 80);
    
    // g.print();

    vertex* riga = g.vertices["Riga"];
    vertex* jelgava = g.vertices["Jelgava"];
    
    g.dijkstra(g, riga, jelgava);

    return 0;
}