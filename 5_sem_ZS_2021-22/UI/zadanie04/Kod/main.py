import math
import random
import time
from tkinter import *
# from PIL import Image


# globalne premenne
class glob:
    canvas1 = None
    okno1 = None
    canvas3 = None
    okno3 = None
    canvas7 = None
    okno7 = None
    canvas15 = None
    okno15 = None

    RED = 1                     # cisla skupin
    GREEN = 2
    BLUE = 3
    MAGENTA = 4

    pocetBodov = 20000          # 20 000 bodov

    k = 3                       # pocet susedov

    # x > 0 : prava polka platna
    body1 = {RED: [(-4500, -4400), (-4100, -3000), (-1800, -2400), (-2500, -3400), (-2000, -1400)],       # rozdelenie mapky na casti
             GREEN: [(4500, -4400), (4100, -3000), (1800, -2400), (2500, -3400), (2000, -1400)],
             BLUE: [(-4500, 4400), (-4100, 3000), (-1800, 2400), (-2500, 3400), (-2000, 1400)],
             MAGENTA: [(4500, 4400), (4100, 3000), (1800, 2400), (2500, 3400), (2000, 1400)]}

    # x <= 0 : lava polka platna a stred
    body2 = {RED: [(-4500, -4400), (-4100, -3000), (-1800, -2400), (-2500, -3400), (-2000, -1400)],       # obe mapky na zaciatky obsahuju uvodne body aby vysledok nebol tak ovplyvneny
             GREEN: [(4500, -4400), (4100, -3000), (1800, -2400), (2500, -3400), (2000, -1400)],
             BLUE: [(-4500, 4400), (-4100, 3000), (-1800, 2400), (-2500, 3400), (-2000, 1400)],
             MAGENTA: [(4500, 4400), (4100, 3000), (1800, 2400), (2500, 3400), (2000, 1400)]}

    # pre ostatne k ako zo vstupu
    body_k1 = {RED: [],
                GREEN: [],
                BLUE: [],
                MAGENTA: []}
    body_k3 = {RED: [],
                GREEN: [],
                BLUE: [],
                MAGENTA: []}
    body_k7 = {RED: [],
                GREEN: [],
                BLUE: [],
                MAGENTA: []}
    body_k15 = {RED: [],
                GREEN: [],
                BLUE: [],
                MAGENTA: []}

    pocetTestov = 0

    pocetChyb = 0               # pocet pre zadane K
    pocetChyb1 = 0              # pocet chyb pre k = 1
    pocetChyb3 = 0              # pocet chyb pre k = 3
    pocetChyb7 = 0              # pocet chyb pre k = 7
    pocetChyb15 = 0             # pocet chyb pre k = 15

    width = 10000                                       # original zo zadania 10 000
    scale = 20                                          # vysledok 1:x
    start = 0                                           # zaciatocny bod
    can_w = width / scale                               # velkost platna v skale
    hrana = (can_w * 0.1)                               # kde sa menia farby (-500, 500)
    middle = can_w / 2                                  # stred platna
    bod_pad = math.sqrt(((can_w * can_w) / 15000))      # aky padding musi mat bod aby sa pokrylo cele platno todo?
    bod_pad2 = math.sqrt(((can_w * can_w) / 4800))      # trocha vacsi bod
    padding = int(can_w / 3)                            # okraj - celkovo
    pad_side = padding / 2                              # okraj na kraji
    total_w = can_w + padding                           # velkost okna


# ------------------------------------------------------------------- INE
# input od uzivatela
def aktualizujGlob():
    try:
        glob.scale = int(input("Zadaj skalu (1:x) min odporucana 1:10 :"))
        # glob.pocetBodov = int(input("Zadaj pocet bodov (zo zadania 20 000) : "))
        glob.k = int(input("Zadaj k (1, 3, 7, 15) : "))
    except ValueError:
        return

    if 10 > glob.scale > 100:
        glob.scale = 20
    if glob.k != 1 and glob.k != 3 and glob.k != 7 and glob.k != 15:
        glob.k = 1

    glob.can_w = glob.width / glob.scale                # velkost platna v skale
    glob.hrana = (glob.can_w * 0.1)                     # kde sa menia farby (-500, 500)
    glob.middle = glob.can_w / 2                        # stred platna
    glob.bod_pad = math.sqrt(((glob.can_w * glob.can_w) / 15000))   # aky padding musi mat bod aby sa pokrylo cele platno todo
    glob.bod_pad2 = math.sqrt(((glob.can_w * glob.can_w) / 4800))   # trocha vacsi bod
    glob.padding = int(glob.can_w / 3)                  # okraj - celkovo
    if glob.can_w + glob.padding < 550:
        glob.padding = 550 - glob.can_w
    glob.pad_side = glob.padding / 2                    # okraj na kraji
    glob.total_w = glob.can_w + glob.padding            # velkost okna


