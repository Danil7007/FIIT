import tkinter
import random
# POMOC SO SURADNICAMI __________________________________________________________________________________
def suradnice (klik) :
    a = klik.x
    b = klik.y
    print ("x", a, "y", b)

# PLATNO ________________________________________________________________________________________________
sirka = 1200
vyska = 750
canvas = tkinter.Canvas (width = sirka, height = vyska, bg = "black")
farba_c = "lightgreen"

#domcek---------------------------
b1=canvas.create_rectangle(20, 20, 60, 60, fill='blue')
b2=canvas.create_rectangle(60, 60, 100, 100, fill='blue')
b3=canvas.create_rectangle(60, 20, 100, 60, fill='blue')
b4=canvas.create_rectangle(20, 60, 60, 100, fill='blue')

r1=canvas.create_rectangle(20, 600, 60, 640, fill='red')
r2=canvas.create_rectangle(60, 640, 100, 680, fill='red')
r3=canvas.create_rectangle(60, 600, 100, 640, fill='red')
r4=canvas.create_rectangle(20, 640, 60, 680, fill='red')

g1=canvas.create_rectangle(1100, 600, 1140, 640, fill='green')
g2=canvas.create_rectangle(1140, 640, 1180, 680, fill='green')
g3=canvas.create_rectangle(1140, 600, 1180, 640, fill='green')
g4=canvas.create_rectangle(1100, 640, 1140, 680, fill='green')

y1=canvas.create_rectangle(1100, 20, 1140, 60, fill='yellow')
y2=canvas.create_rectangle(1140, 60, 1180, 100, fill='yellow')
y3=canvas.create_rectangle(1140, 20, 1180, 60, fill='yellow')
y4=canvas.create_rectangle(1100, 60, 1140, 100, fill='yellow')

#figurky---------------
canvas.create_oval (20, 20, 60, 60, fill='darkblue')
canvas.create_oval (60, 60, 100, 100, fill='darkblue')
canvas.create_oval (60, 20, 100, 60, fill='darkblue')
canvas.create_oval (20, 60, 60, 100, fill='darkblue')

canvas.create_oval (20, 600, 60, 640, fill='darkred')
canvas.create_oval (60, 640, 100, 680, fill='darkred')
canvas.create_oval (60, 600, 100, 640, fill='darkred')
canvas.create_oval (20, 640, 60, 680, fill='darkred')

canvas.create_oval(1100, 600, 1140, 640, fill='lightgreen')
canvas.create_oval(1140, 640, 1180, 680, fill='lightgreen')
canvas.create_oval(1140, 600, 1180, 640, fill='lightgreen')
canvas.create_oval(1100, 640, 1140, 680, fill='lightgreen')

canvas.create_oval(1100, 20, 1140, 60, fill='gold')
canvas.create_oval(1140, 60, 1180, 100, fill='gold')
canvas.create_oval(1140, 20, 1180, 60, fill='gold')
canvas.create_oval(1100, 60, 1140, 100, fill='gold')

#kocka-------------------
canvas.create_rectangle(50, 345, 130, 425, fill='white')
def stvorcek(x, y, info):
    canvas.create_rectangle(x-10, y-10, x+10, y+10)
    canvas.create_text(x, y, text=info)
def button1_klik():
    canvas.create_rectangle(50, 345, 130, 425, fill='white')
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

button1 = tkinter.Button(text='kocka', command=button1_klik)
button1.pack()

# hracia plocha----------------
p1=canvas.create_oval (560,600,590,630, fill = "red")
canvas.create_text(575,615,  text='1', fill = "blue")

p40=canvas.create_oval (600,600,630,630, fill = "white")
canvas.create_text(615,615,  text='40', fill = "blue")

p39=canvas.create_oval (640,600,670,630, fill = "white")
canvas.create_text(655,615,  text='39', fill = "blue")

p2=canvas.create_oval (560,560,590,590, fill = "white")
canvas.create_text(575,575,  text='2', fill = "blue")

canvas.create_oval (600,560,630,590, fill = "red")

p38=canvas.create_oval (640,560,670,590, fill = "white")
canvas.create_text(655,575,  text='38', fill = "blue")

p3=canvas.create_oval (560,520,590,550, fill = "white")
canvas.create_text(575,535,  text='3', fill = "blue")

canvas.create_oval (600,520,630,550, fill = "red")

p37=canvas.create_oval (640,520,670,550, fill = "white")
canvas.create_text(655,535,  text='37', fill = "blue")

p4=canvas.create_oval (560,480,590,510, fill = "white")
canvas.create_text(575,495,  text='4', fill = "blue")

canvas.create_oval (600,480,630,510, fill = "red")
p36=canvas.create_oval (640,480,670,510, fill = "white")
canvas.create_text(655,495,  text='36', fill = "blue")


p5=canvas.create_oval (560,440,590,470, fill = "white")
canvas.create_text(575,455,  text='5', fill = "blue")

