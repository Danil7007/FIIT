from scapy.all import *
import sys
import os

F_NONE = None
F_ETHERNET_II = 1
F_IEEE_RAW = 2
F_IEEE_LLC = 3
F_IEEE_LLC_SNAP = 4

FrameTypes = {
    F_ETHERNET_II: "Ethernet II",
    F_IEEE_RAW: "IEEE 802.3 - RAW",
    F_IEEE_LLC: "IEEE 802.2 LLC",
    F_IEEE_LLC_SNAP: "IEEE 802.3 LLC + SNAP",
    None: "Unknown",
}

EtherTypes = {
    512: "XEROX PUP",
    513: "PUP Addr Trans",
    2048: "Internet IP (IPv4)",
    2049: "X.75 Internet",
    2053: "X.25 Level 3",
    2054: "ARP (Address Resolution Protocol)",
    32821: "Reverse ARP",
    32923: "Appletalk",
    33011: "AppleTalk AARP (Kinetics)",
    33024: "IEEE 802.1Q VLAN-tagged frames",
    33079: "Novell IPX",
    34525: "IPv6",
    34827: "PPP",
    34887: "MPLS",
    34888: "MPLS with upstream-assigned label",
    34915: "PPPoE Discovery Stage",
    34916: "PPPoE Session Stage",
    None: "Unknown",
    # todo: dopisat ostatnie?
}

IEEE_types = {
    170: "SNAP ...",  # IEEE 802.3 LLC + SNAP
    224: "IPX (Novell NetWare)",  # Novell 802.3 RAW
    0: "Null SAP",
    2: "LLC Sublayer Management / Individual",
    3: "LLC Sublayer Management / Group",
    6: "IP (DoD Internet Protocol",
    14: "PROWAY (IEC 955) Network Management, Maintenance and Installation",
    66: "BDPU (Bridge PDU / 802.1 Spanning Tree)",
    78: "MMS (Manufacturing Massage Service) EIA-RS 511",
    94: "ISI IP",
    126: "X.25 PLP (ISO 8208)",
    142: "PROWAY (IEC 955) Active Station List Maintenance",
    244: "LAN Management",
    254: "ISO Network Layer Protocols",
    255: "Global DSAP",
    None: "Unknown",  # Pre SAP ktore nie su v zozname
    # todo: dopisat ostatnie, secke sa 802.3 LLC
}

ipProtocols = {
    1: "ICMP",
    2: "IGMP",
    6: "TCP",
    # ...
    17: "UDP",
    # ...
    None: "Unknown protocol",
}

udpPorts = {
53: "DNS", # DORABKA
None: "Unknown"
}

tcpPorts = {}

def isEthernet(etherType):
    for et in EtherTypes.keys():
        if etherType == et:
            return F_ETHERNET_II, et  # Vrati typ ramcu a ether type
    return F_NONE, None  # Inak vrati None, None


def isIEEE(pLen, byteDsap, byteSsap):
    if byteDsap == 0xFF and byteSsap == 0xFF:  # IEEE 802.3 - RAW
        return F_IEEE_RAW, byteDsap, byteSsap
    elif byteDsap == 0xAA and byteSsap == 0xAA:  # IEEE 802.3 LLC + SNAP
        return F_IEEE_LLC_SNAP, byteDsap, byteSsap
    dsapType = None
    ssapType = None
    for sap in IEEE_types.keys():
        if sap == byteSsap:
            ssapType = sap
        if sap == byteDsap:
            dsapType = sap
    return F_IEEE_LLC, dsapType, ssapType


def getIP(byteArr):
    return '.'.join(str(x) for x in byteArr)


def getMAC(byteArr):
    return ':'.join(hex(x).replace("0x", "").zfill(2) for x in byteArr)


# -----------------

# ================== PACKET ===================
packetList = []
ipSrcDict = {}  # Zoznam zdrojovich IP a pocet IPv4 packetov ktore odoslali {IP:pocet}


