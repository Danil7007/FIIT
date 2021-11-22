import socket
import struct
import os
import math
import msvcrt
import time
import zlib
import sys
from enum import Enum

TMT_WAIT_FOR_MSG = 2

DATATEXT = 0
FILENAME = 1
DATAFILE = 2
DATARESPONSE = 3
KEEPALIVE = 4


class Header:
    fragType = None  # 1B
    fragSize = 0  # 4B
    fragCount = 0  # 4B
    fragIdx = 0  # 4B

    # Velkosti premennych
    fragTypeSize = 1
    fragCountSize = 4
    fragIdxSize = 4
    fragSizeSize = 4

    def __init__(self, fragType=0, fragSize=0, fragCount=0, fragIdx=0):
        self.fragType = fragType
        self.fragSize = fragSize
        self.fragCount = fragCount
        self.fragIdx = fragIdx

    @classmethod
    def getSize(cls):
        return cls.fragTypeSize + cls.fragCountSize + cls.fragIdxSize + cls.fragSizeSize

    def setFragIdx(self, fragIdx):
        self.fragIdx = fragIdx

    def setFragSize(self, fragSize):
        self.fragSize = fragSize

    def __str__(self):
        return \
            "fragType: " + str(self.fragType) + ", " + \
            "fragSize: " + str(self.fragSize) + ", " + \
            "fragCount: " + str(self.fragCount) + ", " + \
            "fragIdx: " + str(self.fragIdx) + "\n"


class Fragment:
    header = None  # 14B, getSize()
    checksum = None  # 4B
    data = None  # 1B, alebo viac
    checksumSize = 4

    def __init__(self, fragHeader=Header(), checksum=0, data=0):
        # zarucuje ze fragHeader bude typu Header
        self.header = fragHeader
        self.checksum = checksum
        self.data = bytes(data)

    @classmethod
    def getSize(cls):
        return cls.header.getSize() + cls.checksumSize + len(cls.data)

    def setData(self, data):
        self.data = data

    def getChecksum(self):
        return self.checksum

    def __str__(self):
        return \
            "Header: " + str(self.header) + \
            "Checksum: " + str(self.checksum) + "\n" + \
            "Data: " + str(self.data) + "\n"

def getCRC(byteData):
    return zlib.crc32(byteData) & 0xffffffff

def packHeader(header):
    """ vrati header ako bytestring s dlzkou 13
    """
    # zarucuje ze v header je objekt typu Header
    return struct.pack('<BIII', header.fragType, header.fragSize, header.fragCount, header.fragIdx)


def unpackHeader(headerBytes):
    # ; hviezdicka rozobere list/tuple na argumenty, cize unpack vrati (1, 2, 3, 4) a * spravi aby odovzdalo argumenty ako 1, 2, 3, 4
    # ; tj. ako 4 argumenty ni ako 1 tuple
    return Header(*struct.unpack('<BIII', headerBytes))


def packFragment(byteData):
    """ Vrati Fragment ako spackuvanu strukturu urcenu na posielanie po sieti
    spackuje header a checksum cez struct.pack a na koniec pripoji bytestring dat
    """
    return packHeader(byteData.header) + struct.pack('<I', byteData.checksum) + byteData.data


def unpackFragment(fragmentBytes):
    fragType = fragmentBytes[0] # 1struct.unpack('<B', fragmentBytes[0])
    fragData = None
    if fragType == DATATEXT  or fragType == DATAFILE or fragType == FILENAME:
        # Data bude cely fragment aj s hlavickou
        # Rozsah cisel pri notacii list[n:m] je <n;m)
        fragHeader = unpackHeader(fragmentBytes[:Header.getSize()])
        fragData = Fragment(fragHeader)
        fragData.checksum = struct.unpack('<I', fragmentBytes[Header.getSize():Header.getSize() + 4])
        fragData.data = fragmentBytes[Header.getSize() + 4:]
    elif fragType == DATARESPONSE:
        # Data budu 4B, index fragmentu na ktory reciever caka
        fragData = struct.unpack('<I', fragmentBytes[1:])
        fragData = fragData[0]
    elif fragType == KEEPALIVE:
        # Data bude None, keepAlive nepotrebuje ziadne data
        fragData = None
    return fragType, fragData


def openSocket():
    """ Funkcia otvori socket a naviaze ho na IP a port
    """
    ipAddress = input("ZadajteIP adresu: ")
    port = int(input("Zadajte port: "))
    try:
        newSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # ;
    except:
        print("Nepodarilo sa vytvorit socket")
        exit()
    else:
        print("Otvoreny socket na Ip adresa: ", ipAddress, " port: ", port)
        return ipAddress, port, newSocket


