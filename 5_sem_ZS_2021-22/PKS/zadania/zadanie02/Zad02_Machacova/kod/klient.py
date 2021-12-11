import os
import threading
from time import sleep

import main

import math
import socket
import zlib


class glob:
    SERVERIP = "localhost"      # defaultne hodnoty ak pouzivatel zada nespravny vstup
    SERVERPORT = 10000
    DEF_VELKOST_FRAGMENTU = 20
    TIMEOUT = 20

    TEXT_MSG = 1                # typy hlaviciek
    DATA_MSG = 2
    REQ_TXT = 3
    REQ_DATA = 4
    ACK = 5
    NACK = 6
    CHANGE = 7
    KEEPALIVE = 8

    TRESHOLD = 5                # kolko sprav posle v jednom okne


class farby:
    B = '\u001b[34m'
    M = '\u001b[35m'
    Y = '\u001b[33m'
    C = '\u001b[36m'
    R = '\u001b[31m'
    ENDC = '\u001b[0m'


# informacie o serveri, ktore klient zisti z ich komunikacie / vstupov ...
class serverInfo:
    server_adress = (glob.SERVERIP, glob.SERVERPORT)      # ak uzivatel da vstup zmeni sa to, toto je def hodnota
    serverConnected = 0                                   # ci mame nadviazane spojenie so serverom - NENULOVAT
    keepaliveWait = 0                                     # ci spolu akurat komunikuju ( 0 = keepalive nie je zastaveny)


class klientInfo:
    fName = None                # nazov suboru
    pth = None                  # kde sa u klienta nachadza
    sprava = ""                 # to co chce poslat pouzivatel
    buffer = []                 # queue fragmentov co sa maju poslat
    uvodnaSprava = b''          # sprava na nadviazanie spojenia so serverom
    pocetFragmentov = 0         # v kolkych fragmentoch to je
    typKomunikacie = 0          # 1 - sprava zo stdin, 2 - subor
    lastSent = 1                # last sent sn
    pocetDavok = 0              # v kolkych davkach sa bude posielat sprava
    pocetPoslanych = 0          # pocet poslanych davok fragmentov
    klientRun = 0               # info ci je vytvoreny klient
    port = 0                    # klient port
    posliChybu = 0              # info ci ma poslat aj chybny fragment (0 nie 1 ano)
    pocetnostChyb = 5           # ako casto ma poslat chybu
    serverSetup = 0             # ci sme nastavili info na odosielanie
    pocetKeepalive = 0          # keepalive counter


# ------------------------------------------------------------------------------- FUNKCIE

# ------------------------------------------------- INE
# vynulovanie premennych pre dalsiu komunikaciu
def vynuluj():                                          # todo na zaver aktualizovat
    klientInfo.fName = None
    klientInfo.pth = None
    klientInfo.sprava = ""
    klientInfo.buffer = []
    klientInfo.uvodnaSprava = b''
    klientInfo.pocetFragmentov = 0
    klientInfo.typKomunikacie = 0
    klientInfo.lastSent = 1
    klientInfo.pocetDavok = 0
    klientInfo.pocetPoslanych = 0
    klientInfo.klientRun = 0
    klientInfo.port = 0
    klientInfo.posliChybu = 0
    klientInfo.pocetnostChyb = 5
    klientInfo.pocetKeepalive = 0

    serverInfo.server_adress = (glob.SERVERIP, glob.SERVERPORT)
    serverInfo.keepaliveWait = 0


# ------------------------------------------------- SPRACOVANIE DAT
# add do bufferu fragmenty aj s ich hlavickami
def vytvorFragmenty(fragment, i):
    # tvar: TYP | DLZKA FRAGMENTU | POCET FRAGMENTOV | SEQUENCE NUMBER | CRC | data
    # todo edit # tvar: TYP | SEQUENCE NUMBER | CRC | data

    typ = klientInfo.typKomunikacie.to_bytes(4, byteorder="big")
    dlzka = len(fragment).to_bytes(4, byteorder="big")
    pocetFragmentov = klientInfo.pocetFragmentov.to_bytes(4, byteorder="big")
    sequenceNumber = i.to_bytes(4, byteorder="big")

    hlavicka = typ + dlzka + pocetFragmentov + sequenceNumber  # este treba pridat CRC

    # encoding
    if isinstance(fragment, str):
        fragment = fragment.encode("utf-8")

    crc = zlib.crc32(fragment) & 0xffffffff                    # zo spravy spravime CRC
    crc = crc.to_bytes(4, byteorder="big")

    hlavicka = hlavicka + crc                                  # pridanie CRC do hlavicky

    finalFragment = hlavicka + fragment                        # hlavicka + fragment (sprava)

    return (finalFragment)


