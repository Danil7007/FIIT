vstup = str (input (""))

ind_rok = 1
miesto = 1
rok = 0
cislo_int = 0
while ind_rok <= 4 :
    cislo = vstup[len(vstup)-ind_rok]

    if cislo == "0" :
        cislo_int = 0
        rok += cislo_int * miesto
    if cislo == "1" :
        cislo_int = 1
        rok += cislo_int * miesto
    if cislo == "2" :
        cislo_int = 2
        rok += cislo_int * miesto
    if cislo == "3" :
        cislo_int = 3
        rok += cislo_int * miesto
    if cislo == "4" :
        cislo_int = 4
        rok += cislo_int * miesto
    if cislo == "5" :
        cislo_int = 5
        rok += cislo_int * miesto
    if cislo == "6" :
        cislo_int = 6
        rok += cislo_int * miesto
    if cislo == "7" :
        cislo_int = 7
        rok += cislo_int * miesto
    if cislo == "8" :
        cislo_int = 8
        rok += cislo_int * miesto
    if cislo == "9" :
        cislo_int = 9
        rok += cislo_int * miesto

    miesto *= 10
    ind_rok += 1

print ("rok", rok)

ind_bodka = 0
ind = 0
while vstup[ind] != "." :
    ind += 1
    if vstup[ind] == "." :
        ind_bodka = ind


ind_den = 0
miesto = 10
den = 0
cislo_int = 0
while ind_den < ind_bodka :
    cislo = vstup[ind_den]

    if cislo == "0" :
        cislo_int = 0
        den += cislo_int * miesto
    if cislo == "1" :
        cislo_int = 1
        den += cislo_int * miesto
    if cislo == "2" :
        cislo_int = 2
        den += cislo_int * miesto
    if cislo == "3" :
        cislo_int = 3
        den += cislo_int * miesto
    if cislo == "4" :
        cislo_int = 4
        den += cislo_int * miesto
    if cislo == "5" :
        cislo_int = 5
        den += cislo_int * miesto
    if cislo == "6" :
        cislo_int = 6
        den += cislo_int * miesto
    if cislo == "7" :
        cislo_int = 7
        den += cislo_int * miesto
    if cislo == "8" :
        cislo_int = 8
        den += cislo_int * miesto
    if cislo == "9" :
        cislo_int = 9
        den += cislo_int * miesto

    miesto /= 10
    ind_den += 1

if ind_bodka == 1 :
    den //= 10

print ("den", den)

spod_hranica = ind_bodka + 1
vrch_hranica = len(vstup) - 5

mesiac = []
while spod_hranica < vrch_hranica :
    mesiac.append (vstup[spod_hranica])
    spod_hranica += 1

print ("mesiac", mesiac)