# random co vie robit aj so zapornymi cislami
def rand(minimum, maximum):
    return int(minimum + (maximum - minimum) * random.random())


# pridanie bodu do pola bodov - bud jedneho alebo druheho
def pridajBod(x, y, kategoria):
    if x > 0:
        glob.body1[kategoria].append((x, y))

    else:
        glob.body2[kategoria].append((x, y))


# podla vzorca vypocita vzdialenost dvoch bodov
def getVzdialenost(x, y, x2, y2):
    # d = (odm) (ax - bx) na 2 + (ay - by) na 2     todo check
    vzdialenost = (x-x2)*(x-x2) + (y-y2)*(y-y2)
    vzdialenost = math.sqrt(vzdialenost)

    return vzdialenost


# ------------------------------------------------------------------- GRAFIKA
# vykreslenie bodu do 2D priestoru
def kresliBod(x, y, farba, velkost, k):
    # prepocitanie
    if x >= 0:
        x = (glob.can_w / 2) + (x / glob.scale) + glob.pad_side
    else:
        x = abs(x)
        x = (glob.middle - (x / glob.scale) + glob.pad_side)
    if y >= 0:
        y = (glob.can_w / 2) - (y / glob.scale) + glob.pad_side
    else:
        y = abs(y)
        y = (glob.middle + (y / glob.scale) + glob.pad_side)

    # vycentrovanie
    x -= velkost / 2
    y -= velkost / 2

    # print(x, y)

    # nakreslenie
    if k == 1:
        glob.canvas1.create_oval(x, y, x + velkost, y + velkost, fill=farba, outline="")
    if k == 3:
        glob.canvas3.create_oval(x, y, x + velkost, y + velkost, fill=farba, outline="")
    if k == 7:
        glob.canvas7.create_oval(x, y, x + velkost, y + velkost, fill=farba, outline="")
    if k == 15:
        glob.canvas15.create_oval(x, y, x + velkost, y + velkost, fill=farba, outline="")


# vyplnenie pozadia 2D priestoru podla klasifikatora - tieto body sa uz nepridavaju do pola bodov
def dopln():
    maxPerc = 0
    count = 0
    total = 10000 / 120 * 10000 / 120
    for i in range(-5000, 5000, 120):
        for j in range(-5000, 5000, 120):
            count += 1

            if int(count / total * 100) > maxPerc + 4:
                maxPerc = int(count / total * 100)
                print("doplnanie prazdnych miest:", maxPerc, "%")

            # zo vstupu
            farba, kat = klasifikator(j, i, glob.k)
            if farba == "red":  # R
                kresliBod(j, i, 'brown4', glob.bod_pad2, glob.k)
            elif farba == "green":  # R
                kresliBod(j, i, 'dark olive green', glob.bod_pad2, glob.k)
            elif farba == "blue":  # R
                kresliBod(j, i, 'RoyalBlue4', glob.bod_pad2, glob.k)
            elif farba == "magenta":  # R
                kresliBod(j, i, 'VioletRed4', glob.bod_pad2, glob.k)

            # ostatne
            if glob.k != 1:
                f1, k1 = klasifikator(j, i, 1)
                if f1 == "red":  # R
                    kresliBod(j, i, 'brown4', glob.bod_pad2, 1)
                elif f1 == "green":  # R
                    kresliBod(j, i, 'dark olive green', glob.bod_pad2, 1)
                elif f1 == "blue":  # R
                    kresliBod(j, i, 'RoyalBlue4', glob.bod_pad2, 1)
                elif f1 == "magenta":  # R
                    kresliBod(j, i, 'VioletRed4', glob.bod_pad2, 1)
            if glob.k != 3:
                f3, k3 = klasifikator(j, i, 3)
                if f3 == "red":  # R
                    kresliBod(j, i, 'brown4', glob.bod_pad2, 3)
                elif f3 == "green":  # R
                    kresliBod(j, i, 'dark olive green', glob.bod_pad2, 3)
                elif f3 == "blue":  # R
                    kresliBod(j, i, 'RoyalBlue4', glob.bod_pad2, 3)
                elif f3 == "magenta":  # R
                    kresliBod(j, i, 'VioletRed4', glob.bod_pad2, 3)
            if glob.k != 7:
                f7, k7 = klasifikator(j, i, 7)
                if f7 == "red":  # R
                    kresliBod(j, i, 'brown4', glob.bod_pad2, 7)
                elif f7 == "green":  # R
                    kresliBod(j, i, 'dark olive green', glob.bod_pad2, 7)
                elif f7 == "blue":  # R
                    kresliBod(j, i, 'RoyalBlue4', glob.bod_pad2, 7)
                elif f7 == "magenta":  # R
                    kresliBod(j, i, 'VioletRed4', glob.bod_pad2, 7)
            if glob.k != 15:
                f15, k15 = klasifikator(j, i, 15)
                if f15 == "red":  # R
                    kresliBod(j, i, 'brown4', glob.bod_pad2, 15)
                elif f15 == "green":  # R
                    kresliBod(j, i, 'dark olive green', glob.bod_pad2, 15)
                elif f15 == "blue":  # R
                    kresliBod(j, i, 'RoyalBlue4', glob.bod_pad2, 15)
                elif f15 == "magenta":  # R
                    kresliBod(j, i, 'VioletRed4', glob.bod_pad2, 15)


