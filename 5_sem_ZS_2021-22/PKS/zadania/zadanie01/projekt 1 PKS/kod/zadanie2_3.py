import main


def vypisIPstatistiku(ipStatistika) :
    try:

        print(main.farby.YELLOW + "IP adresy vysielajucich uzlov (IPv4):" + main.farby.WHITE)
        print("Adresa:", "\t\t\t", "Pocet sprav:")

        for key, value in ipStatistika.items():
            print(key, end='')              # ip adresa
            if (len(key) <= 8):
                print("\t\t\t\t ", end='')
            elif (len(key)) < 11:
                print("\t\t\t ", end='')
            elif (len(key)) <= 12:
                print("\t\t ", end='')
            elif (len(key) <= 15):
                print("\t\t ", end='')
            print(value)                    # pocet sprav

        print("\nCelkovy pocet uzlov:", len(ipStatistika))

        print(main.farby.YELLOW + "\nAdresa uzla s najvacsim poctom odoslanych paketov:" + main.farby.WHITE)
        v = list(ipStatistika.values())
        k = list(ipStatistika.keys())
        print(k[v.index(max(v))], "\t\t", ipStatistika[k[v.index(max(v))]], "paketov")

    except ValueError:
        print("Subor neobsahuje IPv4 ramce")


def nacitajSubor(etherTypy, lsapy, ipProtokoly, tcpy, udpy, icmpy):
    riadky = []
    switch = "x"

    with open("ExternySubor.txt") as subor:
        riadky = subor.readlines()

    pocetRiadkov = len(riadky)

    for i in range (0, pocetRiadkov) :

        # -------------------------------------------------------- fields
        # Ethertypes
        if riadky[i] == "#Ethertypes\n" :
            switch = "eth"
            i += 1
        # LSAPs
        elif riadky[i] == "#LSAPs\n" :
            switch = "lsap"
            i += 1
        # IPProtocolNumbers
        elif riadky[i] == "#IPProtocolNumbers\n" :
            switch = "ip"
            i += 1
        # TCPs
        elif riadky[i] == "#TCPs\n":
            switch = "tcp"
            i += 1
        # UDPs
        elif riadky[i] == "#UDPs\n":
            switch = "udp"
            i += 1
        # ICMPs
        elif riadky[i] == "#ICMPs\n":
            switch = "icmp"
            i += 1

        # -------------------------------------------------- switch
        if switch == "eth" :
            etherTypy[riadky[i][0:4]] = riadky[i][5:-1]
        elif switch == "lsap":
            lsapy[riadky[i][0:2]] = riadky[i][3:-1]
        elif switch == "ip" :
            ipProtokoly[riadky[i][0:2]] = riadky[i][3:-1]
        elif switch == "udp" :
            udpy[riadky[i][0:4]] = riadky[i][5:-1]
        elif switch == "tcp" :
            tcpy[riadky[i][0:4]] = riadky[i][5:-1]
        elif switch == "icmp" :
            icmpy[riadky[i][0:2]] = riadky[i][3:-1]

    subor.close()
    return etherTypy, lsapy, ipProtokoly, tcpy, udpy, icmpy


def ipv4_getSrcIp(ramec, ipStatistika, vnoreny_protokol) :
    dvojica = ""
    adresa = ""

    for i in range(main.glob.START_SRC_IP, main.glob.END_SRC_IP) :
        dvojica += ramec[i]
        if i % 2 == 1:
            adresa += str((int(dvojica, 16)))
            adresa += "."
            dvojica = ""
    adresa = adresa[:-1]

    # if vnoreny_protokol == "TCP":           # keby je statistika len pre IPv4 s TCP
    if vnoreny_protokol is not None:
        if adresa in ipStatistika:
            ipStatistika[adresa] += 1
        else:
            ipStatistika[adresa] = 1

    return adresa, ipStatistika


def ipv6_getSrcIp (ramec) :
    adresa = ""

    for i in range(main.glob.START_SRC_IPv6, main.glob.END_SRC_IPv6) :
        adresa += ramec[i]
        if i % 4 == 1 :
            adresa += ":"

    adresa = adresa[:-1]

    return adresa


def ipv4_getDestIp (ramec) :
    dvojica = ""
    adresa = ""

    for i in range(main.glob.END_SRC_IP, main.glob.END_DEST_IP):
        dvojica += ramec[i]
        if i % 2 == 1:
            adresa += str((int(dvojica, 16)))
            adresa += "."
            dvojica = ""

    return adresa[:-1]


def ipv6_getDestIp (ramec) :
    adresa = ""

    for i in range(main.glob.END_SRC_IPv6, main.glob.END_DEST_IPv6):
        adresa += ramec[i]
        if i % 4 == 1:
            adresa += ":"

    return adresa[:-1]


def ipv4_getVnorenyProtokol (ramec, ipProtokoly) :
    typ = ""

    for i in range(main.glob.START_IP_PROT, main.glob.END_IP_PROT):
        typ += ramec[i]

    for key, value in ipProtokoly.items():
        if typ == key:
            return value        # ak ho pozna

    return int(typ, 16)         # ak ho nepozna


def ipv6_getVnorenyProtokol (ramec, ipProtokoly) :
    typ = ""

    for i in range(main.glob.START_IPv6_PROT, main.glob.END_IPv6_PROT):
        typ += ramec[i]

    for key, value in ipProtokoly.items():
        if typ == key:
            return value        # ak ho pozna

    return int(typ, 16)         # ak ho nepozna


def getVnorenyProtokol (ramec, typRamca, etherTypy, lsapy):

    # ETHER II -------------------------------------------------------------------------------------
    if typRamca == "Ethernet II" :
        typ = ""  # cast co urcuje typ ramca

        for i in range((main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA),
                       (main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_ETHERTYPE)):
            typ += ramec[i]

        for key, value in etherTypy.items():
            if typ == key :
                return value            # ak ho pozna
        return int(typ, 16)             # ak ho nepozna

    # IEEE -----------------------------------------------------------------------------------------
    else:
        dsap = ""
        ssap = ""
        dsapSsap = ""

        for i in range((main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_ETHERTYPE),
                       (main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_ETHERTYPE + 2)):
            dsap += ramec[i]
        for i in range((main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_ETHERTYPE + 2),
                       (main.glob.OBE_MAC + main.glob.ZACIATOK_RAMCA + main.glob.DLZKA_ETHERTYPE + 4)):
            ssap += ramec[i]

        dsapSsap += (dsap + " " + ssap)

        for key, value in lsapy.items():
            if dsap == key :
                return value        # ak ho pozna

        dsapSsap = "DSAP: " + dsap + ", " + "SSAP: " + ssap
        return dsapSsap             # ak ho nepozna