# posekanie spravy na fragmenty
def spracujSpravu():
    fragmenty = []

    # posekanie dat na fragmenty
    if klientInfo.typKomunikacie == glob.TEXT_MSG:
        fragmenty = [klientInfo.sprava[i:i + glob.DEF_VELKOST_FRAGMENTU] for i in range(0, len(klientInfo.sprava), glob.DEF_VELKOST_FRAGMENTU)]
    else:
        print(farby.M + "\n-> pockajte prosim, spracuvam subor" + farby.ENDC)
        try:
            with open(klientInfo.sprava, 'rb') as subor:
                while True:
                    fragment = subor.read(glob.DEF_VELKOST_FRAGMENTU)
                    if not fragment:
                        break
                    fragmenty.append(fragment)
        except FileNotFoundError:
            pass

    klientInfo.pocetFragmentov = len(fragmenty)

    # spracovanie fragmentov
    for i in range(0, klientInfo.pocetFragmentov):
        fragment = fragmenty[i]
        finalFragment = vytvorFragmenty(fragment, i + 1)  # aby SN zacinalo od 1

        # print("finalny fragment", finalFragment)

        # typ = int.from_bytes(finalFragment[0:4], "big")                 # kontrola
        # dlzkaFragmentu = int.from_bytes(finalFragment[4:8], "big")
        # pocetFragmentov = int.from_bytes(finalFragment[8:12], "big")
        # sequenceNumber = int.from_bytes(finalFragment[12:16], "big")
        # crc = int.from_bytes(finalFragment[16:20], "big")

        # print("typ:", typ, "dlzka fragmentu:", dlzkaFragmentu, "pocet fragmentov:", pocetFragmentov, "seq. number:", sequenceNumber, "crc:", crc)

        klientInfo.buffer.append(finalFragment)  # obsahuje fragmenty sprav


# vytvorenie uvodnej spravy na nadviazanie spojenia
def vytvorUvodnuSpravu():
    # tvar: TYP | DLZKA DATA | POCET FRAGMENTOV | CELKOVE CRC | (nazov)
    uvodnaSprava = sprava = typ = ""

    if klientInfo.typKomunikacie == glob.TEXT_MSG:            # typ zavisi od toho, co sa bude posielat
        typ = glob.REQ_TXT.to_bytes(4, byteorder="big")
    elif klientInfo.typKomunikacie == glob.DATA_MSG:
        typ = glob.REQ_DATA.to_bytes(4, byteorder="big")

    dlzka = len(klientInfo.sprava).to_bytes(4, byteorder="big")
    pocetFragmentov = klientInfo.pocetFragmentov.to_bytes(4, byteorder="big")

    if isinstance(klientInfo.sprava, str):                    # zistenie CRC pre celu spravu
        sprava = klientInfo.sprava.encode("utf-8")

    celkoveCrc = zlib.crc32(sprava) & 0xffffffff
    celkoveCrc = celkoveCrc.to_bytes(4, byteorder="big")

    if klientInfo.typKomunikacie == glob.TEXT_MSG:            # ak je to text zo stdin
        uvodnaSprava = typ + dlzka + pocetFragmentov + celkoveCrc
    elif klientInfo.typKomunikacie == glob.DATA_MSG:          # ak je to subor
        fName = klientInfo.fName
        fName = fName.encode("utf-8")
        uvodnaSprava = typ + dlzka + pocetFragmentov + celkoveCrc + fName

    klientInfo.uvodnaSprava = uvodnaSprava


