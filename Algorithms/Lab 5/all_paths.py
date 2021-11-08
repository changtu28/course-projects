def adjacency_list(graph_str):
    """Turns a textual representation of a graph into an adjcency list"""
    graph = graph_str.splitlines()
    info = graph.pop(0)
    info = info.split()
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


def all_paths(graph_string, source, destination):
    """Uses backtracking to find the list of all simle paths on a graph given
       a start point and a destination"""
    adj_list = adjacency_list(graph_string)
    paths = [] #Solutions
    partial_path = [source]
    backtrack_dfs(partial_path, adj_list, paths, destination)
    return paths
    
    
def backtrack_dfs(partial_path, adj_list, paths, end_vertex):
    """Performs a backtrack depth first search"""
    if is_a_solution(partial_path[-1], end_vertex):
        process_solution(partial_path, paths)
    else:
        partial_path.append(None) #So that it doesn't just keep added new things and only does one index at a time
        for poss_vertex in next_possible_vertices(adj_list, partial_path):
            partial_path[-1] = poss_vertex
            backtrack_dfs(list(partial_path), adj_list, paths, end_vertex)
    
    
def is_a_solution(curr_vertex, end_vertex):
    return curr_vertex == end_vertex
    
    
def process_solution(solution, paths):
    paths.append(solution)
    
def next_possible_vertices(adj_list, partial_path):
    """Finds the next possible vertices in a graph (the ones connected to the
       current vertex that are not currently in the partial path"""
    possible_vertices = []
    curr_vertex = partial_path[-2]
    for poss_vertex in adj_list[curr_vertex]:
        if not poss_vertex[0] in partial_path:
            possible_vertices.append(poss_vertex[0])
    return possible_vertices