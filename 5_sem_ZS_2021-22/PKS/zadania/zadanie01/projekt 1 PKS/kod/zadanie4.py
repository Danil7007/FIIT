from scapy.compat import bytes_hex
from scapy.utils import rdpcap

import main
import zadanie1
import zadanie2_3


# zoznamy komunikacii a pomocne premenne
class kom:
    arp = {}            # pre ARP
    arp_komp_no = 1

    tcp = {}            # pre TCP

    icmp = {}           # pre ICMP

    tftp = {}           # pre TFTP
    tftp_no = 0
    opcode = ""
    prvy_opcode = ""
    tftp_a_ip = ""
    tftp_b_ip = ""
    tftp_a_port = ""
    tftp_b_port = ""


def hexToMAC(string):
    mac = ""
    for i in range(0, len(string)):
        mac += string[i].upper()
        if i % 2 == 1:  # medzery medzi dvojicami
            mac += " "
    return mac


def hexToIP(string):
    dvojica = ""
    adresa = ""

    for i in range(0, len(string)):
        dvojica += string[i]
        if i % 2 == 1:
            adresa += str((int(dvojica, 16)))
            adresa += "."
            dvojica = ""

    return adresa[:-1]


def start(t, etherTypy, lsapy, ipProtokoly, tcpy, udpy, icmpy):
    pathname = "./pcaps/" + input("\nZadaj nazov suboru: ")     # pre otvorenie suboru
    print("")

    try:
        pkts_list = rdpcap(pathname)                            # loading
    except FileNotFoundError:
        print("Subor", pathname[8:], "neexistuje")
        start(t, etherTypy, lsapy, ipProtokoly, tcpy, udpy, icmpy)
        return

    num = len(pkts_list)                                        # pocet ramcov

    for i in range(0, num):                                     # volanie triedenia ramcov
        vyberProtokol(pkts_list, i, t, etherTypy, lsapy, ipProtokoly, tcpy, udpy)

    # switch na vysledny vypis -----------------------------------------------------
    if t == "a" or t == "b" or t == "c" or t == "d" or t == "e" or t == "f":
        vypisTCP(pkts_list, tcpy, t)    # TCP kom.
    elif t == "i":                      # ARP dvojice
        vypisARP(pkts_list)
    elif t == "g":                      # TFTP ramce komunikacie
        vypisTFTP(pkts_list)
    elif t == "h":                      # ICMP komunikacie
        vypisICMP(pkts_list, icmpy)
    else:
        print("Nespravny vstupny prikaz")

    return


