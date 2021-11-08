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