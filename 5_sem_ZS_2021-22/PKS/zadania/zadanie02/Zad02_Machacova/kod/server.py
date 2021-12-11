import math
import os

import main

import socket
import zlib


class glob:
    SERVERIP = "localhost"      # defaultne hodnoty ak pouzivatel zada nespravny vstup
    SERVERPORT = 10000
    DEF_VELKOST_FRAGMENTU = 20
    TIMEOUT = 15

    TEXT_MSG = 1                # typy hlaviciek
    DATA_MSG = 2
    REQ_TXT = 3
    REQ_DATA = 4
    ACK = 5
    NACK = 6
    CHANGE = 7

    TRESHOLD = 5                # kolko sprav posle v jednom okne


class farby:
    B = '\u001b[34m'
    M = '\u001b[35m'
    Y = '\u001b[33m'
    C = '\u001b[36m'
    R = '\u001b[31m'
    ENDC = '\u001b[0m'


class serverInfo:
    server_adress = ""      # info o serveri    - NENULOVAT
    running = 0             # ci server bezi    - NENULOVAT

    typKomunikacie = 0      # 1 - sprava zo stdin, 2 - subor

    prijataSprava = []      # vysledna sprava
    dlzkaDat = 0            # jej dlzka
    pocetFrag = 0           # z kolkych je fragmentov
    dataCrc = 0             # ake ma CRC
    recOK = 0               # flag ci fragmen prisiel OK
    pocetPrijatych = 0      # kolko fragmentov uz prislo
    maxSn = 0               # ukazuje, ktory najvyssi fragment prisiel OK
    fName = None            # nazov prichadzajuceho suboru


# informacie o klientovi, ktore server zisti z ich komunikacie
class klientInfo:
    klient_adress = ""      # adresa klienta    - NENULOVAT


# ------------------------------------------------------------------------------- FUNKCIE

# ------------------------------------------------- INE
# vynulovanie temp po komunikacii
def vynuluj():
    serverInfo.typKomunikacie = 0
    serverInfo.prijataSprava = []
    serverInfo.dlzkaDat = 0
    serverInfo.pocetFrag = 0
    serverInfo.dataCrc = 0
    serverInfo.recOK = 0
    serverInfo.pocetPrijatych = 0
    serverInfo.maxSn = 0
    serverInfo.running = 0


# ------------------------------------------------- PRACA S DATAMI


def ulozSubor():
    pth = "./inbox"
    fName = serverInfo.fName
    fullPth = pth + "/" + fName

    serverInfo.inputPth = serverInfo.inputPth + "/" + fName

    try:
        file = open(serverInfo.inputPth, "wb")
    except FileNotFoundError:
        print(farby.B + "-> dane umiestnenie sa nepodarilo najst, subor sa uklada na preddefinovane miesto" + farby.ENDC)
        file = open(fullPth, "wb")

    for i in range(0, serverInfo.pocetFrag):
        fragment = serverInfo.prijataSprava[i]
        file.write(fragment)

    fullPth = os.path.abspath(fullPth)

    print(farby.C + "\n-> subor bol uspesne doruceny ako", fName, "v umiestneni", fullPth, "\n")
    file.close()


# ------------------------------------------------- VYTVORENIE SERVRU
# vytvorenie
def vytvorServer():
    serverSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # TCP/IP socket

    # pri zle zadanych hodnotach sa pouziju prednastavene
    print(farby.Y + "------------------------------------------------------")
    try:
        try:
            sP = int(input("-> zadaj port, na ktorom server pocuva: \n... "))
        except ValueError:
            sP = glob.SERVERPORT
            pass

        glob.SERVERPORT = sP

        try:
            # Bind
            serverInfo.server_address = (glob.SERVERIP, sP)  # skus bind na zadany port
            serverSock.bind(serverInfo.server_address)

        except socket.gaierror:
            # Bind
            serverInfo.server_address = (glob.SERVERIP, sP + 1)  # skus bind na dalsi port
            serverSock.bind(serverInfo.server_address)
            glob.SERVERPORT = sP + 1

        serverInfo.inputPth = input(farby.Y + "-> zadaj kam sa maju ukladat subory (napr. ./inbox) : \n... ")
        print("------------------------------------------------------")

        print(farby.B, end='')
        print("\n-> spusta sa server na %s, port %s" % serverInfo.server_address)
        print("-> pocuvam spravy na adrese %s, port %s" % serverInfo.server_address, farby.ENDC)
        serverInfo.running = 1
        return serverSock

    except OSError:
        print(farby.Y + "\n-> dany server uz bezi" + farby.ENDC)
        serverInfo.running = 0
        main.main()


