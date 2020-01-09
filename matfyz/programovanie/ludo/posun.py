import tkinter
import random
# POMOC SO SURADNICAMI __________________________________________________________________________________
def suradnice (klik) :
    a = klik.x
    b = klik.y
    print ("x", a, "y", b)

# PLATNO ________________________________________________________________________________________________

sirka = 1200
vyska = 822
canvas = tkinter.Canvas (width = sirka, height = vyska, bg = "black")


hod = 0

canvas.create_rectangle(60, 350, 120, 420, fill='white')
def stvorcek(x, y, info):
    canvas.create_rectangle(x-10, y-10, x+10, y+10)
    canvas.create_text(x, y, text=info)
def button1_klik():
    sucet_1 = 0

    canvas.create_rectangle(60, 350, 120, 420, fill='white')
    asd= random.randrange(1,7)
    if asd == 1:
        a1=canvas.create_oval (65,350,85,370, fill = "black")

    if asd == 2:
        a2=canvas.create_oval (65,350,85,370, fill = "black"),canvas.create_oval (95,400,115,420, fill = "black")

    if asd == 3:
        a3=canvas.create_oval (65,375,85,395, fill = "black"),canvas.create_oval (95,375,115,395, fill = "black"),canvas.create_oval (65,400,85,420, fill = "black")

    if asd == 4:
        a4=canvas.create_oval (65,375,85,395, fill = "black"),canvas.create_oval (95,375,115,395, fill = "black"),canvas.create_oval (65,400,85,420, fill = "black"),canvas.create_oval (95,400,115,420, fill = "black")

    if asd==5:
        a5=canvas.create_oval (95,350,115,370, fill = "black"),canvas.create_oval (65,375,85,395, fill = "black"),canvas.create_oval (95,375,115,395, fill = "black"),canvas.create_oval (65,400,85,420, fill = "black"),canvas.create_oval (95,400,115,420, fill = "black")

    if asd == 6:
        a6=canvas.create_oval (65,350,85,370, fill = "black"),canvas.create_oval (95,350,115,370, fill = "black"),canvas.create_oval (65,375,85,395, fill = "black"),canvas.create_oval (95,375,115,395, fill = "black"),canvas.create_oval (65,400,85,420, fill = "black"),canvas.create_oval (95,400,115,420, fill = "black")

    sucet_1 += asd
    print(sucet_1)

    p27=canvas.create_oval (720,360,750,390, fill = "white")
    canvas.create_text(735,375,  text='27', fill = "blue")

    p28=canvas.create_oval (760,360,790,390, fill = "white")
    canvas.create_text(775,375,  text='28', fill = "blue")

    p29=canvas.create_oval (800,360,830,390, fill = "white")
    canvas.create_text(815,375,  text='29', fill = "blue")

    p30=canvas.create_oval (800,400,830,430, fill = "white")
    canvas.create_text(815,415,  text='30', fill = "blue")

    p31=canvas.create_oval (800,440,830,470, fill = "green")
    canvas.create_text(815,455,  text='31', fill = "blue")

    p32=canvas.create_oval (760,440,790,470, fill = "white")
    canvas.create_text(775,455,  text='32', fill = "blue")

    p33=canvas.create_oval (720,440,750,470, fill = "white")
    canvas.create_text(735,455,  text='33', fill = "blue")

    global hod
    hod += sucet_1 - 1
    print (hod)

    zoznam = [[720, 360],[760, 360],[800, 360],[800, 440],[760, 440],[720, 440]]
    x = (zoznam[hod][0])
    y = (zoznam[hod][1])
    hrac = canvas.create_oval (x,y,x+30,y+30, fill = "red")

button1 = tkinter.Button(text='kocka', command=button1_klik)
button1.pack()





# POMOC SO SURADNICAMI __________________________________________________________________________________
canvas.bind ("<ButtonPress>", suradnice)

# NECESSITIES ____________________________________________________________________________________________
canvas.pack ()
canvas.mainloop ()