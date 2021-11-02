from scapy.all import rdpcap
from scapy.compat import bytes_hex

import main
import zadanie2_3
import zadanie4


def start(etherTypy, lsapy, ipProtokoly, udpy, tcpy, icmpy, ipStatistika):

    # pathname = "./pcaps/trace-25.pcap"
    pathname = "./pcaps/" + input("\nZadaj nazov suboru: ")

    print("")

    try:
        pkts_list = rdpcap(pathname)                # loading
    except FileNotFoundError:
        print("Subor", pathname[8:], "neexistuje")
        start(etherTypy, lsapy, ipProtokoly, udpy, tcpy, icmpy, ipStatistika)
        return ipStatistika

    num = len(pkts_list)                            # pocet ramcov

    # pkts_list[0].show()

    for i in range(0, num):                         # volanie vypisu
        ipStatistika = pkt_print(pkts_list, i, etherTypy, lsapy, ipProtokoly, udpy, tcpy, icmpy, ipStatistika)

    zadanie2_3.vypisIPstatistiku(ipStatistika)

    return ipStatistika


def get_typ_ramca(ramec):
    typ_ramca = ""          # cast co urcuje typ ramca
    presny_typ_ramca = ""   # aky typ IEEE ramca to je

    for i in range((main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA), (main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_ETHERTYPE)):
        typ_ramca += ramec[i]
    for i in range((main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_ETHERTYPE), (main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + 2 * main.glob.DLZKA_ETHERTYPE)):
        presny_typ_ramca += ramec[i]

    # print(int(typ_ramca, 16))
    if int(typ_ramca, 16) >= 1563:
        return ("Ethernet II")
    elif presny_typ_ramca == "aaaa":
        return ("IEEE 802.3 s LLC a SNAP")
    elif presny_typ_ramca == "ffff":
        return ("IEEE 802.3 - Raw")
    else:
        return ("IEEE 802.3 s LLC")  # 4242 aj e0e0 atd...


def get_src_mac(ramec):
    mac = ""
    for i in range(main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_MAC, main.glob.ZACIATOK_RAMCA + main.glob.OBE_MAC):
        mac += ramec[i].upper()
        if i % 2 == 1:  # medzery medzi dvojicami
            mac += " "
    return mac


def get_dest_mac(ramec):
    mac = ""
    for i in range(main.glob.ZACIATOK_RAMCA, main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_MAC):
        mac += (ramec[i].upper())
        if i % 2 == 1:  # medzery medzi dvojicami
            mac += " "
    return mac


def print_ramec(ramec, max_rozsah):
    color = ''
    typ = get_typ_ramca(ramec)
    for i in range(main.glob.ZACIATOK_RAMCA, max_rozsah):
        # farba
        if i in range(main.glob.ZACIATOK_RAMCA, main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_MAC):
            color = main.farby.BLUE
        elif i in range(main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_MAC, main.glob.ZACIATOK_RAMCA + main.glob.OBE_MAC):
            color = main.farby.YELLOW
        elif i in range(main.glob.ZACIATOK_RAMCA + main.glob.OBE_MAC, main.glob.ZACIATOK_RAMCA + main.glob.OBE_MAC + main.glob.DLZKA_TYP):
            if i < (main.glob.ZACIATOK_RAMCA + main.glob.OBE_MAC + main.glob.DLZKA_ETHERTYPE):
                color = main.farby.GREEN
            elif i >= (main.glob.ZACIATOK_RAMCA + main.glob.OBE_MAC + main.glob.DLZKA_ETHERTYPE) and typ != "Ethernet II":
                color = main.farby.GREEN
            else:
                color = main.farby.WHITE
        else:
            color = main.farby.WHITE
        # vypis
        print(color + ramec[i].upper(), end='')
        # formatovanie
        if i % 2 == 1:  # medzery medzi dvojicami
            print(" ", end='')
        if i % 16 == 1:
            print("  ", end='')
        if i % 32 == 1:  # odseky
            print("\n", end='')
    return