def kresliUvodneBody(k):
    kresliBod(-4500, -4400, 'red', glob.bod_pad2, k)
    kresliBod(-4100, -3000, 'red', glob.bod_pad2, k)
    kresliBod(-1800, -2400, 'red', glob.bod_pad2, k)
    kresliBod(-2500, -3400, 'red', glob.bod_pad2, k)
    kresliBod(-2000, -1400, 'red', glob.bod_pad2, k)

    kresliBod(4500, -4400, 'lime green', glob.bod_pad2, k)
    kresliBod(4100, -3000, 'lime green', glob.bod_pad2, k)
    kresliBod(1800, -2400, 'lime green', glob.bod_pad2, k)
    kresliBod(2500, -3400, 'lime green', glob.bod_pad2, k)
    kresliBod(2000, -1400, 'lime green', glob.bod_pad2, k)

    kresliBod(-4500, 4400, 'deep sky blue', glob.bod_pad2, k)
    kresliBod(-4100, 3000, 'deep sky blue', glob.bod_pad2, k)
    kresliBod(-1800, 2400, 'deep sky blue', glob.bod_pad2, k)
    kresliBod(-2500, 3400, 'deep sky blue', glob.bod_pad2, k)
    kresliBod(-2000, 1400, 'deep sky blue', glob.bod_pad2, k)

    kresliBod(4500, 4400, 'magenta', glob.bod_pad2, k)
    kresliBod(4100, 3000, 'magenta', glob.bod_pad2, k)
    kresliBod(1800, 2400, 'magenta', glob.bod_pad2, k)
    kresliBod(2500, 3400, 'magenta', glob.bod_pad2, k)
    kresliBod(2000, 1400, 'magenta', glob.bod_pad2, k)