# ------------------------------------------------- KOMUNIKACIA
# poslanie ACK
def posliAck(serverSock):
    # tvar: TYP | 0000
    typ = glob.ACK.to_bytes(4, byteorder="big")
    telo = int(0).to_bytes(4, byteorder="big")

    sprava = typ + telo

    print(farby.B + "-> posielam ACK na adresu", klientInfo.klient_adress, farby.ENDC)

    serverSock.sendto(sprava, klientInfo.klient_adress)


# poslanie NACK
def posliNack(serverSock):
    # tvar: TYP | 0000
    typ = glob.NACK.to_bytes(4, byteorder="big")
    telo = int(0).to_bytes(4, byteorder="big")

    sprava = typ + telo

    print(farby.R + "-> posielam spravu o chybe na adresu", klientInfo.klient_adress, farby.ENDC)
    serverSock.sendto(sprava, klientInfo.klient_adress)


# kontroluje to, ci chybaju spravy, ktore by sme mali uz mat
def chceckPrijatychSprav():

    for i in range(0, serverInfo.maxSn):
        if serverInfo.prijataSprava[i] == 0:
            return 0    # niektora nam chyba

    return 1            # je to OK


# ------------------------------------------------- POCUVANIE
# pocuvanie sprav od klienta
def pocuvaj(serverSock):

    try:
        try:
            recData, klientInfo.klient_adress = serverSock.recvfrom(4096)

            typ = int.from_bytes(recData[0:4], "big")
            # print("-> zachytenych %s b od %s " % (len(recData), klientInfo.klient_adress), "- ", recData)

            return typ, recData

        except OSError:
            return 0, 0
    except AttributeError:
        return 0, 0