def pkt_print(pkts_list, no, etherTypy, lsapy, ipProtokoly, udpy, tcpy, icmpy, ipStatistika):

    ramec = str(bytes_hex(pkts_list[no]))   # string obsahujuci aktualny ramec
    dlzka_API = len(pkts_list[no])          # dlzka aktualneho ramca
    dlzka = dlzka_API                       # dlzka presnasana po mediu
    poradove_cislo = no + 1                 # poradove cislo ramca v subore
    max_rozsah = ((dlzka_API * 2) + main.glob.ZACIATOK_RAMCA)  # rozsah informacie v packete - pre vypis

    # PORADOVE CISLO RAMCA ----------------------------------------------
    print("ramec", poradove_cislo)

    # DLZKA RAMCA -------------------------------------------------------
    if (dlzka_API + main.glob.VELKOST_HLAVICKY) < main.glob.MIN_DLZKA_RAMCA:
        dlzka = main.glob.MIN_DLZKA_RAMCA
    else:
        dlzka += main.glob.VELKOST_HLAVICKY

    print("dlzka ramca poskytnuta pcap API -", dlzka_API, "B")
    print("dlzka ramca prenasaneho po mediu -", dlzka, "B")

    # TYP RAMCA ---------------------------------------------------------
    print(main.farby.GREEN + get_typ_ramca(ramec) + main.farby.WHITE)

    # MAC ADRESY --------------------------------------------------------
    print("Zdrojova MAC adresa:", main.farby.YELLOW + get_src_mac(ramec) + main.farby.WHITE)

    print("Cielova MAC adresa: ", main.farby.BLUE + get_dest_mac(ramec) + main.farby.WHITE)

    # IDENTIFIKACIA ETHERTYPES ------------------------------------------
    vnoreny_protokol = zadanie2_3.getVnorenyProtokol(ramec, get_typ_ramca(ramec), etherTypy, lsapy)
    print(main.farby.GREEN + "", end='')
    print(vnoreny_protokol)
    print("" + main.farby.WHITE, end='')

    # IP adresy a vnorene protokoly --------------------------------------
    if vnoreny_protokol == "IPv4":
        vnoreny_protokol = zadanie2_3.ipv4_getVnorenyProtokol(ramec, ipProtokoly)

        src_ip, ipStatistika = zadanie2_3.ipv4_getSrcIp(ramec, ipStatistika, vnoreny_protokol)
        dest_ip = zadanie2_3.ipv4_getDestIp(ramec)

        print("zdrojova IP adresa:", src_ip)
        print("cielova IP adresa: ", dest_ip)

        print(main.farby.GREEN + "", end='')
        print(vnoreny_protokol)
        print("" + main.farby.WHITE, end='')

        if vnoreny_protokol == "UDP":
            src_port = ramec[main.glob.START_SRC_UDP_PORT:main.glob.END_SRC_UDP_PORT]
            dest_port = ramec[main.glob.END_SRC_UDP_PORT:main.glob.END_DST_UDP_PORT]

            s = d = 1
            for key, value in udpy.items():
                if (src_port == key):
                    print("src port: ", int(src_port, 16), "-", value)
                    s = 0
                    break

            for key, value in udpy.items():
                if (dest_port == key):
                    print("dest port:", int(dest_port, 16), "-", value)
                    d = 0
                    break

            if s:
                print("src port: ", int(src_port, 16))
            if d:
                print("dest port:", int(dest_port, 16))

        elif vnoreny_protokol == "TCP":
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

        elif vnoreny_protokol == "ICMP":
            header_len = int(ramec[31:32], 16)
            typ = ramec[(header_len * 4 * 2) + 30:(header_len * 4 * 2) + 30 + 2]
            typ = zadanie4.getICMPtype(typ, icmpy)
            print("Type:", typ)

    elif vnoreny_protokol == "IPv6":
        vnoreny_protokol = zadanie2_3.ipv6_getVnorenyProtokol(ramec, ipProtokoly)

        src_ip = zadanie2_3.ipv6_getSrcIp(ramec)
        dest_ip = zadanie2_3.ipv6_getDestIp(ramec)

        print("zdrojova adresa:", src_ip)
        print("cielova adresa: ", dest_ip)

        print(main.farby.GREEN + "", end='')
        print(vnoreny_protokol)
        print("" + main.farby.WHITE, end='')

        if vnoreny_protokol == "UDP":
            src_port = ramec[110:114]
            dest_port = ramec[114:118]

            s = d = 1
            for key, value in udpy.items():
                if (src_port == key):
                    print("src port: ", int(src_port, 16), "-", value)
                    s = 0
                    break

            for key, value in udpy.items():
                if (dest_port == key):
                    print("dest port:", int(dest_port, 16), "-", value)
                    d = 0
                    break

            if s:
                print("src port: ", int(src_port, 16))
            if d:
                print("dest port:", int(dest_port, 16))

    elif vnoreny_protokol == "ARP":
        # vnoreny_protokol = zadanie2_3.ipv6_getVnorenyProtokol(ramec, ipProtokoly) # todo aj tu?

        opcode = ramec[main.glob.ARP_OPCODE_START:main.glob.ARP_OPCODE_END]
        src_ip = zadanie4.hexToIP(ramec[main.glob.ARP_SRCMAC_END:main.glob.ARP_SRCIP_END])
        dest_ip = zadanie4.hexToIP(ramec[main.glob.ARP_DESTMAC_END:main.glob.ARP_DESTIP_END])

        if opcode == "01":
            print("Type: Request")
        elif opcode == "02":
            print("Type: Reply")

        print("zdrojova IP adresa:", src_ip)
        print("cielova IP adresa: ", dest_ip)

        print(main.farby.GREEN + "", end='')
        # print(vnoreny_protokol)
        print("" + main.farby.WHITE, end='')

    # VYPIS RAMCA -------------------------------------------------------
    print_ramec(ramec, max_rozsah)
    print("\n")

    return ipStatistika
