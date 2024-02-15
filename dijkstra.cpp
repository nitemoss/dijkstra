#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <list>
#include <algorithm> 

#define INF 0x3f3f3f3f

using namespace std;
struct vertex {
    
    typedef pair<int, vertex*> edge; // <distance, destination>
    
    // Dijkstra attributes
    bool visited = false; // visited = false => shortest time = infinity
    int shortest_path = INF;
    vertex* previous = NULL;
    
    vector<edge> edges;
    string name;
    
    vertex(string _name) : name(_name) {}
    vertex(string _name, bool visited) : name(_name) {}
    
    void print_edges();
    bool operator<(const vertex &second){
        return shortest_path < second.shortest_path;
    }
};
struct vertex_queue {
    std::vector<vertex*> vertices{};

    void add(vertex* v){
        vertices.push_back(v);
    }
    
    vertex* get_closest(){
        vertex* minElement = NULL;
        for(vertex* v : vertices) {    
            if(minElement == NULL or minElement->shortest_path > v->shortest_path){
                minElement = v;
            }
        }
        return minElement;
    }
    void erase_closest(){
        vertex* minElement = get_closest();
        auto it = find(vertices.begin(), vertices.end(), minElement);
        if (it != vertices.end()) {
            vertices.erase(it);
        }
    }
    bool empty(){
        return vertices.empty();
    }
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
    
    void dijkstra(vertex* from, vertex* to);

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

void graph::dijkstra(vertex* from, vertex* to){

    cout << "Making direction from " << from->name << " to " << to->name << "..." << endl;
    
    vertex* current = from;
    
    // Priority queue <distance, vertex>
    vertex_queue q;
    q.add(current);

    while(!q.empty()){

        current = q.get_closest();        
        q.erase_closest();

        // Vertex with a minimum distance of edge from a current vertex, which will be used as a current vertex in next iteration
        vertex* closest_neighbor = NULL;

        if(current == from){
            cout << "Start vertex found, set as visited, distance = 0." << endl;
            current->visited = true;
            current->shortest_path = 0;
        }    
        if(current == to){
            break;
        }    

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
            
            // Set new current vertex if is not set yet or distance to vertex is new minimum 
            
            if(closest_neighbor == NULL or current->shortest_path + edge_distance < edge_destination->shortest_path){
                closest_neighbor = edge_destination;
                closest_neighbor->shortest_path = current->shortest_path + edge_distance;
                closest_neighbor->previous = current;
                
                cout << "Updating distance of " << closest_neighbor->name << " to " << closest_neighbor->shortest_path << endl;
                q.add(closest_neighbor);
            }
            

            cout << "\t" << current->name << " -> " << edge_destination->name << " : " << edge_distance << " ";
            cout << (edge_destination->visited ? "(visited)" : "") << endl;
            
        }
    

        // closest_neighbor->visited = true;
        
        // cout << closest_neighbor->name << " (" << closest_neighbor->shortest_path << ") visited" << endl;
        current = closest_neighbor;
        
        
    }

    vertex* backtrace_iterator = to;
    while(backtrace_iterator != NULL){
        cout << backtrace_iterator->name << " <- ";
        backtrace_iterator = backtrace_iterator->previous;
    }
        
    
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
    g.add_edge("Kekava", "Ventspils", 3);

    // g.print();

    vertex* from = g.vertices["Riga"];
    vertex* to = g.vertices["Ventspils"];
    
    g.dijkstra(from, to);

    return 0;
}