# pokazi fragment
def corruptData(data):

    # print("----------------------------------------------------------------------------")

    typ = int.from_bytes(data[0:4], "big")                          # rozbalenie
    dlzkaFragmentu = int.from_bytes(data[4:8], "big")
    pocetFragmentov = int.from_bytes(data[8:12], "big")
    sequenceNumber = int.from_bytes(data[12:16], "big")
    crc = int.from_bytes(data[16:20], "big")

    # recMsg = data[20:]
    # recMsg = recMsg.decode('utf-8')
    # dlzka = len(recMsg)

    corruptedMsg = glob.DEF_VELKOST_FRAGMENTU * "§"

    typ = typ.to_bytes(4, byteorder="big")    # zabalenie
    dlzkaFragmentu = dlzkaFragmentu.to_bytes(4, byteorder="big")
    pocetFragmentov = pocetFragmentov.to_bytes(4, byteorder="big")
    sequenceNumber = sequenceNumber.to_bytes(4, byteorder="big")
    crc = crc.to_bytes(4, byteorder="big")
    corruptedMsg = corruptedMsg.encode("utf-8")

    finalFragment = typ + dlzkaFragmentu + pocetFragmentov + sequenceNumber + crc + corruptedMsg

    return (finalFragment)


# ------------------------------------------------- SPOJENIE A KOMUNIKACIA
# uvodne nadviazanie spojenia so serverom
def nadviazSpojenie(klientSock):
    odpoved = -1

    try:
        klientSock.sendto(klientInfo.uvodnaSprava, serverInfo.server_adress)
        print(farby.M + "\n-> posielam ziadost o potvrdenie nadviazania spojenia" + farby.ENDC)
        odpoved = getOdpovedServeru(klientSock, klientInfo.typKomunikacie)
    except TypeError:
        pass

    return odpoved


# chceck ci server poslal odpoved
def getOdpovedServeru(klientSock, typKomunikacie):
    recData = b''

    if typKomunikacie != glob.KEEPALIVE:
        print(farby.M + "-> cakam odpoved serveru" + farby.ENDC)

    try:

        try:
            klientSock.settimeout(glob.TIMEOUT)
            recData, serverInfo.server_adress = klientSock.recvfrom(4096)
        except ConnectionError:
            # EXIT
            print(farby.M + "\n-> nepodarilo sa kontaktovat server", farby.ENDC)
            vynuluj()
            serverInfo.serverConnected = 0
            taskMenu(klientSock)

    except socket.timeout:
        # EXIT
        print(farby.R + "\n-> SERVER TIMED OUT" + farby.ENDC)
        vynuluj()
        klientSock.close()
        serverInfo.serverConnected = 0
        klient()

    try:
        typ = int.from_bytes(recData[0:4], "big")

        if len(recData) > 0:
            if typ == glob.ACK:
                print(farby.B + "-> zachytenych %s b od %s - ACK" % (len(recData), serverInfo.server_adress), farby.ENDC)
                return 1                # pre uspesne odoslanie
            else:
                print(farby.R + "-> zachytenych %s b od %s - NACK" % (len(recData), serverInfo.server_adress), farby.ENDC)
                return 0
        else:
            return 0

    except UnboundLocalError:
        pass


# ACK <-> ACK
def checkServer(klientSock, typKomunikacie):
    # tvar: TYP | 0000
    typ = glob.ACK.to_bytes(4, byteorder="big")
    telo = int(0).to_bytes(4, byteorder="big")

    sprava = typ + telo                                         # poslanie ACK

    try:
        klientSock.sendto(sprava, serverInfo.server_adress)
        if typKomunikacie != glob.KEEPALIVE:
            print(farby.M + "\n-> posielam ziadost o potvrdenie prijatia packetov" + farby.ENDC)
        else:
            print(farby.M + "\n-> posielam KEEPALIVE" + farby.ENDC)

        odpoved = getOdpovedServeru(klientSock, typKomunikacie)
        return odpoved

    except OSError:
        pass  # pre istotu


# posle ziadost o vymenu roli
def posliChangeReq(klientSock):
    # tvar: TYP | 0000
    typ = glob.CHANGE.to_bytes(4, byteorder="big")
    telo = int(0).to_bytes(4, byteorder="big")

    sprava = typ + telo                                         # poslanie CHANGE REQ

    klientSock.sendto(sprava, serverInfo.server_adress)

    print(farby.M + "\n-> posielam ziadost o zmenu roli" + farby.ENDC)
    odpoved = getOdpovedServeru(klientSock, klientInfo.typKomunikacie)
    return odpoved


