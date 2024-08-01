
import tkinter as tk
from tkinter import ttk

# root window
root = tk.Tk()
root.geometry('200x200')
root.resizable(True, True)
root.title('Button Demo')

root.rowconfigure(0,weight=2)
root.rowconfigure(1,weight=2)
root.columnconfigure(0,weight=2)
root.columnconfigure(1,weight=2)

CONTROL = 4
def button_pressed_cb(event):
    if event.widget['state'] != tk.DISABLED:
        print("You pressed " + event.widget['text'])
        if (event.state & CONTROL) == CONTROL:
            event.widget.config(state=tk.DISABLED)
            event.widget.config(relief=tk.SUNKEN)

def button_release_cb(event):
    if (event.state & CONTROL) != CONTROL:
        print("You released " + event.widget['text'])
        event.widget.config(state=tk.NORMAL)
        event.widget.config(relief=tk.RAISED)

def new_controller(pos,motor,action):
    button = ttk.Button(
        root,
        text=f'{motor}{action}',
        command=lambda: None
    )
    button.bind("<ButtonPress>", button_pressed_cb)#lambda _: print(f"{motor} {action}"))
    button.bind("<ButtonRelease>",button_release_cb) #lambda _: print("f{motor}{stop}"))
    
    button.grid(column=pos[0], row=pos[1], sticky='nsew', padx=5, pady=5) 
    return button

new_controller([0,0],"left","forward")
new_controller([0,1],"left","backward")
new_controller([1,0],"right","forward")
new_controller([1,1],"right","backward")

root.mainloop()
