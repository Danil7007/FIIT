#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ethernet;
char globalProtocolName[100];

int globalIeeProtocolVal;
char globalIeeProtocolName[100];

int globalEtherTypeVal;
char globalEtherTypeName[100];

int ipv4;

int ipv4bool = 0;
int globalIPv4ProtocolVal;
char globalIPv4ProtocolName[100];

int tcp;
char tcpProtocolName[100];

int http;
int https;
int telnet;
int ssh;
int ftp_control;
int ftp_data;


int udp;
int tftp;
char tftp_name[50];


int icmp;
char icmp_type[16];
char imcp_type_name[30];
int arp;
int arp_request;
char arp_request_name[50];
int arp_reply;
char arp_reply_name[50];
int destination;

unsigned int SYN = 2;
unsigned int FIN = 1;
unsigned int RST = 4;
unsigned int ACK = 16;
int finBool = 0;
int rstBool = 0;
int ackBool = 0;


//Protokoly
void open_ethernet() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/ethernet.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	ethernet = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_iee8023() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	ethernet = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalProtocolName[i] = constant[i];
	fclose(fkonstanta);
}

//IEE vnorene protokoly
void open_bdup() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/bdup.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_ip() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/ip.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_ipx() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/ipx.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_isiIP() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/isiIP.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_lan() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/lan.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_llc1() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/llc1.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_llc2() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/llc2.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_mms() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/mms.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_nullSap() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/nullSap.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_proway() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/proway.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_proway2() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/proway2.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_snap() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/snap.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_raw() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/raw.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_ieeX25() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/protocols/iee802.3/x25.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIeeProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIeeProtocolName[i] = constant[i];
	fclose(fkonstanta);
}

//EtherType
void open_appleTalk() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/appleTalk.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);	
	
	for(int i=0; i<sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_appleTalkAARP() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/appleTalkAARP.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_arp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/arp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);
	arp = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_iee8021q() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/iee802.1q.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_ipv4() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/ipv4.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);
	ipv4 = globalEtherTypeVal;

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_ipv6() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/ipv6.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_mpls() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/mpls.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_mpls2() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/mpls2.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_novellIpx() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/novellIPX.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_ppp() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/ppp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_pppoe() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/pppoe.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_pppoe2() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/pppoe2.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_pup() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/pupAddrTrans.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_reverseARP() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/reverseARP.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_x25() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/x25Internet.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_x75() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/x75Internet.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}
void open_xerox() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/EtherType/xeroxPup.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalEtherTypeVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalEtherTypeName[i] = constant[i];

	fclose(fkonstanta);
}

//IPv4 protokoly
void open_icmp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/icmp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);
	icmp = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_igmp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/igmp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_tcp() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/tcp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);
	tcp = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_igrp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/igrp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_udp() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/udp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);
	udp = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_gre() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/gre.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_esp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/esp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_ah() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/ah.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_skip() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/skip.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_ospf() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/ospf.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_eigrp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/eigrp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}
void open_l2tp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/ipv4Protocols/l2tp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	globalIPv4ProtocolVal = atoi(constant);

	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		globalIPv4ProtocolName[i] = constant[i];

	fclose(fkonstanta);
}

//TCP porty
void open_http() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/tcpPorts/http.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	http= atoi(constant);
	fgets(constant, sizeof(constant), fkonstanta);
	for (int i = 0; i < sizeof(constant); i++)
		tcpProtocolName[i] = constant[i];


	fclose(fkonstanta);
}
void open_https() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/tcpPorts/https.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	https = atoi(constant);
	fgets(constant, sizeof(constant), fkonstanta);
	for (int i = 0; i < sizeof(constant); i++)
		tcpProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_ftp_control() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/tcpPorts/ftp_control.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	ftp_control = atoi(constant);
	fclose(fkonstanta);
}
void open_ftp_data() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/tcpPorts/ftp_data.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	ftp_data = atoi(constant);
	fclose(fkonstanta);
}
void open_telnet() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/tcpPorts/telnet.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	telnet = atoi(constant);
	fgets(constant, sizeof(constant), fkonstanta);
	for (int i = 0; i < sizeof(constant); i++)
		tcpProtocolName[i] = constant[i];
	fclose(fkonstanta);
}
void open_ssh() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/tcpPorts/ssh.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	ssh = atoi(constant);
	fgets(constant, sizeof(constant), fkonstanta);
	for (int i = 0; i < sizeof(constant); i++)
		tcpProtocolName[i] = constant[i];
	fclose(fkonstanta);
}

