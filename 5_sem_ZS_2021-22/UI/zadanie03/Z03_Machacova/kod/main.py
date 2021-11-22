import random
import time
from itertools import groupby
from random import randint
import numpy as np


class zahrada:
    zaciatky = []       # odkial sa da vstupit do zahradky - poradove cislo podla obvodu
    policka = []        # zahradka
    zahradaX = 0        # rozmer
    zahradaY = 0        # rozmer
    pocetKamenov = 0
    pocetPolicok = 0    # pocet policok zahradky
    obvod = 0           # pocet policok tvoriacich obvod


class pohyb:
    POHYB_X = [1, 0, -1, 0]     # DOLE, DOPRAVA, HORE, DOLAVA
    POHYB_Y = [0, 1, 0, -1]     # 0       1       2      3


class glob:
    START = 0       # urcuju kde u mnicha najdeme ktore informacie
    OPER = 1
    POC = 2
    KAMEN = 3

    VYBER = 2       # flag pre vyber sposobu vyberu mnichov
    ZASEKNUTIE = 1  # flag ci moze ukoncit hrabanie v zahradke ( 1 moze / inak nemoze )

    LIMIT = 95000

    POCET_MNICHOV = 10           # pre (dalsie generacie) mnichov
    POCET_MNICHOV_PRVA_GEN = 30
    POCET_MAX_MNICHOV = 1
    POCET_MAX_MNICHOV_ZASEK = 1
    TOP_PERCENTO = 5
    POCET_NOVYCH_MUTACII = 5
    ROZSAH_PAROVANIA = 10

    # POCET_STARTOV = 80           # je to len na inicializaciu prvej generacie - genom bude ovela mensi ked sa odstrania duplikaty
    POCET_OPERATOROV = 9


class farby:
    SAND = '\u001b[43;1m'
    STONE = '\u001b[30m\u001b[47;1m'

    R = '\u001b[31m'
    G = '\u001b[32m'
    Y = '\u001b[33m'
    B = '\u001b[34m'
    M = '\u001b[35m'
    C = '\u001b[36m'

    ENDC = '\033[0m'


# suradnice okrajov zahrady
def najdiZaciatky(x, y):
    for i in range(0, x):
        for j in range(0, y):

            if (i == 0 or i == x-1):
                zahrada.zaciatky.append([i, j], )
            elif (j == 0 or j == y-1):
                zahrada.zaciatky.append([i, j], )

    return


def zistiUmiestnenie(x, y):
    if x == 0 and y == 0:                       # lavy horny roh
        return 0
    elif x == 0 and y != zahrada.zahradaY - 1:  # vrch
        return 1
    elif x == 0 and y == zahrada.zahradaY - 1:  # vrchny pravy roh
        return 2
    elif y == 0 and x !=  zahrada.zahradaX - 1: # lava strana
        return 3
    elif y == 0 and x == zahrada.zahradaX - 1:  # lavy dolny roh
        return 4
    elif x == zahrada.zahradaX - 1 and y != zahrada.zahradaY - 1: # spodna strana
        return 5
    elif x == zahrada.zahradaX - 1 and y == zahrada.zahradaY - 1: # spody pravy roh
        return 6
    elif y == zahrada.zahradaY - 1:     # prava strana
        return 7


def porovnajSmer(startX, startY, posX, posY):

    umiestnenie = zistiUmiestnenie(startX, startY)

    if umiestnenie == 3 and posX == 0:
        return 0        # nejde po lavom okraji
    elif umiestnenie == 1 and posY == 0:
        return 0        # nejde po hornom okraji
    elif umiestnenie == 7 and posX == 0:
        return 0        # nejde po pravom okraji
    elif umiestnenie == 5 and posY == 0:
        return 0        # nedje po spodnom okraji
    elif umiestnenie == 0 or umiestnenie == 2 or umiestnenie == 4 or umiestnenie == 6:
        return 0        # je v rohu
    else:
        return 1        # IDE POZDLZ PO OKRAJI


