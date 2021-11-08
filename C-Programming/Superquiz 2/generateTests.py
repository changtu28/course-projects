import sys
from string import ascii_lowercase
import itertools
def main(args):
    num_chars = int(args[1])
    file = open("bugtests.txt", "w")
    line_to_format = "1,{},-1,-1,-1,-1\n"
    for perm in itertools.product(ascii_lowercase, repeat=num_chars):
        text = ""
        for char in perm:
            text += char
        file.write(line_to_format.format(text))
    
if __name__ == "__main__":
    main(sys.argv)