def keepAlive(klientSock):
    zijem = pokracuj = 1

    while True:
        sleep(5)
        pocetChybnych = 0

        # ak spojenie so serverom nebolo ukoncene a neprebieha komunikacia
        if serverInfo.serverConnected == 1 and serverInfo.keepaliveWait == 0 and zijem:
            zijem = checkServer(klientSock, glob.KEEPALIVE)     # ak nedostane KA tu "umre" po 25s

            klientInfo.pocetKeepalive += 1

            if klientInfo.pocetKeepalive % 10 == 0:
                serverInfo.keepaliveWait = 1
                print(farby.Y + "\n-> klient je IDLE - cakam na prikaz (alebo x pre ukoncenie, w pre wait) \n... ")

        if zijem == 0:
            print(farby.M + "\n-> server neodpoveda")
            vynuluj()
            klient()


# ------------------------------------------------- ODOSIELANIE
# postupne odoslanie celeho bufferu
def posliBuffer(klientSock):
    fullPth = ""

    klientInfo.pocetDavok = math.ceil(klientInfo.pocetFragmentov / glob.TRESHOLD)     # na kolkokrat sa to bude odosielat

    if klientInfo.typKomunikacie == glob.DATA_MSG:
        fName = klientInfo.fName
        pth = klientInfo.pth

        fullPth = pth + "/" + fName
        fullPth = os.path.abspath(fullPth)
        print(farby.M + "-> posielam subor s nazvom", klientInfo.fName, "z umiestnania", fullPth, farby.ENDC)

    if klientInfo.pocetDavok > 0:

        print(farby.M + "\n-> pocet okien v ktorych sa spravy odoslu je:", klientInfo.pocetDavok, "- pocet fragmentov:", klientInfo.pocetFragmentov, "a ich velkost", glob.DEF_VELKOST_FRAGMENTU, "b\n" + farby.ENDC)

        cisloDavky = 1
        while cisloDavky <= klientInfo.pocetDavok:
            print(farby.M + "-> posielam davku c.", cisloDavky, "/", klientInfo.pocetDavok, farby.ENDC)

            posliDavku(klientSock)                                        # poslanie davky fragmentov
            uspech = checkServer(klientSock, klientInfo.typKomunikacie)   # zistovanie, ci fragmenty prisli

            if uspech:
                cisloDavky += 1                         # ak sa davka poslala uspesne posli dalsiu (inak sa neinkrementuje a posle tu istu)
                klientInfo.pocetPoslanych += 1          # ak sa uspesne davka poslala inkrementuj
                klientInfo.lastSent += glob.TRESHOLD    # ktory fragment sa ako posledny podarilo poslat

        # EXIT 1 - ak chceckserver skonci neuspesne
        uspech = checkServer(klientSock, klientInfo.typKomunikacie)      # zistovanie na konci, ci cela sprava prisla

        # EXIT 2 - ak komunikacia prebehla OK
        if uspech:
            print(farby.C + "\n-> komunikacia prebehla uspesne")
            if klientInfo.typKomunikacie == glob.DATA_MSG:
                print("-> preneseny subor s nazvom", klientInfo.fName, "z umiestnania", fullPth, farby.ENDC)

            print(farby.Y + "\nKLIENT MENU" + farby.ENDC)
            vynuluj()
            klient()

    return 0    # sem sa to obsac dostane - a zbytocne by to kontrolovalo treti krat server po ukonceni kom


