def mean(numbers):
    return float(sum(numbers)) / max(len(numbers), 1)

def calc_slot_times(num_backoffs):
    avg_num_slot_times = 0
    for backoff in range(num_backoffs):
        avg_num_slot_times += mean(range((2**min(10, num_backoffs) - 1) + 1))
    return avg_num_slot_times