from geopy.geocoders import Nominatim
import requests
import heapq

# Initialize Nominatim API
geolocator = Nominatim(user_agent="seggianiluca2004@gmail.com")

# List of towns
# towns = ["Grosseto", "Roselle", "Istia d'Ombrone", "Arcille", "Sant'Antonio", "Granaione", "Cinigiano", "Campagnatico", "Baccinello",
#          "Cana", "Vallerona", "Santa Caterina", "Roccalbegna", "Preselle", "Polveraia", "Montorgiali", "Pancole", "Scansano", "Poggioferro",
#          "Murci", "Usi", "Stribugliano", "Castiglioncello Bandini", "Monticello Amiata", "Salaiola", "Arcidosso", "San Lorenzo",
#          "Castel del Piano", "Montegiovi", "Seggiani", "Bagnore", "Santa Fiora", "Selva", "Selvena", "Abbadia San Salvatore",
#          "Triana", "Cellena", "Petricci", "Marruchina", "Semproniano", "Rocchette di Fazio", "Catabbio", "Poggio Murella", "San Martino Sul Fiora",
#          "Saturnia", "Pomonte", "Montemerano", "Manciano", "Sovana", "Pitigliano", "Castell'Azzara", "Sorano"]

towns = ["Baccinello", "Granaione"]

# Get coordinates for each town
coordinates = {}
for town in towns:
    location = geolocator.geocode(town + ", Italy")
    if location:
        coordinates[town] = (location.latitude, location.longitude)

print("Got coordinates: ", end="")
print(coordinates)

def get_distance(coord1, coord2):
    url = f"http://router.project-osrm.org/route/v1/driving/{coord1[1]},{coord1[0]};{coord2[1]},{coord2[0]}?overview=false"
    print("Making request for: " +  url)
    response = requests.get(url)
    data = response.json()
    if 'routes' in data:
        return data['routes'][0]['distance'] / 1000  # Convert meters to kilometers
    else:
        return None

# Create a dictionary to store distances
distances = {}

town_names = list(coordinates.keys())
coord_list = list(coordinates.values())

# Calculate distances between all pairs
for i, town1 in enumerate(town_names):
    for j, town2 in enumerate(town_names):
        if i < j:
            distance = get_distance(coord_list[i], coord_list[j])
            if distance is not None:
                distances[(i, j)] = distance

print("Got distances: ", end="")
print(distances)

# Define the number of closest neighbors to consider as adjacent
k = 1  # Example: each town will be connected to its 1 closest neighbors

adjacent_pairs = []

# For each town, find the k closest towns based on road distances
for i, town1 in enumerate(town_names):
    # Create a min-heap to store the closest neighbors
    heap = []
    for j, town2 in enumerate(town_names):
        if i < j:
            if (i, j) in distances:
                dist = distances[(i, j)]
            elif (j, i) in distances:
                dist = distances[(j, i)]
            else:
                continue
            heapq.heappush(heap, (dist, j))
    # Get the k closest neighbors
    for _ in range(k):
        if heap:
            _, j = heapq.heappop(heap)
            adjacent_pairs.append((i, j))


print("Got adjacent pairs: ", end="")
print(adjacent_pairs)

# Generate arcs for adjacent cities
arcs = []
for pair in adjacent_pairs:
    town1, town2 = pair
    if (town1, town2) in distances:
        distance = distances[(town1, town2)]
    else:
        distance = distances[(town2, town1)]
    arcs.append((town1, town2, distance))

print("Got arcs: ", end="")
print(arcs)

# File generation
file = open("road_info.txt", 'w')
for town in towns:
    file.write("n " + town + "\n")
file.write("\n")
for arc in arcs:
    file.write(f"a {arc[0]} {arc[1]} {arc[2]}\n")
file.close()

print("Data written to file road_info.txt")