class MyPacket():
    def __init__(self, packetIdx, packetData):
        # 1a) Vypis poradove cislo packetu
        self.packetIdx = packetIdx
        self.packetData = packetData
        # 1b) Dlzka podla API a prenasana po mediu
        self.length = str(len(self.packetData))
        self.mediaLength = int(self.length)
        if self.mediaLength <= 60:
            self.mediaLength = 64
        else:
            self.mediaLength += 4
        pLen = int.from_bytes(self.packetData[12:14], "big")
        self.frameType, self.protocol = isEthernet(pLen)
        # 1c) typ ramca
        self.dstMac = getMAC(self.packetData[0:6])
        self.srcMac = getMAC(self.packetData[6:12])
        if not self.frameType:
            self.frameType, self.dsapType, self.ssapType = isIEEE(pLen, self.packetData[14], self.packetData[15])
        # Ak je IPv4
        self.srcIP = ""
        self.dstIP = ""
        self.ipProtocol = ""
        self.srcPort = ""
        self.dstPort = ""
        if self.protocol == 2048:
            self.srcIP, self.dstIP, self.ipProtocol, self.srcPort, self.dstPort = processIPv4Packet(
                self)  # Data z EthernetII ramca
        if self.srcIP != "":
            if self.srcIP in ipSrcDict.keys():  # Ak je IP uz v slovniku
                ipSrcDict[self.srcIP] += 1  # Pripocitaj 1 k poctu byslanych paketov
            else:
                ipSrcDict[self.srcIP] = 1  # Inak, pridaj do slovnika
        # Ak je ARP
        if self.protocol == 2054:
            processArpPacket(self)

    def __str__(self):
        retStr = "Packet " + str(self.packetIdx+1) + ":\n"
        retStr += "Packet length by API: " + str(self.length) + "\n"
        retStr += "Packet lentgh on media: " + str(self.mediaLength) + "\n"
        retStr += "Destination MAC: " + self.dstMac + "\n"
        retStr += "Source MAC:      " + self.srcMac + "\n"

        byteArr = ' '.join(format(x, '02X') for x in self.packetData).split()
        for byteIdx, byteData in enumerate(byteArr):
            retStr += byteData + " "
            if (byteIdx + 1) % 16 == 0:
                retStr += "\n"  # Novy riadok
            elif (byteIdx + 1) % 8 == 0:
                retStr += "  "  # Odsadi druhy "stlpec"
        retStr += "\n"
        if self.frameType == F_ETHERNET_II:
            retStr += FrameTypes[self.frameType] + " " + EtherTypes[self.protocol] + "\n"
            if self.srcIP:  # Ak ma src IP adresu, znamena ze je IPv4 a bude mat aj dst protocol
                retStr += "IPv4 + " + ipProtocols[self.ipProtocol] + "\n"
                retStr += "  Src IP: " + self.srcIP + "\n"
                if self.srcPort:
                    retStr += "  Src port: " + str(self.srcPort) + "\n"
                retStr += "  Dst IP: " + self.dstIP + "\n"
                if self.dstPort:
                    retStr += "  Dst port: " + str(self.dstPort) + "\n"
        else:
            retStr += FrameTypes[self.frameType] + "\n"
            retStr += "  DSAP: " + IEEE_types[self.dsapType] + "\n"
            retStr += "  SSAP: " + IEEE_types[self.ssapType] + "\n"
        return retStr
    # =============================================


# ==================== ICMP ===================
class IcmpPacket():
    pass


class CommArp():
    pass


# =============================================
# ==================== ARP ====================
ARP_REQUEST = 1  # opcode request v ARP packete
ARP_RESPONSE = 2  # opcode response v ARP packete


class ArpPacket():
    def __init__(self, packet, opcode, senderMac, senderIP, targetMac, targetIP):
        self.packet = packet  # objekt myPacket
        self.opcode = opcode
        self.senderMac = senderMac
        self.senderIP = senderIP
        self.targetMac = targetMac
        self.targetIP = targetIP

    def __str__(self):
        retStr = str(self.packet)
        if self.opcode == ARP_REQUEST:
            retStr += "ARP request:\n"
        else:
            retStr += "ARP response:\n"
        retStr += "  Sender MAC: " + str(self.senderMac) + "\n"
        retStr += "  Sender IP: " + str(self.senderIP) + "\n"
        retStr += "  Target MAC: " + str(self.targetMac) + "\n"
        retStr += "  Target IP: " + str(self.targetIP) + "\n"
        return retStr


