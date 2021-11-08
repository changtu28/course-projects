from tkinter import *
from tkinter.ttk import *  

lorem = """Lorem ipsum dolor sit amet, consectetur adipiscing elit. 
Praesent non turpis lacus. Suspendisse tristique elit dui, 
vel sollicitudin eros aliquet eget. Cras ac maximus magna, 
at molestie magna. Aenean ornare ante tortor, 
porta convallis ex elementum ut. Nullam nisl neque, auctor
at lacus in, tincidunt placerat risus. Duis pulvinar, odio ac 
convallis tincidunt, nunc nisl fringilla ante, quis 
sollicitudin lectus velit ac urna. Pellentesque imperdiet
augue sapien. Maecenas vestibulum sapien in volutpat varius.

Vestibulum et pulvinar metus. Fusce sodales orci ex,
non porttitor orci finibus a. Morbi cursus neque id sagittis 
venenatis. Nullam non nulla vel quam feugiat consectetur.
Nunc dapibus gravida libero ac convallis.
Aenean in mi cursus, cursus dolor eget, pellentesque nunc. 
Integer tincidunt auctor ipsum non luctus. Aliquam vestibulum 
augue et finibus rutrum. Cras et fermentum odio. Donec
lacinia, dui ac pretium viverra, justo magna consequat 
enim, at aliquam nulla mauris ut ante. Pellentesque ac 
nibh nec ante mattis dictum at vitae ante. Nullam 
luctus mattis egestas. Proin posuere pellentesque 
justo, sit amet vestibulum sapien pharetra nec. 
Suspendisse vel nisl ante. Donec eu semper mi."""

window = Tk()
text = Text(window, height=10, width=24, wrap=NONE)
text.insert(END, lorem)

vert_scrollbar = Scrollbar(window, orient=VERTICAL)
vert_scrollbar.pack(side=RIGHT, fill=Y)
vert_scrollbar.config(command=text.yview)

horiz_scrollbar = Scrollbar(window, orient=HORIZONTAL)
horiz_scrollbar.pack(side=BOTTOM, fill=X)
horiz_scrollbar.config(command=text.xview)

text.config(xscrollcommand=horiz_scrollbar.set)
text.config(yscrollcommand=vert_scrollbar.set)
text.pack()

window.mainloop()