# finalna kompletizacia obrazu v 2D priestore
def vytvorGraf(uspesnost1, uspesnost3, uspesnost7, uspesnost15):
    # farebne pozadie
    dopln()

    # obdlzkiky podla farieb
    start = glob.start
    pad_side = glob.pad_side
    can_w = glob.can_w
    # middle = glob.middle
    # hrana = glob.hrana

    # glob.canvas.create_rectangle(start + pad_side, can_w + pad_side, middle + hrana + pad_side, middle - hrana + pad_side, fill="", outline='red')
    # glob.canvas.create_rectangle(can_w + pad_side, can_w + pad_side, middle - hrana + pad_side, middle - hrana + pad_side, fill="", outline='green')
    # glob.canvas.create_rectangle(start + pad_side, start + pad_side, middle + hrana + pad_side, middle + hrana + pad_side, fill="", outline='blue')
    # glob.canvas.create_rectangle(can_w + pad_side, start + pad_side, middle - hrana + pad_side, middle + hrana + pad_side, fill="", outline='magenta')

    # klasifikovane body -----------------------------------------------------------------------------------
    # zo vstupu
    # red
    for i in range(0, len(glob.body1[glob.RED])):  # R
        kresliBod(glob.body1[glob.RED][i][0], glob.body1[glob.RED][i][1], 'red4', glob.bod_pad, glob.k)
    for i in range(0, len(glob.body2[glob.RED])):
        kresliBod(glob.body2[glob.RED][i][0], glob.body2[glob.RED][i][1], 'red4', glob.bod_pad, glob.k)

    # green
    for i in range(0, len(glob.body1[glob.GREEN])):  # G
        kresliBod(glob.body1[glob.GREEN][i][0], glob.body1[glob.GREEN][i][1], 'OliveDrab4', glob.bod_pad, glob.k)
    for i in range(0, len(glob.body2[2])):
        kresliBod(glob.body2[glob.GREEN][i][0], glob.body2[glob.GREEN][i][1], 'OliveDrab4', glob.bod_pad, glob.k)

    # blue
    for i in range(0, len(glob.body1[glob.BLUE])):  # B
        kresliBod(glob.body1[glob.BLUE][i][0], glob.body1[glob.BLUE][i][1], 'DodgerBlue4', glob.bod_pad, glob.k)
    for i in range(0, len(glob.body2[3])):
        kresliBod(glob.body2[glob.BLUE][i][0], glob.body2[glob.BLUE][i][1], 'DodgerBlue4', glob.bod_pad, glob.k)

    # magenta
    for i in range(0, len(glob.body1[glob.MAGENTA])):  # M
        kresliBod(glob.body1[glob.MAGENTA][i][0], glob.body1[glob.MAGENTA][i][1], 'PaleVioletRed4', glob.bod_pad, glob.k)
    for i in range(0, len(glob.body2[4])):
        kresliBod(glob.body2[glob.MAGENTA][i][0], glob.body2[glob.MAGENTA][i][1], 'PaleVioletRed4', glob.bod_pad, glob.k)

    # ostatne --------------------------
    if glob.k != 1:
        for i in range(0, (len(glob.body_k1[glob.RED]))):
            kresliBod(glob.body_k1[glob.RED][i][0], glob.body_k1[glob.RED][i][1], 'red4', glob.bod_pad, 1)
        for i in range(0, (len(glob.body_k1[glob.GREEN]))):
            kresliBod(glob.body_k1[glob.GREEN][i][0], glob.body_k1[glob.GREEN][i][1], 'OliveDrab4', glob.bod_pad, 1)
        for i in range(0, (len(glob.body_k1[glob.BLUE]))):
            kresliBod(glob.body_k1[glob.BLUE][i][0], glob.body_k1[glob.BLUE][i][1], 'DodgerBlue4', glob.bod_pad, 1)
        for i in range(0, (len(glob.body_k1[glob.MAGENTA]))):
            kresliBod(glob.body_k1[glob.MAGENTA][i][0], glob.body_k1[glob.MAGENTA][i][1], 'PaleVioletRed4', glob.bod_pad, 1)
    if glob.k != 3:
        for i in range(0, (len(glob.body_k3[glob.RED]))):
            kresliBod(glob.body_k3[glob.RED][i][0], glob.body_k3[glob.RED][i][1], 'red4', glob.bod_pad, 3)
        for i in range(0, (len(glob.body_k3[glob.GREEN]))):
            kresliBod(glob.body_k3[glob.GREEN][i][0], glob.body_k3[glob.GREEN][i][1], 'OliveDrab4', glob.bod_pad, 3)
        for i in range(0, (len(glob.body_k3[glob.BLUE]))):
            kresliBod(glob.body_k3[glob.BLUE][i][0], glob.body_k3[glob.BLUE][i][1], 'DodgerBlue4', glob.bod_pad, 3)
        for i in range(0, (len(glob.body_k3[glob.MAGENTA]))):
            kresliBod(glob.body_k3[glob.MAGENTA][i][0], glob.body_k3[glob.MAGENTA][i][1], 'PaleVioletRed4', glob.bod_pad, 3)
    if glob.k != 7:
        for i in range(0, (len(glob.body_k7[glob.RED]))):
            kresliBod(glob.body_k7[glob.RED][i][0], glob.body_k7[glob.RED][i][1], 'red4', glob.bod_pad, 7)
        for i in range(0, (len(glob.body_k7[glob.GREEN]))):
            kresliBod(glob.body_k7[glob.GREEN][i][0], glob.body_k7[glob.GREEN][i][1], 'OliveDrab4', glob.bod_pad, 7)
        for i in range(0, (len(glob.body_k7[glob.BLUE]))):
            kresliBod(glob.body_k7[glob.BLUE][i][0], glob.body_k7[glob.BLUE][i][1], 'DodgerBlue4', glob.bod_pad, 7)
        for i in range(0, (len(glob.body_k7[glob.MAGENTA]))):
            kresliBod(glob.body_k7[glob.MAGENTA][i][0], glob.body_k7[glob.MAGENTA][i][1], 'PaleVioletRed4', glob.bod_pad, 7)
    if glob.k != 15:
        for i in range(0, (len(glob.body_k15[glob.RED]))):
            kresliBod(glob.body_k15[glob.RED][i][0], glob.body_k15[glob.RED][i][1], 'red4', glob.bod_pad, 15)
        for i in range(0, (len(glob.body_k15[glob.GREEN]))):
            kresliBod(glob.body_k15[glob.GREEN][i][0], glob.body_k15[glob.GREEN][i][1], 'OliveDrab4', glob.bod_pad, 15)
        for i in range(0, (len(glob.body_k15[glob.BLUE]))):
            kresliBod(glob.body_k15[glob.BLUE][i][0], glob.body_k15[glob.BLUE][i][1], 'DodgerBlue4', glob.bod_pad, 15)
        for i in range(0, (len(glob.body_k15[glob.MAGENTA]))):
            kresliBod(glob.body_k15[glob.MAGENTA][i][0], glob.body_k15[glob.MAGENTA][i][1], 'PaleVioletRed4', glob.bod_pad, 15)

    # uvodne body --------------------------------------------------------------------------------------------
    kresliUvodneBody(1)
    kresliUvodneBody(3)
    kresliUvodneBody(7)
    kresliUvodneBody(15)

    # text --------------------------------------------------------------------------------------------------------------------------
    text1 = "Počet bodov: 20 000, veľkosť: " + str(int(can_w)) + " x " + str(int(can_w)) + ", pomer 1:" + str(glob.scale) + ", k = 1"
    text3 = "Počet bodov: 20 000, veľkosť: " + str(int(can_w)) + " x " + str(int(can_w)) + ", pomer 1:" + str(glob.scale) + ", k = 3"
    text7 = "Počet bodov: 20 000, veľkosť: " + str(int(can_w)) + " x " + str(int(can_w)) + ", pomer 1:" + str(glob.scale) + ", k = 7"
    text15 = "Počet bodov: 20 000, veľkosť: " + str(int(can_w)) + " x " + str(int(can_w)) + ", pomer 1:" + str(glob.scale) + ", k = 15"

    glob.canvas1.create_text(glob.total_w / 2, start + (pad_side / 2), fill="black", font="Times 15 bold", text=text1, anchor=CENTER)
    glob.canvas3.create_text(glob.total_w / 2, start + (pad_side / 2), fill="black", font="Times 15 bold", text=text3, anchor=CENTER)
    glob.canvas7.create_text(glob.total_w / 2, start + (pad_side / 2), fill="black", font="Times 15 bold", text=text7, anchor=CENTER)
    glob.canvas15.create_text(glob.total_w / 2, start + (pad_side / 2), fill="black", font="Times 15 bold", text=text15, anchor=CENTER)

    text1 = "Úspešnosť klasifikátora: " + str(int(uspesnost1)) + " %"
    text3 = "Úspešnosť klasifikátora: " + str(int(uspesnost3)) + " %"
    text7 = "Úspešnosť klasifikátora: " + str(int(uspesnost7)) + " %"
    text15 = "Úspešnosť klasifikátora: " + str(int(uspesnost15)) + " %"

    glob.canvas1.create_text(glob.total_w / 2, glob.total_w - (pad_side / 2), fill="black", font="Times 15 bold", text=text1, anchor=CENTER)
    glob.canvas3.create_text(glob.total_w / 2, glob.total_w - (pad_side / 2), fill="black", font="Times 15 bold", text=text3, anchor=CENTER)
    glob.canvas7.create_text(glob.total_w / 2, glob.total_w - (pad_side / 2), fill="black", font="Times 15 bold", text=text7, anchor=CENTER)
    glob.canvas15.create_text(glob.total_w / 2, glob.total_w - (pad_side / 2), fill="black", font="Times 15 bold", text=text15, anchor=CENTER)

    # ULOZENIE
    # save_as_png(obraz, "pokus")


