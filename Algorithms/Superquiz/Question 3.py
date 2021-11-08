def adjacency_list(graph_str):
    """Turns a textual representation of a graph into an adjcency list"""
    graph = graph_str.splitlines()
    info = graph.pop(0)
    info = info.split()
    output_list = []
    for i in range(int(info[1])):
        output_list.append([])
    return create_undirected(graph, output_list, True)
    
def create_undirected(graph, output_list, weighted=False):
    """Returns an undirected graph adjacency list"""
    for line in graph:
        line = line.split()
        index = int(line[0])
        edge = int(line[1])
        index_2 = edge
        edge_2 = index
        output_list[index].append(create_tuple(edge, int(line[2])))
        output_list[index_2].append(create_tuple(edge_2, int(line[2])))
    return output_list
    
def create_tuple(edge, weight=None):
    """Creates the tuple to show an adjacency"""
    return (edge, weight)

def dijkstra(adj_list, start):
    """Implements dijkstras algorithm"""
    len_adj = len(adj_list)
    in_tree = [False] * len_adj
    distance = [float('inf')] * len_adj
    parent = [None] * len_adj
    distance[start] = 0
    
    no_possible_vertex = []
    
    while not all(in_tree):
        next_vert = next_vertex(in_tree, distance)
        if next_vert == float('inf'):
            break
        in_tree[next_vert] = True
        for vertex, weight in adj_list[next_vert]:
            test = distance[next_vert] + weight
            if not in_tree[vertex] and test < distance[vertex]:
                distance[vertex] = test
                parent[vertex] = next_vert
    return parent, distance
        
def next_vertex(in_tree, distance_array):
    """Takes both arrays and returns the vertex that should be added to 
       the tree next"""
    lowest_distance = float('inf')
    lowest_vertex = float('inf')
    for index, vertex in enumerate(in_tree):
        if not vertex:
            if distance_array[index] < lowest_distance:
                lowest_vertex = index
                lowest_distance = distance_array[index]
    
    return lowest_vertex
            
###New code

def longest_path(city_map, position):
    """Takes a textual representation of a weighted undirected graph and a start
    position, then returns a list beginning with the start position, followed by
    the path to the furthest away vertex from the start position (including the
    last vertex)"""
    adj_list = adjacency_list(city_map)
    dijk_parent, dijk_distance = dijkstra(adj_list, position)
    output_path = []
    dest_dist = 0
    dest_index = 0
    for index, dist in enumerate(dijk_distance):
        if dist > dest_dist and not dist == float('inf'):
            dest_dist = dist
            dest_index = index
    
    parent = dijk_parent[dest_index]
    if parent == None:
        output_path.append(position)
        return output_path
    while not parent == position:
        output_path.insert(0, parent)
        parent = dijk_parent[parent]
        
    output_path.insert(0, position)    
    output_path.append(dest_index)
        
    return output_path


##city_map = """\
##U 7 W
##0 1 6
##1 2 6
##0 2 10
##0 3 3
##3 4 3
##4 5 1
##"""

##print(longest_path(city_map, 0))
##print(longest_path(city_map, 1))
##print(longest_path(city_map, 2))
##print(longest_path(city_map, 3))
##print(longest_path(city_map, 4))
##print(longest_path(city_map, 5))
##print(longest_path(city_map, 6))

"""Should print
[0, 2]
[1, 0, 3, 4, 5]
[2, 0, 3, 4, 5]
[3, 0, 2]
[4, 3, 0, 2]
[5, 4, 3, 0, 2]
[6]
"""