def pocet_dni_medzi (mesiac1, rok1, mesiac2, rok2) :
    mesiac1 = str (input("mesiac1"))
mesiac2 = str (input("mesiac2"))
rok1 =  int (input("rok1"))
rok2 = int (input("rok2"))

if mesiac1 == mesiac2 and rok1 == rok2 :
    print ("0")

if mesiac1 == "jan" :
    m1 = 1
if mesiac1 == "feb" :
    m1 = 2
if mesiac1 == "mar" :
    m1 = 3
if mesiac1 == "apr" :
    m1 = 4
if mesiac1 == "maj" :
    m1 = 5
if mesiac1 == "jun" :
    m1 = 6
if mesiac1 == "jul" :
    m1 = 7
if mesiac1 == "aug" :
    m1 = 8
if mesiac1 == "sep" :
    m1 = 9
if mesiac1 == "okt" :
    m1 = 10
if mesiac1 == "nov" :
    m1 = 11
if mesiac1 == "dec" :
    m1 = 12

if mesiac2 == "jan" :
    m2 = 1
if mesiac2 == "feb" :
    m2 = 2
if mesiac2 == "mar" :
    m2 = 3
if mesiac2 == "apr" :
    m2 = 4
if mesiac2 == "maj" :
    m2 = 5
if mesiac2 == "jun" :
    m2 = 6
if mesiac2 == "jul" :
    m2 = 7
if mesiac2 == "aug" :
    m2 = 8
if mesiac2 == "sep" :
    m2 = 9
if mesiac2 == "okt" :
    m2 = 10
if mesiac2 == "nov" :
    m2 = 11
if mesiac2 == "dec" :
    m2 = 12

celkovy_pocet = 0
while rok1 <= rok2 :
    while m1 <= m2 :
        dni = 0

        if rok1 % 4 == 0:
            prestupny = 1
        else :
            prestupny = 0

        if m1 == 2 and prestupny == 0 :
            dni = 28
        if m1 == 2 and prestupny == 1 :
            dni = 29
        if m1 == 4 or m1 == 6 or m1 == 9 or m1 == 11 :
            dni = 30
        else :
            dni = 31

        celkovy_pocet += dni
        m1 += 1
    rok1 += 1

    print (celkovy_pocet)
