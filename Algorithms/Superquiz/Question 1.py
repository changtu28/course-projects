def checklist(conditions):
    """Takes a description of which components must be checked before which
    and returns (if possible) an ordering of components such that all given
    conditions are satisfied. If there is no solution, returns None"""
    
    #First I need to get an adjacency list
    component_graph, length = adjacency_list(conditions)
    #print(component_graph)
    
    if contains_cycle(component_graph): #Checks for any cycles and hence if there is a solution
        return None
    
    output = []
    for i in range(length):
        output.append(i)
    
    for i in range(length):
        for a, component in enumerate(component_graph): 
            for b in component:
            #if b == a: #If a must come before a
            #    return None 
            #else:
                a_index = output.index(a)
                b_index = output.index(b)
                if a_index > b_index:
                #output[b_index], output[a_index] = output[a_index], output[b_index]
                    output.remove(a)
                    output.insert(b_index, a)
            
    return output

def contains_cycle(adj_list):
    """Initialises a state array and iterates over the (directed) adj_list and
    tests each vertex with dfs_visit"""
    state_array = ["Undiscovered"] * len(adj_list)
    found_cycle = [False] #We use a list so that all functions called refer to the same list
    
    for v_index, vertex in enumerate(adj_list):
        if state_array[v_index] == "Undiscovered":
            dfs_visit(adj_list, v_index, state_array, found_cycle)
        if found_cycle[0]:
            break
    return found_cycle[0]

def dfs_visit(adj_list, v_index, state_array, found_cycle):
    """Takes an adjacency list and an index to start at and for each edge in
    that index recursively checks if a cycle is present that loops back to
    the starting index."""
    if found_cycle[0]: #Stop dfs if cycle is found
        return 
    state_array[v_index] = "Discovered" #Discovered nodes are in the current path
    for anc_index, anc_index in enumerate(adj_list[v_index]): #Check the ancestors/neighbours 
        if state_array[anc_index] == "Discovered": #If a loop in current path is present
            found_cycle[0] = True
            return
        if state_array[anc_index] == "Undiscovered":
            dfs_visit(adj_list, anc_index, state_array, found_cycle)
    state_array[v_index] = "Processed"

     
    
def adjacency_list(graph_str):
    """Turns a textual representation of a graph into an adjcency list
    This has been specifically customised for unweighted directed graphs"""
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
        output_list[index].append(edge)
    return output_list, int(info[1])