def vypisTCP(pcap_list, tcpy, t):
    # k vypisu
    cisloKom = 1

    kompletna = 0
    nekompletna = 0

    print(main.farby.YELLOW, end='')
    if (t == "a"):
        print("Vypis HTTP komunikacii")
    elif (t == "b"):
        print("Vypis HTTPs komunikacii")
    elif (t == "c"):
        print("Vypis TELNET komunikacii")
    elif (t == "d"):
        print("Vypis SSH komunikacii")
    elif (t == "e"):
        print("Vypis FTP-riadiacich komunikacii")
    elif (t == "f"):
        print("Vypis FTP-datovych komunikacii")
    print(main.farby.WHITE, end='')

    for keys, values in kom.tcp.items():  # pre jednotlive komunikacie (key = dvojica uzlov)

        # kontrola (ne)kompletnosti --------------------------------------------

        # urgent    - nezaujimave
        # ack       - 10 ACK
        # push      - 18 PSH ACK
        # reset     - 04 RST ; C PSH RST?; 14 RST ACK; 24 URG RST
        # syn       - 02 SYN ; 06 (nebude); 22 URG SYN?; 12 SYN ACK
        # fin       - 01 FIN ; 03 05 09 (nebude); 11 FIN ACK; 21 FIN URG?

        # pre zaciatok komunikacie treba bud: 2X SYN ACK;  2X SYN 2x ACK;  1X SYN ACK 1X SYN 1X ACK
        # pre koniec treba: 1x RST ACK; 1x RST; 2x FIN ACK; 1x FIN ACK; 1x FIN; 2x FIN ... (ACK PSH FIN ?)

        syn_ack = syn = ack = 0
        rst_ack = rst = fin_ack = fin = fin_psh_ack = 0
        psh_ack = 0

        # zistenie sprav
        for value in values:

            ramec = str(bytes_hex(pcap_list[value - 1]))  # string obsahujuci aktualny ramec
            flag = ramec[96:98]

            if flag == "12":  # SYN ACK
                syn_ack += 1
            elif flag == "02":  # SYN
                syn += 1
            elif flag == "10":  # ACK
                ack += 1
            elif flag == "14":  # RST ACK
                rst_ack += 1
            elif flag == "04":  #RST
                rst += 1
            elif flag == "11":  #FIN ACK
                fin_ack += 1
            elif flag == "01":  #FIN
                fin += 1
            elif flag == "18":  # PSH ACK
                psh_ack += 1
            elif flag == "19":  # FIN PSH ACK
                fin_psh_ack += 1

        # kontrola
        # print(syn_ack, syn, ack, rst_ack, psh_ack, rst, fin_ack, fin)
        # print(syn_ack + syn + ack + rst_ack + psh_ack + rst + fin_ack + fin)

        zac = kon = 0
        # zistenie ci to splna poziadavky na komunikaciu -----------------------------------------

        # zaciatok - zadanie "obsahuje otvorenie SYN ... "
        if (syn_ack == 2) or (syn == 2 and ack >= 2) or (syn == 1 and ack >= 2 and syn_ack == 1) \
                or (syn == 2 and psh_ack >= 2) or (syn == 1 and psh_ack >= 2 and syn_ack == 1) \
                or (syn == 2 and ack >= 1 and psh_ack >= 1) or \
                (syn == 1 and ack >= 1 and psh_ack >= 1 and syn_ack == 1):
            zac = 1         # ak nieje zac 1 nie je to ani komunikacia

        # koniec - zadanie: "...a ukoncenie FIN na oboch stracach alebo FIN a RST alebo iba RST"
        if (fin == 2) or (fin == 1 and fin_ack == 1) or (fin_ack == 2) or (rst >= 1) or (rst_ack >= 1) \
                or (fin_psh_ack == 2) or (fin_psh_ack == 1 and fin == 1) or (fin_psh_ack == 1 and fin_ack == 1):
            kon = 1         # pri nekompletnych kon == 0

        # k vypisu ---------------------------------------------------------------------------------------
        # ak este nemame taku komunikaciu, zacala korektne a skoncila / neskoncila (kompletna/nekompletna)
        if (kompletna == 0 and zac == 1 and kon == 1) or (nekompletna == 0 and zac == 1 and kon == 0):

            print(main.farby.CYAN + "\nKomunikacia c.", cisloKom, main.farby.WHITE)

            # flagy
            if (zac == 1 and kon == 1):
                kompletna = 1
                print("Prva kompletna komunikacia, ", end='')
            elif (zac == 0 and kon == 1) or (zac == 1 and kon == 0):
                nekompletna = 1
                print("Prva nekompletna komunikacia, ", end='')

            print("pocet ramcov v komunikacii:", len(values), "\n")

            cisloRamca = 1
            for value in values:

                if ((cisloRamca <= main.glob.LIMIT_VYPISU) or (cisloRamca > len(values) - main.glob.LIMIT_VYPISU)):

                    ramec = str(bytes_hex(pcap_list[value - 1]))  # string obsahujuci aktualny ramec

                    print("ramec", value)

                    flag = ramec[96:98]

                    if flag == "12":  # SYN ACK
                        flag = "SYN ACK"
                    elif flag == "02":  # SYN
                        flag = "SYN"
                    elif flag == "10":  # ACK
                        flag = "ACK"
                    elif flag == "14":  # RST ACK
                        flag = "RST ACK"
                    elif flag == "04":  # RST
                        flag = "RST"
                    elif flag == "11":  # FIN ACK
                        flag = "FIN ACK"
                    elif flag == "01":  # FIN
                        flag = "FIN"
                    elif flag == "18":  # PSH ACK
                        flag = "PSH ACK"
                    elif flag == "19":  # FIN PSH ACK
                        flag = "FIN PSH ACK"

                    print("flag:", flag)

                    dlzka_API = len(pcap_list[value - 1])   # dlzka aktualneho ramca
                    dlzka = dlzka_API                       # dlzka presnasana po mediu
                    max_rozsah = ((dlzka_API * 2) + main.glob.ZACIATOK_RAMCA)  # rozsah informacie v packete - pre vypis

                    # DLZKA RAMCA -------------------------------------------------------
                    if (dlzka_API + main.glob.VELKOST_HLAVICKY) < main.glob.MIN_DLZKA_RAMCA:
                        dlzka = main.glob.MIN_DLZKA_RAMCA
                    else:
                        dlzka += main.glob.VELKOST_HLAVICKY

                    print("dlzka ramca poskytnuta pcap API -", dlzka_API, "B")
                    print("dlzka ramca prenasaneho po mediu -", dlzka, "B")

                    # TYP RAMCA ---------------------------------------------------------
                    print(main.farby.GREEN + zadanie1.get_typ_ramca(ramec) + main.farby.WHITE)

                    # MAC ADRESY --------------------------------------------------------
                    print("Zdrojova MAC adresa:", main.farby.YELLOW + zadanie1.get_src_mac(ramec) + main.farby.WHITE)
                    print("Cielova MAC adresa: ", main.farby.BLUE + zadanie1.get_dest_mac(ramec) + main.farby.WHITE)

                    # IDENTIFIKACIA ETHERTYPES ------------------------------------------
                    print(main.farby.GREEN + "", end='')
                    print("TCP")
                    print("" + main.farby.WHITE, end='')

                    src_ip, ipStatistika = zadanie2_3.ipv4_getSrcIp(ramec, None, None)
                    dest_ip = zadanie2_3.ipv4_getDestIp(ramec)

                    print("zdrojova IP adresa:", src_ip)
                    print("cielova IP adresa: ", dest_ip)

                    # vnoreny_protokol = getTCPprotokol(ramec, tcpy)

                    src_port = ramec[main.glob.START_SRC_TCP_PORT:main.glob.END_SRC_TCP_PORT]
                    dest_port = ramec[main.glob.END_SRC_TCP_PORT:main.glob.END_DST_TCP_PORT]

                    s = d = 1
                    for key, value in tcpy.items():
                        if (src_port == key):
                            print("src port: ", int(src_port, 16), "-", value)
                            s = 0
                            break

                    for key, value in tcpy.items():
                        if (dest_port == key):
                            print("dest port:", int(dest_port, 16), "-", value)
                            d = 0
                            break

                    if s:
                        print("src port: ", int(src_port, 16))
                    if d:
                        print("dest port:", int(dest_port, 16))

                    # VYPIS RAMCA -------------------------------------------------------
                    zadanie1.print_ramec(ramec, max_rozsah)
                    print("\n")

                cisloRamca += 1

        # ak uz mame kompletnu aj nekompletnu
        if (kompletna == 1 and nekompletna == 1):
            main.ipStatistika = {}  # reset
            kom.tcp = {}
            return

        cisloKom += 1

    if (kompletna == 0):
        print("V subore nebola najdena kompletna komunikacia")
    if (nekompletna == 0):
        print("V subore nebola najdena nekompletna komunikacia")

    # reset
    main.ipStatistika = {}
    kom.tcp = {}
    return