class Sender:
    def __init__(self):
        """ Konstruktor triedy Sender
        prvo nacita ip a port
        potom ...
        """
        self.maxFragSize = 0
        self.ipAddress, self.port, self.senderSocket = openSocket()  # Nacita IP a port a otvori socket
        #self.senderSocket.bind(('', self.port))
        self.senderSocket.setblocking(0)
        self.sendDataType = "0"
        self.fragErr = False
        self.promptType()
        done = False
        kaCounter = 0
        startTmt = time.perf_counter()
        while not done:
            #if msvcrt.kbhit():
            self.sendDataType = msvcrt.getch().decode('utf-8')
            self.maxFragSize = int(input("Zadajte maximalnu velkost fragmentu: "))
            self.fragErr = int(input("Mam poslat chybny fragment? 0=nie: "))
                #done = True
           # else:
              #  newTmt = time.perf_counter()
               # if newTmt - startTmt > 5:
                    #self.senderSocket.sendto(struct.pack('<B', KEEPALIVE), (self.ipAddress, self.port))
                   # try:
                        #self.senderSocket.recvfrom(4096)
                  #  except socket.error:
                      #  kaCounter += 1
                        #if kaCounter > 3:
                           # print("Vyprsal KA timeout")
                          #  exit()
                    #else:
                       # print("Prijal som spatnu KA spravu")
                    #startTmt = time.perf_counter()
            if self.sendDataType == "1":
                self.senderSocket.setblocking(1)
                self.sendMsg()
                self.promptType()
                self.senderSocket.setblocking(0)
            elif self.sendDataType == "2":
                self.senderSocket.setblocking(1)
                self.sendFile()
                self.promptType()
                self.senderSocket.setblocking(0)
            elif self.sendDataType == "3":
                self.senderSocket.close()
                exit()
            elif self.sendDataType == "0":
                continue
            else:
                print("Nespravny prikaz " + str(self.sendDataType) + "! Zadajte znovu.")

    def promptType(self):
        print('-------------------------------------------------------------------------------------')
        print("Chcete poslat: ")
        print(' 1 - spravu\n 2 - subor\n 3 - Koniec')
        print('-------------------------------------------------------------------------------------')

    def sendMsg(self):
        msgString = input("Zadajte spravu: ")
        msgByte = bytearray(msgString, 'utf-8')
        self.sendData(msgByte, DATATEXT)

    def sendFile(self):
        while True:
            filePath = input("Zadajte subor: ")
            if not os.path.exists(filePath):
                print("Nespravna cesta k suboru, zadajte znovu")
                continue
            else:
                break
        fileName = os.path.basename(filePath)
        nameByte = bytearray(fileName, 'utf-8')
        self.sendData(nameByte, FILENAME)
        # C:\Users\User\Desktop\beer.jpg
        # C:\Users\User\Desktop\beer.jpg
        with open(filePath, "rb") as filePtr:# Otvori subor a nacita riadky
            fileData = filePtr.read()
            print(str(fileData))
            dataByte = bytearray(fileData)
            print(str(dataByte))
            self.sendData(dataByte, DATAFILE)


    def sendData(self, byteData, dataType):
        """ Posle data v arg bytestring s typom dataType

        byteData: bytearray
        dataType: TypFragmentu
        """
        byteDataSize = len(byteData)  # Dlzka bytoveho pola dat ktore posielame

        # V ramci pola byteData zluci elemnty podla maxFrag size a zapise novy list do toSend
        # cize ak byteData=["Hello_world"] a maxFragSize = 4
        # toSend bude ["Hell", "o_w", "orl", "d"]
        toSend = list()  # list dat ktore sa zapisu do fragmentov
        for fragIdx in range(0, len(byteData), self.maxFragSize):
            fragIdx2 = fragIdx + self.maxFragSize
            if fragIdx2 < len(byteData):
                toSend.append(bytes(byteData[fragIdx:fragIdx2]))
            else:
                toSend.append(bytes(byteData[fragIdx:]))
                break

        fragCount = math.ceil(byteDataSize / self.maxFragSize)
        fragHeader = Header(dataType, 0, fragCount, 0)
        fragment = Fragment(fragHeader)
        fragIdx = 0
        while fragIdx < fragCount:
            fragData = toSend[fragIdx]
            fragHeader.setFragIdx(fragIdx)
            fragHeader.setFragSize(len(fragData))
            fragment.setData(fragData)
            fragment.checksum = getCRC(fragment.data)
            if self.fragErr != 0 and self.fragErr == fragIdx:
                print("Posielam chybny fragment")
                fragment.checksum = 0
                self.fragErr = 0
            print("Posielam fragment:" + str(fragment))
            self.senderSocket.sendto(packFragment(fragment), (self.ipAddress, self.port))
            recMsg = None
            while True:
                print("Cakam na odpoved", fragIdx, fragCount)
                self.senderSocket.setblocking(0)
                responseTimer = time.perf_counter()
                while True:
                    try:
                        recMsg, addr = self.senderSocket.recvfrom(4096)
                    except:
                        if time.perf_counter() - responseTimer > TMT_WAIT_FOR_MSG:
                            self.senderSocket.sendto(packFragment(fragment), (self.ipAddress, self.port))
                    else:
                        self.senderSocket.setblocking(1)
                        break
                if recMsg:  # Ak dosla odpoved od recievera
                    fragType, nextIdx = unpackFragment(recMsg) # musi byt typ DATARESPONSE
                    if nextIdx != fragIdx + 1:
                        # print nextIndex musi byt fragIdx+1, chyba
                        print("Reciever si vyziadal iny fragment index=", nextIdx)
                    fragIdx = nextIdx
                    print("---------\n")
                    break
        print("===========\n")


