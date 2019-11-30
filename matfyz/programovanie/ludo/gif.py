from PIL import Image, ImageTk
import tkinter

canvas = tkinter.Canvas(bg='navy')
canvas.pack()
a = canvas.create_image(200, 150)
########################################################
pole = [tkinter.PhotoImage(file='C:\DATA\FIIT\matfyz\programovanie\ludo\d{}.gif'.format(i)) for i in range(5)]
########################################################
i = 0
while True:
    canvas.itemconfig(a, image=pole[i])
    i = (i + 1) % len(pole)
    canvas.update()
    canvas.after(150)