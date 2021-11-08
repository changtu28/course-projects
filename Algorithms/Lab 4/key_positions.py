def key_positions(seq, key):
    """Returns an array (list) such that the i-th element"""
    k_list = []
    for i in seq:
        k_list.append(key(i))
    k = max(k_list)
    
    C = []
    for i in range(k+1):
        C.append(0)
        
    for a in seq:
        C[key(a)] = C[key(a)] + 1
    
    sum_ = 0
    
    for i in range(k+1):
        C[i], sum_ = sum_, sum_ + C[i]
    return C