# done
def vytvorZahradu(source):
    try:
        subor = open(source, "r")
    except FileNotFoundError:
        print("Dany subor neexistuje")
        return

    poradie = 0
    kamenX = kamenY = 0
    pocetKamenov = 0

    try:
        for i in subor:
            #print(i[:-1], end = ", ")
            i = i[:-1]          # odstranenie enteru

            if i.isdigit():
                poradie += 1

                if poradie == 1:    # SIRKA
                    zahrada.zahradaX = int(i)
                elif poradie == 2:  # VYSKA
                    zahrada.zahradaY = int(i)
                    # print("sirka x", zahrada.zahradaX, "vyska y", zahrada.zahradaY)
                    zahrada.policka = [[0 for stlpec in range(0, zahrada.zahradaY)] for riadok in range(0, zahrada.zahradaX)]

                elif poradie % 2 == 1:
                    kamenX = int(i)
                else:
                    kamenY = int(i)
                    pocetKamenov += 1
                    # print("kamen:", pocetKamenov, "x:", kamenX, "y:", kamenY)
                    zahrada.policka[kamenX][kamenY] = "K"
    except IndexError:
        print("Zle zadane rozmery v subore")

    zahrada.pocetKamenov = pocetKamenov
    zahrada.pocetPolicok = zahrada.zahradaX * zahrada.zahradaY - pocetKamenov
    najdiZaciatky(zahrada.zahradaX, zahrada.zahradaY)
    zahrada.obvod = (2 * zahrada.zahradaY + 2 * zahrada.zahradaX) - 4
    print("\nZahrada vytvorena, rozmer", zahrada.zahradaX, "x", zahrada.zahradaY, "\npocet kamenov", pocetKamenov, "pocet policok", zahrada.pocetPolicok, "obvod", zahrada.obvod)
    #print(zahrada.zaciatky)
    # todo aby ich nebolo viac - pri STARTOCH sa to upravi samo a netreba to takto ako OPERATORY
    if int(zahrada.obvod / 4) < glob.POCET_OPERATOROV:
        glob.POCET_OPERATOROV = int(zahrada.obvod / 4)      # del. 4, 6... alebo deleno 8 ? pri 4 nasiel riesenie rychlo celkom

    return


# done
def vypisZahradu(policka):
    for x in range(0, zahrada.zahradaX):
        for y in range(0, zahrada.zahradaY):
            #print(x, y, end=', ')
            policko = policka[x][y]
            if policko == "K":
                print(farby.STONE, "", policko, farby.ENDC, end='')
            else:
                if int(policko) < 10:
                    if int(policko) == 0:
                        print(farby.SAND, "", policko, farby.ENDC, end='')
                    elif int(policko) % 3 == 0:
                        print(farby.SAND + farby.G, "", policko, farby.ENDC, end='')
                    elif int(policko) % 2 == 0:
                        print(farby.SAND + farby.B, "", policko, farby.ENDC, end='')
                    else:
                        print(farby.SAND + farby.R, "", policko, farby.ENDC, end='')
                else:
                    if int(policko) % 3 == 0:
                        print(farby.SAND + farby.C, policko, farby.ENDC, end='')
                    elif int(policko) % 2 == 0:
                        print(farby.SAND + farby.M, policko, farby.ENDC, end='')
                    else:
                        print(farby.SAND + farby.B, policko, farby.ENDC, end='')

        print()