# toto je rozrobene ale neslo mi stiahnut kniznicu
def save_as_png(canvas, fileName):
    # save postscipt image
    canvas.postscript(file=fileName + '.eps')
    # use PIL to convert to PNG
    img = Image.open(fileName + '.eps')
    img.save(fileName + '.png', 'png')


# inicializacia canvas
def init():
    glob.okno1 = Tk()
    glob.okno3 = Tk()
    glob.okno7 = Tk()
    glob.okno15 = Tk()

    glob.okno1.title('Graf programu pre k=1')
    glob.okno1.resizable(False, False)
    glob.okno3.title('Graf programu pre k=3')
    glob.okno3.resizable(False, False)
    glob.okno7.title('Graf programu pre k=7')
    glob.okno7.resizable(False, False)
    glob.okno15.title('Graf programu pre k=15')
    glob.okno15.resizable(False, False)

    # CANVAS
    glob.canvas1 = Canvas(glob.okno1, width=glob.total_w, height=glob.total_w)
    glob.canvas1.pack()
    glob.canvas3 = Canvas(glob.okno3, width=glob.total_w, height=glob.total_w)
    glob.canvas3.pack()
    glob.canvas7 = Canvas(glob.okno7, width=glob.total_w, height=glob.total_w)
    glob.canvas7.pack()
    glob.canvas15 = Canvas(glob.okno15, width=glob.total_w, height=glob.total_w)
    glob.canvas15.pack()

    # MENU - zacate
    # menu = Menu(glob.okno1)
    # glob.okno1.config(menu=menu)
    # filemenu = Menu(menu)
    # menu.add_cascade(label='File', menu=filemenu)
    # filemenu.add_command(label='Save')
    # filemenu.add_command(label='Minimalize', command=okno.attributes("-fullscreen", False))
    # filemenu.add_command(label='Maximalize', command=okno.attributes("-fullscreen", True))
    # filemenu.add_separator()
    # filemenu.add_command(label='Exit', command=glob.okno.quit)
    # helpmenu = Menu(menu)
    # menu.add_cascade(label='Help', menu=helpmenu)
    # helpmenu.add_command(label='About')


