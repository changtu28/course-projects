from tkinter import *
from tkinter.ttk import * 
master = Tk()
c = Canvas(master, width=200, height=200)
c.pack()
#c.create_line(0, 0, 200, 100, tags=("cool"))
#c.create_line(0, 100, 200, 0, fill="red", dash=(4, 4), tags=("cool"))
x1 = 5
y1 = 10
x2 = x1 + 20
y2 = 150
rect = c.create_rectangle(x1, y1, x2, y2, fill="blue")
c.itemconfigure("cool", fill="blue")
c.itemconfigure(rect, fill="red")    
master.mainloop()