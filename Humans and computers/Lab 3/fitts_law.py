from tkinter import *
from tkinter.ttk import * 
from random import randrange, shuffle
from itertools import product
import time, csv, os, sys

class Fitts:
    def __init__(self, window, canvas_width, canvas_height, repetitions, filename):
        distances = [64, 128, 256, 512]
        widths = [8, 16, 32]
        self.options = list(product(distances, widths))
        shuffle(self.options)
        self.window = window
        self.canvas = Canvas(window, width=canvas_width, height=canvas_height)
        self.canvas.pack()
        
        self.on_left = False
        self.canvas_width = canvas_width
        self.iteration = 0
        self.repetitions = repetitions
        self.rep = 0
        self.time = time.time()
        self.filename = filename

        self.draw_rectangles(self.options[self.iteration][0],
                             self.options[self.iteration][1])        
        
        
    def log_time(self, distance, width):
        total_time = (time.time() - self.time) * 1000
                            
        with open(self.filename, "a", newline="") as file:
            file_writer = csv.writer(file, delimiter=" ")            
            file_writer.writerow(['Harrison', distance, width, self.rep, total_time])
        
        self.time = time.time()

    def iterate(self, *args):
        if self.iteration >= len(self.options):
            self.window.destroy()
        else:
            option = self.options[self.iteration]
            self.log_time(option[0], option[1])
                
            self.draw_rectangles(option[0], option[1])
            if (self.rep >= self.repetitions - 1):
                self.iteration += 1
                self.rep = 0
            else:
                self.rep += 1
        
    def draw_rectangles(self, distance, width):
        self.canvas.delete("boxes")
        self.canvas.tag_unbind("left", "<ButtonPress-1>")
        self.canvas.tag_unbind("right", "<ButtonPress-1>")        
        #distance = self.distances.pop(randrange(len(self.distances)))
        #width = self.widths.pop(randrange(len(self.widths)))
        pad_left = (self.canvas_width / 2) - (distance / 2)
        pad_right = (self.canvas_width / 2) + (distance / 2)
        
        self.canvas.create_rectangle(pad_left - width, 
                                     0, 
                                     pad_left, 
                                     self.canvas_width, 
                                     fill="green" if self.on_left else "blue", 
                                     tags=("left", "boxes"))
        
        self.canvas.create_rectangle(pad_right + width, 
                                     0, 
                                     pad_right, 
                                     self.canvas_width, 
                                     fill="blue" if self.on_left else "green", 
                                     tags=("right", "boxes"))
        
        self.canvas.tag_bind("left" if self.on_left else "right", "<ButtonPress-1>", self.iterate)
        
        self.on_left = not self.on_left

filename = "fitts_law_log.txt"

if os.path.exists(filename):
    os.remove(filename)

master = Tk()
fitts = Fitts(master, 580, 425, 8, filename)
master.mainloop()