# ------------------------------------------------------------------- KLASIFIKACIA
# hlavna funkcia na klasifikovanie bodov
def klasifikator(x, y, k):
    # uklada vzdialenosti bodov
    vzdialenosti = []
    najmensieVzdialenosti = []

    # vyber v ktorom poli ma hladat a pridavanie vzdialenosti --------------------
    if x <= 0:          # lava polka a stred
        for cisloSkupinyFarieb in glob.body1:
            for bodSkupiny in glob.body1[cisloSkupinyFarieb]:
                # vypocitanie velkosti vzdialenosti
                x2 = bodSkupiny[0]
                y2 = bodSkupiny[1]
                vzdialenost = getVzdialenost(x, y, x2, y2)

                # pridanie (data[skupina][vzdialenost])
                vzdialenosti.append((cisloSkupinyFarieb, vzdialenost))

    else:               # prava polka
        for cisloSkupinyFarieb in glob.body2:
            for bodSkupiny in glob.body2[cisloSkupinyFarieb]:
                # vypocitanie velkosti vzdialenosti
                x2 = bodSkupiny[0]
                y2 = bodSkupiny[1]
                vzdialenost = getVzdialenost(x, y, x2, y2)

                # pridanie (data[skupina][vzdialenost])
                vzdialenosti.append((cisloSkupinyFarieb, vzdialenost))

    # zoradovanie a vyber vzdialenosti -------------------------------------------
    # indexy
    skup = 0
    vzd = 1

    # zoradenie pola vzdialenosti od najmensej (podla vzdialenosti nie skupiny)
    vzdialenosti.sort(key=lambda tup: tup[vzd])

    # vyber prvych k vzdialenosti (k najblizsich susedov)
    for i in range(0, k):
        najmensieVzdialenosti.append(vzdialenosti[i])

    # roztriedenie a spocitanie susedov ------------------------------------------
    pocetRed = pocetGreen = pocetBlue = pocetMagenta = 0  # pocet najblizsich susedov v k vzdialenostiach podla skupiny

    for sused in najmensieVzdialenosti:
        if sused[skup] == glob.RED:
            pocetRed += 1
        elif sused[skup] == glob.GREEN:
            pocetGreen += 1
        elif sused[skup] == glob.BLUE:
            pocetBlue += 1
        elif sused[skup] == glob.MAGENTA:
            pocetMagenta += 1

    # jednoznacny vyber - z niektorej skupiny je najviac ----------------------- R / G / B / M
    if pocetRed > max(pocetGreen, pocetBlue, pocetMagenta):
        return "red", glob.RED
    elif pocetGreen > max(pocetRed, pocetBlue, pocetMagenta):
        return "green", glob.GREEN
    elif pocetBlue > max(pocetRed, pocetGreen, pocetMagenta):
        return "blue", glob.BLUE
    elif pocetMagenta > max(pocetRed, pocetGreen, pocetBlue):
        return "magenta", glob.MAGENTA

    # zhodne vsetky - vyberie sa nahodne farba ---------------------------------- RGBM
    elif pocetRed == pocetGreen == pocetBlue == pocetMagenta:   # all
        sanca = random.randint(0, 80)
        if sanca < 20:
            return "red", glob.RED
        elif sanca < 40:
            return "green", glob.GREEN
        elif sanca < 60:
            return "blue", glob.BLUE
        else:
            return "magenta", glob.MAGENTA

    # zhodne tri ---------------------------------------------------------------- RGB, RGM, RBM, GBM
    elif pocetRed == pocetGreen == pocetBlue:           # kombinacia 1
        sanca = random.randint(0, 60)
        if sanca < 20:
            return "red", glob.RED
        elif sanca < 40:
            return "green", glob.GREEN
        else:
            return "blue", glob.BLUE
    elif pocetRed == pocetGreen == pocetMagenta:        # kombinacia 2
        sanca = random.randint(0, 60)
        if sanca < 20:
            return "red", glob.RED
        elif sanca < 40:
            return "green", glob.GREEN
        else:
            return "magenta", glob.MAGENTA
    elif pocetRed == pocetBlue == pocetMagenta:         # kombinacia 3
        sanca = random.randint(0, 60)
        if sanca < 20:
            return "red", glob.RED
        elif sanca < 40:
            return "blue", glob.BLUE
        else:
            return "magenta", glob.MAGENTA
    elif pocetGreen == pocetBlue == pocetMagenta:       # kombinacia 4
        sanca = random.randint(0, 60)
        if sanca < 20:
            return "green", glob.GREEN
        elif sanca < 40:
            return "blue", glob.BLUE
        else:
            return "magenta", glob.MAGENTA

    # zhodne dve ---------------------------------------------------------------
    elif pocetRed == pocetGreen:                    # RG -----
        sanca = random.randint(0, 100)
        if sanca > 50:
            return "red", glob.RED
        else:
            return "green", glob.GREEN
    elif pocetRed == pocetBlue:  # RB
        sanca = random.randint(0, 100)
        if sanca > 50:
            return "red", glob.RED
        else:
            return "blue", glob.BLUE
    elif pocetRed == pocetMagenta:                  # RM
        sanca = random.randint(0, 100)
        if sanca > 50:
            return "red", glob.RED
        else:
            return "magenta", glob.MAGENTA
    elif pocetBlue == pocetGreen:                   # BG -----
        sanca = random.randint(0, 100)
        if sanca > 50:
            return "blue", glob.BLUE
        else:
            return "green", glob.GREEN
    elif pocetBlue == pocetMagenta:                 # BM
        sanca = random.randint(0, 100)
        if sanca > 50:
            return "blue", glob.BLUE
        else:
            return "magenta", glob.MAGENTA
    elif pocetGreen == pocetMagenta:                # GM  -----
        sanca = random.randint(0, 100)
        if sanca > 50:
            return "magenta", glob.MAGENTA
        else:
            return "red", glob.RED
    else:
        pass  # uz by nemala zostat ina moznost


