def dni_v_tyzdni (vstup) :

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


    spod_hranica = ind_bodka + 1
    vrch_hranica = len(vstup) - 5

    mesiac = []
    while spod_hranica < vrch_hranica :
        mesiac.append (vstup[spod_hranica])
        spod_hranica += 1

    if mesiac == ['j','a','n','u','a','r'] :
        mes2 = 1
    if mesiac == ['f','e','b',"r",'u','a','r'] :
        mes2 = 2
    if mesiac == ["m","a","r","e","c"] :
        mes2 = 3
    if mesiac == ["a","p","r","i","l"] :
        mes2 = 4
    if mesiac == ["m","a","j"] :
        mes2 = 5
    if mesiac == ["j","u","n"] :
        mes2 = 6
    if mesiac == ["j","u","l"] :
        mes2 = 7
    if mesiac == ["a","u","g","u","s","t"] :
        mes2 = 8
    if mesiac == ["s","e","p","t","e","m","b","e",'r'] :
        mes2 = 9
    if mesiac == ["o","k","t","o","b","e","r"] :
        mes2 = 10
    if mesiac == ["n","o","v","e","m","b","e","r"] :
        mes2 = 11
    if mesiac == ["d","e","c","e","m","b","e","r"] :
        mes2 = 12


    mes1 = 1
    rok1 = 1901

    rok2 = rok

    datum1 = (mes1 * 10000 + rok1)
    datum2 = (mes2 * 10000 + rok2)

    dni_spolu = 0
    while datum1 <= datum2 :

        while datum1 // 10000 <= 12 :

            dni_v_mesiaci = 0

            if datum1 // 10000 == 1 or datum1 // 10000 == 3 or datum1 // 10000 == 5 or datum1 // 10000 == 7 or datum1 // 10000 == 8 or datum1 // 10000 == 10 or datum1 // 10000 == 12 :
                dni_v_mesiaci = 31
            elif datum1 // 10000 == 2 :
                if datum1 % 4 == 0 :
                    dni_v_mesiaci = 29
                else :
                    dni_v_mesiaci = 28
            else :
                dni_v_mesiaci = 30

            dni_spolu += dni_v_mesiaci

            if datum1 == datum2 :
                dni_spolu -= dni_v_mesiaci
                break
            else :
                datum1 += 1 * 10000


        if datum1 == datum2 :
            break
        datum1 -= 120000
        datum1 += 1

    dni_spolu += den

    #----------------------------------------------------------------------------------------------------------------------------------------------------- ODTIALTO TO ZISTUJE DEN, POCET DNI FUNGUJE ASI DOBRE

    tyzden = dni_spolu // 7
    extra = dni_spolu - tyzden*7 - 1

    if extra == -1 :
        extra = 6

    if extra == 0 :
        return ("utorok")
    if extra == 1 :
        return ("streda")
    if extra == 2 :
        return ("stvrtok")
    if extra == 3 :
        return ("piatok")
    if extra == 4 :
        return ("sobota")
    if extra == 5 :
        return ("nedela")
    if extra == 6 :
        return ("pondelok")