def vypisARP(pcap_list):

    print(main.farby.YELLOW + "VYPIS ARP DVOJIC" + main.farby.WHITE)

    if (len(kom.arp) == 0):
        print("subor neobsahuje ARP komunikaciu")

    # k vypisu
    cisloKom = 1
    for keys, values in kom.arp.items():        # pre jednotlive komunikacie (key = dvojica uzlov)

        print(main.farby.CYAN + "\nKomunikacia c.", cisloKom, main.farby.WHITE)
        print("pocet ramcov v komunikacii:", len(values), end='')

        cisloRamca = 1
        for value in values:

            # vypis prvych 10 a poslednych 10 ramcov (kom. c. 2 v trace-27.pcap)
            if ((cisloRamca <= main.glob.LIMIT_VYPISU) or (cisloRamca > len(values) - main.glob.LIMIT_VYPISU)):

                ramec = str(bytes_hex(pcap_list[value-1]))                  # string obsahujuci aktualny ramec
                dlzka_API = len(pcap_list[value-1])                         # dlzka aktualneho ramca
                dlzka = dlzka_API                                           # dlzka presnasana po mediu
                max_rozsah = ((dlzka_API * 2) + main.glob.ZACIATOK_RAMCA)   # rozsah informacie v packete - pre vypis

                # minimalna dlzka (60 + 4)
                if (dlzka_API + main.glob.VELKOST_HLAVICKY) < main.glob.MIN_DLZKA_RAMCA:
                    dlzka = main.glob.MIN_DLZKA_RAMCA
                else:
                    dlzka += main.glob.VELKOST_HLAVICKY

                opcode = ramec[main.glob.ARP_OPCODE_START:main.glob.ARP_OPCODE_END]
                srcMAC = hexToMAC(ramec[main.glob.ARP_OPCODE_END:main.glob.ARP_SRCMAC_END])
                srcIP = hexToIP(ramec[main.glob.ARP_SRCMAC_END:main.glob.ARP_SRCIP_END])
                destMAC = hexToMAC(ramec[main.glob.ARP_SRCIP_END:main.glob.ARP_DESTMAC_END])
                destIP = hexToIP(ramec[main.glob.ARP_DESTMAC_END:main.glob.ARP_DESTIP_END])

                if destMAC == "00 00 00 00 00 00 ":
                    destMAC = "???"

                # vypis ------------------------------------------------------------------------------------
                if opcode == "01":
                    print(main.farby.MAGENTA + "\n\nARP-Request, IP adresa:", destIP, "MAC adresa:", destMAC)
                    print("Zdrojova IP:", srcIP, "Cielova IP adresa:", destIP, main.farby.WHITE, end='')
                elif opcode == "02":
                    print(main.farby.RED + "\n\nARP-Reply, IP adresa:", srcIP, "MAC adresa:", srcMAC)
                    print("Zdrojova IP:", srcIP, "Cielova IP adresa:", destIP, main.farby.WHITE, end='')

                print("\nramec", value)
                print("dlzka ramca poskytnuta pcap API -", dlzka_API, "B")
                print("dlzka ramca prenasaneho po mediu -", dlzka, "B")
                print(main.farby.GREEN + "Ethernet II\nARP", main.farby.WHITE)
                print("Zdrojova MAC adresa:", main.farby.YELLOW + zadanie1.get_src_mac(ramec) + main.farby.WHITE)
                print("Cielova MAC adresa: ", main.farby.BLUE + zadanie1.get_dest_mac(ramec) + main.farby.WHITE)
                zadanie1.print_ramec(ramec, max_rozsah)
                # vypis ------------------------------------------------------------------------------------

            cisloRamca += 1

        cisloKom += 1
        print("")

    # reset
    main.ipStatistika = {}
    kom.arp = {}
    kom.req = kom.rep = kom.arp_nekompl = kom.arp_kompl = -1
    return