void open_tftp() {


	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/tftp.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	tftp = atoi(constant);
	fgets(constant, sizeof(constant), fkonstanta);
	for (int i = 0; i < sizeof(constant); i++)
		tftp_name[i] = constant[i];
	
	fclose(fkonstanta);
}
void open_icmp_type() {

	FILE *fkonstanta;
	char constant[50];
	int n = 0;
	int i = 0;

	if ((fkonstanta = fopen("konstanty/icmp_type.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}

	while (!feof(fkonstanta)) {
			fgets(constant, sizeof(constant), fkonstanta);
			if (n % 2 == 0) {
				icmp_type[i] = atoi(constant);
				//printf("%d, ", int_type[i]);
				i++;
			}
			n++;
	}
	fclose(fkonstanta);
}
void open_arp_request() {
	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/arp_request.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	arp_request = atoi(constant);
	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		arp_request_name[i] = constant[i];
	fclose(fkonstanta);
}
void open_arp_reply() {
	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/arp_reply.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	arp_reply = atoi(constant);
	fgets(constant, sizeof(constant), fkonstanta);

	for (int i = 0; i < sizeof(constant); i++)
		arp_reply_name[i] = constant[i];
	fclose(fkonstanta);
}
void open_destination() {

	FILE *fkonstanta;
	char constant[50];

	if ((fkonstanta = fopen("konstanty/destination_unreach.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}
	fgets(constant, sizeof(constant), fkonstanta);
	destination = atoi(constant);
	fclose(fkonstanta);
}

int porovnanieIeeProtocols(int localIeeProtocolVal) {
	if (localIeeProtocolVal == globalIeeProtocolVal)
		return 1;
	else return 2;
}

void ieeProtocol(int localIeeProtocolVal) {

	open_bdup();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_ip();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_ipx();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_isiIP();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_lan();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_llc1();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_llc2();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_mms();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_nullSap();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_proway();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_proway2();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_snap();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_raw();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;

	open_ieeX25();
	if (porovnanieIeeProtocols(localIeeProtocolVal) == 1)
		return;


}

int porovnanieEtherVals(int localEtherTypeVal) {
	if (localEtherTypeVal == globalEtherTypeVal)
		return 1;
	else return 2;
		
}

void etherType(int localEtherTypeVal) {


	open_appleTalk();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_appleTalkAARP();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_arp();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_iee8021q();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_ipv4();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		ipv4bool = 1;
		return;

	open_ipv6();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_mpls();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_mpls2();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_novellIpx();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_ppp();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_pppoe();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_pppoe2();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_pup();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_reverseARP();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_x25();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_x75();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;

	open_xerox();
	if (porovnanieEtherVals(localEtherTypeVal) == 1)
		return;
}

int porovnanieIPv4Protokols(int localIPv4EtherTypeVal) {

	if (localIPv4EtherTypeVal == globalIPv4ProtocolVal)
		return 1;
	else return 2;

}

void ipv4Protocol(int localIPv4ProtocolVal) {

	open_icmp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_igmp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_tcp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_igrp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_udp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_gre();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_esp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_ah();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_skip();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_eigrp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_ospf();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;

	open_l2tp();
	if (porovnanieIPv4Protokols(localIPv4ProtocolVal) == 1)
		return;
}



void vsetko() {

	char errbuff[PCAP_ERRBUF_SIZE];
	char cesta[100];
	int poc_ramcov = 0;
	int pocitadlo = 1;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	
	typedef struct ip {
		unsigned char ip[4];
		int data;
		struct ip *dalsi;
	};
	struct ip *prvy = (struct ip*)malloc(sizeof(struct ip));
	struct ip *aktualny = (struct ip*)malloc(sizeof(struct ip));
	int src_ip = 26;

	FILE *vystup_f;
	vystup_f = fopen("output/vsetko.txt", "w");

	fprintf(vystup_f, "\n");


	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {
		ipv4bool = 0;

		//zistuje cislo ramca
		fprintf(vystup_f, "Ramec %d\n", ++poc_ramcov);

		//zistuje dlzku ramca
		fprintf(vystup_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

		if ((hlavicka->len) >= 60)
			fprintf(vystup_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
		else
			fprintf(vystup_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

		//zistuje ci je ethernet alebo 802.3
		open_ethernet();
		if (((data[12] * 256) + data[13]) > ethernet) {
			fprintf(vystup_f, "%s\n", globalProtocolName);

			//zistuje zdrojovu MAC adresu
			fprintf(vystup_f, "Zdrojova MAC adresa: ");
			for (int j = 6; j < 12; j++)
				fprintf(vystup_f, "%.2X ", data[j]);

			//zistuje cielovu MAC adresu
			fprintf(vystup_f, "\n");
			fprintf(vystup_f, "Cielova MAC adresa: ");
			for (int j = 0; j < 6; j++)
				fprintf(vystup_f, "%.2X ", data[j]);

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			fprintf(vystup_f, "\n%s", globalEtherTypeName);

			//vypis src a dst IP addr pre IPv4
			if (ipv4bool == 1) {

				//vypis zdrojovej IP
				fprintf(vystup_f, "\nZdrojova IP adresa: ");
				for (int i = 26; i < 29; i++)
					fprintf(vystup_f, "%d.", data[i]);
				fprintf(vystup_f, "%d\n", data[29]);

				//vypis cielovej IP
				fprintf(vystup_f, "Cielova IP adresa: ");
				for (int i = 30; i < 33; i++)
					fprintf(vystup_f, "%d.", data[i]);
				fprintf(vystup_f, "%d\n", data[33]);

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);
				fprintf(vystup_f, "%s", globalIPv4ProtocolName);

				//ulozenie src addr na vypis
				//pre prvu ipv4 src addr
				if (pocitadlo == 1) {
					src_ip = 26;
					for (int i = 0; i < 4; i++) {
						prvy->ip[i] = data[src_ip++];
					}
					prvy->data = 1;
					aktualny = prvy;
					aktualny->dalsi = NULL;
					pocitadlo++;
				}
				//pre ostatne ipv4 src addr
				else {
					aktualny = prvy;
					//nacitam addr
					int src_IP_arr[4];
					src_ip = 26;
					for (int i = 0; i < 4; i++) {
						src_IP_arr[i] = data[src_ip++];
					}
					//ak dalsi je null tak porovnam 1. addr s aktualnou
					if (aktualny->dalsi == NULL) {

						int compare = 0;
						for (int i = 0; i < 4; i++) {
							if (src_IP_arr[i] == aktualny->ip[i])
								compare++;
						}
						//ak su neni rovnake, pridam do zoznamu
						if (compare != 4) {
							struct ip *novy = (struct ip*)malloc(sizeof(struct ip));
							aktualny->dalsi = novy;
							aktualny = novy;
							src_ip = 26;
							for (int i = 0; i < 4; i++) {
								aktualny->ip[i] = data[src_ip++];
							}
							aktualny->data = 1;
							aktualny->dalsi = NULL;
						}
					}
					else {
						while (aktualny != NULL) {												
							int compare = 0;
							for (int i = 0; i < 4; i++) {
								if (src_IP_arr[i] == aktualny->ip[i])
									compare++;
							}
							
							if (compare == 4) {
								aktualny->data++;
								break;
							}
							else {								
								if (aktualny->dalsi == NULL) {
									struct ip *novy = (struct ip*)malloc(sizeof(struct ip));
									aktualny->dalsi = novy;
									aktualny = novy;
									src_ip = 26;
									for (int i = 0; i < 4; i++) {
										aktualny->ip[i] = data[src_ip++];
									}
									aktualny->data = 1;
									aktualny->dalsi = NULL;

									break;
								}
								aktualny = aktualny->dalsi;
							}
						}				
					}
					pocitadlo++;
					src_ip = 26;
				}
				
			}
		}
		else {
			open_iee8023();
			fprintf(vystup_f, "%s\n", globalProtocolName);

			//zistuje zdrojovu MAC adresu
			fprintf(vystup_f, "Zdrojova MAC adresa: ");
			for (int j = 6; j < 12; j++)
				fprintf(vystup_f, "%.2X ", data[j]);

			//zistuje cielovu MAC adresu
			fprintf(vystup_f, "\n");
			fprintf(vystup_f, "Cielova MAC adresa: ");
			for (int j = 0; j < 6; j++)
				fprintf(vystup_f, "%.2X ", data[j]);

			if (data[14] == data[15]) {
				int saps = data[14];
				ieeProtocol(saps);
				fprintf(vystup_f, "%s\n", globalIeeProtocolName);			
			}				
		}

	//vypis ramca
		fprintf(vystup_f, "\n");
		for (int i = 0; i < (hlavicka->caplen); i++) {
			if ((i % 16) == 0)
				fprintf(vystup_f, "\n");

			if ((i % 16) == 8)
				fprintf(vystup_f, "    ");

			fprintf(vystup_f, "%.2X ", data[i]);
		}

		fprintf(vystup_f, "\n\n");
	}

	aktualny=prvy;
	int max = 0;
	fprintf(vystup_f, "\nIP adresy vysielajúcich uzlov:\n");
	while (aktualny != NULL) {
		for (int i = 0; i < 4; i++) {
			fprintf(vystup_f, "%d.", aktualny->ip[i]);
		}

		fprintf(vystup_f, "\n");
		if (aktualny->data > max)
			max = aktualny->data;
		aktualny = aktualny->dalsi;
	}

	aktualny = prvy;
	fprintf(vystup_f, "\nAdresa uzla s najväčším počtom odoslaných paketov:\n");
	while (aktualny != NULL) {
		if (aktualny->data == max) {
			for (int i = 0; i < 4; i++)
				fprintf(vystup_f, "%d.", aktualny->ip[i]);
			break;
		}
		aktualny = aktualny->dalsi;
	}
	fprintf(vystup_f, "  %d paketov", max);
	fclose(vystup_f);
	
}

//TCP
void port_http() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//definicia output txt suboru; sluzi na vypisovania
	FILE *TCP_f;
	TCP_f = fopen("output/TCP_F.txt", "w");

	typedef struct komunikacia {
		int ip1[4];
		int ip2[4];
		int first;
		int twoFin;
		int finRst;
		int rst;
		struct komunikacia *dalsi;
	}KOMUNIKACIA;

	KOMUNIKACIA *prvy = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));
	KOMUNIKACIA *aktualny = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

	int counting = 0;

	//nacitanie komunikacii do struktury
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {
		++poc_ramcov;


		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == ipv4)) {

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);

				if (data[23] == tcp) {

					open_http();

					if ((data[34] * 256 + data[35]) == http || (data[36] * 256 + data[37]) == http) {

						unsigned int flag = data[47];

						if ((flag & SYN) != 0) {
							counting++;
							if (counting == 1) {

								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									prvy->ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									prvy->ip2[pom++] = data[i];
								}

								prvy->twoFin = 0;
								prvy->finRst = 0;
								prvy->rst = 0;
								prvy->dalsi = NULL;
								prvy->first = poc_ramcov;
								aktualny = prvy;
							}
							else {
								int ip1[4];
								int ip2[4];
								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									ip2[pom++] = data[i];
								}

								aktualny = prvy;
								while (aktualny != NULL) {
									int comp1, comp2;
									comp1 = 0;
									comp2 = 0;

									for (int i = 0; i < 4; i++) {
										if (ip1[i] == aktualny->ip2[i])
											comp1++;
									}
									for (int i = 0; i < 4; i++) {
										if (ip2[i] == aktualny->ip1[i])
											comp2++;
									}
									if (comp1 == 4 || comp2 == 4) {
										break;
									}
									else {
										if (aktualny->dalsi == NULL) {
											KOMUNIKACIA *new = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

											int pom = 0;
											for (int i = 26; i <= 29; i++) {
												new->ip1[pom++] = data[i];
											}

											pom = 0;
											for (int i = 30; i <= 33; i++) {
												new->ip2[pom++] = data[i];
											}

											new->twoFin = 0;
											new->finRst = 0;
											new->rst = 0;
											new->first = poc_ramcov;
											new->dalsi = NULL;
											aktualny->dalsi = new;
											aktualny = new;
											break;
										}
										else
											aktualny = aktualny->dalsi;

									}
								}
							}
						}

						if ((flag & FIN) != 0) {
							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;

								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}
								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->twoFin = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}

						if ((flag & RST) != 0) {

							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							/*
							if (poc_ramcov == 1124) {
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip2[i]);
								}
								printf("\n");

								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip2[i]);
								}
								printf("\n");

							}
							*/
							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;
								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}

								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->rst = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}
					}
				}
			}
		}
	}

	aktualny = prvy;

	/*
	while (aktualny != NULL) {
		printf("Ramec c.: %d\n", aktualny->first);
		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip1[i]);
		}
		printf("\n");

		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip2[i]);
		}
		printf("\ntwoFin: %d\n", aktualny->twoFin);
		printf("finRst: %d\n", aktualny->finRst);
		printf("Rst: %d\n", aktualny->rst);
		printf("\n----------------------------------------------\n");

		aktualny = aktualny->dalsi;
	}
	*/


	pcap_close(pcap_file);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	//vypis prvej kompletnej komunikacie
	aktualny = prvy;
	while (aktualny != NULL) {
		if (aktualny->twoFin == 1 || aktualny->rst == 1 || aktualny->finRst == 1) {
			break;
		}
		else aktualny = aktualny->dalsi;
	}

	fprintf(TCP_f, "Prvá kompletná komunikácia HTTP:\n\n");
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;

		if (poc_ramcov >= aktualny->first) {


			//zistuje ci je ethernet
			open_ethernet();

			if (((data[12] * 256) + data[13]) > ethernet) {

				//zistuje EtherType
				int localEtherTypeVal = ((data[12] * 256) + data[13]);
				etherType(localEtherTypeVal);

				if ((((data[12] * 256) + data[13]) == ipv4)) {

					//zistenie IPv4 protokolu
					int localIPv4ProtocolType = data[23];
					ipv4Protocol(localIPv4ProtocolType);

					if (data[23] == tcp) {

						open_http();

						if ((data[34] * 256 + data[35]) == http || (data[36] * 256 + data[37]) == http) {

							unsigned int flag = data[47];

							int ip1[4];
							int ip2[4];
							int pom = 0;
							//nacitanie src a dst ip
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							//porovnanie so strukturou

							int comp1 = 0;
							int comp2 = 0;
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip1[i])
									comp1++;
							}
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip2[i])
									comp2++;
							}

							if (comp1 == 4 || comp2 == 4) {

								comp1 = 0;
								comp2 = 0;
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip1[i])
										comp1++;
								}
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip2[i])
										comp2++;
								}
								if (comp1 == 4 || comp2 == 4) {

									if ((poc_ramcov != aktualny->first) && ((flag & SYN) != 0)) {
										continue;
									}




									//zistuje cislo ramca
									fprintf(TCP_f, "Ramec %d\n", poc_ramcov);

									//zistuje dlzku ramca
									fprintf(TCP_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

									if ((hlavicka->len) >= 60)
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
									else
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

									//vypis ethernet
									fprintf(TCP_f, "%s\n", globalProtocolName);

									//zistuje zdrojovu MAC adresu
									fprintf(TCP_f, "Zdrojova MAC adresa: ");
									for (int j = 6; j < 12; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//zistuje cielovu MAC adresu
									fprintf(TCP_f, "\n");
									fprintf(TCP_f, "Cielova MAC adresa: ");
									for (int j = 0; j < 6; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//vypis IPv4
									fprintf(TCP_f, "\n%s\n", globalEtherTypeName);

									//vypis zdrojovej IP
									int pom = 0;
									fprintf(TCP_f, "Zdrojova IP adresa: ");
									for (int i = 26; i < 29; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[29]);

									//vypis cielovej IP
									pom = 0;
									fprintf(TCP_f, "Cielova IP adresa: ");
									for (int i = 30; i < 33; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[33]);

									//vypis TCP
									fprintf(TCP_f, "%s\n", globalIPv4ProtocolName);

									//vypis http
									fprintf(TCP_f, "%s\n", tcpProtocolName);


									//vypis zdrojoveho a cieloveho portu
									fprintf(TCP_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
									fprintf(TCP_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

									//vypis ramca
									fprintf(TCP_f, "\n");
									for (int i = 0; i < (hlavicka->caplen); i++) {
										if ((i % 16) == 0)
											fprintf(TCP_f, "\n");

										if ((i % 16) == 8)
											fprintf(TCP_f, "    ");

										fprintf(TCP_f, "%.2X ", data[i]);
									}

									fprintf(TCP_f, "\n\n");


									if ((finBool == 0) && (flag & FIN != 0)) {
										printf("\nRamec: %d --> finBool = 1\n", poc_ramcov);
										finBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 0) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 1\n", poc_ramcov);
										ackBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 1) && ((flag & FIN) != 0)) {
										printf("Ramec: %d --> finBool = 2\n", poc_ramcov);
										finBool = 2;
										continue;
									}
									if ((finBool == 0) && (ackBool == 0) && ((flag & RST) != 0)) {
										printf("Ramec: %d -->1. RST and break after = 2\n", poc_ramcov);
										break;
									}

									if ((finBool == 1) && (ackBool == 1) && ((flag & RST) != 0)) {
										printf("Ramec: %d --> RST and break after = 2\n", poc_ramcov);
										break;

									}
									if ((finBool == 2) && (ackBool == 1) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 2 and break after\n", poc_ramcov);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(TCP_f);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	aktualny = prvy;
}
void port_https() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//definicia output txt suboru; sluzi na vypisovania
	FILE *TCP_f;
	TCP_f = fopen("output/TCP_F.txt", "w");

	typedef struct komunikacia {
		int ip1[4];
		int ip2[4];
		int first;
		int twoFin;
		int finRst;
		int rst;
		struct komunikacia *dalsi;
	}KOMUNIKACIA;

	KOMUNIKACIA *prvy = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));
	KOMUNIKACIA *aktualny = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

	int counting = 0;

	//nacitanie komunikacii do struktury
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {
		++poc_ramcov;


		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == ipv4)) {

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);

				if (data[23] == tcp) {

					open_https();

					if ((data[34] * 256 + data[35]) == https || (data[36] * 256 + data[37]) == https) {

						unsigned int flag = data[47];

						if ((flag & SYN) != 0) {
							counting++;
							if (counting == 1) {

								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									prvy->ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									prvy->ip2[pom++] = data[i];
								}

								prvy->twoFin = 0;
								prvy->finRst = 0;
								prvy->rst = 0;
								prvy->dalsi = NULL;
								prvy->first = poc_ramcov;
								aktualny = prvy;
							}
							else {
								int ip1[4];
								int ip2[4];
								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									ip2[pom++] = data[i];
								}

								aktualny = prvy;
								while (aktualny != NULL) {
									int comp1, comp2;
									comp1 = 0;
									comp2 = 0;

									for (int i = 0; i < 4; i++) {
										if (ip1[i] == aktualny->ip2[i])
											comp1++;
									}
									for (int i = 0; i < 4; i++) {
										if (ip2[i] == aktualny->ip1[i])
											comp2++;
									}
									if (comp1 == 4 || comp2 == 4) {
										break;
									}
									else {
										if (aktualny->dalsi == NULL) {
											KOMUNIKACIA *new = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

											int pom = 0;
											for (int i = 26; i <= 29; i++) {
												new->ip1[pom++] = data[i];
											}

											pom = 0;
											for (int i = 30; i <= 33; i++) {
												new->ip2[pom++] = data[i];
											}

											new->twoFin = 0;
											new->finRst = 0;
											new->rst = 0;
											new->first = poc_ramcov;
											new->dalsi = NULL;
											aktualny->dalsi = new;
											aktualny = new;
											break;
										}
										else
											aktualny = aktualny->dalsi;

									}
								}
							}
						}

						if ((flag & FIN) != 0) {
							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;
	
								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}
								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->twoFin = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}

						if ((flag & RST) != 0) {

							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							/*
							if (poc_ramcov == 1124) {
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip2[i]);
								}
								printf("\n");

								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip2[i]);
								}
								printf("\n");

							}
							*/
							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;
								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}

								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->rst = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}
					}
				}
			}
		}
	}

	aktualny = prvy;

	/*
	while (aktualny != NULL) {
		printf("Ramec c.: %d\n", aktualny->first);
		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip1[i]);
		}
		printf("\n");

		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip2[i]);
		}
		printf("\ntwoFin: %d\n", aktualny->twoFin);
		printf("finRst: %d\n", aktualny->finRst);
		printf("Rst: %d\n", aktualny->rst);
		printf("\n----------------------------------------------\n");

		aktualny = aktualny->dalsi;
	}
	*/
	

	pcap_close(pcap_file);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	//vypis prvej kompletnej komunikacie
	aktualny = prvy;
	while (aktualny != NULL) {
		if (aktualny->twoFin == 1 || aktualny->rst == 1 || aktualny->finRst == 1) {
			break;
		}
		else aktualny = aktualny->dalsi;
	}

	fprintf(TCP_f, "Prvá kompletná komunikácia HTTPS:\n\n");
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;

		if (poc_ramcov >= aktualny->first) {


			//zistuje ci je ethernet
			open_ethernet();

			if (((data[12] * 256) + data[13]) > ethernet) {

				//zistuje EtherType
				int localEtherTypeVal = ((data[12] * 256) + data[13]);
				etherType(localEtherTypeVal);

				if ((((data[12] * 256) + data[13]) == ipv4)) {

					//zistenie IPv4 protokolu
					int localIPv4ProtocolType = data[23];
					ipv4Protocol(localIPv4ProtocolType);

					if (data[23] == tcp) {

						open_https();

						if ((data[34] * 256 + data[35]) == https || (data[36] * 256 + data[37]) == https) {

							unsigned int flag = data[47];

							int ip1[4];
							int ip2[4];
							int pom = 0;
							//nacitanie src a dst ip
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							//porovnanie so strukturou

							int comp1 = 0;
							int comp2 = 0;
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip1[i])
									comp1++;
							}
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip2[i])
									comp2++;
							}

							if (comp1 == 4 || comp2 == 4) {

								comp1 = 0;
								comp2 = 0;
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip1[i])
										comp1++;
								}
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip2[i])
										comp2++;
								}
								if (comp1 == 4 || comp2 == 4) {

									if ((poc_ramcov != aktualny->first) && ((flag & SYN) != 0)) {
										continue;
									}




									//zistuje cislo ramca
									fprintf(TCP_f, "Ramec %d\n", poc_ramcov);

									//zistuje dlzku ramca
									fprintf(TCP_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

									if ((hlavicka->len) >= 60)
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
									else
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

									//vypis ethernet
									fprintf(TCP_f, "%s\n", globalProtocolName);

									//zistuje zdrojovu MAC adresu
									fprintf(TCP_f, "Zdrojova MAC adresa: ");
									for (int j = 6; j < 12; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//zistuje cielovu MAC adresu
									fprintf(TCP_f, "\n");
									fprintf(TCP_f, "Cielova MAC adresa: ");
									for (int j = 0; j < 6; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//vypis IPv4
									fprintf(TCP_f, "\n%s\n", globalEtherTypeName);

									//vypis zdrojovej IP
									int pom = 0;
									fprintf(TCP_f, "Zdrojova IP adresa: ");
									for (int i = 26; i < 29; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[29]);

									//vypis cielovej IP
									pom = 0;
									fprintf(TCP_f, "Cielova IP adresa: ");
									for (int i = 30; i < 33; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[33]);

									//vypis TCP
									fprintf(TCP_f, "%s\n", globalIPv4ProtocolName);

									//vypis http
									fprintf(TCP_f, "%s\n", tcpProtocolName);


									//vypis zdrojoveho a cieloveho portu
									fprintf(TCP_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
									fprintf(TCP_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

									//vypis ramca
									fprintf(TCP_f, "\n");
									for (int i = 0; i < (hlavicka->caplen); i++) {
										if ((i % 16) == 0)
											fprintf(TCP_f, "\n");

										if ((i % 16) == 8)
											fprintf(TCP_f, "    ");

										fprintf(TCP_f, "%.2X ", data[i]);
									}

									fprintf(TCP_f, "\n\n");


									if ((finBool == 0) && (flag & FIN != 0)) {
										printf("\nRamec: %d --> finBool = 1\n", poc_ramcov);
										finBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 0) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 1\n", poc_ramcov);
										ackBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 1) && ((flag & FIN) != 0)) {
										printf("Ramec: %d --> finBool = 2\n", poc_ramcov);
										finBool = 2;
										continue;
									}
									if ((finBool == 0) && (ackBool == 0) && ((flag & RST) != 0)) {
										printf("Ramec: %d -->1. RST and break after = 2\n", poc_ramcov);
										break;
									}

									if ((finBool == 1) && (ackBool == 1) && ((flag & RST) != 0)) {
										printf("Ramec: %d --> RST and break after = 2\n", poc_ramcov);
										break;

									}
									if ((finBool == 2) && (ackBool == 1) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 2 and break after\n", poc_ramcov);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(TCP_f);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	aktualny = prvy;
}
void port_telnet() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//definicia output txt suboru; sluzi na vypisovania
	FILE *TCP_f;
	TCP_f = fopen("output/TCP_F.txt", "w");

	typedef struct komunikacia {
		int ip1[4];
		int ip2[4];
		int first;
		int twoFin;
		int finRst;
		int rst;
		struct komunikacia *dalsi;
	}KOMUNIKACIA;

	KOMUNIKACIA *prvy = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));
	KOMUNIKACIA *aktualny = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

	int counting = 0;

	//nacitanie komunikacii do struktury
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {
		++poc_ramcov;


		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == ipv4)) {

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);

				if (data[23] == tcp) {

					open_telnet();

					if ((data[34] * 256 + data[35]) == telnet || (data[36] * 256 + data[37]) == telnet) {

						unsigned int flag = data[47];

						if ((flag & SYN) != 0) {
							counting++;
							if (counting == 1) {

								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									prvy->ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									prvy->ip2[pom++] = data[i];
								}

								prvy->twoFin = 0;
								prvy->finRst = 0;
								prvy->rst = 0;
								prvy->dalsi = NULL;
								prvy->first = poc_ramcov;
								aktualny = prvy;
							}
							else {
								int ip1[4];
								int ip2[4];
								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									ip2[pom++] = data[i];
								}

								aktualny = prvy;
								while (aktualny != NULL) {
									int comp1, comp2;
									comp1 = 0;
									comp2 = 0;

									for (int i = 0; i < 4; i++) {
										if (ip1[i] == aktualny->ip2[i])
											comp1++;
									}
									for (int i = 0; i < 4; i++) {
										if (ip2[i] == aktualny->ip1[i])
											comp2++;
									}
									if (comp1 == 4 || comp2 == 4) {
										break;
									}
									else {
										if (aktualny->dalsi == NULL) {
											KOMUNIKACIA *new = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

											int pom = 0;
											for (int i = 26; i <= 29; i++) {
												new->ip1[pom++] = data[i];
											}

											pom = 0;
											for (int i = 30; i <= 33; i++) {
												new->ip2[pom++] = data[i];
											}

											new->twoFin = 0;
											new->finRst = 0;
											new->rst = 0;
											new->first = poc_ramcov;
											new->dalsi = NULL;
											aktualny->dalsi = new;
											aktualny = new;
											break;
										}
										else
											aktualny = aktualny->dalsi;

									}
								}
							}
						}

						if ((flag & FIN) != 0) {
							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;

								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}
								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->twoFin = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}

						if ((flag & RST) != 0) {

							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							/*
							if (poc_ramcov == 1124) {
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip2[i]);
								}
								printf("\n");

								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip2[i]);
								}
								printf("\n");

							}
							*/
							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;
								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}

								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->rst = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}
					}
				}
			}
		}
	}

	aktualny = prvy;

	/*
	while (aktualny != NULL) {
		printf("Ramec c.: %d\n", aktualny->first);
		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip1[i]);
		}
		printf("\n");

		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip2[i]);
		}
		printf("\ntwoFin: %d\n", aktualny->twoFin);
		printf("finRst: %d\n", aktualny->finRst);
		printf("Rst: %d\n", aktualny->rst);
		printf("\n----------------------------------------------\n");

		aktualny = aktualny->dalsi;
	}
	*/


	pcap_close(pcap_file);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	//vypis prvej kompletnej komunikacie
	aktualny = prvy;
	while (aktualny != NULL) {
		if (aktualny->twoFin == 1 || aktualny->rst == 1 || aktualny->finRst == 1) {
			break;
		}
		else aktualny = aktualny->dalsi;
	}

	fprintf(TCP_f, "Prvá kompletná komunikácia TELNET:\n\n");
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;

		if (poc_ramcov >= aktualny->first) {


			//zistuje ci je ethernet
			open_ethernet();

			if (((data[12] * 256) + data[13]) > ethernet) {

				//zistuje EtherType
				int localEtherTypeVal = ((data[12] * 256) + data[13]);
				etherType(localEtherTypeVal);

				if ((((data[12] * 256) + data[13]) == ipv4)) {

					//zistenie IPv4 protokolu
					int localIPv4ProtocolType = data[23];
					ipv4Protocol(localIPv4ProtocolType);

					if (data[23] == tcp) {

						open_telnet();

						if ((data[34] * 256 + data[35]) == telnet || (data[36] * 256 + data[37]) == telnet) {

							unsigned int flag = data[47];

							int ip1[4];
							int ip2[4];
							int pom = 0;
							//nacitanie src a dst ip
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							//porovnanie so strukturou

							int comp1 = 0;
							int comp2 = 0;
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip1[i])
									comp1++;
							}
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip2[i])
									comp2++;
							}

							if (comp1 == 4 || comp2 == 4) {

								comp1 = 0;
								comp2 = 0;
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip1[i])
										comp1++;
								}
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip2[i])
										comp2++;
								}
								if (comp1 == 4 || comp2 == 4) {

									if ((poc_ramcov != aktualny->first) && ((flag & SYN) != 0)) {
										continue;
									}




									//zistuje cislo ramca
									fprintf(TCP_f, "Ramec %d\n", poc_ramcov);

									//zistuje dlzku ramca
									fprintf(TCP_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

									if ((hlavicka->len) >= 60)
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
									else
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

									//vypis ethernet
									fprintf(TCP_f, "%s\n", globalProtocolName);

									//zistuje zdrojovu MAC adresu
									fprintf(TCP_f, "Zdrojova MAC adresa: ");
									for (int j = 6; j < 12; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//zistuje cielovu MAC adresu
									fprintf(TCP_f, "\n");
									fprintf(TCP_f, "Cielova MAC adresa: ");
									for (int j = 0; j < 6; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//vypis IPv4
									fprintf(TCP_f, "\n%s\n", globalEtherTypeName);

									//vypis zdrojovej IP
									int pom = 0;
									fprintf(TCP_f, "Zdrojova IP adresa: ");
									for (int i = 26; i < 29; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[29]);

									//vypis cielovej IP
									pom = 0;
									fprintf(TCP_f, "Cielova IP adresa: ");
									for (int i = 30; i < 33; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[33]);

									//vypis TCP
									fprintf(TCP_f, "%s\n", globalIPv4ProtocolName);

									//vypis http
									fprintf(TCP_f, "%s\n", tcpProtocolName);


									//vypis zdrojoveho a cieloveho portu
									fprintf(TCP_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
									fprintf(TCP_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

									//vypis ramca
									fprintf(TCP_f, "\n");
									for (int i = 0; i < (hlavicka->caplen); i++) {
										if ((i % 16) == 0)
											fprintf(TCP_f, "\n");

										if ((i % 16) == 8)
											fprintf(TCP_f, "    ");

										fprintf(TCP_f, "%.2X ", data[i]);
									}

									fprintf(TCP_f, "\n\n");


									if ((finBool == 0) && (flag & FIN != 0)) {
										printf("\nRamec: %d --> finBool = 1\n", poc_ramcov);
										finBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 0) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 1\n", poc_ramcov);
										ackBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 1) && ((flag & FIN) != 0)) {
										printf("Ramec: %d --> finBool = 2\n", poc_ramcov);
										finBool = 2;
										continue;
									}
									if ((finBool == 0) && (ackBool == 0) && ((flag & RST) != 0)) {
										printf("Ramec: %d -->1. RST and break after = 2\n", poc_ramcov);
										break;
									}

									if ((finBool == 1) && (ackBool == 1) && ((flag & RST) != 0)) {
										printf("Ramec: %d --> RST and break after = 2\n", poc_ramcov);
										break;

									}
									if ((finBool == 2) && (ackBool == 1) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 2 and break after\n", poc_ramcov);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(TCP_f);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	aktualny = prvy;
}
void port_ssh() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//definicia output txt suboru; sluzi na vypisovania
	FILE *TCP_f;
	TCP_f = fopen("output/TCP_F.txt", "w");

	typedef struct komunikacia {
		int ip1[4];
		int ip2[4];
		int first;
		int twoFin;
		int finRst;
		int rst;
		struct komunikacia *dalsi;
	}KOMUNIKACIA;

	KOMUNIKACIA *prvy = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));
	KOMUNIKACIA *aktualny = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

	int counting = 0;

	//nacitanie komunikacii do struktury
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {
		++poc_ramcov;


		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == ipv4)) {

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);

				if (data[23] == tcp) {

					open_ssh();

					if ((data[34] * 256 + data[35]) == ssh || (data[36] * 256 + data[37]) == ssh) {

						unsigned int flag = data[47];

						if ((flag & SYN) != 0) {
							counting++;
							if (counting == 1) {

								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									prvy->ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									prvy->ip2[pom++] = data[i];
								}

								prvy->twoFin = 0;
								prvy->finRst = 0;
								prvy->rst = 0;
								prvy->dalsi = NULL;
								prvy->first = poc_ramcov;
								aktualny = prvy;
							}
							else {
								int ip1[4];
								int ip2[4];
								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									ip2[pom++] = data[i];
								}

								aktualny = prvy;
								while (aktualny != NULL) {
									int comp1, comp2;
									comp1 = 0;
									comp2 = 0;

									for (int i = 0; i < 4; i++) {
										if (ip1[i] == aktualny->ip2[i])
											comp1++;
									}
									for (int i = 0; i < 4; i++) {
										if (ip2[i] == aktualny->ip1[i])
											comp2++;
									}
									if (comp1 == 4 || comp2 == 4) {
										break;
									}
									else {
										if (aktualny->dalsi == NULL) {
											KOMUNIKACIA *new = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

											int pom = 0;
											for (int i = 26; i <= 29; i++) {
												new->ip1[pom++] = data[i];
											}

											pom = 0;
											for (int i = 30; i <= 33; i++) {
												new->ip2[pom++] = data[i];
											}

											new->twoFin = 0;
											new->finRst = 0;
											new->rst = 0;
											new->first = poc_ramcov;
											new->dalsi = NULL;
											aktualny->dalsi = new;
											aktualny = new;
											break;
										}
										else
											aktualny = aktualny->dalsi;

									}
								}
							}
						}

						if ((flag & FIN) != 0) {
							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;

								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}
								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->twoFin = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}

						if ((flag & RST) != 0) {

							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							/*
							if (poc_ramcov == 1124) {
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip2[i]);
								}
								printf("\n");

								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip2[i]);
								}
								printf("\n");

							}
							*/
							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;
								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}

								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->rst = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}
					}
				}
			}
		}
	}

	aktualny = prvy;

	/*
	while (aktualny != NULL) {
		printf("Ramec c.: %d\n", aktualny->first);
		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip1[i]);
		}
		printf("\n");

		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip2[i]);
		}
		printf("\ntwoFin: %d\n", aktualny->twoFin);
		printf("finRst: %d\n", aktualny->finRst);
		printf("Rst: %d\n", aktualny->rst);
		printf("\n----------------------------------------------\n");

		aktualny = aktualny->dalsi;
	}
	*/


	pcap_close(pcap_file);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	//vypis prvej kompletnej komunikacie
	aktualny = prvy;
	while (aktualny != NULL) {
		if (aktualny->twoFin == 1 || aktualny->rst == 1 || aktualny->finRst == 1) {
			break;
		}
		else aktualny = aktualny->dalsi;
	}

	fprintf(TCP_f, "Prvá kompletná komunikácia SSH:\n\n");
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;

		if (poc_ramcov >= aktualny->first) {


			//zistuje ci je ethernet
			open_ethernet();

			if (((data[12] * 256) + data[13]) > ethernet) {

				//zistuje EtherType
				int localEtherTypeVal = ((data[12] * 256) + data[13]);
				etherType(localEtherTypeVal);

				if ((((data[12] * 256) + data[13]) == ipv4)) {

					//zistenie IPv4 protokolu
					int localIPv4ProtocolType = data[23];
					ipv4Protocol(localIPv4ProtocolType);

					if (data[23] == tcp) {

						open_ssh();

						if ((data[34] * 256 + data[35]) == ssh || (data[36] * 256 + data[37]) == ssh) {

							unsigned int flag = data[47];

							int ip1[4];
							int ip2[4];
							int pom = 0;
							//nacitanie src a dst ip
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							//porovnanie so strukturou

							int comp1 = 0;
							int comp2 = 0;
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip1[i])
									comp1++;
							}
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip2[i])
									comp2++;
							}

							if (comp1 == 4 || comp2 == 4) {

								comp1 = 0;
								comp2 = 0;
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip1[i])
										comp1++;
								}
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip2[i])
										comp2++;
								}
								if (comp1 == 4 || comp2 == 4) {

									if ((poc_ramcov != aktualny->first) && ((flag & SYN) != 0)) {
										continue;
									}




									//zistuje cislo ramca
									fprintf(TCP_f, "Ramec %d\n", poc_ramcov);

									//zistuje dlzku ramca
									fprintf(TCP_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

									if ((hlavicka->len) >= 60)
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
									else
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

									//vypis ethernet
									fprintf(TCP_f, "%s\n", globalProtocolName);

									//zistuje zdrojovu MAC adresu
									fprintf(TCP_f, "Zdrojova MAC adresa: ");
									for (int j = 6; j < 12; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//zistuje cielovu MAC adresu
									fprintf(TCP_f, "\n");
									fprintf(TCP_f, "Cielova MAC adresa: ");
									for (int j = 0; j < 6; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//vypis IPv4
									fprintf(TCP_f, "\n%s\n", globalEtherTypeName);

									//vypis zdrojovej IP
									int pom = 0;
									fprintf(TCP_f, "Zdrojova IP adresa: ");
									for (int i = 26; i < 29; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[29]);

									//vypis cielovej IP
									pom = 0;
									fprintf(TCP_f, "Cielova IP adresa: ");
									for (int i = 30; i < 33; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[33]);

									//vypis TCP
									fprintf(TCP_f, "%s\n", globalIPv4ProtocolName);

									//vypis http
									fprintf(TCP_f, "%s\n", tcpProtocolName);


									//vypis zdrojoveho a cieloveho portu
									fprintf(TCP_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
									fprintf(TCP_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

									//vypis ramca
									fprintf(TCP_f, "\n");
									for (int i = 0; i < (hlavicka->caplen); i++) {
										if ((i % 16) == 0)
											fprintf(TCP_f, "\n");

										if ((i % 16) == 8)
											fprintf(TCP_f, "    ");

										fprintf(TCP_f, "%.2X ", data[i]);
									}

									fprintf(TCP_f, "\n\n");


									if ((finBool == 0) && (flag & FIN != 0)) {
										printf("\nRamec: %d --> finBool = 1\n", poc_ramcov);
										finBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 0) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 1\n", poc_ramcov);
										ackBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 1) && ((flag & FIN) != 0)) {
										printf("Ramec: %d --> finBool = 2\n", poc_ramcov);
										finBool = 2;
										continue;
									}
									if ((finBool == 0) && (ackBool == 0) && ((flag & RST) != 0)) {
										printf("Ramec: %d -->1. RST and break after = 2\n", poc_ramcov);
										break;
									}

									if ((finBool == 1) && (ackBool == 1) && ((flag & RST) != 0)) {
										printf("Ramec: %d --> RST and break after = 2\n", poc_ramcov);
										break;

									}
									if ((finBool == 2) && (ackBool == 1) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 2 and break after\n", poc_ramcov);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(TCP_f);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	aktualny = prvy;
}
void port_ftp_control() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//definicia output txt suboru; sluzi na vypisovania
	FILE *TCP_f;
	TCP_f = fopen("output/TCP_F.txt", "w");

	typedef struct komunikacia {
		int ip1[4];
		int ip2[4];
		int first;
		int twoFin;
		int finRst;
		int rst;
		struct komunikacia *dalsi;
	}KOMUNIKACIA;

	KOMUNIKACIA *prvy = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));
	KOMUNIKACIA *aktualny = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

	int counting = 0;

	//nacitanie komunikacii do struktury
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {
		++poc_ramcov;


		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == ipv4)) {

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);

				if (data[23] == tcp) {

					open_ftp_control();

					if ((data[34] * 256 + data[35]) == ftp_control || (data[36] * 256 + data[37]) == ftp_control) {

						unsigned int flag = data[47];

						if ((flag & SYN) != 0) {
							counting++;
							if (counting == 1) {

								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									prvy->ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									prvy->ip2[pom++] = data[i];
								}

								prvy->twoFin = 0;
								prvy->finRst = 0;
								prvy->rst = 0;
								prvy->dalsi = NULL;
								prvy->first = poc_ramcov;
								aktualny = prvy;
							}
							else {
								int ip1[4];
								int ip2[4];
								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									ip2[pom++] = data[i];
								}

								aktualny = prvy;
								while (aktualny != NULL) {
									int comp1, comp2;
									comp1 = 0;
									comp2 = 0;

									for (int i = 0; i < 4; i++) {
										if (ip1[i] == aktualny->ip2[i])
											comp1++;
									}
									for (int i = 0; i < 4; i++) {
										if (ip2[i] == aktualny->ip1[i])
											comp2++;
									}
									if (comp1 == 4 || comp2 == 4) {
										break;
									}
									else {
										if (aktualny->dalsi == NULL) {
											KOMUNIKACIA *new = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

											int pom = 0;
											for (int i = 26; i <= 29; i++) {
												new->ip1[pom++] = data[i];
											}

											pom = 0;
											for (int i = 30; i <= 33; i++) {
												new->ip2[pom++] = data[i];
											}

											new->twoFin = 0;
											new->finRst = 0;
											new->rst = 0;
											new->first = poc_ramcov;
											new->dalsi = NULL;
											aktualny->dalsi = new;
											aktualny = new;
											break;
										}
										else
											aktualny = aktualny->dalsi;

									}
								}
							}
						}

						if ((flag & FIN) != 0) {
							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;

								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}
								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->twoFin = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}

						if ((flag & RST) != 0) {

							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							/*
							if (poc_ramcov == 1124) {
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip2[i]);
								}
								printf("\n");

								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip2[i]);
								}
								printf("\n");

							}
							*/
							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;
								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}

								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->rst = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}
					}
				}
			}
		}
	}

	aktualny = prvy;

	/*
	while (aktualny != NULL) {
		printf("Ramec c.: %d\n", aktualny->first);
		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip1[i]);
		}
		printf("\n");

		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip2[i]);
		}
		printf("\ntwoFin: %d\n", aktualny->twoFin);
		printf("finRst: %d\n", aktualny->finRst);
		printf("Rst: %d\n", aktualny->rst);
		printf("\n----------------------------------------------\n");

		aktualny = aktualny->dalsi;
	}
	*/


	pcap_close(pcap_file);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	//vypis prvej kompletnej komunikacie
	aktualny = prvy;
	while (aktualny != NULL) {
		if (aktualny->twoFin == 1 || aktualny->rst == 1 || aktualny->finRst == 1) {
			break;
		}
		else aktualny = aktualny->dalsi;
	}

	fprintf(TCP_f, "Prvá kompletná komunikácia FTP Control:\n\n");
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;

		if (poc_ramcov >= aktualny->first) {


			//zistuje ci je ethernet
			open_ethernet();

			if (((data[12] * 256) + data[13]) > ethernet) {

				//zistuje EtherType
				int localEtherTypeVal = ((data[12] * 256) + data[13]);
				etherType(localEtherTypeVal);

				if ((((data[12] * 256) + data[13]) == ipv4)) {

					//zistenie IPv4 protokolu
					int localIPv4ProtocolType = data[23];
					ipv4Protocol(localIPv4ProtocolType);

					if (data[23] == tcp) {

						open_ftp_control();

						if ((data[34] * 256 + data[35]) == ftp_control || (data[36] * 256 + data[37]) == ftp_control) {

							unsigned int flag = data[47];

							int ip1[4];
							int ip2[4];
							int pom = 0;
							//nacitanie src a dst ip
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							//porovnanie so strukturou

							int comp1 = 0;
							int comp2 = 0;
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip1[i])
									comp1++;
							}
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip2[i])
									comp2++;
							}

							if (comp1 == 4 || comp2 == 4) {

								comp1 = 0;
								comp2 = 0;
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip1[i])
										comp1++;
								}
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip2[i])
										comp2++;
								}
								if (comp1 == 4 || comp2 == 4) {

									if ((poc_ramcov != aktualny->first) && ((flag & SYN) != 0)) {
										continue;
									}




									//zistuje cislo ramca
									fprintf(TCP_f, "Ramec %d\n", poc_ramcov);

									//zistuje dlzku ramca
									fprintf(TCP_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

									if ((hlavicka->len) >= 60)
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
									else
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

									//vypis ethernet
									fprintf(TCP_f, "%s\n", globalProtocolName);

									//zistuje zdrojovu MAC adresu
									fprintf(TCP_f, "Zdrojova MAC adresa: ");
									for (int j = 6; j < 12; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//zistuje cielovu MAC adresu
									fprintf(TCP_f, "\n");
									fprintf(TCP_f, "Cielova MAC adresa: ");
									for (int j = 0; j < 6; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//vypis IPv4
									fprintf(TCP_f, "\n%s\n", globalEtherTypeName);

									//vypis zdrojovej IP
									int pom = 0;
									fprintf(TCP_f, "Zdrojova IP adresa: ");
									for (int i = 26; i < 29; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[29]);

									//vypis cielovej IP
									pom = 0;
									fprintf(TCP_f, "Cielova IP adresa: ");
									for (int i = 30; i < 33; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[33]);

									//vypis TCP
									fprintf(TCP_f, "%s\n", globalIPv4ProtocolName);

									//vypis http
									fprintf(TCP_f, "%s\n", tcpProtocolName);


									//vypis zdrojoveho a cieloveho portu
									fprintf(TCP_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
									fprintf(TCP_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

									//vypis ramca
									fprintf(TCP_f, "\n");
									for (int i = 0; i < (hlavicka->caplen); i++) {
										if ((i % 16) == 0)
											fprintf(TCP_f, "\n");

										if ((i % 16) == 8)
											fprintf(TCP_f, "    ");

										fprintf(TCP_f, "%.2X ", data[i]);
									}

									fprintf(TCP_f, "\n\n");


									if ((finBool == 0) && (flag & FIN != 0)) {
										printf("\nRamec: %d --> finBool = 1\n", poc_ramcov);
										finBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 0) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 1\n", poc_ramcov);
										ackBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 1) && ((flag & FIN) != 0)) {
										printf("Ramec: %d --> finBool = 2\n", poc_ramcov);
										finBool = 2;
										continue;
									}
									if ((finBool == 0) && (ackBool == 0) && ((flag & RST) != 0)) {
										printf("Ramec: %d -->1. RST and break after = 2\n", poc_ramcov);
										break;
									}

									if ((finBool == 1) && (ackBool == 1) && ((flag & RST) != 0)) {
										printf("Ramec: %d --> RST and break after = 2\n", poc_ramcov);
										break;

									}
									if ((finBool == 2) && (ackBool == 1) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 2 and break after\n", poc_ramcov);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(TCP_f);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	aktualny = prvy;
}
void port_ftp_data() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//definicia output txt suboru; sluzi na vypisovania
	FILE *TCP_f;
	TCP_f = fopen("output/TCP_F.txt", "w");

	typedef struct komunikacia {
		int ip1[4];
		int ip2[4];
		int first;
		int twoFin;
		int finRst;
		int rst;
		struct komunikacia *dalsi;
	}KOMUNIKACIA;

	KOMUNIKACIA *prvy = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));
	KOMUNIKACIA *aktualny = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

	int counting = 0;

	//nacitanie komunikacii do struktury
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {
		++poc_ramcov;


		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == ipv4)) {

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);

				if (data[23] == tcp) {

					open_ftp_data();

					if ((data[34] * 256 + data[35]) == ftp_data || (data[36] * 256 + data[37]) == ftp_data) {

						unsigned int flag = data[47];

						if ((flag & SYN) != 0) {
							counting++;
							if (counting == 1) {

								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									prvy->ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									prvy->ip2[pom++] = data[i];
								}

								prvy->twoFin = 0;
								prvy->finRst = 0;
								prvy->rst = 0;
								prvy->dalsi = NULL;
								prvy->first = poc_ramcov;
								aktualny = prvy;
							}
							else {
								int ip1[4];
								int ip2[4];
								int pom = 0;
								for (int i = 26; i <= 29; i++) {
									ip1[pom++] = data[i];
								}

								pom = 0;
								for (int i = 30; i <= 33; i++) {
									ip2[pom++] = data[i];
								}

								aktualny = prvy;
								while (aktualny != NULL) {
									int comp1, comp2;
									comp1 = 0;
									comp2 = 0;

									for (int i = 0; i < 4; i++) {
										if (ip1[i] == aktualny->ip2[i])
											comp1++;
									}
									for (int i = 0; i < 4; i++) {
										if (ip2[i] == aktualny->ip1[i])
											comp2++;
									}
									if (comp1 == 4 || comp2 == 4) {
										break;
									}
									else {
										if (aktualny->dalsi == NULL) {
											KOMUNIKACIA *new = (KOMUNIKACIA*)malloc(sizeof(KOMUNIKACIA));

											int pom = 0;
											for (int i = 26; i <= 29; i++) {
												new->ip1[pom++] = data[i];
											}

											pom = 0;
											for (int i = 30; i <= 33; i++) {
												new->ip2[pom++] = data[i];
											}

											new->twoFin = 0;
											new->finRst = 0;
											new->rst = 0;
											new->first = poc_ramcov;
											new->dalsi = NULL;
											aktualny->dalsi = new;
											aktualny = new;
											break;
										}
										else
											aktualny = aktualny->dalsi;

									}
								}
							}
						}

						if ((flag & FIN) != 0) {
							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;

								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}
								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->twoFin = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}

						if ((flag & RST) != 0) {

							int ip1[4];
							int ip2[4];
							int pom = 0;
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							/*
							if (poc_ramcov == 1124) {
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", ip2[i]);
								}
								printf("\n");

								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip1[i]);
								}
								printf("\n");
								for (int i = 0; i < 4; i++) {
									printf("%d.", aktualny->ip2[i]);
								}
								printf("\n");

							}
							*/
							aktualny = prvy;
							while (aktualny != NULL) {

								int compare = 0;
								for (int i = 0; i < 4; i++) {
									if (ip1[i] == aktualny->ip1[i] || ip1[i] == aktualny->ip2[i])
										compare++;
								}

								if (compare == 4) {
									compare = 0;
									for (int i = 0; i < 4; i++)
										if (ip2[i] == aktualny->ip2[i] || ip2[i] == aktualny->ip1[i])
											compare++;
									if (compare == 4) {
										aktualny->rst = 1;
										break;
									}
									else aktualny = aktualny->dalsi;
								}
								else {
									aktualny = aktualny->dalsi;
								}
							}
						}
					}
				}
			}
		}
	}

	aktualny = prvy;

	/*
	while (aktualny != NULL) {
		printf("Ramec c.: %d\n", aktualny->first);
		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip1[i]);
		}
		printf("\n");

		for (int i = 0; i < 4; i++) {
			printf("%d.", aktualny->ip2[i]);
		}
		printf("\ntwoFin: %d\n", aktualny->twoFin);
		printf("finRst: %d\n", aktualny->finRst);
		printf("Rst: %d\n", aktualny->rst);
		printf("\n----------------------------------------------\n");

		aktualny = aktualny->dalsi;
	}
	*/


	pcap_close(pcap_file);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	//vypis prvej kompletnej komunikacie
	aktualny = prvy;
	while (aktualny != NULL) {
		if (aktualny->twoFin == 1 || aktualny->rst == 1 || aktualny->finRst == 1) {
			break;
		}
		else aktualny = aktualny->dalsi;
	}

	fprintf(TCP_f, "Prvá kompletná komunikácia FTP Data:\n\n");
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;

		if (poc_ramcov >= aktualny->first) {


			//zistuje ci je ethernet
			open_ethernet();

			if (((data[12] * 256) + data[13]) > ethernet) {

				//zistuje EtherType
				int localEtherTypeVal = ((data[12] * 256) + data[13]);
				etherType(localEtherTypeVal);

				if ((((data[12] * 256) + data[13]) == ipv4)) {

					//zistenie IPv4 protokolu
					int localIPv4ProtocolType = data[23];
					ipv4Protocol(localIPv4ProtocolType);

					if (data[23] == tcp) {

						open_ftp_data();

						if ((data[34] * 256 + data[35]) == ftp_data || (data[36] * 256 + data[37]) == ftp_data) {

							unsigned int flag = data[47];

							int ip1[4];
							int ip2[4];
							int pom = 0;
							//nacitanie src a dst ip
							for (int i = 26; i <= 29; i++) {
								ip1[pom++] = data[i];
							}

							pom = 0;
							for (int i = 30; i <= 33; i++) {
								ip2[pom++] = data[i];
							}

							//porovnanie so strukturou

							int comp1 = 0;
							int comp2 = 0;
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip1[i])
									comp1++;
							}
							for (int i = 0; i < 4; i++) {
								if (ip1[i] == aktualny->ip2[i])
									comp2++;
							}

							if (comp1 == 4 || comp2 == 4) {

								comp1 = 0;
								comp2 = 0;
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip1[i])
										comp1++;
								}
								for (int i = 0; i < 4; i++) {
									if (ip2[i] == aktualny->ip2[i])
										comp2++;
								}
								if (comp1 == 4 || comp2 == 4) {

									if ((poc_ramcov != aktualny->first) && ((flag & SYN) != 0)) {
										continue;
									}




									//zistuje cislo ramca
									fprintf(TCP_f, "Ramec %d\n", poc_ramcov);

									//zistuje dlzku ramca
									fprintf(TCP_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

									if ((hlavicka->len) >= 60)
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
									else
										fprintf(TCP_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

									//vypis ethernet
									fprintf(TCP_f, "%s\n", globalProtocolName);

									//zistuje zdrojovu MAC adresu
									fprintf(TCP_f, "Zdrojova MAC adresa: ");
									for (int j = 6; j < 12; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//zistuje cielovu MAC adresu
									fprintf(TCP_f, "\n");
									fprintf(TCP_f, "Cielova MAC adresa: ");
									for (int j = 0; j < 6; j++)
										fprintf(TCP_f, "%.2X ", data[j]);

									//vypis IPv4
									fprintf(TCP_f, "\n%s\n", globalEtherTypeName);

									//vypis zdrojovej IP
									int pom = 0;
									fprintf(TCP_f, "Zdrojova IP adresa: ");
									for (int i = 26; i < 29; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[29]);

									//vypis cielovej IP
									pom = 0;
									fprintf(TCP_f, "Cielova IP adresa: ");
									for (int i = 30; i < 33; i++) {
										fprintf(TCP_f, "%d.", data[i]);
									}
									fprintf(TCP_f, "%d\n", data[33]);

									//vypis TCP
									fprintf(TCP_f, "%s\n", globalIPv4ProtocolName);

									//vypis http
									fprintf(TCP_f, "%s\n", tcpProtocolName);


									//vypis zdrojoveho a cieloveho portu
									fprintf(TCP_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
									fprintf(TCP_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

									//vypis ramca
									fprintf(TCP_f, "\n");
									for (int i = 0; i < (hlavicka->caplen); i++) {
										if ((i % 16) == 0)
											fprintf(TCP_f, "\n");

										if ((i % 16) == 8)
											fprintf(TCP_f, "    ");

										fprintf(TCP_f, "%.2X ", data[i]);
									}

									fprintf(TCP_f, "\n\n");


									if ((finBool == 0) && (flag & FIN != 0)) {
										printf("\nRamec: %d --> finBool = 1\n", poc_ramcov);
										finBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 0) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 1\n", poc_ramcov);
										ackBool = 1;
										continue;
									}
									if ((finBool == 1) && (ackBool == 1) && ((flag & FIN) != 0)) {
										printf("Ramec: %d --> finBool = 2\n", poc_ramcov);
										finBool = 2;
										continue;
									}
									if ((finBool == 0) && (ackBool == 0) && ((flag & RST) != 0)) {
										printf("Ramec: %d -->1. RST and break after = 2\n", poc_ramcov);
										break;
									}

									if ((finBool == 1) && (ackBool == 1) && ((flag & RST) != 0)) {
										printf("Ramec: %d --> RST and break after = 2\n", poc_ramcov);
										break;

									}
									if ((finBool == 2) && (ackBool == 1) && ((flag & ACK) != 0)) {
										printf("Ramec: %d --> ackBool = 2 and break after\n", poc_ramcov);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(TCP_f);

	pcap_file = pcap_open_offline(cesta, errbuff);
	poc_ramcov = 0;

	aktualny = prvy;
}

void port_tftp() {

		char errbuff[PCAP_ERRBUF_SIZE];

		//cesta k input pcap suboru
		char cesta[100];
		int poc_ramcov = 0;
		int spol_hodnota = 0;

		printf("Zadaj cestu k suboru pcap.\n");
		scanf("%s", &cesta);

		pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

		struct pcap_pkthdr *hlavicka;
		const u_char *data;

		//nacitanie hodnot do globalnych premennych
		open_tftp();

		//definicia output txt suboru; sluzi na vypisovania
		FILE *tftp_f;
		tftp_f = fopen("output/tftp_output.txt", "w");

		while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

			++poc_ramcov;

			//zistuje ci je ethernet
			open_ethernet();

			if (((data[12] * 256) + data[13]) > ethernet) {

				//zistuje EtherType
				int localEtherTypeVal = ((data[12] * 256) + data[13]);
				etherType(localEtherTypeVal);

				if ((((data[12] * 256) + data[13]) == ipv4)) {

					//zistenie IPv4 protokolu
					int localIPv4ProtocolType = data[23];
					ipv4Protocol(localIPv4ProtocolType);

					if (data[23] == udp) {
						open_tftp();
						if ((data[34] * 256 + data[35]) == tftp) {

							spol_hodnota = (data[36] * 256 + data[37]);

							//zistuje cislo ramca
							fprintf(tftp_f, "Ramec %d\n", poc_ramcov);

							//zistuje dlzku ramca
							fprintf(tftp_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

							if ((hlavicka->len) >= 60)
								fprintf(tftp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
							else
								fprintf(tftp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

							//vypis ethernet
							fprintf(tftp_f, "%s\n", globalProtocolName);

							//zistuje zdrojovu MAC adresu
							fprintf(tftp_f, "Zdrojova MAC adresa: ");
							for (int j = 6; j < 12; j++)
								fprintf(tftp_f, "%.2X ", data[j]);

							//zistuje cielovu MAC adresu
							fprintf(tftp_f, "\n");
							fprintf(tftp_f, "Cielova MAC adresa: ");
							for (int j = 0; j < 6; j++)
								fprintf(tftp_f, "%.2X ", data[j]);


							//vypis IPv4
							fprintf(tftp_f, "\n%s\n", globalEtherTypeName);

							//vypis zdrojovej IP
							fprintf(tftp_f, "Zdrojova IP adresa: ");
							for (int i = 26; i < 29; i++)
								fprintf(tftp_f, "%d.", data[i]);
							fprintf(tftp_f, "%d\n", data[29]);

							//vypis cielovej IP
							fprintf(tftp_f, "Cielova IP adresa: ");
							for (int i = 30; i < 33; i++)
								fprintf(tftp_f, "%d.", data[i]);
							fprintf(tftp_f, "%d\n", data[33]);

							//vypis UDP
							fprintf(tftp_f, "%s\n", globalIPv4ProtocolName);

							//vypis zdrojoveho a cieloveho portu
							fprintf(tftp_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
							fprintf(tftp_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

							//vypis ramca
							fprintf(tftp_f, "\n");
							for (int i = 0; i < (hlavicka->caplen); i++) {
								if ((i % 16) == 0)
									fprintf(tftp_f, "\n");

								if ((i % 16) == 8)
									fprintf(tftp_f, "    ");

								fprintf(tftp_f, "%.2X ", data[i]);
							}
							fprintf(tftp_f, "\n\n");
						}

						else {
							if ((data[36] * 256 + data[37]) == tftp) {

								spol_hodnota = (data[34] * 256 + data[35]);

								//zistuje cislo ramca
								fprintf(tftp_f, "Ramec %d\n", poc_ramcov);

								//zistuje dlzku ramca
								fprintf(tftp_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

								if ((hlavicka->len) >= 60)
									fprintf(tftp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
								else
									fprintf(tftp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

								//vypis ethernet
								fprintf(tftp_f, "%s\n", globalProtocolName);

								//zistuje zdrojovu MAC adresu
								fprintf(tftp_f, "Zdrojova MAC adresa: ");
								for (int j = 6; j < 12; j++)
									fprintf(tftp_f, "%.2X ", data[j]);

								//zistuje cielovu MAC adresu
								fprintf(tftp_f, "\n");
								fprintf(tftp_f, "Cielova MAC adresa: ");
								for (int j = 0; j < 6; j++)
									fprintf(tftp_f, "%.2X ", data[j]);



								//vypis IPv4
								fprintf(tftp_f, "\n%s\n", globalEtherTypeName);

								//vypis zdrojovej IP
								fprintf(tftp_f, "Zdrojova IP adresa: ");
								for (int i = 26; i < 29; i++)
									fprintf(tftp_f, "%d.", data[i]);
								fprintf(tftp_f, "%d\n", data[29]);

								//vypis cielovej IP
								fprintf(tftp_f, "Cielova IP adresa: ");
								for (int i = 30; i < 33; i++)
									fprintf(tftp_f, "%d.", data[i]);
								fprintf(tftp_f, "%d\n", data[33]);

								//vypis UDP
								fprintf(tftp_f, "%s\n", globalIPv4ProtocolName);

								//vypis zdrojoveho a cieloveho portu
								fprintf(tftp_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
								fprintf(tftp_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

								//vypis ramca
								fprintf(tftp_f, "\n");
								for (int i = 0; i < (hlavicka->caplen); i++) {
									if ((i % 16) == 0)
										fprintf(tftp_f, "\n");

									if ((i % 16) == 8)
										fprintf(tftp_f, "    ");

									fprintf(tftp_f, "%.2X ", data[i]);
								}
								fprintf(tftp_f, "\n\n");

							}

							else {
								if ((data[34] * 256 + data[35]) == spol_hodnota || (data[36] * 256 + data[37]) == spol_hodnota) {

										//zistuje cislo ramca
										fprintf(tftp_f, "Ramec %d\n", poc_ramcov);

										//zistuje dlzku ramca
										fprintf(tftp_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

										if ((hlavicka->len) >= 60)
											fprintf(tftp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
										else
											fprintf(tftp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

										//vypis ethernet
										fprintf(tftp_f, "%s\n", globalProtocolName);

										//zistuje zdrojovu MAC adresu
										fprintf(tftp_f, "Zdrojova MAC adresa: ");
										for (int j = 6; j < 12; j++)
											fprintf(tftp_f, "%.2X ", data[j]);

										//zistuje cielovu MAC adresu
										fprintf(tftp_f, "\n");
										fprintf(tftp_f, "Cielova MAC adresa: ");
										for (int j = 0; j < 6; j++)
											fprintf(tftp_f, "%.2X ", data[j]);



										//vypis IPv4
										fprintf(tftp_f, "\n%s\n", globalEtherTypeName);

										//vypis zdrojovej IP
										fprintf(tftp_f, "Zdrojova IP adresa: ");
										for (int i = 26; i < 29; i++)
											fprintf(tftp_f, "%d.", data[i]);
										fprintf(tftp_f, "%d\n", data[29]);

										//vypis cielovej IP
										fprintf(tftp_f, "Cielova IP adresa: ");
										for (int i = 30; i < 33; i++)
											fprintf(tftp_f, "%d.", data[i]);
										fprintf(tftp_f, "%d\n", data[33]);

										//vypis UDP
										fprintf(tftp_f, "%s\n", globalIPv4ProtocolName);

										//vypis zdrojoveho a cieloveho portu
										fprintf(tftp_f, "Zdrojovy port: %d\n", (data[34] * 256) + data[35]);
										fprintf(tftp_f, "Cielovy port: %d", (data[36] * 256) + data[37]);

										//vypis ramca
										fprintf(tftp_f, "\n");
										for (int i = 0; i < (hlavicka->caplen); i++) {
											if ((i % 16) == 0)
												fprintf(tftp_f, "\n");

											if ((i % 16) == 8)
												fprintf(tftp_f, "    ");

											fprintf(tftp_f, "%.2X ", data[i]);
										}
										fprintf(tftp_f, "\n\n");
									}
							}
								
						}
					}
				}
			}
		}
		fclose(tftp_f);
	}

void protokol_icmp() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//definicia output txt suboru; sluzi na vypisovania
	FILE *icmp_f;
	icmp_f = fopen("output/icmp_output.txt", "w");

	FILE *fkonstanta;
	if ((fkonstanta = fopen("konstanty/icmp_type.txt", "r")) == NULL) {
		printf("Subor sa neotvoril.");
		return NULL;
	}

	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;
		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == ipv4)) {

				//zistenie IPv4 protokolu
				int localIPv4ProtocolType = data[23];
				ipv4Protocol(localIPv4ProtocolType);

				open_icmp_type();

				if (data[23] == icmp) {
					for (int j = 0; j < 16; j++) {
						if (data[34] == icmp_type[j]) {

							//zistuje cislo ramca
							fprintf(icmp_f, "Ramec %d\n", poc_ramcov);

							//zistuje dlzku ramca
							fprintf(icmp_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

							if ((hlavicka->len) >= 60)
								fprintf(icmp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
							else
								fprintf(icmp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

							//vypis ethernet
							fprintf(icmp_f, "%s\n", globalProtocolName);

							//zistuje zdrojovu MAC adresu
							fprintf(icmp_f, "Zdrojova MAC adresa: ");
							for (int j = 6; j < 12; j++)
								fprintf(icmp_f, "%.2X ", data[j]);

							//zistuje cielovu MAC adresu
							fprintf(icmp_f, "\n");
							fprintf(icmp_f, "Cielova MAC adresa: ");
							for (int j = 0; j < 6; j++)
								fprintf(icmp_f, "%.2X ", data[j]);


							//vypis IPv4
							fprintf(icmp_f, "\n%s\n", globalEtherTypeName);

							//vypis zdrojovej IP
							fprintf(icmp_f, "Zdrojova IP adresa: ");
							for (int i = 26; i < 29; i++)
								fprintf(icmp_f, "%d.", data[i]);
							fprintf(icmp_f, "%d\n", data[29]);

							//vypis cielovej IP
							fprintf(icmp_f, "Cielova IP adresa: ");
							for (int i = 30; i < 33; i++)
								fprintf(icmp_f, "%d.", data[i]);
							fprintf(icmp_f, "%d\n", data[33]);

							//vypis ICMP
							fprintf(icmp_f, "%s\n", globalIPv4ProtocolName);

							//type
							fprintf(icmp_f, "Type: %d - ", icmp_type[j]);
							int k;
							char constant[50];
							for (k = 0; k <= ((2*j)+1); k++) {
								fgets(constant, sizeof(constant), fkonstanta);
								if (k == ((2*j)+1)) {									
									fprintf(icmp_f, "%s", constant);
									fseek(fkonstanta, 0L, SEEK_SET);
								}
							}

							//vypis ramca
							fprintf(icmp_f, "\n");
							for (int i = 0; i < (hlavicka->caplen); i++) {
								if ((i % 16) == 0)
									fprintf(icmp_f, "\n");

								if ((i % 16) == 8)
									fprintf(icmp_f, "    ");

								fprintf(icmp_f, "%.2X ", data[i]);
							}
							fprintf(icmp_f, "\n\n");
						}
					}
				}
			}
		}
	}
	fclose(icmp_f);
}

void komunikacia_arp() {

	char errbuff[PCAP_ERRBUF_SIZE];

	//cesta k input pcap suboru
	char cesta[100];
	int poc_ramcov = 0;
	int poz_tpa = 38; //target protocol address
	int poz_spa = 28;
	int rovnake = 0;
	int c_kom = 0;

	printf("Zadaj cestu k suboru pcap.\n");
	scanf("%s", &cesta);

	pcap_t* pcap_file = pcap_open_offline(cesta, errbuff);

	struct pcap_pkthdr *hlavicka;
	const u_char *data;

	//nacitanie hodnot do globalnych premennych

	open_arp();
	open_arp_request();
	open_arp_reply();


	//definicia output txt suboru; sluzi na vypisovania
	FILE *arp_f;
	arp_f = fopen("output/arp_output.txt", "w");

	FILE *fkonstanta;
	char constant[10];

	typedef struct ip {
		int op;
		unsigned char ip[4];
		struct ip *dalsi;
		struct ip *predchadzajuci;
	};

	struct ip *prvy = NULL;
	struct ip *aktualny = NULL;
	struct ip *pom = NULL;

	//zapis ramcov do zoznamu
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		//zistuje ci je ethernet
		open_ethernet();

		if (((data[12] * 256) + data[13]) > ethernet) {

			//zistuje EtherType
			int localEtherTypeVal = ((data[12] * 256) + data[13]);
			etherType(localEtherTypeVal);

			if ((((data[12] * 256) + data[13]) == arp)) {

				//zapis prveho
				if (prvy == NULL) {

					prvy = (struct ip*)malloc(sizeof(struct ip));
					aktualny = (struct ip*)malloc(sizeof(struct ip));
					//request
					if ((data[20] * 256) + data[21] == arp_request) {

						prvy->op = 1;

						for (int j = 0; j < 4; j++) {
							prvy->ip[j] = data[poz_tpa];
							poz_tpa++;
						}
						poz_tpa = 38;
						aktualny = prvy;
						aktualny->dalsi = NULL;
						aktualny->predchadzajuci = NULL;

					}

					//reply
					if ((data[20] * 256) + data[21] == arp_reply) {

						prvy->op = 2;

						for (int j = 0; j < 4; j++) {
							prvy->ip[j] = data[poz_spa];
							poz_spa++;
						}
						poz_spa = 28;
						prvy->dalsi = NULL;
						prvy->predchadzajuci = NULL;
						aktualny = prvy;
					}
				}
				else {
						// zapis ostatnych

							aktualny->dalsi = (struct ip*)malloc(sizeof(struct ip));
							pom = (struct ip*)malloc(sizeof(struct ip));
							
							//request
							if ((data[20] * 256) + data[21] == arp_request) {

								aktualny->dalsi->op = 1;

								for (int j = 0; j < 4; j++) {
									aktualny->dalsi->ip[j] = data[poz_tpa];
									poz_tpa++;
								}
								
								poz_tpa = 38;
								pom = aktualny;
								aktualny = aktualny->dalsi;
								aktualny->dalsi= NULL;								
								aktualny->predchadzajuci = pom;
								pom = NULL;
							}

							//reply
							if ((data[20] * 256) + data[21] == arp_reply) {

								aktualny->dalsi->op = 2;

								for (int j = 0; j < 4; j++) {
									aktualny->dalsi->ip[j] = data[poz_spa];
									poz_spa++;
								}
								poz_spa = 28;
								aktualny->dalsi->dalsi = NULL;
								pom = aktualny;
								aktualny = aktualny->dalsi;
								aktualny->predchadzajuci = pom;
								pom = NULL;
							}
						
				}
				
			}
		}
	}

	pcap_close(pcap_file);
	pcap_file = pcap_open_offline(cesta, errbuff);
	
	aktualny = prvy;
	pom = (struct ip*)malloc(sizeof(struct ip));

	//prehladavanie a vypis
	while (pcap_next_ex(pcap_file, &hlavicka, &data) != -2) {

		++poc_ramcov;

		
		if (((data[12] * 256) + data[13]) > ethernet) {
			if ((((data[12] * 256) + data[13]) == arp)) {
								
				//ak je aktualny request
				if (aktualny->op == 1) {

					//zisti aky je dalsi
					if (aktualny->dalsi != NULL) {

						//ak dalsi je reply
						//vypis
						if (aktualny->dalsi->op == 2) {
							//a ip su rovnake, vypisuje
							if (memcmp(aktualny->ip, aktualny->dalsi->ip, sizeof(aktualny->ip)) == 0) {

								//vypis ramca request
								fprintf(arp_f,"Komunikacia c. %d\n", ++c_kom);
								fprintf(arp_f, "ARP-Request, IP adresa: ");

								for (int j = 0; j < 4; j++) {
									fprintf(arp_f, "%d. ", aktualny->ip[j]);
								}

								fprintf(arp_f, "MAC adresa: ???\n");

								fprintf(arp_f, "Zdrojova IP: ");
								for (int j = 28; j < 32; j++) {
									fprintf(arp_f, "%d. ", data[j]);
								}

								fprintf(arp_f, "Cielova IP: ");
								for (int j = 0; j < 4; j++) {
									fprintf(arp_f, "%d. ", aktualny->ip[j]);
								}

								fprintf(arp_f, "\n");
								fprintf(arp_f, "Ramec %d\n", poc_ramcov);

								//zistuje dlzku ramca
								fprintf(arp_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

								if ((hlavicka->len) >= 60)
									fprintf(arp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
								else
									fprintf(arp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

								//zistuje zdrojovu MAC adresu
								fprintf(arp_f, "Zdrojova MAC adresa: ");
								for (int j = 6; j < 12; j++)
									fprintf(arp_f, "%.2X ", data[j]);

								//zistuje cielovu MAC adresu
								fprintf(arp_f, "\n");
								fprintf(arp_f, "Cielova MAC adresa: ");
								for (int j = 0; j < 6; j++)
									fprintf(arp_f, "%.2X ", data[j]);

								fprintf(arp_f, "\n");
								for (int i = 0; i < (hlavicka->caplen); i++) {
									if ((i % 16) == 0)
										fprintf(arp_f, "\n");

									if ((i % 16) == 8)
										fprintf(arp_f, "    ");

									fprintf(arp_f, "%.2X ", data[i]);
								}

								fprintf(arp_f, "\n\n");

							}

						}

						//alebo dalsi je request
						if (aktualny->dalsi->op == 1) {
							//a rovnaju sa adresy
							//vypis
							if (memcmp(aktualny->ip, aktualny->dalsi->ip, sizeof(aktualny->ip)) == 0) {

								if (aktualny->dalsi != NULL)
									pom = aktualny->dalsi;

								if (pom->dalsi != NULL)
								{

									while (memcmp(pom->ip, pom->dalsi->ip, sizeof(pom->ip)) == 0 && pom->dalsi->op == 1) {

										if (pom->dalsi != NULL)
											pom = pom->dalsi;

										if (pom->dalsi == NULL)
											break;
									}



									if (memcmp(pom->ip, pom->dalsi->ip, sizeof(pom->ip)) == 0 && pom->dalsi->op == 2) {

										//vypis ramca request
										fprintf(arp_f, "Komunikacia c. %d\n", ++c_kom);
										fprintf(arp_f, "ARP-Request, IP adresa: ");

										for (int j = 0; j < 4; j++) {
											fprintf(arp_f, "%d. ", aktualny->ip[j]);
										}

										fprintf(arp_f, "MAC adresa: ???\n");

										fprintf(arp_f, "Zdrojova IP: ");
										for (int j = 28; j < 32; j++) {
											fprintf(arp_f, "%d. ", data[j]);
										}

										fprintf(arp_f, "Cielova IP: ");
										for (int j = 0; j < 4; j++) {
											fprintf(arp_f, "%d. ", aktualny->ip[j]);
										}

										fprintf(arp_f, "\n");
										fprintf(arp_f, "Ramec %d\n", poc_ramcov);

										//zistuje dlzku ramca
										fprintf(arp_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

										if ((hlavicka->len) >= 60)
											fprintf(arp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
										else
											fprintf(arp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

										//zistuje zdrojovu MAC adresu
										fprintf(arp_f, "Zdrojova MAC adresa: ");
										for (int j = 6; j < 12; j++)
											fprintf(arp_f, "%.2X ", data[j]);

										//zistuje cielovu MAC adresu
										fprintf(arp_f, "\n");
										fprintf(arp_f, "Cielova MAC adresa: ");
										for (int j = 0; j < 6; j++)
											fprintf(arp_f, "%.2X ", data[j]);

										fprintf(arp_f, "\n");
										for (int i = 0; i < (hlavicka->caplen); i++) {
											if ((i % 16) == 0)
												fprintf(arp_f, "\n");

											if ((i % 16) == 8)
												fprintf(arp_f, "    ");

											fprintf(arp_f, "%.2X ", data[i]);
										}

										fprintf(arp_f, "\n\n");
									}
								}
							}
							
						}
					}
				}
				//ak je aktualny reply
				//vypis
				if (aktualny->op == 2) {

					if (aktualny->predchadzajuci->op == 1) {
						if (memcmp(aktualny->ip, aktualny->predchadzajuci->ip, sizeof(aktualny->ip)) == 0) {

							fprintf(arp_f, "ARP-Reply, IP adresa: ");

							for (int j = 0; j < 4; j++) {
								fprintf(arp_f, "%d. ", aktualny->ip[j]);
							}

							fprintf(arp_f, "MAC adresa: ");
							for (int j = 22; j < 28; j++)
								fprintf(arp_f, "%.2X ", data[j]);

							fprintf(arp_f, "\n");
							fprintf(arp_f, "Zdrojova IP: ");
							for (int j = 0; j < 4; j++) {
								fprintf(arp_f, "%d. ", aktualny->ip[j]);
							}

							fprintf(arp_f, "Cielova IP: ");
							for (int j = 38; j < 41; j++) {
								fprintf(arp_f, "%d. ", data[j]);
							}

							fprintf(arp_f, "\n");
							fprintf(arp_f, "Ramec %d\n", poc_ramcov);

							//zistuje dlzku ramca
							fprintf(arp_f, "Dlzka ramca poskytnuta v pcap API - %d B\n", hlavicka->len);

							if ((hlavicka->len) >= 60)
								fprintf(arp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", (hlavicka->len) += 4);
							else
								fprintf(arp_f, "Dlzka ramca prenasaneho po mediu - %d B\n", 64);

							//zistuje zdrojovu MAC adresu
							fprintf(arp_f, "Zdrojova MAC adresa: ");
							for (int j = 6; j < 12; j++)
								fprintf(arp_f, "%.2X ", data[j]);

							//zistuje cielovu MAC adresu
							fprintf(arp_f, "\n");
							fprintf(arp_f, "Cielova MAC adresa: ");
							for (int j = 0; j < 6; j++)
								fprintf(arp_f, "%.2X ", data[j]);

							fprintf(arp_f, "\n");
							for (int i = 0; i < (hlavicka->caplen); i++) {
								if ((i % 16) == 0)
									fprintf(arp_f, "\n");

								if ((i % 16) == 8)
									fprintf(arp_f, "    ");

								fprintf(arp_f, "%.2X ", data[i]);
							}

							fprintf(arp_f, "\n\n");

							c_kom++;
						}
					}

				}
				//posun na dalsi ramec
				if (aktualny->dalsi != NULL)
					aktualny = aktualny->dalsi;
			}
		}
	}
	fclose(arp_f);
}

int main(int argc, char *argv[]) {

	char z;

	printf("Pre vykonanie operacie stlac klavesu.\n");
	printf("Pre vypis vsetkych ramcov stlac klavesu 'x'\n");
	printf("Pre vypis ramcov obsahujucich http protokol stlac klavesu 'a'\n");
	printf("Pre vypis ramcov obsahujucich https protokol stlac klavesu 'b'\n");
	printf("Pre vypis ramcov obsahujucich telnet protokol stlac klavesu 'c'\n");
	printf("Pre vypis ramcov obsahujucich ssh protokol stlac klavesu 'd'\n");
	printf("Pre vypis ramcov obsahujucich FTP control protokol stlac klavesu 'e'\n");
	printf("Pre vypis ramcov obsahujucich FTP data protokol stlac klavesu 'f'\n");
	printf("Pre vypis ramcov obsahujucich TFTP stlac klavesu 'g'\n");
	printf("Pre vypis ramcov obsahujucich ICMP stlac klavesu 'h'\n");
	printf("Pre vypis ramcov obsahujucich ARP dvojice stlac klavesu 'i'\n");
	printf("Pre ukoncenie programu stlac klavesu 'k'.\n");

	while ((scanf("%s", &z)) == 1) {
		switch (z) {

		case 'x':
			vsetko();
			break;
		case 'a':
			port_http();
			break;
		case 'b':
			port_https();
			break;
		case 'c':
			port_telnet();
			break;
		case 'd':
			port_ssh();
			break;
		case 'e':
			port_ftp_control();
			break;
		case 'f':
			port_ftp_data();
			break;
		case'g':
			port_tftp();
			break;
		case'h':
			protokol_icmp();
			break;
		case'i':
			komunikacia_arp();
			break;	
		case 'k':
			return 0;	
		}
	}
}