# poslanie jedneho okna
def posliDavku(klientSock):
    lastSent = klientInfo.lastSent

    for i in range(lastSent, lastSent + glob.TRESHOLD):
        if i <= klientInfo.pocetFragmentov:     # ak taky fragment existuje

            cisloFragmentu = int.from_bytes(klientInfo.buffer[i-1][12:16], "big")
            velkostFragmentu = int.from_bytes(klientInfo.buffer[i-1][4:8], "big")

            try:
                # ak ma poslat chybu
                if klientInfo.posliChybu == 1 and cisloFragmentu % klientInfo.pocetnostChyb == 0:
                    # print(farby.M + "      posielam chybny fragment c.", i, klientInfo.buffer[i - 1], farby.ENDC)
                    print(farby.M + "      posielam fragment c.", i, "s velkostou", velkostFragmentu, "b", farby.ENDC)
                    naOdoslanie = corruptData(klientInfo.buffer[i-1])
                    klientInfo.pocetnostChyb *= 7                      # aby sa postupne pocet chyb znizoval
                    klientSock.sendto(naOdoslanie, serverInfo.server_adress)

                else:
                    # inak posle OK data
                    # print(farby.M + "      posielam fragment c.", i, klientInfo.buffer[i - 1], farby.ENDC)
                    print(farby.M + "      posielam fragment c.", i, "s velkostou", velkostFragmentu, "b", farby.ENDC)
                    klientSock.sendto(klientInfo.buffer[i-1], serverInfo.server_adress)
            except OSError:
                print(farby.M + "\n-> bola zadana zla velkost fragmentu - vraciam sa do menu", farby.ENDC)
                taskMenu(klientSock)


# ------------------------------------------------- MENU
# spusti spracovanie a odosielanie dat
def runKlient(klientSock):

    if klientInfo.pocetnostChyb >= len(klientInfo.sprava):                   # aby sa robili chyby ak maju aj pri kratkych spravach
        klientInfo.pocetnostChyb = 1

    spracujSpravu()                         # rozseka spravu na fragmenty a vytvori im hlavicky
    vytvorUvodnuSpravu()                    # vytvori spravu na nadviazanie spojenia
    if nadviazSpojenie(klientSock):         # nadviaze spojenie so serverom
        serverInfo.keepaliveWait = 1        # zacina prebiehat komunikacia
        serverInfo.serverConnected = 1      # nastavi, ze pripojenie je ok
        posliBuffer(klientSock)             # spusti odosielanie
        serverInfo.keepaliveWait = 0        # skoncila komunikacia
    else:
        # serverInfo.serverConnected = 0    # nastavi, ze pripojenie zlyhalo
        pass


# vypytanie si vstupu pouzivatela
def userInput(nastavenie):
    if nastavenie == 1:

        if klientInfo.serverSetup:
            print(farby.Y + "-> aktualne udaje su - IP: %s a port: %s" % serverInfo.server_adress, farby.ENDC)
        else:
            print(farby.Y + "-> aktualne server nie je nastaveny", farby.ENDC)

        try:
            print(farby.Y, end='')
            sIp = (input("-> zadaj IP, na ktoru chces spravy odoslat: \n... "))
            sP = int(input("-> zadaj port, na ktory chces spravy odoslat: \n... "))
        except ValueError:
            sP = glob.SERVERPORT
            sIp = glob.SERVERIP

        glob.SERVERPORT = sP
        glob.SERVERIP = sIp
        serverInfo.server_adress = (glob.SERVERIP, glob.SERVERPORT)
        klientInfo.serverSetup = 1

    elif nastavenie == 2:
        try:
            print(farby.Y, end='')
            velkostFragmentu = int(input("\n-> zadaj max velkost fragmentu (max. odporucana 1400) : \n... "))
            chyba = int(input("\n-> zelate si odoslat aj chybne fragmenty? (1 - ano, 0 - nie) \n... "))
        except ValueError:
            velkostFragmentu = glob.DEF_VELKOST_FRAGMENTU
            chyba = klientInfo.posliChybu

        glob.DEF_VELKOST_FRAGMENTU = velkostFragmentu
        klientInfo.posliChybu = chyba


