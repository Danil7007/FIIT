# 3. zadanie: najcastejsie
# autor: Mário Chebeň
# datum: 15.11.2019
tab = []

def citaj(meno_suboru):
    zoznam2 = []
    slovo = ''
    slovko = ''
    with open(meno_suboru,'r',encoding='utf-8')as subor:
        text = subor.readlines()
        for riadok in text:
            for znak in riadok:
                slovko += znak
        zoznam = slovko.split()
        for slovo in zoznam:
            if not slovo in zoznam2:
                pocet_rovnakych_slov = zoznam.count(slovo)
                dvojica = slovo, pocet_rovnakych_slov
                zoznam2.append(slovo)
                tab.append(list(dvojica))

def pocet_vyskytov(slovo):
    pocet = 0
    for dvojica in tab:
        if dvojica[0] == slovo:
            pocet += 1
    return pocet



def zoznam_najcastejsich():
    zoznam = []
    maximum = 0
    for dvojica in tab:
        if dvojica[1] > maximum:
            maximum = dvojica[1]
    for i in range(len(tab)):
        if tab[i][1] == maximum:
            zoznam.append((tab[i][0]))
    return zoznam

def zoznam_s_poctom(n):
    zoznam = []
    for i in range(len(tab)):
        if tab[i][1] == n:
            zoznam.append((tab[i][0]))
    return zoznam

def zoznam_najdlhsich():
    zoznam = []
    maximum = 0
    for dvojica in tab:
        if len(dvojica[0]) > maximum:
            maximum = len(dvojica[0])
    for i in range(len(tab)):
        if len(tab[i][0]) == maximum:
            zoznam.append((tab[i][0]))
    return zoznam

def zoznam_najkratsich():
    zoznam = []
    najmensie = len(tab)
    for dvojica in tab:
        if len(dvojica[0]) < najmensie:
            najmensie = len(dvojica[0])
    for i in range(len(tab)):
        if len(tab[i][0]) == najmensie:
            zoznam.append((tab[i][0]))
    return zoznam

def zoznam_s_dlzkou(n):
    zoznam = []
    for i in range(len(tab)):
        if len(tab[i][0]) == n:
            zoznam.append((tab[i][0]))
    return zoznam


if __name__ == '__main__':
    citaj('text1.txt')
    print('pocet vyskytov "the":', pocet_vyskytov('the'))
    print('najcastejsie:', zoznam_najcastejsich())
    print('najdlhsie:', zoznam_najdlhsich())
    print('najkratsie:', zoznam_najkratsich())
    print('len s poctom 5:', zoznam_s_poctom(5))
    print('len s poctom 10:', zoznam_s_poctom(10))
    print('len s dlzkou 10:', zoznam_s_dlzkou(10))
    print('pocet roznych slov =', len(tab))