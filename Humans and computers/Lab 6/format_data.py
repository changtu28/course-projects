import csv

def format_data(filename):
    with open(filename, "r") as file:
        times = {}
        for line in file.readlines():
            line = line.strip().split(" ")
            block_num, time = int(line[3]), float(line[4])
            if block_num in times:
                times[block_num].append(time)
            else:
                times[block_num] = [time]
    
        result = []
        for key in times:
            result.append(sum(times[key]) / len(times[key]))
    
        return result


def main():
    print("DYNAMIC: " + str(format_data("experiment_dynamic_log.txt")))
    print("STATIC: " + str(format_data("experiment_static_log.txt"))) 

if __name__ == "__main__":
    main()