def vypisTFTP(pcap_list):
    print(main.farby.YELLOW + "VYPIS TFTP KOMUNIKACII" + main.farby.WHITE)

    if (kom.tftp_no == 0):
        print("subor neobsahuje TFTP komunikaciu")

    # k vypisu
    cisloKom = 1
    for keys, values in kom.tftp.items():  # pre jednotlive komunikacie (key = dvojica uzlov)

        print(main.farby.CYAN + "\nKomunikacia c.", cisloKom, main.farby.WHITE)
        print("pocet ramcov v komunikacii:", len(values), end='')

        cisloRamca = 1
        for value in values:

            # vypis prvych 10 a poslednych 10 ramcov (kom. c. 1 v eth-9.pcap)
            if ((cisloRamca <= main.glob.LIMIT_VYPISU) or (cisloRamca > len(values) - main.glob.LIMIT_VYPISU)):

                ramec = str(bytes_hex(pcap_list[value - 1]))     # string obsahujuci aktualny ramec
                dlzka_API = len(pcap_list[value - 1])            # dlzka aktualneho ramca
                dlzka = dlzka_API                                # dlzka presnasana po mediu
                max_rozsah = ((dlzka_API * 2) + main.glob.ZACIATOK_RAMCA)                   # rozsah informacie v packete - pre vypis
                if (dlzka_API + main.glob.VELKOST_HLAVICKY) < main.glob.MIN_DLZKA_RAMCA:    # minimalna dlzka (60 + 4)
                    dlzka = main.glob.MIN_DLZKA_RAMCA
                else:
                    dlzka += main.glob.VELKOST_HLAVICKY

                opcode = ramec[main.glob.TFTP_OPCODE_START:main.glob.TFTP_OPCODE_END]
                srcIP, pom = zadanie2_3.ipv4_getSrcIp(ramec, None, None)
                destIP = zadanie2_3.ipv4_getDestIp(ramec)
                src_port = int(ramec[main.glob.TFTP_SRCPORT_START:main.glob.TFTP_SRCPORT_END], 16)
                dest_port = int(ramec[main.glob.TFTP_SRCPORT_END:main.glob.TFTP_DESTPORT_END], 16)

                # vypis ------------------------------------------------------------------------------------
                if opcode == "01":
                    print(main.farby.MAGENTA + "\n\nRead Request, \nod ", srcIP, "port", src_port)
                    print("pre", destIP, "port", dest_port, main.farby.WHITE, end='')
                elif opcode == "02":
                    print(main.farby.MAGENTA + "\n\nWrite Request, \nod ", srcIP, "port", src_port)
                    print("pre", destIP, "port", dest_port, main.farby.WHITE, end='')
                elif opcode == "03":
                    print(main.farby.BLUE + "\n\nData, \nod ", srcIP, "port", src_port)
                    print("pre", destIP, "port", dest_port, main.farby.WHITE, end='')
                elif opcode == "04":
                    print(main.farby.BLUE + "\n\nAcknowledgement, \nod ", srcIP, "port", src_port)
                    print("pre", destIP, "port", dest_port, main.farby.WHITE, end='')
                elif opcode == "05":
                    print(main.farby.MAGENTA + "\n\nError Code, \nod ", srcIP, "port", src_port)
                    print("pre", destIP, "port", dest_port, main.farby.WHITE, end='')

                print("\nramec", value)
                print("dlzka ramca poskytnuta pcap API -", dlzka_API, "B")
                print("dlzka ramca prenasaneho po mediu -", dlzka, "B")
                print(main.farby.GREEN + "Ethernet II", main.farby.WHITE)
                print("Zdrojova MAC adresa:", main.farby.YELLOW + zadanie1.get_src_mac(ramec) + main.farby.WHITE)
                print("Cielova MAC adresa: ", main.farby.BLUE + zadanie1.get_dest_mac(ramec) + main.farby.WHITE)
                print(main.farby.GREEN + "IPv4", main.farby.WHITE)
                print("zdrojova IP adresa:", srcIP, "\ncielova IP adresa: ", destIP)
                print(main.farby.GREEN + "UDP", main.farby.WHITE)
                zadanie1.print_ramec(ramec, max_rozsah)
                # vypis ------------------------------------------------------------------------------------

            cisloRamca += 1

        cisloKom += 1
        print("")

    # reset
    main.ipStatistika = {}
    kom.tftp = {}
    kom.tftp_no = 0
    kom.opcode = kom.prvy_opcode = kom.tftp_a_ip = kom.tftp_b_ip = kom.tftp_a_port = kom.tftp_b_port = ""
    return


