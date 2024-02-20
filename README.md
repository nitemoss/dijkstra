# Dijkstra's Algorithm
An algorithm that finds the shortest path between two vertices on the graph.

## How to run (using GitHub Codespace)

- Go to GitHub codespaces: https://github.com/codespaces
- Create new Codespace
- Select this repository: `nitemoss/dijkstra`
- Install C++ extension in the codespace
- Open the terminal and type `clang++ --std=c++11 dijkstra.cpp && ./a.out`

## Graph Templates

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
#### `./graph_templates/sometemplate/vertices.dat`
Each line contains start vertex, destination and distance:
```
Riga Jurmala 30
Jurmala Jelgava 50
Riga Jelgava 90
```


## Generating new graph templates using `gen_graph.py`
There is an option to generate new graph templates based on the real locations of the cities.
- Install python, install python libraries `pandas` and `geopy`.
- Change the code if you need to select some continent
```python
capitals = capitals[capitals['ContinentName'] == "Europe"]
```
- Specify the export graph template name
```python
save_template(template_name = "europe")
```
- Run `python3 gen_graph.py`.