# switch
def taskMenu(klientSock):
    print(farby.Y, end='')
    swtch = input("\n------------------------------------------------------"
                  "\n-> pre nastavenie informacii o serveri stlacte .. (a)"
                  "\n-> pre nastavenie velkosti fragmentov stlacte ... (b) \n"
                  
                  "\n-> pre odoslanie spravy stlacte ... (c) "
                  "\n-> pre odoslanie suboru stlac ..... (d) "
                  "\n-> pre vymenu roli stlac .......... (e) \n"
                  
                  "\n-> pre ukoncenie spojenia stlac ... (x)"
                  "\n------------------------------------------------------"
                  "\n... ")
    print(farby.ENDC, end='')

    if swtch == "a":    # nastavenia -----------------------------
        serverInfo.keepaliveWait = 1          # aby nechodili keepalive
        userInput(1)
        print(farby.Y + "-> NASTAVENIE DOKONCENE" + farby.ENDC)
        serverInfo.keepaliveWait = 0
        taskMenu(klientSock)

    elif swtch == "b":  # nastavenia -----------------------------
        serverInfo.keepaliveWait = 1  # aby nechodili keepalive
        userInput(2)
        print(farby.Y + "-> NASTAVENIE DOKONCENE" + farby.ENDC)
        serverInfo.keepaliveWait = 0
        taskMenu(klientSock)

    elif swtch == "c" and klientInfo.serverSetup:  # posli spravu -----------------------------
        serverInfo.keepaliveWait = 1               # aby nechodili keepalive
        klientInfo.typKomunikacie = glob.TEXT_MSG  # textova komunikacia

        print(farby.Y, end='')
        klientInfo.sprava = input("\n-> zadaj spravu na odoslanie: \n... ")
        print(farby.ENDC, end='')

        print(farby.M + '\n-> poslem text "%s" ' % klientInfo.sprava, farby.ENDC)
        runKlient(klientSock)

    elif swtch == "d" and klientInfo.serverSetup:  # posli data -----------------------------
        serverInfo.keepaliveWait = 1               # aby nechodili keepalive
        klientInfo.typKomunikacie = glob.DATA_MSG  # DATOVA komunikacia

        # pokus o otvorenie suboru
        print(farby.Y, end='')
        pth = input("\n-> zadaj cestu k suboru (napr. ./subory) : \n... ")        # path k priecinku subory je C:\Users\Emmachac\PycharmProjects\PKS02
        fName = input("-> zadaj nazov suboru (napr. subor1.txt) : \n... ")

        try:
            subor = open(pth + "/" + fName, "rb")
            subor.close()
        except FileNotFoundError:
            print("-> dany subor sa nepodarilo najst")
            taskMenu(klientSock)

        klientInfo.fName = fName
        klientInfo.pth = pth
        klientInfo.sprava = klientInfo.pth + "/" + klientInfo.fName
        print(farby.ENDC, end='')
        runKlient(klientSock)

    elif swtch == "e":
        serverInfo.keepaliveWait = 1          # aby nechodili keepalive
        try:
            print(farby.Y, end='')
            sIp = (input("\n-> zadaj IP serveru, s ktorym sa ma vymenit rola: \n... "))
            sP = int(input("\n-> zadaj port serveru, s ktorym sa ma vymenit rola: \n... "))
        except ValueError:
            sP = glob.SERVERPORT
            sIp = glob.SERVERIP

        glob.SERVERPORT = sP
        glob.SERVERIP = sIp

        serverInfo.server_adress = (glob.SERVERIP, glob.SERVERPORT)

        klientInfo.typKomunikacie = glob.CHANGE                 # vymena roli
        print(farby.ENDC, end='')

        uspech = posliChangeReq(klientSock)

        if uspech:
            klientSock.close()
            print(farby.Y + "\nSPUSTAM VERZIU SERVER" + farby.ENDC)
            serverInfo.serverConnected = 0
            main.server.server()        # aby v tomto subore nebol includnuty server a nemiesalo sa to urcite

    elif swtch == "x":
        vynuluj()
        klientSock.close()
        serverInfo.serverConnected = 0
        main.main()

    elif swtch == "w":
        # caka sa
        serverInfo.keepaliveWait = 0

    else:
        if klientInfo.serverSetup:
            print(farby.R + "\n-> neznamy prikaz" + farby.ENDC)
            serverInfo.keepaliveWait = 0
        else:
            print(farby.R + "\n-> najskor je potrebne zadat informacie v nastaveniach komunikacie" + farby.ENDC)
        taskMenu(klientSock)


def klient():
    # vytvorenie socketu
    klientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    klientInfo.klientRun = 1

    # cast klient
    t1 = threading.Thread(target=taskMenu, args=(klientSock,))
    t1.start()

    # kepalive
    t2 = threading.Thread(target=keepAlive, args=(klientSock,))
    t2.start()


if __name__ == '__main__':
    # print(farby.Y + "\nSPUSTAM VERZIU KLIENT" + farby.ENDC)
    main.main()