def getICMPtype(typ, icmpy):
    for key, value in icmpy.items():
        if key == typ:
            return value
    return (int(key, 16))


def vypisICMP(pcap_list, icmpy):
    print(main.farby.YELLOW + "VYPIS ICMP KOMUNIKACII" + main.farby.WHITE)

    if (len(kom.icmp) == 0):
        print("subor neobsahuje ICMP komunikaciu")

    # k vypisu
    cisloKom = 1
    for keys, values in kom.icmp.items():  # pre jednotlive komunikacie (key = dvojica uzlov)

        print(main.farby.CYAN + "\nKomunikacia c.", cisloKom, main.farby.WHITE)
        print("pocet ramcov v komunikacii:", len(values), "\n")

        cisloRamca = 1
        for value in values:

            if ((cisloRamca <= main.glob.LIMIT_VYPISU) or (cisloRamca > len(values) - main.glob.LIMIT_VYPISU)):

                ramec = str(bytes_hex(pcap_list[value - 1]))     # string obsahujuci aktualny ramec

                header_len = int(ramec[31:32], 16)
                typ = ramec[(header_len * 4 * 2) + 30:(header_len * 4 * 2) + 30 + 2]

                dlzka_API = len(pcap_list[value - 1])
                dlzka = dlzka_API
                max_rozsah = ((dlzka_API * 2) + main.glob.ZACIATOK_RAMCA)

                if (dlzka_API + main.glob.VELKOST_HLAVICKY) < main.glob.MIN_DLZKA_RAMCA:
                    dlzka = main.glob.MIN_DLZKA_RAMCA
                else:
                    dlzka += main.glob.VELKOST_HLAVICKY

                srcIP, pom = zadanie2_3.ipv4_getSrcIp(ramec, None, None)
                destIP = zadanie2_3.ipv4_getDestIp(ramec)

                print("ramec", value, end='')
                typ = getICMPtype(typ, icmpy)
                print(main.farby.MAGENTA, "typ:", typ, main.farby.WHITE) # todo what je 30

                print("dlzka ramca poskytnuta pcap API -", dlzka_API, "B")
                print("dlzka ramca prenasaneho po mediu -", dlzka, "B")
                print(main.farby.GREEN + "Ethernet II", main.farby.WHITE)
                print("Zdrojova MAC adresa:", main.farby.YELLOW + zadanie1.get_src_mac(ramec) + main.farby.WHITE)
                print("Cielova MAC adresa: ", main.farby.BLUE + zadanie1.get_dest_mac(ramec) + main.farby.WHITE)
                print(main.farby.GREEN + "IPv4", main.farby.WHITE)
                print("zdrojova IP adresa:", srcIP, "\ncielova IP adresa: ", destIP)
                print(main.farby.GREEN + "ICMP", main.farby.WHITE)
                zadanie1.print_ramec(ramec, max_rozsah)
                print("\n")

            cisloRamca += 1

        cisloKom += 1
        print("")

    # reset
    main.ipStatistika = {}
    kom.icmp = {}
    return


