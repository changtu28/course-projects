
#def dijkstra(graph, start):
    #"""Implements dijkstras algorithm on a sorted adjacency matrix"""
    #graph_len = len(graph)
    #intree = [False] * graph_len
    #distance = [float('inf')] * graph_len
    #unvisited_vertices = []
    
    #for vertex in graph:
        #unvisited_vertices.append(vertex)
    ##for i in range(graph_len):
        ##unvisited_vertices.append(i)
     
    #distance[start] = 0
    #current_vertex = start
     
    #while len(unvisited_vertices) > 0:
        #least_dist = unvisited_vertices[current_vertex.pop(0).pop(0)]
        #unvisited_vertices.remove(least_dist)
        #for neighbour in graph[least_dist]:
            #alternative = 
        
     
     
        
    #parent = [-1] * graph_len
    
    #distance[start] = 0
    #current_vertex = start
    
    #while (intree[current_vertex] == False):
        #intree[current_vertex] = True
        #temp_pointer = edges_of_graph[current_vertex]
        #while not temp_pointer == None:
            #next_vertex = 
            
import adjacency_list

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

city_map = """\
U 4 W
0 2 5
0 3 2
3 2 2
"""

#print(dijkstra([[(2, 5), (3, 2)], [], [(0, 5), (3, 2)], [(0, 2), (2, 2)]], 0))
print(dijkstra(adjacency_list.adjacency_list(city_map), 0))
print(dijkstra(adjacency_list.adjacency_list(city_map), 1))
print(dijkstra(adjacency_list.adjacency_list(city_map), 2))
print(dijkstra(adjacency_list.adjacency_list(city_map), 3))