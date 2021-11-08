from tkinter import *
from tkinter.ttk import *

board = ['qwertyuiop', 'asdfghjkl', 'zxcvbnm']

def add_text(text, char):
    text.insert(END, char)
    
def clear_text(text):
    text.delete('1.0', END)    

window = Tk()

text = Text(window, height=1, width=24)
text.grid(row=0, column=0)

clear_button = Button(window, text="Clear", command=lambda: clear_text(text))
clear_button.grid(row=0, column=1)

frame = Frame(window, borderwidth=3, relief=RIDGE)
frame.grid(row=1, column=0, columnspan=2, sticky="nsew", pady=2, padx=2)
frame.grid_rowconfigure(0, weight=1)
frame.grid_columnconfigure(0, weight=1)

for row in range(len(board)):
    frame_row = Frame(frame)
    frame_row.grid(row=row, column=0, columnspan=2)
    
    for col in range(len(board[row])):
        char = board[row][col]
        button = Button(frame_row, text=char, width=2, command=lambda: add_text(text, char))
        button.pack(side="left", padx=1, pady=1)
        #button.grid(row=row, column=col)

window.mainloop()