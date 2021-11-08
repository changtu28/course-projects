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


###Adjacency Matrix begin

def adjacency_matrix(graph_str):
    """Takes a textual representation of a weighted graph and returns the 
    adjacency matrix of it"""
    #graph = graph_str.splitlines()
    #info = graph.pop(0).split()
    output_list = empty_matrix(int(graph_str.splitlines().pop(0).split()[1])) #condensed above lines into one as I don't need any other information from graph_str
    adj_list = adjacency_list(graph_str)
    for index, vertex_adj in enumerate(adj_list):
        for tup in vertex_adj:
            output_list[index][tup[0]] = tup[1]        
    
            
    return output_list

def empty_matrix(length):
    """Takes a length and creates an empty adjacency_matrix"""
    output_list = []
    for i in range(length):
        output_list.append([])
    for index, list_ in enumerate(output_list):
        for i in range(length):
            if index == i:
                list_.append(0)
            else:
                list_.append(float('inf'))
        
    return output_list


def floyd(adjacency_matrix):
    """Takes an adjacency matrix of a weighted graph and uses the Floyd-Warshall
    algorithm to compute all-pairs shortest paths"""
    num_vertices = len(adjacency_matrix)
    #output_list = empty_matrix(num_vertices)
    #print(adjacency_matrix)
    for k in range(num_vertices):
        for i in range(num_vertices):
            for j in range(num_vertices):
                current = adjacency_matrix[i][j]
                test = adjacency_matrix[i][k] + adjacency_matrix[k][j]
                if test < current:
                    adjacency_matrix[i][j] = test
                    
    return adjacency_matrix
