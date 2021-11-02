import random
import time


class farby:  # trieda na pracovanie s farbami
    C = '\u001b[40;1m'
    CE = '\u001b[40;1m\u001b[31;1m'

    B = '\u001b[47;1m\u001b[30;1m'
    BE = '\u001b[47;1m\u001b[31m'

    S = '\u001b[42m\u001b[30;1m'
    ENDC = '\033[0m'


class temp:  # trieda s globalnymi premennymi
    maxKrok = 0     # pri ciastocnom rieseni - kam sme sa dostali najdalej
    maxSachovnica = [["x" for stlpec in range(0, 20)] for riadok in range(0, 20)]
    cas = 0         # na pocitanie casu
    tl = 0          # flag ci bol prekroceny casovy limit


class stat:  # statisticke udaje
    poc_5 = 0  # pocet testov 5x5
    poc_6 = 0  # pocet testov 6x6
    poc_ine = 0
    poc_overall = 0

    start_b_5 = 0  # pocet startov z cierneho policka (5x5)
    start_b_6 = 0  # pocet startov z cierneho policka (6x6)
    start_b_ine = 0
    start_b_overall = 0

    tle_6 = 0  # time limit exceeded pre velkost 6x6
    tle = 0

    end_b_5 = 0  # pocet uspesnych ukonceni z cierneho policka (5x5)
    end_b_6 = 0  # pocet uspesnych ukonceni z cierneho policka (6x6)
    end_b_ine = 0
    end_b_overall = 0

    start_w_5 = 0  # pocet startov z bieleho policka (5x5)
    start_w_6 = 0  # pocet startov z bieleho policka (6x6)
    start_w_ine = 0
    start_w_overall = 0

    end_w_5 = 0  # pocet uspesnych ukonceni z bieleho policka (5x5)
    end_w_6 = 0  # pocet uspesnych ukonceni z bieleho policka (6x6)
    end_w_ine = 0
    end_w_overall = 0

    end_ok = 0

    time_ok_5 = 0  # celkovy cas na najdenie riesenia (5x5)
    time_ok_6 = 0  # celkovy cas na najdenie riesenia (6x6)
    time_overall = 0


class glob:  # staticke globalne premenne
    TIMELIMIT = 16
    # pohyb todo vymysliet poradie
    # POSUN_X = [1, 2, -1, -2, -1, -2, 1, 2]            # verzia 1
    # POSUN_Y = [2, 1, 2, 1, -2, -1, -2, -1]
    POSUN_X = [-1, 1, 2, -2, -2, 2, 1, -1]              # verzia 2
    POSUN_Y = [2, 2, 1, 1, -1, -1, -2, -2]


def vypis(sachovnica, velkost):  # vypis vysledku
    for i in range(0, velkost):
        for j in range(0, velkost):
            cislo = sachovnica[i][j]
            if cislo == "x":
                if isBlack(i, j) == 1:
                    print(farby.CE, " x", farby.ENDC, end='')
                else:
                    print(farby.BE, " x", farby.ENDC, end='')
            elif cislo < 10:
                if cislo == 1:
                    print(farby.S, "0", end='')
                    print(cislo, farby.ENDC, end='')
                elif (i % 2 == 1 and j % 2 == 1) or (i % 2 == 0 and j % 2 == 0):
                    print(farby.C, "0", end='')
                    print(cislo, farby.ENDC, end='')
                else:
                    print(farby.B, "0", end='')
                    print(cislo, farby.ENDC, end='')
            else:
                if (i % 2 == 1 and j % 2 == 1) or (i % 2 == 0 and j % 2 == 0):
                    print(farby.C, cislo, farby.ENDC, end='')
                else:
                    print(farby.B, cislo, farby.ENDC, end='')
        print()


def isBlack(x, y):  # kontrola farby policka
    if (x % 2 == 1 and y % 2 == 1) or (x % 2 == 0 and y % 2 == 0):
        return 1
    else:
        return 0