# ------------------------------------------------- MENU
def server():
    # vytvorenie serveru - ak nebezi
    if serverInfo.running == 0:
        serverSock = vytvorServer()

    # pocuvaj spravy od klienta
    while True:

        # ---------------- pocuvaj
        typRecSpravy, recData = pocuvaj(serverSock)

        # ak pride ziadost o nadviazanie spojenia # tvar: TYP | DLZKA DATA | POCET FRAGMENTOV | CELKOVE CRC |
        if typRecSpravy == glob.REQ_TXT:

            serverInfo.typKomunikacie = glob.TEXT_MSG                   # nastavenie typu komunikacie

            serverInfo.dlzkaDat = int.from_bytes(recData[4:8], "big")
            serverInfo.pocetFrag = int.from_bytes(recData[8:12], "big")
            serverInfo.dataCrc = int.from_bytes(recData[12:16], "big")

            try:
                velkostFragmentov = math.ceil(serverInfo.dlzkaDat / serverInfo.pocetFrag)
            except ZeroDivisionError:
                velkostFragmentov = 1

            serverInfo.prijataSprava = [0 for i in range(0, serverInfo.pocetFrag)]
            print(farby.M + "\n---------------------------------------------------------------------------------------- START KOMUNIKACIE")
            print("-> prijata ziadost o nadviazanie spojenia - TXT sprava")
            print("-> pocet fragmentov na prijatie:", serverInfo.pocetFrag, "a ich apx. velkost:", velkostFragmentov, "b\n", farby.ENDC)
            posliAck(serverSock)

        # ak pride ziadost o nadviazanie spojenia # tvar: TYP | DLZKA DATA | POCET FRAGMENTOV | CELKOVE CRC | nazov
        elif typRecSpravy == glob.REQ_DATA:
            serverInfo.typKomunikacie = glob.DATA_MSG                   # nastavenie typu komunikacie

            serverInfo.dlzkaDat = int.from_bytes(recData[4:8], "big")
            serverInfo.pocetFrag = int.from_bytes(recData[8:12], "big")
            serverInfo.dataCrc = int.from_bytes(recData[12:16], "big")
            serverInfo.fName = recData[16:]
            serverInfo.fName = serverInfo.fName.decode('utf-8')

            velkostFragmentov = math.ceil(serverInfo.dlzkaDat / serverInfo.pocetFrag)

            serverInfo.prijataSprava = [0 for i in range(0, serverInfo.pocetFrag)]
            print(farby.M + "\n---------------------------------------------------------------------------------------- START KOMUNIKACIE")
            print("-> prijata ziadost o nadviazanie spojenia - SUBOR")
            print("-> pocet fragmentov na prijatie:", serverInfo.pocetFrag, "a ich apx. velkost:", velkostFragmentov, "b\n", farby.ENDC)
            posliAck(serverSock)

        # ak pridu data # tvar: TYP | DLZKA FRAGMENTU | POCET FRAGMENTOV | SEQUENCE NUMBER | CRC | data
        # todo edit # tvar: TYP | SEQUENCE NUMBER | CRC | data
        elif typRecSpravy == glob.TEXT_MSG or typRecSpravy == glob.DATA_MSG:

            recDlzka = int.from_bytes(recData[4:8], "big")
            recPocet = int.from_bytes(recData[8:12], "big")
            recSn = int.from_bytes(recData[12:16], "big")
            recCrc = int.from_bytes(recData[16:20], "big")
            recMsg = recData[20:]
            chceckCrc = zlib.crc32(recMsg) & 0xffffffff

            if typRecSpravy == glob.TEXT_MSG:
                recMsg = recMsg.decode('utf-8')
                # print(farby.M + '-> prijate data "%s", s hodnotou CRC' % recMsg, ":", recCrc, "kontrolne CRC :", chceckCrc, farby.ENDC)
                print(farby.M + "-> prijaty fragment so spravou c.", recSn, "o dlzke", recDlzka, "b, s hodnotou CRC", recCrc, " - kontrolne CRC :", chceckCrc, farby.ENDC)
            else:
                print(farby.M + "-> prijaty fragment so suborom c.", recSn, "o dlzke", recDlzka, "s hodnotou CRC", recCrc, " - kontrolne CRC :", chceckCrc, farby.ENDC)

            # ak je fragment OK
            if recCrc == chceckCrc:

                if recSn > serverInfo.maxSn:
                    serverInfo.maxSn = recSn        # aktualizacia najvyssej OK spravy

                # ak este neprisiel
                if serverInfo.prijataSprava[recSn - 1] == 0:
                    serverInfo.prijataSprava[recSn - 1] = recMsg
                    serverInfo.pocetPrijatych += 1

                    # ak je pocet prijatych fragmentov == celkovemu poctu co mal prist .........................
                    if serverInfo.pocetPrijatych == serverInfo.pocetFrag:

                        # ak to bola sprava zo stdin
                        if serverInfo.typKomunikacie == glob.TEXT_MSG:
                            print(farby.C + "\n-> komunikacia prebehla uspesne - vysledna sprava:")
                            vyslednaSprava = ''.join(map(str, serverInfo.prijataSprava))
                            print("   " + vyslednaSprava, "\n", farby.ENDC)
                            # pocet a velkost fragmentov
                            velkostFragmentov = math.ceil(serverInfo.dlzkaDat / serverInfo.pocetFrag)
                            print(farby.M + "-> pocet prijatych fragmentov:", serverInfo.pocetFrag, "a ich priemerna velkost:", velkostFragmentov, "b\n", farby.ENDC)
                            # reset
                            vynuluj()

                        elif serverInfo.typKomunikacie == glob.DATA_MSG:
                            ulozSubor()
                            # pocet fragmentov
                            print(farby.M + "-> pocet prijatych fragmentov:", serverInfo.pocetFrag, farby.ENDC)
                            # reset
                            vynuluj()
                    # ...........................................................................................

                if chceckPrijatychSprav():          # ak mame vsetky spravy co klient zatial poslal
                    serverInfo.recOK = 0
            else:
                serverInfo.recOK = 1                # posle sa nack

        elif typRecSpravy == glob.ACK:
            print(farby.M + "-> prijata ziadost o potvrdenie spojenia", farby.ENDC)

            if serverInfo.recOK == 0:
                posliAck(serverSock)
            else:
                posliNack(serverSock)

        elif typRecSpravy == glob.CHANGE:
            print(farby.M + "\n-> prijata ziadost o zmenu roli", farby.ENDC)
            posliAck(serverSock)
            vynuluj()
            serverSock.close()
            print(farby.Y + "\nSPUSTAM VERZIU KLIENT" + farby.ENDC)
            main.klient.klient()                      # aby v tomto subore nebol includnuty klient a nemiesalo sa to urcite


if __name__ == '__main__':
    # print(farby.Y + "\nSPUSTAM VERZIU SERVER\n" + farby.ENDC)
    main.main()