class CommArp():  # ARP komunikacia
    def __init__(self, reqPacket):
        self.requests = [reqPacket]  # Moze byt jeden alebo viac requestov
        self.response = None  # Response, ak existuje

    def addRequest(self, newReq):
        self.requests.append(newReq)

    def setResponse(self, response):
        self.response = response

    def compareRequest(self, pck):  # Porovnava iba cielove a zdrojove adresy
        if self.requests[0].senderMac == pck.senderMac \
                and self.requests[0].senderIP == pck.senderIP \
                and self.requests[0].targetMac == pck.targetMac \
                and self.requests[0].targetIP == pck.targetIP:
            return True  # Vrat True ak je rovnaky request ako pck
        else:
            return False  # Inak vrat false

    def isResponse(self, pck):
        if self.requests[0].senderMac == pck.targetMac \
                and self.requests[0].senderIP == pck.targetIP \
                and self.requests[0].targetIP == pck.senderIP:
            return True
        else:
            return False

    def __str__(self):
        retStr = ""
        for req in self.requests:
            retStr += str(req)
        if self.response:
            retStr += str(self.response)
        else:
            retStr += "No response to ARP requests\n"
        return retStr


arpCommunications = []  # Zoznam ARP komunikacii, commArp objektov


def updateArpComms(newPacket):
    if newPacket.opcode == ARP_REQUEST:
        for comm in arpCommunications:
            if comm.compareRequest(newPacket) and comm.response == None:
                # Nasiel sa uz rovnaky request na ktory nebolo odpovedane
                comm.addRequest(newPacket)
                break
        else:  # Nenasiel sa rovnaky request bez response (nebol break)
            arpCommunications.append(CommArp(newPacket))  # Nova komunikacia
    else:  # newPacket.opcode == ARP_RESPONSE
        for comm in arpCommunications:
            if comm.isResponse(newPacket):
                comm.setResponse(newPacket)


def processArpPacket(arpPacket):
    # Vytvory novy ArpPacket a posle ho do updateArpComms ktory ho zaradi do jednej z komunikacii
    arpPacketData = arpPacket.packetData[14:]  # Oddelit Ethernet II ramec od packetu
    opcode = int.from_bytes(arpPacketData[6:8], "big")
    sendercMac = getMAC(arpPacketData[8:14])
    senderIp = getIP(arpPacketData[14:18])
    targetMac = getMAC(arpPacketData[18:24])
    targetIp = getIP(arpPacketData[24:28])
    newArpPacket = ArpPacket(arpPacket, opcode, sendercMac, senderIp, targetMac, targetIp)
    updateArpComms(newArpPacket)


# =============================================

# ==================== TCP ====================
class TcpPacket():
    def __init__(self, tcpPacket):
        pass


class CommTcp():  # Jedna TCP komunikacia
    def __init__(self, openCommPacket):
        self.packets = [openCommPacket]  # Prvy packet, otvara komunikaciu


tcpCommunications = []  # Zoznam commTcp objektov


def updateTcpComms(newPacket):
    # todo: podobne ako updateArpComm, zistit ci je s rovnakej komunikacii (podla IP)
    pass


def processTcpPacket(tcpPacket):
    return None, None
    pass


# =============================================

# ==================== UDP ====================

class UdpPacket():
    def __init__(self, packet, srcPort, dstPort, length):
        self.packet = packet  # objekt myPacket
        self.srcPort = srcPort
        self.dstPort = dstPort
        self.length = length

    def __str__(self):
        retStr = str(self.packet)
        retStr += "  Source port: " + str(self.srcPort) + "\n"
        retStr += "  Destination port: " + str(self.dstPort) + "\n"
        return retStr


class CommUdp():  # Jedna TCP komunikacia
    def __init__(self, openCommPacket):
        self.packets = [openCommPacket]  # Prvy packet, otvara komunikaciu


udpCommunications = []  # Zoznam commUdp objektov


def updateUdpComms(newPacket):
    # todo: podobne ako updateArpComm, zistit ci je s rovnakej komunikacii (podla IP? portov?)
    pass


dnsPackets=[]

def processUdpPacket(udpPacket):
    udpPacketData = udpPacket.packetData[34:]  # Oddeli Ethernet II a IPv4 ramce od UDP packetu
    srcPort = int.from_bytes(udpPacketData[:2], "big")
    dstPort = int.from_bytes(udpPacketData[2:4], "big")
    length = int.from_bytes(udpPacketData[4:6], "big")
    newUdpPacket = UdpPacket(udpPacket, srcPort, dstPort, length)
    #updateUdpComms(newUdpPacket) # DORABKA
    if srcPort == 53 or dstPort == 53:
        dnsPackets.append(newUdpPacket)
    return srcPort, dstPort


