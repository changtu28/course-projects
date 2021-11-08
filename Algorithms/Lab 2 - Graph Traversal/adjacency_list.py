def adjacency_list(graph_str):
    """Turns a textual representation of a graph into an adjcency list"""
    graph = graph_str.splitlines()
    info = graph.pop(0)
    info = info.split()
    #try:
        #graph.pop()
    #except IndexError: ###only needed because main() added a newline
        #3 + 5
    output_list = []
    for i in range(int(info[1])):
        output_list.append([])
    try:
        info[2]
        if info[0] == "U":
            return create_undirected(graph, output_list, True)
        elif info[0] == "D":
            return create_directed(graph, output_list, True)      
    except IndexError:
        if info[0] == "U":
            return create_undirected(graph, output_list)
        elif info[0] == "D":
            return create_directed(graph, output_list)        
        
    
def create_undirected(graph, output_list, weighted=False):
    """Returns an undirected graph adjacency list"""
    for line in graph:
        line = line.split()
        index = int(line[0])
        edge = int(line[1])
        index_2 = edge
        edge_2 = index
        if weighted:
            output_list[index].append(create_tuple(edge, int(line[2])))
            output_list[index_2].append(create_tuple(edge_2, int(line[2])))
        else:
            output_list[index].append(create_tuple(edge))
            output_list[index_2].append(create_tuple(edge_2))
    return output_list
    
def create_directed(graph, output_list, weighted=False):
    for line in graph:
        line = line.split()
        index = int(line[0])
        edge = int(line[1])
        if weighted:
            output_list[index].append(create_tuple(edge, int(line[2])))
        else:
            output_list[index].append(create_tuple(edge))
    return output_list
    
def create_tuple(edge, weight=None):
    """Creates the tuple to show an adjacency"""
    return (edge, weight)

def bfs_tree(adj_list, start):
    """Takes an adjacency list and a starting vertex and performs a BFS and
       returns the parent array"""
    n = len(adj_list)
    parent_array = [None] * n
    state_array = ["Undiscovered"] * n
    queue = []
    state_array[start] = "Discovered"
    queue.append(start) #Enqueue
    return bfs_loop(adj_list, queue, state_array, parent_array)

def bfs_loop(adj_list, queue, state_array, parent_array):
    """"""
    while len(queue) > 0: #While queue is not empty
        parent = queue.pop(0) #Dequeue
        for vertex in adj_list[parent]:
            vertex = vertex[0]
            if state_array[vertex] == "Undiscovered":
                state_array[vertex] = "Discovered"
                parent_array[vertex] = parent
                queue.append(vertex) #Enqueue
            state_array[parent] = "Processed"
    return parent_array


def dfs_tree(adj_list, start):
    """Takes an adjacency list and a starting vertex and performs a DFS and
       returns the parent array"""
    n = len(adj_list)
    parent_array = [None] * n
    state_array = ["Undiscovered"] * n
    state_array[start] = "Discovered"
    dfs_loop(adj_list, start, state_array, parent_array)
    return parent_array

def dfs_loop(adj_list, start, state_array, parent_array):
    """"""
    for vertex in adj_list[start]:
        vertex = vertex[0]
        if state_array[vertex] == "Undiscovered":
            state_array[vertex] = "Discovered"
            parent_array[vertex] = start
            dfs_loop(adj_list, vertex, state_array, parent_array)
            
city_map = """\
U 4 W
0 2 5
0 3 2
3 2 2
"""

print(adjacency_list(city_map))
#print(bfs_tree(adjacency_list(city_map), 0))
#print(bfs_tree(adjacency_list(city_map), 1))
#print(bfs_tree(adjacency_list(city_map), 2))
#print(bfs_tree(adjacency_list(city_map), 3))