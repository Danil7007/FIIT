import socket, threading
from enum import Enum

global ip_address, port

class TypFragmentu(Enum):
    DATATEXT = 0
    MENOSUBORU = 1
    DATASUBOR = 2
    KEEPALIVE = 3

class Header:
    typ = None
    pocetF = 0
    indexF = 0
    velkost = 0

class Fragment:
    header = None  # 14B
    data = None  # 1B, alebo viac
    CRC = None  # 4B

class Sender:
    mojSubor = open("a.txt", "r")
    # rozkuskovat subor a posielat fragmenty
    # poslat = new Fragment()

    # def sendFragment(self):
        # poslat.hlavicka = new Hlavicka()
        # poslat.data = getData()
        # poslat.CRC = getCRC(poslat.data)
        # if jeTotoChybnyFragment==True:
        #     poslat.CRC += 1
        # socket.send(Fragment.toBytes())

class Reciever:
    buffer = "toto je subor\n"
    def recieveFragment(self):
        # recievedData = socket.recieve() #funkcia na citanie zo socketu
        # novyFragment = (Fragment)recievedData
        # if novyFragment.hlavicka.typ == DATA:
        #   self.buffer+=novyFragment.data
        pass
    # prijmat fragmenty a zlepit subor


    prijimenySubor = open("b.txt", "w")
    prijimenySubor.write(buffer)

# Toto by bolo mozno dobre dat do zvlast suboru
class ClientThread(threading.Thread):

    def __init__(self,clientAddress,clientsocket):
        threading.Thread.__init__(self)
        self.csocket = clientsocket
        print("New connection added: ", clientAddress)

    def run(self):
        global pseudo_IK, pseudo_SPK, pseudo_OPK, pseudo_OPKid
        global key_b
        global r
        user = ''
        print("Connection from : ", clientAddress)

def sender():
    global ip_address, port
    
    
    frag_size = 0
    ip_address = input("Zadajte cielovu IP adresu: ")
    port = int(input("Zadajte port: "))
    print("Ip adresa: ", ip_address, " port: ", port, ", velkost fragmentu: ", fragment_max_size)
    print('-------------------------------------------------------------------------------------')
    print("Chcete poslat: ")
    print(' 1 - spravu\n 2 - subor ')
    print('-------------------------------------------------------------------------------------')
    to_send = input()
    # posiela sa sprava
    if to_send == "1":
        msg = input("Napiste spravu, ktoru chcete poslat: ")
        msg_to_send = str.encode(msg)
        while True:
            fragment_max_size = int(input("Zadajte maximalnu velkost fragmentu: "))
            if (not(frag_size > 0 and frag_size <= fragment_max_size)) :
                print("Velkost fragmentu musi byt vacsia ako 0 a  mensia/rovnaka ako ", fragment_max_size)
                continue

            if (frag_size > len(msg_to_send)):
                frag_size = len(msg_to_send)

                frag_count = (len(msg_to_send)- (len(msg_to_send) % frag_size)) / frag_size

            if ((len(msg_to_send) % frag_size) != 0):
                frag_zvysok = len(msg_to_send) % frag_size
                frag_pocet += 1
            else:
                frag_zvysok = frag_size
            if( ((frag_size <= fragment_max_size) and (frag_size <= len(msg_to_send)) and (frag_size > 0))):
                break
    else:
        file = ""
    receiver()

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip_address, port))


def receiver():
    global ip_address, port
    def __init__(arg1, arg2):
        ''' #; takto sa zapisuje anotacia funkcii, ugl. len velky komentar kery popisuje
        co je funkica aj ako/preco sa pouziva. Je velmo dobre toto pisat. (moze byt 3x' alebo 3x"
        v pythone ' a " sa skroz istie)
        __init__ je konstruktor triedy, argumenty sa tie kerie das ked vytvaras triedu
        tato sa vykona ked zavolas sender(volaco, volaco), mozes si prekonat ak kces
        volat bez argumentov. Tu mozes pokracuvat s nacitanim IP adresy, portu, itd...
        '''
        pass #; pass je prazdna funkcia, nerobi nist, toto je istvo ako keby si v C napisala init(){ }
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((ip_address, port))
    print("Server started")
    print("Waiting for client request..")
    server.listen(1)
    clientsock, clientAddress = server.accept()
    newthread = ClientThread(clientAddress, clientsock)
    newthread.start()

def main():
    while True:
        print("Zvolte moznost: 1 = Sender alebo 2 = Recever")
        user = input()
        if user == "1":
            print("Sender")
            sender()
            break
        elif user == "2":
            user = "Receiver"
            break
        else:
            print("Nespravny prikaz! Zadajte znovu.")

    print(user)

if "__name__" == "__main__":
    main()  #; takto sa v pythone vola main, v podstate nije bitnvo preco preco.... :D
#; ... ale ak chces vediet tak, v podstate
#; secke default veci sa v pythone spristupnenie a maju format __xxx__
#; __name__ je meno suboru (v tvojom pripade pokus1.py)
#; __main__ je meno suboru kery sa spusti ako prvy
#; Ked zavolas/spustis .py subor kery referencuje druhie .py subory
#; tak python automaticky prideli internu premennu __main__ na meno toho suboru