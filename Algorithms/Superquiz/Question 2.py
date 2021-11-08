def possible_locations(safe_map):
    """Takes a map of a/the city containing only "safe" roads (unflooded) and
    produces a list indicating the min num of fire trucks required and
    possible locaitons at which a firetruck must be positioned"""
    adj_list, length = adjacency_list(safe_map)
    to_bfs = []
    output = []
    tree_output = set()
    for i in range(length):
        to_bfs.append(i)
    
    while len(to_bfs) > 0:
        to_add = []
        for index, num in enumerate(bfs_tree(adj_list, to_bfs[0])):
            if not num == None:
                to_add.append(index)
                to_bfs.remove(index)
        output.append([to_bfs.pop(0)] + to_add)
    return output
    
def adjacency_list(graph_str):
    """Turns a textual representation of a graph into an adjcency list
    This has been specifically customised for unweighted undirected graphs"""
    graph = graph_str.splitlines()
    info = graph.pop(0)
    info = info.split()
    output_list = []
    for i in range(int(info[1])):
        output_list.append([])
    for line in graph:
        line = line.split()
        index = int(line[0])
        edge = int(line[1])
        index_2 = edge
        edge_2 = index
        output_list[index].append(edge)
        output_list[index_2].append(edge_2)
    return output_list, int(info[1])

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
            #vertex = vertex[0]
            if state_array[vertex] == "Undiscovered":
                state_array[vertex] = "Discovered"
                parent_array[vertex] = parent
                queue.append(vertex) #Enqueue
            state_array[parent] = "Processed"
    return parent_array