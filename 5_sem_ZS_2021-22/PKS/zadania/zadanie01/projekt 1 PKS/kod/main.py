import zadanie1
import zadanie2_3
import zadanie4


class glob:  # oproti hodnotam vo WS je to posunute o 2 kvoli "'b" co je pridane pred kazdy ramec (a *2 obv)
    ZACIATOK_RAMCA = 2          # posun o pridane charaktery (b')
    DLZKA_MAC = 12              # pocet charakterov MAC adresy
    OBE_MAC = DLZKA_MAC * 2     # dlzka oboch MAC adries
    DLZKA_TYP = 8               # cast urcujuca typ ramca
    DLZKA_ETHERTYPE = 4         # dlzka pola s ethertypom
    MIN_DLZKA_RAMCA = 64
    VELKOST_HLAVICKY = 4

    LIMIT_VYPISU = 10           # ak komunikacia obsahuje viac ako x ramcov vypise sa prvych a poslednych 10

    ARP_OPCODE_START = 44       # informacie pre umiestnenie poli v arp protokole
    ARP_OPCODE_END = 46
    ARP_SRCMAC_END = 58
    ARP_SRCIP_END = 66
    ARP_DESTMAC_END = 78
    ARP_DESTIP_END = 86

    TFTP_OPCODE_START = 88      # informacie pre umiestnenie poli v tftp protokole
    TFTP_OPCODE_END = 90
    TFTP_SRCPORT_START = 70
    TFTP_SRCPORT_END = 74
    TFTP_DESTPORT_END = 78

    START_SRC_IP = 54           # informacie pre umiestnenie poli v ipv4 protokole
    END_SRC_IP = 62
    END_DEST_IP = 70
    START_IP_PROT = 48
    END_IP_PROT = 50

    START_IPv6_PROT = 42        # informacie pre umiestnenie poli v ipv6 protokole
    END_IPv6_PROT = 44
    START_SRC_IPv6 = 46
    END_SRC_IPv6 = 78
    END_DEST_IPv6 = 110

    START_SRC_TCP_PORT = START_SRC_UDP_PORT = 70     # informacie pre umiestnenie poli v tcp protokole
    END_SRC_TCP_PORT = END_SRC_UDP_PORT = 74
    END_DST_TCP_PORT = END_DST_UDP_PORT = 78


#class farby:
#    BLUE = '\033[94m'
#    WHITE = '\033[0m'
#    CYAN = '\033[96m'
#    GREEN = '\033[92m'
#    YELLOW = '\033[93m'
#    MAGENTA = '\u001b[35m'
#    RED = '\u001b[31;1m'


class farby:        # ak terminal nepodporuje farby
    BLUE = ''
    WHITE = ''
    CYAN = ''
    GREEN = ''
    YELLOW = ''
    MAGENTA = ''
    RED = ''


def vypisSlovnik(etherTypy, lsapy, ipProtokoly):
    print(farby.CYAN + "----- EXTERNY SUBOR: -----" + farby.BLUE)
    print("#Ethertypy")
    for key, value in etherTypy.items():
        print(key, value)
    print(farby.CYAN + "#Lsapy")
    for key, value in lsapy.items():
        print(key, value)
    print(farby.BLUE + "#IpProtokoly")
    for key, value in ipProtokoly.items():
        print(key, value)
    print(farby.CYAN + "#TCPy")
    for key, value in tcpy.items():
        print(key, value)
    print(farby.BLUE + "#UDPy")
    for key, value in udpy.items():
        print(key, value)
    print(farby.CYAN + "#ICMPy")
    for key, value in icmpy.items():
        print(key, value)
    print("" + farby.WHITE)


if __name__ == '__main__':
    # zo suboru - typy
    etherTypy = {}
    lsapy = {}
    ipProtokoly = {}
    tcpy = {}
    udpy = {}
    icmpy = {}

    # statistika IP
    ipStatistika = {}

    # nacitanie
    etherTypy, lsapy, ipProtokoly, tcpy, udpy, icmpy = zadanie2_3.nacitajSubor(etherTypy, lsapy, ipProtokoly, tcpy, udpy, icmpy)
    # vypisSlovnik(etherTypy, lsapy, ipProtokoly)

    # program
    cont = True
    while cont:
        print(farby.YELLOW + "MENU\n\t-> pre prvu cast zadania stlac\t\t(a)"
                             "\n\t-> pre druhu cast zadania stlac\t\t(b)"
                             "\n\t-> pre vypis externeho suboru stlac\t(c)"
                             "\n\n\t-> pre ukoncenie programu stlac\t\t(x)\n" + farby.WHITE)
        k = input()

        if k == "a":
            ipStatistika = zadanie1.start(etherTypy, lsapy, ipProtokoly, udpy, tcpy, icmpy, ipStatistika)
            ipStatistika = {}
            print("")
        elif k == "b":
            print(farby.YELLOW + "\t-> pre HTTP stlac\t\t\t(a)"
                                 "\n\t-> pre HTTPS stlac\t\t\t(b)"
                                 "\n\t-> pre TELNET stlac\t\t\t(c)"
                                 "\n\t-> pre SSH stlac\t\t\t(d)"
                                 "\n\t-> pre FTP riadiace stlac\t(e)"
                                 "\n\t-> pre FTP datove stlac\t\t(f)"
                                 "\n\n\t-> pre TFTP stlac\t\t\t(g)"
                                 "\n\t-> pre ICMP stlac\t\t\t(h)"
                                 "\n\t-> pre ARP stlac\t\t\t(i)"
                                 "\n\n\t-> pre navrat do menu stlac\t(x)\n" + farby.WHITE)
            t = input()
            if t != "x":
                zadanie4.start(t, etherTypy, lsapy, ipProtokoly, tcpy, udpy, icmpy)
                print("")
        elif k == "c":
            vypisSlovnik(etherTypy, lsapy, ipProtokoly)
        elif k == "x":
            break
        else:
            print("Nespravny vstupny prikaz\n")
            pass