def updateStat(start, velkost, startX, startY, flag):  # aktualizacia statistiky
    stat.poc_overall += 1  # pocet testov
    if velkost == 5:
        stat.poc_5 += 1
        if flag == 1:  # cas
            stat.time_ok_5 += (time.time() - start)
        stat.time_overall += (time.time() - start)
    elif velkost == 6:
        stat.poc_6 += 1
        if flag == 1:  # cas
            stat.time_ok_6 += (time.time() - start)
        stat.time_overall += (time.time() - start)
    else:
        stat.poc_ine += 1
        stat.time_overall += (time.time() - start)

    if isBlack(startX, startY) == 1:  # vychodiskovy bod
        stat.start_b_overall += 1
        if velkost == 5:
            stat.start_b_5 += 1
            if flag == 1:  # dokoncenie - ok
                stat.end_b_5 += 1
                stat.end_b_overall += 1
        elif velkost == 6:
            stat.start_b_6 += 1
            if flag == 1:  # dokoncenie - ok
                stat.end_b_6 += 1
                stat.end_b_overall += 1
        else:
            stat.start_b_ine += 1
            if flag == 1:  # dokoncenie - ok
                stat.end_b_ine += 1
                stat.end_b_overall += 1
    else:
        stat.start_w_overall += 1
        if velkost == 5:
            stat.start_w_5 += 1
            if flag == 1:  # dokoncenie - ok
                stat.end_w_5 += 1
                stat.end_w_overall += 1
        elif velkost == 6:
            stat.start_w_6 += 1
            if flag == 1:  # dokoncenie - ok
                stat.end_w_6 += 1
                stat.end_w_overall += 1
        else:
            stat.start_w_ine += 1
            if flag == 1:  # dokoncenie - ok
                stat.end_w_ine += 1
                stat.end_w_overall += 1

    if flag == 3:  # presiahnutie casoveho limitu
        stat.tle += 1
        if velkost == 6:
            stat.tle_6 += 1

    stat.end_ok = stat.end_w_overall + stat.end_b_overall
    return


def vypisStat():  # vypis statstiky
    print("\nStatistika -----------------------------------------------------------")
    try:
        print("celkovy cas:", "{:.2f}".format(stat.time_overall), "s, casovy limit:", glob.TIMELIMIT, "\n")

        print("celkovy pocet testov: ", stat.poc_overall, "\t", stat.poc_overall * "*")
        print("\tz toho uspesnych: ", stat.end_ok, "\t", stat.end_ok * "*")
        print("\ta neuspesnych:\t  ", (stat.poc_overall - stat.end_ok), "\t", (stat.poc_overall - stat.end_ok) * "*")
        print("\tz toho TLE:\t\t  ", stat.tle, "\t", stat.tle * "*")
        print("priemerny cas na riesenie:\t", "{:.2f}".format(stat.time_overall / stat.poc_overall), "s")

        print("\npocet testov sachovnice velkosti 5x5:  ", stat.poc_5, "\t", stat.poc_5 * "*")
        print("\tpoc. uspesnych zac. v bielom poli: ", stat.end_w_5, "\t", stat.end_w_5 * "*")
        print("\tpoc. uspesnych zac. v ciernom poli:", stat.end_b_5, "\t", stat.end_b_5 * "*")
        print("\tpoc. neuspesnych testov pre rozmer:", (stat.poc_5 - stat.end_w_5 - stat.end_b_5), "\t",
              (stat.poc_5 - stat.end_w_5 - stat.end_b_5) * "*")
        print("priemerny cas na uspesne riesenie:\t   ", "{:.2f}".format(stat.time_ok_5 / stat.poc_5), "s")

        print("\npocet testov sachovnice velkosti 6x6:  ", stat.poc_6, "\t", stat.poc_6 * "*")
        print("\tpoc. uspesnych zac. v bielom poli: ", stat.end_w_6, "\t", stat.end_w_6 * "*")
        print("\tpoc. uspesnych zac. v ciernom poli:", stat.end_b_6, "\t", stat.end_b_6 * "*")
        print("\tpoc. neuspesnych testov pre rozmer:", (stat.poc_6 - stat.end_w_6 - stat.end_b_6), "\t",
              (stat.poc_6 - stat.end_w_6 - stat.end_b_6) * "*")
        print("\t\t\t\t\t\t\tz toho TLE:", stat.tle_6, "\t", stat.tle_6 * "*")
        print("priemerny cas na uspesne riesenie:\t   ", "{:.2f}".format(stat.time_ok_6 / stat.poc_6), "s")

        print("\npocet testov pre ine velkosti:", stat.poc_ine, "\t", stat.poc_ine * "*")

    except ZeroDivisionError:
        print("\nNedostatok testov pre kompletnu statistiku")

    print("\n----------------------------------------------------------------------")

    return


