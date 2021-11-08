def reorder_adj_list(adj_list):
    """Reorders the sublists of an adjacency list so that the lowest weights
    come first"""
    for index, vertex in enumerate(adj_list):
        edge_dict = {}
        for edge in vertex:
            dest = edge[0]
            weight = edge[1]
            edge_dict[dest] = weight
        #vertex = []
        adj_list[index] = sorted(edge_dict.items(), key=lambda x:x[1]) #Creates a list of
                                                              #tuple ordered by
                                                              #value (weight)
            
    return adj_list