# ------------------------------------------------------------------- GENEROVANIE
# toto pouziva iba generator, nie klasifikator - urci, kde vygeneroval bod
# (napr. mysliac si ze generuje modry bod vygeneruje bod co je v prieseku modra/cervena)
def zistiFarbu(x, y):
    if x >= 500 and y >= 500:
        return "magenta"
    elif x >= 500 and y <= -500:
        return "green"
    elif x <= -500 and y <= -500:
        return "red"
    elif x <= -500 and y >= 500:
        return "blue"
    elif -500 <= x <= 500 <= y:
        return "bluemagenta"
    elif 500 >= x >= -500 >= y:
        return "greenred"
    elif 500 >= y >= -500 >= x:
        return "bluered"
    elif -500 <= y <= 500 <= x:
        return "greenmagenta"
    else:
        return "redgreenbluemagenta"


# generovanie s 99% pravdepodobnostou zo skupiny podla rozsahu (ale moze byt aj v casti co sa prekryva) alebo 1% v celom poli
def generujFarbu(xMin, xMax, yMin, yMax, farSkupina):
    farba = ""

    # vyrata sa pravdepodobnost - ci to ozaj bude zo skupiny alebo z celeho rozsahu
    sanca = random.randint(1, 100)
    ok = 0
    if sanca == 99:                     # z celeho rozsahu
        while ok == 0:                  # kym to nie je unikatny bod
            x = rand(-5000, 5000)       # vytvori suradnice
            y = rand(-5000, 5000)
            if ((x, y) not in glob.body1) and ((x, y) not in glob.body2):   # skontroluje, ci neexistuje
                ok = 1                                                      # ak je unikatny -> OK
            else:
                print("opakujuci sa bod - vytvaram znova")                  # inak to skusi znova
        farba = zistiFarbu(x, y)        # zisti aky bod vytvoril
    else:
        while ok == 0:                  # rovnaky princip
            x = rand(xMin, xMax)
            y = rand(yMin, yMax)
            if ((x, y) not in glob.body1[farSkupina]) and ((x, y) not in glob.body2[farSkupina]):
                ok = 1
            else:
                print("opakujuci sa bod - vytvaram znova")
        farba = zistiFarbu(x, y)        # zistuje lebo vie ze vytvaral z urcitej skupiny, ale nevie ci sa neprekryva s inou

    # testovanie -------------------------------------------------------------------
    zistenaFarba, kat = klasifikator(x, y, glob.k)      # da to urcit klasifikatoru

    # pre porovnanie - v kazdom teste sa rovnake body porovnaju pre vsetky K - podla zadania
    if glob.k != 1:
        farba1, kat1 = klasifikator(x, y, 1)            # testovanie pre k = 1
        glob.body_k1[kat1].append((x, y))
        if farba1 not in farba:
            glob.pocetChyb1 += 1
    if glob.k != 3:
        farba3, kat3 = klasifikator(x, y, 3)            # testovanie pre k = 3
        glob.body_k3[kat3].append((x, y))
        if farba3 not in farba:
            glob.pocetChyb3 += 1
    if glob.k != 7:
        farba7, kat7 = klasifikator(x, y, 7)            # testovanie pre k = 7
        glob.body_k7[kat7].append((x, y))
        if farba7 not in farba:
            glob.pocetChyb7 += 1
    if glob.k != 15:
        farba15, kat15 = klasifikator(x, y, 15)         # testovanie pre k = 15
        glob.body_k15[kat15].append((x, y))
        if farba15 not in farba:
            glob.pocetChyb15 += 1

    # pridanie do zoznamu bodov na dalsiu klasifikaciu - len zistenie pre nase k
    pridajBod(x, y, kat)
    glob.pocetTestov += 1

    # zistenie uspesnosti pre zadane K
    # ak sme napr. vyrvorili bod v prieseku cervenej a modrej a klasifikator netrafi ani cervenu ani modru -> chyba
    if zistenaFarba not in farba:
        glob.pocetChyb += 1


