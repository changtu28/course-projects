import csv, math

def read_file():
    with open("fitts_law_log.txt", "r", newline="") as file:
        return file.readlines()
    
def create_dictionary(lines):
    dictionary = {}
    
    for line in lines:
        line = line.split()
        key = (int(line[1]), int(line[2]), int(line[3]))
        value = float(line[4])
        dictionary[key] = value
        
    return dictionary

def calculate_averages(dictionary):
    averages_dictionary = {}
    
    for key in dictionary:
        if key[2] < 2:
            continue
        new_key = (key[0], key[1])
        if not new_key in averages_dictionary:
            averages_dictionary[new_key] = (dictionary[key], 1)
            
        else:
            current_time, count = averages_dictionary[new_key]
            averages_dictionary[new_key] = (current_time + dictionary[key],
                                            count + 1)
    

    
    with open("summary.csv", "w", newline="") as file:                
        file_writer = csv.writer(file)
        difficulties = {}
        to_write = []
        for key, value in averages_dictionary.items():
            amplitude, width = key
            difficulty = math.log2((amplitude / width) + 1)
            average_time = value[0] / value[1] / 1000
            
            if not difficulty in difficulties:
                difficulties[difficulty] = (average_time , 1)
            else:
                current_time, count = difficulties[difficulty]
                difficulties[difficulty] = (current_time + average_time, count + 1)
            
        
            #file_writer.writerow([amplitude, width, "{0:.2f}".format(difficulty),
                            #"{0:.3f}".format(average_time)])
                    
        for difficulty, value in difficulties.items():
            average_time = value[0] / value[1]
            
            file_writer.writerow(["{0:.3f}".format(difficulty), 
                             "{0:.3f}".format(average_time)])
        
        #to_write.sort()
        
        #file_writer.writerows(to_write)
        
        
def main():
    lines = read_file()
    dictionary = create_dictionary(lines)
    calculate_averages(dictionary)
    
    
if __name__ == "__main__":
    main()