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
    output = [list()] * len(seq)
    
    #for i in range(len(seq)):
    #    output.append([])
    for element in seq:
        output[positions[key(element)]] = element
        positions[key(element)] = positions[key(element)] + 1
        
    return output


def counting_sort(iterable, key):
    """Implements counting sort using sorted_array and key_positions"""
    positions = key_positions(iterable, key) #sorting on iterable
    return sorted_array(iterable, key, positions) #sorting iterable


###Radix code
def get_digit(number, digit):
    """Checks to see if the number has the corresponding digit"""
    try: return int(str(number)[-digit])
    except IndexError: return 0

def radix_sort(numbers, digits):
    """Does a radix sort using counting sort as the stable sorting algorithm,
    digits is the digit length to sort up to"""
    for digit in range(1, digits+1):
        numbers = counting_sort(numbers, lambda number: get_digit(number, digit))

    return numbers

