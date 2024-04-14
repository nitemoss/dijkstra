# Dijkstra's Algorithm
An algorithm that finds the shortest path between two vertices on the graph.

## How to run Google Tests
If you do not have a ready development environment, perform all the necessary steps below to setup it, and type this command in the terminal: <br/>
```clang++ unittest_dijkstra.cpp --std=c++14 -lgtest -lgtest_main -pthread -o unittests && ./unittests```


## How to run (using GitHub Codespace)

- Go to GitHub codespaces: https://github.com/codespaces
- Create new Codespace
- Select this repository: `nitemoss/dijkstra`
- Install C++ extension in the codespace
- Open the terminal and type `clang++ --std=c++14 dijkstra.cpp && ./a.out`

## Command line arguments
There is an option to specify starting and destination vertices. <br/>
To select European graph template and make a path from `Riga` to `Paris`: `./a.out europe Riga Paris` <br/>
To select Latvian graph template and make a path from `Riga` to `Jelgava`: `./a.out latvia Riga Jelgava` <br/>

## Testing Scope
The testing scope is only the `dijkstra(vertex* from, vertex* to)` function. <br/>

## Create graph manually
```c++
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
  
  g.print();
  
  vertex* from = g.vertices["Riga"];
  vertex* to = g.vertices["Ventspils"];
  
  dijkstra(from, to);

  return 0;
}
```

## Importing Graph Templates
```c++
int main(){
  // Create Graph object.
  graph g;

  // Load Europe graph template.
  string template_name = "europe";
  load_vertices("graph_templates/" + template_name + "/vertices.dat", g);
  load_edges("graph_templates/" + template_name + "/edges.dat", g, true);

  // Define start and destination.
  vertex* from = g.vertices["Berlin"];
  vertex* to = g.vertices["Lisbon"];
  
  // Dijkstra algorithm can be performed only once on the same graph.
  dijkstra(from, to);

  // If needed to perform another path search, a graph reset is needed.
  g.reset();

  dijkstra(to, from);
}
```


## Graph Templates structure

The project has `./graph_templates/` directory. It contains graph templates, each template should have two files: `vertices.dat` and `edges.dat`.

So, the structure of files with one graph template 'europe' will look like this:
- `./graph_templates/`
- `./graph_templates/europe`
- `./graph_templates/europe/vertices.dat`
- `./graph_templates/europe/edges.dat`

### Files
#### `./graph_templates/sometemplate/vertices.dat`
Each line contains the name of one vertex:
```
Riga
Jurmala
Jelgava
```
#### `./graph_templates/sometemplate/edges.dat`
Each line contains start vertex, destination vertex and a distance:
```
Riga Jurmala 30
Jurmala Jelgava 50
Riga Jelgava 90
```


## Generating new graph templates using `gen-graph.py`
There is an option to generate new graph templates based on the real locations of the cities.
- Install Python, install Python libraries `pandas` and `geopy` (`pip3 install pandas geopy`).
- Change the code if you need to select some continent
```python
capitals = capitals[capitals['ContinentName'] == "Europe"]
```
- Specify the export graph template name
```python
save_template(template_name = "europe")
```
- Run `python3 gen-graph.py`.