# =============================================

def processIPv4Packet(ipPacket):
    # ipVersion = (ipPacketData[0] & 0xF0) >> 4 # Horna cast prveho Bytu
    # ihl = ipPacketData[0] & 0x0F # Dolna cast prveho Bytu
    # dsf = ipPacketData[1]
    # totalLength = int.from_bytes(ipPacketData[2:4], "big") # 3. a 4. byte = dlzka
    ipPacketData = ipPacket.packetData[14:]
    protocol = ipPacketData[9]  # 10. byte = protokol
    srcIP = getIP(ipPacketData[12:16])
    dstIP = getIP(ipPacketData[16:20])
    srcPort = None
    dstPort = None
    if protocol == 1:
        # todo: processIcmpPacket()
        pass  # ICMP
    elif protocol == 6:
        srcPort, dstPort = processTcpPacket(ipPacket)
    elif protocol == 17:
        srcPort, dstPort = processUdpPacket(ipPacket)
    return srcIP, dstIP, protocol, srcPort, dstPort


def processPcapFile(pcapFile):
    fPcap = rdpcap(pcapFile)  # Otvori pcap subor
    # Nacita vsetky packety zo suboru
    for packetIdx, packetData in enumerate(fPcap):
        hexPacket = bytes(packetData)
        newPacket = MyPacket(packetIdx, hexPacket)  # Vytvori novy objekt MyPacket
        packetList.append(newPacket)  # Zapise ho do zoznamu packetov

    # Vypise vsetky packety podla bodu 1 a 2
    for pck in packetList:
        print(pck)

    # Vypise zdrojove IP z IPv4, podla bodu 3
    if len(ipSrcDict.keys()) > 0:
        maxPackets = 1
        ipWithMaxPackets = []
        print("IPv4 Source adresses:")
        for ipSrc in ipSrcDict.keys():
            print("  ", ipSrc + " (" + str(ipSrcDict[ipSrc]) + " packets)")
            if ipSrcDict[ipSrc] == maxPackets:
                ipWithMaxPackets.append(ipSrc)
            elif ipSrcDict[ipSrc] > maxPackets:
                ipWithMaxPackets = []
                ipWithMaxPackets.append(ipSrc)
                maxPackets = ipSrcDict[ipSrc]
        print("Addresses with max. packet count of", str(maxPackets) + ":")
        for ipSrc in ipWithMaxPackets:
            print("  ", ipSrc)
        print()

    # Vypise vsetky ARP komunikacie podla bodu 3i
    for commIdx, comm in enumerate(arpCommunications):
        print("ARP Communication " + str(commIdx) + ":")
        print(comm)  # Vypise celu komunikaciu (CommArp.__str__())
        print()  # Prazdny riadok

# DORABKA
    for pckIdx, pck in enumerate(dnsPackets):
        print("DNS packet", pckIdx+1)
        print(str(pck))
    print("Total number of DNS packets: ", len(dnsPackets))


# bod 5
def nacitajBod5(filePath):
    subor = open(filePath, "r")
    riadky = subor.readlines()
    port_type = ""
    print(port_type)
    for riadok in riadky:
        if riadok[0] == '#':
            port_type = riadok
            continue
        port_info = riadok.split(" ", 1)
        key = int(port_info[0], 16)
        value = port_info[1]
        print(key,value)

        if port_type == "#Ethertype\n":
            EtherTypes[key] = value
        elif port_type == "#LSAPs":
            IEEE_types[key] = value
        elif port_type == "#IP Protocol numbers":
            ipProtocols[key] = value
        elif port_type == "#TCP ports":
            tcpPorts[key] = value
        elif port_type == "#UDP ports\n":
            udpPorts[key] = value




def main():
  for arg in sys.argv[1:]:
    fName, fExt = os.path.splitext(arg)
    if fExt==".txt" : nacitajBod5(arg)
    elif fExt == ".pcap" : processPcapFile(arg)
    else:
      print("Error")


if __name__== "__main__":
    main()