# generuje postupne body z roznych skupin (aby sa to striedalo)
def generator():
    maxPerc = 0     # na vypis progresu

    # 20 uz mame na zaciatku, vytvori zvysny pocet po styroch - vzdy sa vola generovanie kazdej skupiny farieb
    for i in range(21, glob.pocetBodov + 1, 4):

        if int(glob.pocetTestov / glob.pocetBodov * 100) > maxPerc + 4:     # vypis progresu
            maxPerc = int(glob.pocetTestov / glob.pocetBodov * 100)
            print("klasifikovanie:", maxPerc, "%")

        # abs. rozsah X (od do) a Y (od do)
        generujFarbu(500, -5000, 500, -5000, glob.RED)          # red
        generujFarbu(-500, 5000, 500, -5000, glob.GREEN)        # green
        generujFarbu(500, -5000, -500, 5000, glob.BLUE)         # blue
        generujFarbu(-500, 5000, -500, 5000, glob.MAGENTA)      # magenta


# ------------------------------------------------------------------- MAIN
# volanie funkcii
if __name__ == '__main__':
    aktualizujGlob()            # vstup uzivatela
    init()                      # canvas

    print("\nSpustam klasifikaciu pre", glob.pocetBodov, "bodov, pri k =", glob.k, "\n")
    start = time.time()
    generator()                 # generovanie bodov

    # vypocitanie uspesnosti ----------------------------------------------------------
    aktUspesnost = ((glob.pocetTestov - glob.pocetChyb) / glob.pocetTestov * 100)
    print("\nUspesnost klasifikatora:")
    if glob.k != 15:  # koli formatvaniu
        print("\t PRE K =", glob.k, " :", "{0:.2f}".format(aktUspesnost), "%")
    else:
        print("\t PRE K = 15 :", "{0:.2f}".format(aktUspesnost), "%")

    # ostatne k ako zo vstupu
    if glob.k != 1:
        uspesnost1 = ((glob.pocetTestov - glob.pocetChyb1) / glob.pocetTestov * 100)
        print("\t pre k = 1  :", "{0:.2f}".format(uspesnost1), "%")
    else:
        uspesnost1 = aktUspesnost
    if glob.k != 3:
        uspesnost3 = ((glob.pocetTestov - glob.pocetChyb3) / glob.pocetTestov * 100)
        print("\t pre k = 3  :", "{0:.2f}".format(uspesnost3), "%")
    else:
        uspesnost3 = aktUspesnost
    if glob.k != 7:
        uspesnost7 = ((glob.pocetTestov - glob.pocetChyb7) / glob.pocetTestov * 100)
        print("\t pre k = 7  :", "{0:.2f}".format(uspesnost7), "%")
    else:
        uspesnost7 = aktUspesnost
    if glob.k != 15:
        uspesnost15 = ((glob.pocetTestov - glob.pocetChyb15) / glob.pocetTestov * 100)
        print("\t pre k = 15 :", "{0:.2f}".format(uspesnost15), "%")
    else:
        uspesnost15 = aktUspesnost

    # ---------------------------------------------------------------------------------
    akt = time.time()

    print("\nPocet cervenych bodov:", len(glob.body1[1]) + len(glob.body2[1]))
    print("Pocet zelenych bodov:", len(glob.body1[2]) + len(glob.body2[2]))
    print("Pocet modrych bodov:", len(glob.body1[3]) + len(glob.body2[3]))
    print("Pocet purpurovych bodov:", len(glob.body1[4]) + len(glob.body2[4]))
    print("Celkovy pocet bodov:",  len(glob.body1[1]) + len(glob.body2[1]) +
          len(glob.body1[2]) + len(glob.body2[2]) +
          len(glob.body1[3]) + len(glob.body2[3]) +
          len(glob.body1[4]) + len(glob.body2[4]) - 20)     # 20 je tam na zaciatku duplicitne
    print("Cas pred doplnenim bodov pozadia:", "{0:.2f}".format((akt - start) / 60), "min")
    print("")

    vytvorGraf(uspesnost1, uspesnost3, uspesnost7, uspesnost15)
    end = time.time()

    print("\nTrvanie:", "{0:.2f}".format((end - start) / 60), "min")

    glob.okno1.mainloop()
    glob.okno3.mainloop()
    glob.okno7.mainloop()
    glob.okno15.mainloop()