canvas.create_oval (600,440,630,470, fill = "red")

p35=canvas.create_oval (640,440,670,470, fill = "white")
canvas.create_text(655,455,  text='35', fill = "blue")

canvas.create_oval (560,400,590,430, fill = "blue")
canvas.create_oval (640,400,670,430, fill = "green")

p15=canvas.create_oval (560,360,590,390, fill = "white")
canvas.create_text(575,375,  text='15', fill = "blue")
canvas.create_oval (600,360,630,390, fill = "yellow")
p25=canvas.create_oval (640,360,670,390, fill = "white")
canvas.create_text(655,375,  text='25', fill = "blue")


p16=canvas.create_oval (560,320,590,350, fill = "white")
canvas.create_text(575,335,  text='16', fill = "blue")
canvas.create_oval (600,320,630,350, fill = "yellow")
p24=canvas.create_oval (640,320,670,350, fill = "white")
canvas.create_text(655,335,  text='24', fill = "blue")

p17=canvas.create_oval (560,280,590,310, fill = "white")
canvas.create_text(575,295,  text='17', fill = "blue")
canvas.create_oval (600,280,630,310, fill = "yellow")
p23=canvas.create_oval (640,280,670,310, fill = "white")
canvas.create_text(655,295,  text='23', fill = "blue")

p18=canvas.create_oval (560,240,590,270, fill = "white")
canvas.create_text(575,255,  text='18', fill = "blue")
canvas.create_oval (600,240,630,270, fill = "yellow")
p22=canvas.create_oval (640,240,670,270, fill = "white")
canvas.create_text(655,255,  text='22', fill = "blue")

p19=canvas.create_oval (560,200,590,230, fill = "white")
canvas.create_text(575,215,  text='19', fill = "blue")
p20=canvas.create_oval (600,200,630,230, fill = "white")
canvas.create_text(615,215,  text='20', fill = "blue")
p21=canvas.create_oval (640,200,670,230, fill = "yellow")
canvas.create_text(655,215,  text='21', fill = "blue")


p6=canvas.create_oval (520,440,550,470, fill = "white")
canvas.create_text(535,455,  text='6', fill = "blue")


canvas.create_oval (520,400,550,430, fill = "blue")

p14=canvas.create_oval (520,360,550,390, fill = "white")
canvas.create_text(535,375,  text='14', fill = "blue")


p7=canvas.create_oval (480,440,510,470, fill = "white")
canvas.create_text(495,455,  text='7', fill = "blue")


canvas.create_oval (480,400,510,430, fill = "blue")
p13=canvas.create_oval (480,360,510,390, fill = "white")
canvas.create_text(495,375,  text='13', fill = "blue")
p8=canvas.create_oval (440,440,470,470, fill = "white")

canvas.create_text(455,455,  text='8', fill = "blue")


canvas.create_oval (440,400,470,430, fill = "blue")
p12=canvas.create_oval (440,360,470,390, fill = "white")
canvas.create_text(455,375,  text='12', fill = "blue")


p9=canvas.create_oval (400,440,430,470, fill = "white")
canvas.create_text(415,455,  text='9', fill = "blue")


p10=canvas.create_oval (400,400,430,430, fill = "white")
canvas.create_text(415,415,  text='10', fill = "blue")


p11=canvas.create_oval (400,360,430,390, fill = "blue")
canvas.create_text(415,375,  text='11', fill = "black")


p34=canvas.create_oval (680,440,710,470, fill = "white")
canvas.create_text(695,455,  text='34', fill = "blue")
canvas.create_oval (680,400,710,430, fill = "green")

p26=canvas.create_oval (680,360,710,390, fill = "white")
canvas.create_text(695,375,  text='26', fill = "blue")

p33=canvas.create_oval (720,440,750,470, fill = "white")
canvas.create_text(735,455,  text='33', fill = "blue")
canvas.create_oval (720,400,750,430, fill = "green")
p27=canvas.create_oval (720,360,750,390, fill = "white")
canvas.create_text(735,375,  text='27', fill = "blue")

p32=canvas.create_oval (760,440,790,470, fill = "white")
canvas.create_text(775,455,  text='32', fill = "blue")
canvas.create_oval (760,400,790,430, fill = "green")
p28=canvas.create_oval (760,360,790,390, fill = "white")
canvas.create_text(775,375,  text='28', fill = "blue")

p31=canvas.create_oval (800,440,830,470, fill = "green")
canvas.create_text(815,455,  text='31', fill = "blue")
p30=canvas.create_oval (800,400,830,430, fill = "white")
canvas.create_text(815,415,  text='30', fill = "blue")
p29=canvas.create_oval (800,360,830,390, fill = "white")
canvas.create_text(815,375,  text='29', fill = "blue")

#hra------------------



# POMOC SO SURADNICAMI __________________________________________________________________________________
canvas.bind ("<ButtonPress>", suradnice)

# NECESSITIES ____________________________________________________________________________________________
canvas.pack ()
canvas.mainloop ()