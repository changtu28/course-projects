def key_positions(seq, key):
    """Returns an array (list) such that the i-th element"""
    key_list = []
    for element in seq:
        key_list.append(key(element))
    k = max(key_list)
    
    count_array = []
    for num in range(k+1):
        count_array.append(0)
        
    for element in seq:
        count_array[key(element)] = count_array[key(element)] + 1
    
    count = 0
    
    for index in range(k+1):
        count_array[index], count = count, count + count_array[index]
    return count_array


def sorted_array(seq, key, positions):
    output = []
    for i in range(len(seq)):
        output.append([])
    for a in seq:
        output[positions[key(a)]] = a
        positions[key(a)] = positions[key(a)] + 1
        
    return output