# snad done ?
def pohrab(mnich, flag):

    kopiaZahrady = [[0 for stlpec in range(0, zahrada.zahradaY)] for riadok in range(0, zahrada.zahradaX)]
    mnich[glob.POC] = 0
    mnich[glob.KAMEN] = 0

    zaciatky = []
    smery = []

    # print("starty:", mnich[glob.START])
    # print("pohyby:", mnich[glob.OPER], "\n")

    for i in range(0, zahrada.zahradaX):        # vytvorenie docasnej zahradky
        for j in range(0, zahrada.zahradaY):
            kopiaZahrady[i][j] = zahrada.policka[i][j]

    cisloCesty = 0
    for i in range(0, len(mnich[glob.START])):     # pre vsetky zaciatky

        poz = int(mnich[glob.START][i])

        startX = aktX = zahrada.zaciatky[poz][0]      # kde mnich zacina
        startY = aktY = zahrada.zaciatky[poz][1]

        # VSTUP do zahradky -------------------------------------------------------------------------
        try:
            if kopiaZahrady[startX][startY] == 0:              # ak nebolo pohrabane

                vstup = 1      # strazi ci bol predchadzajuci krok VSTUP do zahradky

                cisloCesty += 1
                # print("ZACINAM na pozicii", poz, "- x", startY, "y", startX, "cislo cesty", cisloCesty)

                for j in range(0, len(mnich[glob.OPER])):      # pre jeho operatory - SMERY

                    posunX = pohyb.POHYB_X[mnich[glob.OPER][j]]
                    posunY = pohyb.POHYB_Y[mnich[glob.OPER][j]]

                    # print("zmena smeru", end=" ")

                    # if (mnich[glob.OPER][j] == 0):
                    #    print("DOLE")
                    # if (mnich[glob.OPER][j] == 1):
                    #    print("DOPRAVA")
                    # if (mnich[glob.OPER][j] == 2):
                    #    print("HORE")
                    # if (mnich[glob.OPER][j] == 3):
                    #    print("DOLAVA")

                    # kym je to v ramci zahradky POKRACUJ ROVNAKYM SMEROM
                    while (aktX >= 0 and aktX < zahrada.zahradaX) and (aktY >= 0 and aktY < zahrada.zahradaY):

                        # ak je to VOLNE policko -----------------------------------------------------
                        if kopiaZahrady[aktX][aktY] == 0 :
                            # print(aktX, aktY, "---", vstup)

                            kopiaZahrady[aktX][aktY] = cisloCesty  # pohrabeme
                            mnich[glob.POC] += 1                   # pripocitame
                            zaciatky.append(poz)                   # pridame kde sme ozaj boli
                            smery.append(mnich[glob.OPER][j])      # smer ktorym sme naozaj isli

                            aktX += posunX  # POSUNIEME sa
                            aktY += posunY

                            # ak sme v predoslom kroku VSTUPILI do zahradky a chceme hned ODIST (spravit protipohyb -> <-)
                            # (bez toho aby sme narazili na prekazku)
                            if vstup == 1:
                                # ak to nieje rohove policko - vtedy vie prejst dovolenym sposobom
                                if not ((aktX == 0 and aktY == 0) or (aktX == zahrada.zahradaX and aktY == zahrada.zahradaY) or (aktX == zahrada.zahradaX and aktY == 0) or (aktX == 0 and aktY == zahrada.zahradaY)) :
                                    # ak ide mimo zahradky
                                    if not ((aktX >= 0 and aktX < zahrada.zahradaX) and (aktY >= 0 and aktY < zahrada.zahradaY)):
                                        # print("nedovoleny krok")
                                        aktX -= posunX  # posunie sa naspat do zahradky
                                        aktY -= posunY
                                        kopiaZahrady[aktX][aktY] = 0  # nastavi sa to na nepohrabane
                                        mnich[glob.POC] -= 1  # cize ho ani nepocita
                                        # print("vraciam sa na", aktX, aktY)
                                        vstup = 0  # nastavenie flagu
                                        break      # dalsi cyklus - skusi dalsi smer z toho policka

                                    # todo mal by ist len tym smerom ako vstupi?  - ak hej toto odkomentovat
                                    #elif porovnajSmer(startX, startY, posunX, posunY) == 1:
                                    #    # print("nedovoleny krok")
                                    #    aktX -= posunX                  # posunie sa naspat
                                    #    aktY -= posunY
                                    #    kopiaZahrady[aktX][aktY] = 0    # nastavi sa to na nepohrabane
                                    #    mnich[glob.POC] -= 1            # cize ho ani nepocita
                                    #    # print("vraciam sa na", aktX, aktY)
                                    #    #vstup = 0                       # nastavenie flagu
                                    #    break  # dalsi cyklus - skusi dalsi smer

                            vstup = 0   # nastavenie flagu

                        # ak to NIE JE volne policko -------------------------------------------------
                        else:
                            # ak je to POSLEDNY mozny POHYB - slepa ulicka - KONIEC
                            if (j == (len(mnich[glob.OPER]) - 1)):
                                # print("ZASEKLI SME SA")

                                # aktualizacia poli
                                zaciatky = list(dict.fromkeys(zaciatky))  # odstranenie vsetkych duplikatov
                                mnich[glob.START] = zaciatky
                                #mnich[glob.OPER] = smery

                                if flag == 1:  # ak ma vypisat
                                    vypisZahradu(kopiaZahrady)
                                    #print(zaciatky)
                                return mnich[glob.POC], 1, mnich

                            # ak este VIE ZMENIT SMER
                            else:
                                # ak sme narazili na KAMEN
                                if (kopiaZahrady[aktX][aktY] == "K"):
                                    # print("KAMEN        ", aktX, aktY)
                                    mnich[glob.KAMEN] += 1        # pocet stretnutych kamenov
                                    aktX -= posunX                # posunie sa naspat pred kamen
                                    aktY -= posunY
                                    kopiaZahrady[aktX][aktY] = 0  # nastavi sa to na nepohrabane
                                    mnich[glob.POC] -= 1          # cize ho ani nepocita
                                    # print("vraciam sa na", aktX, aktY)
                                    break  # dalsi cyklus - skusi dalsi smer z policka pred kamenom

                                # ak sme narazili na POHRABANE
                                elif (kopiaZahrady[aktX][aktY] != 0):
                                    # print("pohrabane    ", aktX, aktY, "cesta", kopiaZahrady[aktX][aktY])
                                    aktX -= posunX  # posunie sa naspat pred pohrabane
                                    aktY -= posunY
                                    kopiaZahrady[aktX][aktY] = 0            # nastavi sa to na nepohrabane
                                    mnich[glob.POC] -= 1                    # cize ho ani nepocita
                                    # print("vraciam sa na", aktX, aktY)
                                    break  # dalsi cyklus - skusi dalsi smer z policka pred pohrabanym
        except IndexError:
            pass

    # ked sme sa dostali sem NEZASEKLI sme sa a skusil vsetky pokyny co mal ----------------------

    # aktualizacia poli
    zaciatky = list(dict.fromkeys(zaciatky))  # odstranenie vsetkych duplikatov
    mnich[glob.START] = zaciatky
    #mnich[glob.OPER] = smery

    if flag == 1:
        vypisZahradu(kopiaZahrady)
        #print(zaciatky)

    return mnich[glob.POC], 0, mnich


