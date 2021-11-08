from tkinter import *
from tkinter.ttk import *
from random import randrange, shuffle
import time, csv, os

class Game:
    def __init__(self, target_letters, num_blocks, dynamic, filename):
        self.block = list(target_letters)
        self.target_letters = target_letters
        self.num_blocks = num_blocks
        self.current_blocks = 1
        self.target = self.select_next_target()
        self.start_time = 0
        self.mode = "dynamic" if dynamic else "static"
        self.filename = filename
        
    def select_next_target(self):
        #print("Before: " + str(self.block) + ", " + str(self.num_blocks))
        if len(self.block) < 1 and self.current_blocks > self.num_blocks:
            return None
        
        index = randrange(len(self.block))
        new_target = self.block.pop(index)
        
        if len(self.block) < 1 and self.current_blocks <= self.num_blocks:
            self.current_blocks += 1
            self.block = list(self.target_letters)
            shuffle(self.block)
            
        self.target = new_target
        return new_target
    
    def log_time(self):
        if self.start_time == 0:
            self.start_time = time.time()
        else:
            total_time = (time.time() - self.start_time) * 1000
            
            block_num = self.current_blocks - 1 if len(self.block) > 5 else self.current_blocks
            
            with open(self.filename, "a", newline="") as file:
                file_writer = csv.writer(file, delimiter=" ")            
                file_writer.writerow(['Harrison', self.mode, self.target, block_num, total_time])
            self.start_time = 0



board = ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']



alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
shuffle(alphabet)

dynamic = False

def randomise_board():
    shuffle(alphabet)
    board[0] = alphabet[:10]
    board[1] = alphabet[10:19]
    board[2] = alphabet[19:]    

#if dynamic:
randomise_board()
shuffle(alphabet)

filename = "experiment_dynamic_log.txt" if dynamic else "experiment_static_log.txt"

#Personal choice to wipe the file each time
if os.path.exists(filename):
    os.remove(filename)
    
game = Game(alphabet[:6], 5, dynamic, filename)    

window = Tk()

text = Text(window, height=1, width=24)
text.grid(row=0, column=0, sticky="nsew", pady=2, padx=2)
text.tag_configure("center", justify='center')

#clear_button = Button(window, text="Clear", command=lambda: text_clear())
#clear_button.grid(row=0, column=1)

frame = Frame(window, borderwidth=3, relief=RIDGE)
frame.grid(row=1, column=0, sticky="nsew", pady=2, padx=2)
frame.grid_rowconfigure(0, weight=1)
frame.grid_columnconfigure(0, weight=1)

def text_append(char):
    text.insert(END, char)
    text.tag_add("center", "1.0", "end")
    
def text_clear():
    text.delete('1.0', END)
    
def text_set(char):
    text_clear()
    text_append(char)
    game.log_time()
    
text_set(game.target)

def button_press(char):
    if char == game.target:
        game.log_time()
        new_target = game.select_next_target()
        if new_target == None:
            window.destroy()
            new_window = Tk()
            done_text = Text(new_window, height=1, width=10)
            done_text.pack()
            done_text.insert(END, "Done!")
        else:
            text_set(new_target)
            return dynamic
    return False

def draw_keyboard():
    def button_action(char):
        if button_press(char):
            randomise_board()
            draw_keyboard()
            
    for row in range(len(board)):
        frame_row = Frame(frame)
        frame_row.grid(row=row, column=0, columnspan=2)
        
        for col in range(len(board[row])):
            button_frame = Frame(frame_row, height=32, width=32)
            button_frame.pack(side="left")
            
            char = board[row][col]
            button = Button(button_frame, text=char, width=2, command=lambda x=char: button_action(x))
            button.pack(fill=BOTH, expand=1)
            #button.pack(side="left", padx=1, pady=1)    

draw_keyboard()

window.mainloop()