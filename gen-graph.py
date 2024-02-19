import pandas as pd
from geopy.distance import geodesic
import itertools

capitals = pd.read_csv("https://raw.githubusercontent.com/j-rossi-nl/teaching-data/main/2022_ITP/concap.csv", index_col = "CapitalName")
capitals = capitals[(capitals['ContinentName'] == "Europe") | (capitals['ContinentName'] == "Asia")]

MAX_DISTANCE = 100000


def cities_distance(city_from: str, city_to: str = "Amsterdam", cities: pd.DataFrame = capitals)->float:
    lat_long = ["CapitalLatitude", "CapitalLongitude"]

    origin = capitals.loc[city_from, lat_long].agg(tuple)
    destination = capitals.loc[city_to, lat_long].agg(tuple)

    return int(geodesic(origin,destination).km)

def save_template(template_name = "europe"):
    city_pairs = list(itertools.combinations(capitals.index, 2))
    cities = capitals.index.tolist()

    vertices_filename = f"./graph_templates/{template_name}/vertices.dat"
    edges_filename = f"./graph_templates/{template_name}/edges.dat"

    print("\tWriting edges...")
    open(vertices_filename, 'w').close()
    with open(vertices_filename, 'w') as f_vertices:
        for city in cities:
            try:
                f_vertices.write(f"{city.replace(' ', '_')}\n")
            except:
                pass
            
    print("\tWriting vertices...")
    open(edges_filename, 'w').close()
    with open(edges_filename, 'w') as f_vertices:
        for pair in city_pairs:
            try:
                distance = cities_distance(pair[0], pair[1])
            except:
                continue
            if distance > MAX_DISTANCE:
                continue
        
            print(f"Writing {pair[0].replace(' ', '_')} {pair[1].replace(' ', '_')} {distance}")
            f_vertices.write(f"{pair[0].replace(' ', '_')} {pair[1].replace(' ', '_')} {distance}\n")
            

save_template(template_name = "eurasia")