def vytvorMnicha():

    operatory = []
    starty = []

    # informacie o STARTOVACICH POLICKACH

    #while (len(starty) < glob.POCET_STARTOV):
    #    start = randint(0, zahrada.obvod - 1)
    #    starty.append(start)
    #    starty = [x[0] for x in groupby(starty)]  # odstranenie dupl. startov
    #    # starty = list(dict.fromkeys(starty))  # odstranenie vsetkych duplikatov

    for i in range(0, zahrada.obvod):   # vyeliminuju sa optom podla operandov
        starty.append(i)

    random.shuffle(starty)

    # informacie o PORADI ZMENY SMERU
    while (len(operatory) < glob.POCET_OPERATOROV):
        sanca = randint(0, 80)

        if sanca < 20:
            operator = randint(0, 1)
        elif sanca < 40:
            operator = randint(1, 3)
        elif sanca < 60:
            operator = randint(1, 2)
        else:
            operator = randint(0, 3)

        operatory.append(operator)
        operatory = [x[0] for x in groupby(operatory)]  # odstranenie dupl. operatorov (za sebou iducich asi)

    mnich = [starty, operatory, 0, 0]
    return mnich


# todo optimalizuj ?
def sparuj(rodic1, rodic2):

    poc1 = rodic1[glob.POC]            # POCET POHRABANYCH
    poc2 = rodic2[glob.POC]

    start1 = rodic1[glob.START]        # STARTOVACIE POZICIE
    start2 = rodic2[glob.START]

    oper1 = rodic1[glob.OPER]          # OPERATORY
    oper2 = rodic2[glob.OPER]

    if len(start1) > len(start2):      # LIMITY
        lim_start = len(start2)
    else:
        lim_start = len(start1)
    if len(oper1) > len(oper2):
        lim_oper = len(oper2)
    else:
        lim_oper = len(oper1)

    new_start = []
    new_oper = []

    # --------------------------------------------------------------- STARTY
    for i in range(0, lim_start):

        sanca = randint(0, 100)

        if poc1 > poc2 and sanca > 30:                  # od rodica 1
            new_start.append(rodic1[glob.START][i])
        elif poc1 > poc2 and sanca <= 30:               # od rodica 2
            new_start.append(rodic2[glob.START][i])
        elif poc1 == poc2 and sanca < 20:               # mutacia
            gen = randint(0, zahrada.obvod - 1)
            new_start.append(gen)
        else:
            gen = int((rodic1[glob.START][i] + rodic2[glob.START][i]) / 2 )
            new_start.append(gen)

    for i in range(0, 5):                               # vyvin

        sanca = randint(0, 100)

        try:

            if poc1 > poc2 and sanca > 30:  # od rodica 1
                new_start.append(rodic1[glob.START][i])
            elif poc1 > poc2 and sanca <= 30:  # od rodica 2
                new_start.append(rodic2[glob.START][i])
            elif poc1 == poc2 and sanca < 20:  # mutacia
                gen = randint(0, zahrada.obvod - 1)
                new_start.append(gen)
            else:
                gen = int((rodic1[glob.START][i] + rodic2[glob.START][i]) / 2)
                new_start.append(gen)

        except IndexError:
            pass

        # --------------------------------------------------------------- OPERATORY
        for i in range(0, lim_oper):

            sanca = randint(0, 100)

            if poc1 > poc2 and sanca > 30:  # od rodica 1
                new_start.append(rodic1[glob.OPER][i])
            elif poc1 > poc2 and sanca <= 30:  # od rodica 2
                new_start.append(rodic2[glob.OPER][i])
            elif poc1 == poc2 and sanca < 20:  # mutacia
                gen = randint(0, zahrada.obvod - 1)
                new_start.append(gen)
            else:
                gen = int((rodic1[glob.OPER][i] + rodic2[glob.OPER][i]) / 2)
                new_start.append(gen)

            new_start = [x[0] for x in groupby(new_start)]  # odstranenie dupl. operatorov (za sebou iducich asi)

        # vyvin
        while (len(new_start) < glob.POCET_OPERATOROV):
            sanca = randint(0, 80)

            if sanca < 20:
                operator = randint(0, 1)
            elif sanca < 40:
                operator = randint(1, 3)
            elif sanca < 60:
                operator = randint(1, 2)
            else:
                operator = randint(0, 3)

            new_start.append(operator)
            new_start = [x[0] for x in groupby(new_start)]  # odstranenie dupl. operatorov (za sebou iducich asi)

    potomok = [new_start, new_oper, 0, 0]
    return potomok