def getTCPprotokol(ramec, tcpy):
    srcPort = ""
    dstPort = ""

    for i in range(main.glob.START_SRC_TCP_PORT, main.glob.END_SRC_TCP_PORT):
        srcPort += ramec[i]
    for i in range(main.glob.END_SRC_TCP_PORT, main.glob.END_DST_TCP_PORT):
        dstPort += ramec[i]

    for key, value in tcpy.items():
        if (srcPort == key) or (dstPort == key):
            return value


def getUDPprotokol(ramec, udpy):
    srcPort = ""
    dstPort = ""

    for i in range(main.glob.START_SRC_UDP_PORT, main.glob.END_SRC_UDP_PORT):
        srcPort += ramec[i]
    for i in range(main.glob.END_SRC_UDP_PORT, main.glob.END_DST_UDP_PORT):
        dstPort += ramec[i]

    for key, value in udpy.items():
        if (srcPort == key) or (dstPort == key):
            return value


# vytvori zoznam komunikacii
def vyberProtokol(pcap_list, no, hladanyTyp, etherTypy, lsapy, ipProtokoly, tcpy, udpy):

    ramec = str(bytes_hex(pcap_list[no]))    # string obsahujuci aktualny ramec
    poradove_cislo = no + 1                  # poradove cislo ramca v subore
    hladany_tcp = ""
    tcp = 0

    typRamca = zadanie1.get_typ_ramca(ramec)
    protokol = zadanie2_3.getVnorenyProtokol(ramec, typRamca, etherTypy, lsapy)

    if hladanyTyp == "a":               # HTTP - TCP - IPv4 --------------------- trace-6.pcap, trace-20.pcap
        tcp = 1
        hladany_tcp = "HTTP"
    elif hladanyTyp == "b":             # HTTPS - TCP - IPv4 --------------------- trace-27.pcap
        tcp = 1
        hladany_tcp = "HTTPs"
    elif hladanyTyp == "c":             # TELNET - TCP - IPv4 --------------------- eth-7.pcap
        tcp = 1
        hladany_tcp = "TELNET"
    elif hladanyTyp == "d":             # SSH - TCP - IPv4 --------------------- eth-5.pcap
        tcp = 1
        hladany_tcp = "SSH"
    elif hladanyTyp == "e":             # FTP-CONTROL - TCP - IPv4 --------------------- trace-8.pcap
        tcp = 1
        hladany_tcp = "FTP-CONTROL"
    elif hladanyTyp == "f":             # FTP-DATA - TCP - IPv4 --------------------- trace-8.pcap
        tcp = 1
        hladany_tcp = "FTP-DATA"

    if tcp == 1:
        if protokol == "IPv4":
            vnoreny_protokol_IPv4 = zadanie2_3.ipv4_getVnorenyProtokol(ramec, ipProtokoly)
            if vnoreny_protokol_IPv4 == "TCP":
                vnoreny_protokol_TCP = getTCPprotokol(ramec, tcpy)
                if vnoreny_protokol_TCP == hladany_tcp:

                    # kontrola SYN - src uzol a dest uzol
                    # kontrola SYN ACK - dest uzla
                    # kontrola ACK - src uzla
                    # kontrola PSH ACK
                    # kym su spravy od spravnych uzlov
                    # kontrola FIN PSH ACK / FIN ACK
                    # pripadne dalsi ramec
                    # kontrola FIN ACK
                    # kontrola ACK

                    src_ip = ramec[main.glob.START_SRC_IP:main.glob.END_SRC_IP]
                    dest_ip = ramec[main.glob.END_SRC_IP:main.glob.END_DEST_IP]
                    src_port = ramec[main.glob.START_SRC_TCP_PORT:main.glob.END_SRC_TCP_PORT]
                    dest_port = ramec[main.glob.END_SRC_TCP_PORT:main.glob.END_DST_TCP_PORT]

                    dvojica = src_ip + src_port + dest_ip + dest_port
                    dvojicaRev = dest_ip + dest_port + src_ip + src_port

                    if dvojica not in kom.tcp:
                        if dvojicaRev not in kom.tcp:
                            # nova komunikacia - uzly nie su zaznamenane
                            kom.tcp.update({dvojica: [poradove_cislo]})
                        else:  # dvojica uz existuje len je ulozena s inym poradim uzlov
                            kom.tcp[dvojicaRev].append((poradove_cislo), )

                    else:  # pridanie do komunikacie -----------------
                        kom.tcp[dvojica].append((poradove_cislo), )

                    # print("cislo", poradove_cislo, src_ip, src_port, ";", dest_ip, dest_port,"flag", ramec[96:98])

    # In TFTP, a transfer is initiated by the client issuing a request to
    # read or write a particular file on the server.
    # A data packet of less than 512 bytes or the agreed blocksize option
    # signals termination of a transfer.

    elif hladanyTyp == "g":         # TFTP - UDP - IPv4 --------------------- eth-8.pcap, eth-9.pcap, trace-15.pcap
        if protokol == "IPv4":
            vnoreny_protokol_IPv4 = zadanie2_3.ipv4_getVnorenyProtokol(ramec, ipProtokoly)
            if vnoreny_protokol_IPv4 == "UDP":

                # 02 WRQ, 01 RRQ, 04 ACK - aktualny opcode
                opcode = ramec[main.glob.TFTP_OPCODE_START:main.glob.TFTP_OPCODE_END]

                vnoreny_protokol_UDP = getUDPprotokol(ramec, udpy)  # -------------------------- TFTP
                if vnoreny_protokol_UDP == "TFTP":                  # prva sprava na port 69

                    kom.tftp_no += 1                                # cislo TFTP komunikacie
                    # print ("Komunikacia c.", kom.tftp_no)

                    # IP adresy a ID
                    kom.tftp_a_ip, pom = zadanie2_3.ipv4_getSrcIp(ramec, None, None)
                    kom.tftp_b_ip = zadanie2_3.ipv4_getDestIp(ramec)
                    dvojica = kom.tftp_a_ip + " " + kom.tftp_b_ip + " " + str(kom.tftp_no)     # ID
                    kom.prvy_opcode = kom.opcode = opcode

                    kom.tftp_a_port = int(ramec[main.glob.TFTP_SRCPORT_START:main.glob.TFTP_SRCPORT_END], 16)
                    kom.tftp_b_port = int(ramec[main.glob.TFTP_SRCPORT_END:main.glob.TFTP_DESTPORT_END], 16)

                    # print(kom.tftp_a_port, kom.tftp_b_port)
                    # print(kom.tftp_a_ip, "->", kom.tftp_b_ip, "kod", opcode, "ramec", poradove_cislo)

                    # pridanie do zoznamu komunikujucich dvojic
                    kom.tftp.update({dvojica: [poradove_cislo]})

                else:                                               # iny UDP ramec
                    src, pom = zadanie2_3.ipv4_getSrcIp(ramec, None, None)
                    dest = zadanie2_3.ipv4_getDestIp(ramec)

                    # ak su to tie iste uzly
                    if ((src == kom.tftp_a_ip and dest == kom.tftp_b_ip) or (dest == kom.tftp_a_ip and src == kom.tftp_b_ip)):

                        # ID
                        if (src == kom.tftp_a_ip):
                            dvojica = src + " " + dest + " " + str(kom.tftp_no)
                        else:
                            dvojica = dest + " " + src + " " + str(kom.tftp_no)

                        # porty
                        src_port = int(ramec[main.glob.TFTP_SRCPORT_START:main.glob.TFTP_SRCPORT_END], 16)
                        dest_port = int(ramec[main.glob.TFTP_SRCPORT_END:main.glob.TFTP_DESTPORT_END], 16)

                        # print (src_port, dest_port)

                        if (kom.tftp_b_port == 69):          # aj je to prva odpoved servera - zistenie portu
                            kom.tftp_b_port = src_port

                        # ak sprava smeruje na prislusne porty
                        if (src_port == kom.tftp_a_port and dest_port == kom.tftp_b_port) or (src_port == kom.tftp_b_port and dest_port == kom.tftp_a_port):

                            # print(src, "->", dest, "kod", opcode, "ramec", poradove_cislo)

                            # ak spravne nasleduju opcody ------------------------------------------------------

                            # RRQ - a posiela ACK, b DAT
                            if kom.prvy_opcode == "01":
                                # a RRQ -> b DAT -> a
                                if (kom.opcode == "01" and opcode == "03" and src == kom.tftp_b_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # b DAT -> a ACK -> b
                                elif (kom.opcode == "03" and opcode == "04" and src == kom.tftp_a_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # a ACK -> b DAT -> a
                                elif (kom.opcode == "04" and opcode == "03" and src == kom.tftp_b_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # b DAT -> b DAT -> a
                                elif (kom.opcode == "03" and opcode == "03" and src == kom.tftp_b_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # error code
                                elif (opcode == "05"):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # a ERROR -> b DAT -> a
                                elif (kom.opcode == "05" and opcode == "03" and src == kom.tftp_b_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode

                            # WRQ - a posiela DAT, b posiela ACK
                            elif kom.prvy_opcode == "02":
                                # a WRQ -> b ACK -> a
                                if (kom.opcode == "02" and opcode == "04" and src == kom.tftp_b_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # b ACK -> a DAT -> b
                                elif (kom.opcode == "04" and opcode == "03" and src == kom.tftp_a_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # a DAT -> b ACK -> a
                                elif (kom.opcode == "03" and opcode == "04" and src == kom.tftp_b_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # a DAT -> a DAT -> b
                                elif (kom.opcode == "03" and opcode == "03" and src == kom.tftp_a_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # error code
                                elif (opcode == "05"):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode                             # nastavenie prew opcode
                                # b ERROR -> a DAT -> b
                                elif (kom.opcode == "05" and opcode == "03" and src == kom.tftp_a_ip):
                                    kom.tftp[dvojica].append((poradove_cislo), )    # pridanie do zoznamu komunikujucich dvojic
                                    kom.opcode = opcode

                        # print(src, "->", dest, "kod", opcode, "ramec", poradove_cislo)

    # "Icmp netreba parovat, teda staci vam mat len filter kde budete vypisovat ramce
    # ktore budu mat eth2, Ipv4, ICMP a treba vypisat typ icmp spravy." - helebrant na videu co mam nahrane

    elif hladanyTyp == "h":         # ICMP - IP --------------------- eth-9.pcap, trace_ip_nad_20_B.pcap
        if protokol == "IPv4":
            vnoreny_protokol_IP = zadanie2_3.ipv4_getVnorenyProtokol(ramec, ipProtokoly)
            if vnoreny_protokol_IP == "ICMP":

                srcIP, pom = zadanie2_3.ipv4_getSrcIp(ramec, None, None)
                destIP = zadanie2_3.ipv4_getDestIp(ramec)

                dvojica = str(srcIP) + " " + str(destIP)
                dvojicaRev = str(destIP) + " " + str(srcIP)

                # pridanie do zoznamu komunikujucich dvojic
                if dvojica not in kom.icmp:
                    if dvojicaRev not in kom.icmp:
                        # nova komunikacia - uzly nie su zaznamenane
                        kom.icmp.update({dvojica: [poradove_cislo]})
                    else:  # dvojica uz existuje len je ulozena s inym poradim uzlov
                        kom.icmp[dvojicaRev].append((poradove_cislo), )

                else:  # pridanie do komunikacie -----------------
                    kom.icmp[dvojica].append((poradove_cislo), )

    elif hladanyTyp == "i":         # ARP -------------------------- trace-1.pcap, trace-2.pcap, trace-27.pcap
        if protokol == "ARP":       # ak najdeme ARP ramec

            # zistime opcode atd
            opcode = ramec[main.glob.ARP_OPCODE_START:main.glob.ARP_OPCODE_END]
            srcIP = ramec[main.glob.ARP_SRCMAC_END:main.glob.ARP_SRCIP_END]
            destIP = ramec[main.glob.ARP_DESTMAC_END:main.glob.ARP_DESTIP_END]

            # vytvorenie dvojice - sluzi ako ID / key - na parovanie komunikacii
            dvojica = ""
            if opcode == "01":                              # sedi ci a -> b alebo b -> a
                dvojica = str(srcIP) + " " + str(destIP)
            elif opcode == "02":
                dvojica = str(destIP) + " " + str(srcIP)

            # ak nema zaznam o dvojici - kompletnu kom. - pridanie do zoznamu komunikujucich dvojic
            if dvojica not in kom.arp:

                kom.arp.update({dvojica: [poradove_cislo]})     # nova komunikacia ---------------------------

            # ak dvojica komunikovala
            else:

                # ak sme nasli odpoved (reply)
                if opcode == "02":
                    kom.arp[dvojica].append((poradove_cislo), )     # pridanie do komunikacie ----------------
                    newKey = dvojica + str(kom.arp_komp_no)         # ID -> IP + IP + cislo kompletnej kom.
                    kom.arp_komp_no += 1                            # zvysenie poctu kompl. kom
                    kom.arp[newKey] = kom.arp[dvojica]              # aby sme uzavreli komunikaciu
                    del kom.arp[dvojica]

                # ak je to dalsi request
                else:
                    kom.arp[dvojica].append((poradove_cislo), )     # pridanie do komunikacie ----------------

                # print("komunikacia c.", cisloKom, "obsahuje", opcode)