def Receiver():
    ipAddress, port, recSocket = openSocket()  # Nacita IP a port a otvori socket
    recSocket.bind(('', port))
    receiverBuffer = bytes() # sem reciever sklada data od senderu
    fragment = Fragment()
    actFragIdx = 0

    # SUBOR
    defaultFilePath = "c:\\users"
    expectedType = None  # Typ fragmentu na ktory caka
    while True:
        recMsg = ""
        recMsg, addr = recSocket.recvfrom(4096)
        if recMsg:
            fragType, fragment = unpackFragment(recMsg)
            if fragType == DATATEXT:
                if fragment.header.fragIdx % 2 != 0:
                    print(str(fragment.data.decode('utf-8')))
                if fragment.header.fragIdx == 0:
                    expectedType = DATATEXT
                elif expectedType != DATATEXT:
                    print("chyba, cakal som text")
                    exit()
            if fragType == DATAFILE:
                if fragment.header.fragIdx == 0:
                    expectedType = DATAFILE
                elif expectedType != DATAFILE:
                    print("chyba, cakal som data file")
                    exit()
            if fragType == FILENAME:
                if fragment.header.fragIdx == 0:
                    expectedType = FILENAME
                elif expectedType != FILENAME:
                    print("chyba, cakal som file name")
                    exit()
            if fragType == KEEPALIVE:
                print("Preposielam KA packet")
                recSocket.sendto(struct.pack('<B', KEEPALIVE), addr)
                continue
            newChecksum = getCRC(bytes(fragment.data))
            newFragIdx = fragment.header.fragIdx
            if newChecksum != fragment.checksum[0]:
                print("Chybna sprava, vyziadam si znovu fragment " + str(newFragIdx))
            else:
                newFragIdx += 1 # vyziadame nasledovny fragment
                receiverBuffer += fragment.data[0:] # Pripise do prijmaceho buffra
            recSocket.sendto(struct.pack('<BI', DATARESPONSE, newFragIdx), addr)
            # Ak boli prijate vsetky fragmenty
            if fragment.header.fragIdx == fragment.header.fragCount - 1:
                if fragType == DATATEXT:
                    # ak je sprava, vypisat
                    expectedType = None # Dalej sa caka hocico
                    print("Sprava bola prijata uspesne:")
                    print(receiverBuffer.decode('utf-8'))
                if fragType == FILENAME:
                    # Ak bolo prijate meno suboru, caka sa na data suboru
                    expectedType = DATAFILE # Dalej sa caka data suboru
                    filePath = os.path.join(defaultFilePath, receiverBuffer.decode('utf-8'))
                    print("Cakam na subor, cesta:", filePath)
                if fragType == DATAFILE:
                    # Prijate boli vsetky fragmenty suboru
                    expectedType = None # Dalej sa caka hocico
                    with open(filePath, "wb") as newFile:
                        newFile.write(receiverBuffer)  # Zapis subor na cestu
                print("===================")
                receiverBuffer = bytes() # Znuluje sa buffer lebo sprava prisla v celku


def main():
    while True:
        print("Zvolte moznost: 1 = Sender alebo 2 = Recever")
        user = input()
        if user == "1":
            print("Sender")
            Sender()
            break
        elif user == "2":
            print("Receiver")
            Receiver()
            break
        else:
            print("Nespravny prikaz! Zadajte znovu.")

    print(user)

if __name__ == "__main__":
    main()