def elitizmus(populacia, generacia, maxMnich, maxMnichZaseknuty):
    zoradovac = lambda x: (x[glob.POC])  # zoradime podla poctu pohrabanych policok
    populacia = sorted(populacia, key=zoradovac)

    generacia += 1
    novaGeneracia = []  # najlepsich x % prezije
    pocet = int(glob.TOP_PERCENTO * len(populacia) / 100)
    novaGeneracia.extend(populacia[len(populacia) - pocet:len(populacia) + 1])

    for i in range(0, glob.POCET_MAX_MNICHOV):  # UZ MAXIMALNI
        novaGeneracia.append(maxMnich)

    for i in range(0, glob.POCET_MAX_MNICHOV_ZASEK):  # UZ MAXIMALNI - ZASEKNUTI
        novaGeneracia.append(maxMnichZaseknuty)

    for i in range(0, glob.POCET_NOVYCH_MUTACII):  # MUTACIA
        mnich = vytvorMnicha()
        novaGeneracia.append(mnich)

    while (len(novaGeneracia) < glob.POCET_MNICHOV):  # ZVYSOK SA SPARUJE Z EXISTUJUCICH

        rodic1 = random.choice(populacia[glob.ROZSAH_PAROVANIA:])
        rodic2 = random.choice(populacia[glob.ROZSAH_PAROVANIA:])

        dieta = sparuj(rodic1, rodic2)
        novaGeneracia.append(dieta)

    novaGeneracia = novaGeneracia[0:glob.POCET_MNICHOV]     # pre istotu aby sa nezvacsovala
    return novaGeneracia, generacia


def ruleta(populacia, generacia, maxMnich, maxMnichZaseknuty):
    novaGeneracia = []  # najlepsich x % prezije
    generacia += 1

    for i in range(0, glob.POCET_MAX_MNICHOV):
        novaGeneracia.append(maxMnich)

    for i in range(0, glob.POCET_MAX_MNICHOV_ZASEK):
        novaGeneracia.append(maxMnichZaseknuty)

    fitness_populacie = sum(populacia[jedinec][glob.POC] for jedinec in populacia)
    pravdepodobnost = [populacia[jedinec][glob.POC] / fitness_populacie for jedinec in populacia]

    for i in range(0, glob.POCET_NOVYCH_MUTACII):
        novaGeneracia.append(vytvorMnicha())

    while len(novaGeneracia) < glob.POCET_MNICHOV:
        rodic1 = np.random.choice(populacia, p=pravdepodobnost)
        rodic2 = np.random.choice(populacia, p=pravdepodobnost)
        dieta = sparuj(rodic1, rodic2)
        novaGeneracia.append(dieta)

    novaGeneracia = novaGeneracia[0:glob.POCET_MNICHOV]     # pre istotu aby sa nezvacsovala
    return novaGeneracia, generacia


