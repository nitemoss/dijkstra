#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>

using namespace std;
#define INF 0x3f3f3f3f

/* ************** VERTEX **************  */

struct vertex {
    
    //          <distance to destination, destination>
    typedef pair<int, vertex*> edge; 
    
    // Dijkstra attributes
    bool visited = false;
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

void vertex::print_edges(){
    for (auto it : edges){
        cout << "\t" << it.first << " to " << it.second->name << ", " << endl;
    }
}

/* ************** VERTEX QUEUE **************  */

struct vertex_queue {
private:
    vector<vertex*> vertices{};

public:
    void add(vertex* v){
        vertices.push_back(v);
    }
    vertex* get_closest(){
        // Will return vertex in queue with minimum shortest path
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
    void print(){
        cout << "Queue: ";
        for(auto &it: vertices){
            cout << " " << it->name;
        }
        cout << endl;
    }
    bool empty(){
        return vertices.empty();
    }
};


/* ************** GRAPH **************  */

class graph {
public:
    typedef map<string, vertex*> vertex_map;
    vertex_map vertices;

    void add_vertex(const string&);
    void add_edge(const string& from, const string& to, double cost, bool bidirectional);
    
    void dijkstra(vertex* from, vertex* to);

    void print();
    void reset();
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
    cout << "Vertex " << name << " already exists!" << endl;
}

void graph::add_edge(const string& from, const string& to, double cost, bool bidirectional = false){
    vertex *f = (vertices.find(from)->second);
    vertex *t = (vertices.find(to)->second);
    pair<int, vertex *> edge = make_pair(cost, t);
    if(bidirectional) add_edge(to, from, cost);
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

void graph::reset(){
    for (vertex_map::iterator it = vertices.begin(); it != vertices.end(); it++){
        it->second->shortest_path = INF;
        it->second->visited = false;
        it->second->previous = NULL;
    }
    cout << "Graph has been reset." << endl;
}