def checkTime():  # kontrola casu
    # ak sme presiahli cas
    temp.cas = time.time()
    if (temp.cas - start) > glob.TIMELIMIT:
        temp.tl = 1
        return 1  # ak sme presiahli cas
    else:
        return 0  # ak sme nepresiahli cas


def inicializuj(start, sachovnica, velkost, startX, startY):  # pomocna funkcia na inicializovnaie premennych

    if velkost < 4:
        return 0

    else:
        pocetPolicok = velkost * velkost

        # sachovnica pre ciastocne riesenia
        temp.maxSachovnica = [["x" for stlpec in range(0, 20)] for riadok in range(0, 20)]
        temp.maxKrok = 0

        # prva pozicia
        sachovnica[startX][startY] = cisloKroku = temp.maxSachovnica[startX][startY] = 1

        # riesenie problemu
        hladajRiesenie(start, startX, startY, sachovnica, velkost, pocetPolicok, startX, startY, cisloKroku)

    return


def hladajRiesenie(start, startX, startY, sachovnica, velkost, pocetPolicok, aktPozX, aktPozY, cisloKroku):
    if (checkTime()):
        return 0

    # EXIT 1
    elif (cisloKroku == pocetPolicok):  # NASLI SME RIESENIE
        # vynulovanie casu
        temp.cas = 0
        print("\nOK")
        vypis(sachovnica, velkost)
        updateStat(start, velkost, startX, startY, 1)
        return 1

    # dalsi pokus
    else:
        for i in range(0, 8):
            dalsieX = aktPozX
            dalsieX += glob.POSUN_X[i]
            dalsieY = aktPozY
            dalsieY += glob.POSUN_Y[i]

            # ak to nieje mimo sachovnice
            if (dalsieX >= 0 <= dalsieY < velkost > dalsieX):
                if (sachovnica[dalsieX][dalsieY] == "x"):  # ak sme tam este neboli

                    # nastavenie hodnoty v poli
                    sachovnica[dalsieX][dalsieY] = (cisloKroku + 1)

                    # pre neuplnu sachovnicu todo check ci to nejde lepsie
                    if (cisloKroku > temp.maxKrok):
                        for k in range(0, velkost):
                            for l in range(0, velkost):
                                temp.maxSachovnica[k][l] = sachovnica[k][l]
                                temp.maxKrok = cisloKroku
                                # print("krok", cisloKroku)
                    else:
                        pass

                    # ak je to dobry krok riesenia
                    if (hladajRiesenie(start, startX, startY, sachovnica, velkost, pocetPolicok, dalsieX, dalsieY,
                                       cisloKroku + 1)):
                        return 1  # a pokracujeme dalej
                    else:  # ak nebol "vratime sa"
                        sachovnica[dalsieX][dalsieY] = "x"
                else:
                    pass
            else:
                pass

        # EXIT 2
        if (temp.tl == 0 and startX == aktPozX and startY == aktPozY and i == 7):
            #  AK SME SA DOSTALI AZ SEM NEMAME RIESENIE
            # vynulovanie casu
            temp.cas = 0
            updateStat(start, velkost, startX, startY, 2)
            print("\nRiesenie nenajdene")
            vypis(temp.maxSachovnica, velkost)
            # vynulovanie casu
            temp.cas = 0

        # EXIT 3
        if (temp.tl == 1 and startX == aktPozX and startY == aktPozY and i == 7):
            #  AK SME PRESIAHLI CASOVY LIMIT
            # vynulovanie casu
            temp.cas = 0
            updateStat(start, velkost, startX, startY, 3)
            print("\nCasovy limit presiahnuty")
            temp.tl = 0
            vypis(temp.maxSachovnica, velkost)
            # vynulovanie casu
            temp.cas = 0

    return 0