def vyries(source):
    vytvorZahradu(source)
    vypisZahradu(zahrada.policka)
    print()

    max = 0
    max2 = 0
    maxMnich = []
    maxMnichZaseknuty = []
    populacia = []
    generacia = 1

    # ------------------------------------------------------------- PRVA GENERACIA
    for i in range(0, glob.POCET_MNICHOV_PRVA_GEN):
        mnich = vytvorMnicha()
        pocet, zaseknutie, mnich = pohrab(mnich, 0)
        populacia.append(mnich)

        if pocet > max and zaseknutie == 0:     # novi top mnichovia
            max = pocet
            maxMnich = mnich
            print("najviac pohrabanych policok je:\t", max, "/", zahrada.pocetPolicok, "\tgeneracia c.:\t", generacia, "\t(bez zaseknutia)")
            #pohrab(maxMnich, 1)  # vypis
        elif pocet > max and pocet > max2 and zaseknutie == 1:
            max2 = pocet
            maxMnichZaseknuty = mnich
            print("najviac pohrabanych policok je:\t", max2, "/", zahrada.pocetPolicok, "\tgeneracia c.:\t", generacia)
            #pohrab(maxMnichZaseknuty, 1)  # vypis

    # AK SME NASLI RIESENIE
    if glob.ZASEKNUTIE == 1 and (max == zahrada.pocetPolicok or max2 == zahrada.pocetPolicok):
        print("\nNASLI SME RIESENIE V PRVEJ GENERACII!")
        if max == zahrada.pocetPolicok:
            pohrab(maxMnich, 1)  # vypis
            print("finalny genom pre vstupy:\t", maxMnich[glob.START])
            print("finalny genom pre operatory:", maxMnich[glob.OPER])
        else:
            pohrab(maxMnichZaseknuty, 1)  # vypis
            print("finalny genom pre vstupy:\t", maxMnichZaseknuty[glob.START])
            print("finalny genom pre operatory:", maxMnichZaseknuty[glob.OPER])
    elif glob.ZASEKNUTIE == 0 and max == zahrada.pocetPolicok :
        print("\nNASLI SME RIESENIE V PRVEJ GENERACII!")
        pohrab(maxMnich, 1)  # vypis
        print("finalny genom pre vstupy:\t", maxMnich[glob.START])
        print("finalny genom pre operatory:", maxMnich[glob.OPER])

    # ----------------------------------------------------------------- DALSIE GENERACIE
    # nech sa to da lahko v kode vypnut
    elif True:
        pokracuj = 1
        while pokracuj:

            # vyber 1 - ELITIZMUS - vyber casti populacie s najvyssiou fitness
            if glob.VYBER == 1:
                novaGeneracia, generacia = elitizmus(populacia, generacia, maxMnich, maxMnichZaseknuty)
            # vyber 2 - RULETA
            else:
                novaGeneracia, generacia = elitizmus(populacia, generacia, maxMnich, maxMnichZaseknuty)

            # dalsie skusanie
            for i in range(0, len(novaGeneracia)):
                try:
                    mnich = novaGeneracia[i]

                    pocet, zaseknutie, mnich = pohrab(mnich, 0)

                    # novi top mnichovia
                    if (pocet > max) and (zaseknutie == 0):
                        max = pocet
                        maxMnich = mnich
                        print("najviac pohrabanych policok je:\t", max, "/", zahrada.pocetPolicok, "\tgeneracia c.:\t", generacia)
                        #pohrab(maxMnich, 1)
                    elif pocet > max and pocet > max2 and zaseknutie == 1:
                        max2 = pocet
                        maxMnichZaseknuty = mnich
                        print("najviac pohrabanych policok je:\t", max2, "/", zahrada.pocetPolicok, "\tgeneracia c.:\t", generacia, "\t(so zaseknutim)")
                        #pohrab(maxMnichZaseknuty, 1)
                except IndexError:
                    pass

            # AK SME NASLI RIESENIE
            if (glob.ZASEKNUTIE == 1) and (max == zahrada.pocetPolicok or max2 == zahrada.pocetPolicok):
                pokracuj = 0
                if max == zahrada.pocetPolicok:
                    print("\nNASLI SME RIESENIE ! gen.c.", generacia)
                    pohrab(maxMnich, 1)  # vypis
                    print("finalny genom pre vstupy:\t", maxMnich[glob.START])
                    print("finalny genom pre operatory:", maxMnich[glob.OPER])
                else:
                    print("\nNASLI SME RIESENIE ! gen.c.", generacia)
                    pohrab(maxMnichZaseknuty, 1)  # vypis
                    print("finalny genom pre vstupy:\t", maxMnichZaseknuty[glob.START])
                    print("finalny genom pre operatory:", maxMnichZaseknuty[glob.OPER])

            elif glob.ZASEKNUTIE == 0 and max == zahrada.pocetPolicok:
                pokracuj = 0
                print("\nNASLI SME RIESENIE ! gen.c.", generacia)
                pohrab(maxMnich, 1)  # vypis
                print("finalny genom pre vstupy:\t", maxMnich[glob.START])
                print("finalny genom pre operatory:", maxMnich[glob.OPER])

            # AK SME PRESIAHLI LIMIT
            elif generacia >= glob.LIMIT:
                pokracuj = 0
                print("\nPresiahli sme maximalny pocet generacii - najlepsie riesenie:")
                if glob.ZASEKNUTIE == 0:
                    print("pocet pohrabanych", max, "bez zaseknutia")
                    pohrab(maxMnich, 1)  # vypis
                    print("finalny genom pre vstupy:\t", maxMnich[glob.START])
                    print("finalny genom pre operatory:", maxMnich[glob.OPER])
                elif max >= max2:
                    print("pocet pohrabanych", max, "bez zaseknutia")
                    pohrab(maxMnich, 1)  # vypis
                    print("finalny genom pre vstupy:\t", maxMnich[glob.START])
                    print("finalny genom pre operatory:", maxMnich[glob.OPER])
                elif max2 > max:
                    print("pocet pohrabanych", max2, "so zaseknutim")
                    pohrab(maxMnichZaseknuty, 1)  # vypis
                    print("finalny genom pre vstupy:\t", maxMnichZaseknuty[glob.START])
                    print("finalny genom pre operatory:", maxMnichZaseknuty[glob.OPER])

    if maxMnich[glob.POC] > maxMnichZaseknuty[glob.POC]:
        pohrabanych = maxMnich[glob.POC]
    else:
        pohrabanych = maxMnichZaseknuty[glob.POC]

    return generacia, pohrabanych


