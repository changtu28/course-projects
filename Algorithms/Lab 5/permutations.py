def permutations(s):
    """Takes a set s and returns a collection of all the permutation of objects
    in s. Permutations are of type tuple"""
    return subsets(s)
    
def backtrack_dfs(partial, fill_index, items, solutions):
    """Performs a backtrack dfs. 
       partial is the current partial solution
       fill_index is the current index in the partial solution being filled
       items is the list of possible characters to fill the solution with
       solutions is the solutions found so far
    """
    if is_a_solution(partial, fill_index, items):
        process_solution(partial, fill_index, items, solutions)
    else:
        for candidate in construct_candidates(partial, fill_index, items): #Construct candidates = what can be placed at position k (fill_index)
            partial[fill_index] = candidate
            backtrack_dfs(partial, fill_index+1, items, solutions)
            
def subsets(s):
    solutions = []
    items = list(s)
    empty_solution = [None] * len(items)
    index_to_fill = 0
    backtrack_dfs(empty_solution, index_to_fill, items, solutions)
    return solutions
        
def is_a_solution(partial, fill_index, items):
    return fill_index == len(items) #If the index to fill is == num of items needed
        
def process_solution(partial, fill_index, items, solutions):
    add_solution = True
    
    for item in items: #Removes any duplicates ((2, 2) or (1, 1)). Comment out this block if you want duplicates (ie. generates all subsets of the same size as original list)
        if not item in partial:
            add_solution = False
            
    if add_solution:
        solution = tuple(partial)
        solutions.append(solution)
    
def construct_candidates(partial, fill_index, items):
    return items