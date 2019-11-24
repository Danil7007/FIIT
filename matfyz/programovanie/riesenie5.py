# 5. zadanie: zoznamy
# autor: Jakub Toma
# datum: 28.11.2018

def pocet_zoznamov(zoznam):
    pocet=1
    for prvok in zoznam:
        if type(prvok) == list:
            pocet+=1
    print(pocet)


def zoznam_prvkov(zoznam):
    zoz = []
    for prvok in zoznam:
        if type(prvok) != list:
            zoz.append(prvok)
        else:
            for prvok_v_zozname in zoznam_prvkov(prvok):
                zoz.append(prvok_v_zozname)
    return zoz

def splosti(zoznam):
    zoz = []
    for prvok in zoznam:
        if type(prvok) != list:
            zoz.append(prvok)
        else:
            for prvok_v_zozname in zoznam_prvkov(prvok):
                zoz.append(prvok_v_zozname)

    ind = 0
    for i in range (len(zoznam)):
        zoznam[ind] = zoz[ind]
        ind += 1

def nahradeny_zoznam(zoznam, hodnota1, hodnota2):
    zoz = []
    for prvok in zoznam:
        if type(prvok) != list:
            if prvok == hodnota1:
                zoz.append(hodnota2)
            else:
                zoz.append(prvok)
        else:
            zoz.append(nahradeny_zoznam(prvok, hodnota1, hodnota2))

    return zoz

def nahrad(zoznam, hodnota1, hodnota2):
    zoz = []
    for prvok in zoznam:
        if type(prvok) != list:
            if prvok == hodnota1:
                zoz.append(hodnota2)
            else:
                zoz.append(prvok)
        else:
            zoz.append(nahradeny_zoznam(prvok, hodnota1, hodnota2))

    ind = 0
    for i in range (len(zoznam)):
        zoznam[ind] = zoz[ind]
        ind += 1