if __name__ == "__main__":

    k = ""

    while k != "x":
        print("\nMENU"
              "\n\t-> pre manualny vstup stlac\t\t\t(a)"
              "\n\t-> pre automaticke testovanie stlac\t(b)"
              "\n\t-> pre test vsetkych moznosti stlac\t(c)"
              "\n\n\t-> pre upravu casoveho limitu stlac\t(d)"
              "\n\n\t-> pre vypis statistiky stlac\t\t(e)"
              "\n\n\t-> pre ukoncenie programu stlac\t\t(x)")
        k = input()
        if k == "a":  # ---------------------------------------------------------------------------
            try:
                velkost: int
                velkost = int(input("\nZadaj velkost sachovnice: "))
                if velkost > 3:
                    print("Zadaj startovaciu poziciu x ( 0 az", velkost - 1, "): ")
                    x = int(input())
                    print("Zadaj startovaciu poziciu y ( 0 az", velkost - 1, "): ")
                    y = int(input())

                    # ak je to v ramci sachovnice
                    if (0 <= x < velkost > y >= 0):
                        # inicializacia podla https://www.kite.com/python/answers/how-to-initialize-a-2d-array-in-python
                        sachovnica = [["x" for stlpec in range(0, velkost)] for riadok in range(0, velkost)]

                        start = time.time()
                        inicializuj(start, sachovnica, velkost, x, y)
                        end = time.time()
                        print("cas:", "{:.2f}".format(end - start), "s")

                    else:
                        print("Nespravny udaj o startovacej pozicii\n")
                        pass
                else:
                    print("Sachovnica je prilis mala")
                    pass

            except ValueError:
                pass

        elif k == "b":  # ---------------------------------------------------------------------------
            print("\nTesty pre sachovnicu 5x5")
            sachovnica1 = [["x" for stlpec in range(0, 5)] for riadok in range(0, 5)]

            start = time.time()
            inicializuj(start, sachovnica1, 5, 4, 0)
            end = time.time()
            print("cas:", "{:.2f}".format(end - start), "s")

            for i in range(0, 4):
                x = random.randint(0, 4)
                y = random.randint(0, 4)
                sachovnica2 = [["x" for stlpec in range(0, 5)] for riadok in range(0, 5)]

                start = time.time()
                inicializuj(start, sachovnica2, 5, x, y)
                end = time.time()
                print("cas:", "{:.2f}".format(end - start), "s")

            print("\nTesty pre sachovnicu 6x6")
            sachovnica3 = [["x" for stlpec in range(0, 6)] for riadok in range(0, 6)]

            start = time.time()
            inicializuj(start, sachovnica3, 6, 5, 0)
            end = time.time()
            print("cas:", "{:.2f}".format(end - start), "s")

            for i in range(0, 4):
                x = random.randint(0, 5)
                y = random.randint(0, 5)
                sachovnica4 = [["x" for stlpec in range(0, 6)] for riadok in range(0, 6)]

                start = time.time()
                inicializuj(start, sachovnica4, 6, x, y)
                end = time.time()
                print("cas:", "{:.2f}".format(end - start), "s")

            pass

        elif k == "c":  # ---------------------------------------------------------------------------
            try:
                velkost: int
                velkost = int(input("\nZadaj velkost sachovnice: "))

                for i in range(0, velkost):
                    for j in range(0, velkost):
                        sachovnica = [["x" for stlpec in range(0, velkost)] for riadok in range(0, velkost)]

                        start = time.time()
                        inicializuj(start, sachovnica, velkost, i, j)
                        end = time.time()
                        print("cas:", "{:.2f}".format(end - start), "s")

            except ValueError:
                pass

        elif k == "d":  # ---------------------------------------------------------------------------
            print("casovy limit =", glob.TIMELIMIT)

            try:
                nTL = float(input("Zadaj novy casovy limit: "))
                glob.TIMELIMIT = nTL
                print()
            except ValueError:
                print("Nespravna hodnota")

        elif k == "e":  # ---------------------------------------------------------------------------
            vypisStat()

        elif k == "x":
            print("Dovidenia")