if __name__ == "__main__":

    pokracuj = 1

    print(farby.B + "\n☯ 🕉️ ZEN ZAHRADA 🕉️ ☯\n" + farby.ENDC)

    # ------------------------------------------------------------------------------ MENU
    while pokracuj:

        print("\t-> pre vyber mapy a spustenie programu stlac \t\t\t(a)\n"
              "\t-> pre automatizovane testovanie stlac \t\t\t\t\t(b)\n"
              "\t-> pre spustenie zahrady zo zadania stlac \t\t\t\t(c)\n"
              "\n\t-> pre zmenu limitu maximalneho poctu generacii stlac \t(d) ")
        swtch = input()

        if swtch == "a":
            print("chcete zadat vlastny nazov suboru? (y/n) ")
            swtch = input()

            if swtch == "y":
                source = input("zadaj nazov suboru: ")
            else:
                source = "zahrada1.txt"

            print("aky sposob vyberu mnichov si zelate pouzit? \n 1 - elitizmus \n 2 - ruleta ")
            swtch = input()

            if swtch == "1":
                glob.VYBER = 1
            else:
                glob.VYBER = 2

            print("moze sa mnich na konci zaseknut v zahradke? (y/n) ")
            swtch = input()

            if swtch == "y":
                glob.ZASEKNUTIE = 1
            else:
                glob.ZASEKNUTIE = 2

            vyries(source)  # ------------------------- SPUSTENIE RIESENIA

        elif swtch == "b":
            print("Automaticke testovanie:")
            pocetMnichovTemp = glob.POCET_MNICHOV       # aby sa neprestavili trvalo hodnoty
            pocetMnichovPrvejGenTemp = glob.POCET_MNICHOV_PRVA_GEN
            rozsahParovaniaTemp = glob.ROZSAH_PAROVANIA
            pocetMaxTemp = glob.POCET_MAX_MNICHOV
            pocetMaxZasekTemp = glob.POCET_MAX_MNICHOV_ZASEK
            topPercentoTemp = glob.TOP_PERCENTO
            pocetNovychTemp = glob.POCET_NOVYCH_MUTACII

            try:
                pocetTestov = int(input("zadaj pocet testov: "))
                glob.POCET_MNICHOV_PRVA_GEN = int(input("zadaj pocet mnichov prvej generacie: (min. 6) "))
                glob.POCET_MNICHOV = int(input("zadaj pocet mnichov jednej generacie: (min. 6) "))
                glob.ZASEKNUTIE = int(input("pre moznost ukoncenia trasy v zahrade stlac (1), inak stlac (0) "))
            except ValueError:
                print("zle zadane hodnoty - budu doplnene automaticky")
                pocetTestov = 10

            if glob.POCET_MNICHOV < 6 or glob.POCET_MNICHOV_PRVA_GEN < 6:               # ak mame dost mnichov na testy
                print("nebol zadany dostatocny pocet mnichov pre spustenie testov")
            else:

                if glob.ROZSAH_PAROVANIA >= glob.POCET_MNICHOV_PRVA_GEN:        # aby nedoslo k chybam indeacie pre zle nastavenie rozsahov
                    glob.ROZSAH_PAROVANIA = glob.POCET_MNICHOV_PRVA_GEN - 1
                elif glob.ROZSAH_PAROVANIA >= glob.POCET_MNICHOV:
                    glob.ROZSAH_PAROVANIA = glob.POCET_MNICHOV - 1

                pocetRuleta = int(pocetTestov/2)                # vypocet pre testy
                pocetElit = int(pocetTestov/2)

                generacieRuleta = 0
                generacieElit = 0

                pohrabanychRuleta = 0
                pohrabanychElit = 0

                test_no = 1

                startRuleta = time.time()
                glob.VYBER = 2
                for i in range(0, pocetRuleta):
                    print("\ntest", test_no, "/", pocetTestov, "- ruleta")
                    test, pohrabanych = vyries("zahrada1.txt")
                    generacieRuleta += test
                    pohrabanychRuleta += pohrabanych
                    test_no += 1
                endRuleta = time.time()
                casRuleta = (endRuleta - startRuleta) / pocetRuleta / 60

                startElit = time.time()
                glob.VYBER = 1
                for i in range(0, pocetElit):
                    print("\ntest", test_no, "/", pocetTestov, "- elit.")
                    test, pohrabanych = vyries("zahrada1.txt")
                    generacieElit += test
                    pohrabanychElit += pohrabanych
                    test_no += 1
                endElit = time.time()
                casElit = (endElit - startElit) / pocetElit / 60

                vysledokRuleta = generacieRuleta / pocetRuleta
                vysledokElit = generacieElit / pocetElit

                vysledokPohrabRuleta = pohrabanychRuleta / pocetRuleta
                vysledokPohrabElit = pohrabanychElit / pocetElit

            glob.ZASEKNUTIE = 1                         # vratenie povodnych hodnot
            glob.POCET_MNICHOV = pocetMnichovTemp
            glob.POCET_MNICHOV_PRVA_GEN = pocetMnichovPrvejGenTemp
            glob.ROZSAH_PAROVANIA = rozsahParovaniaTemp
            glob.POCET_MAX_MNICHOV = pocetMaxTemp
            glob.POCET_MAX_MNICHOV_ZASEK = pocetMaxZasekTemp
            glob.TOP_PERCENTO = topPercentoTemp
            glob.POCET_NOVYCH_MUTACII = pocetNovychTemp

            print(farby.B + "\nVysledok pre", pocetTestov, "testov: \npocet generacii na riesenie pri vybere ruletou:\t ", vysledokRuleta, "; priemerne pohrabanych\t", vysledokPohrabRuleta, "/ 114 policok, priemerny cas na zahradku:\t", casRuleta, "min", "\npocet generacii na riesenie pri vybere elitizmom:", vysledokElit, "; priemerne pohrabanych\t", vysledokPohrabElit, "/ 114 policok, priemerny cas na zahradku:\t", casElit, "min", farby.ENDC)

        elif swtch == "c":
            glob.ZASEKNUTIE = 1
            glob.VYBER = 2
            vyries("zahrada1.txt")

        elif swtch == "d":
            print("aktualny limit generacii je:", glob.LIMIT)
            glob.LIMIT = int(input("zadajte novy limit: "))

        else:
            print("nerozpoznany prikaz")

        print("\nzelate si pokracovat? (y/n) ")
        swtch = input()

        if swtch == "y":
            swtch = 1
        else:
            break