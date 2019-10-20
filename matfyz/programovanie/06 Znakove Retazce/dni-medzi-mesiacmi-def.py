#mes1 = str (input ("Zadaj mesiac 1: "))
#rok1 = int (input ("Zadaj rok 1: "))

#mes2 = str (input ("Zadaj mesiac 2: "))
#rok2 = int (input ("Zadaj rok 2: "))

def pocet_dni (mes1, rok1, mes2, rok2) :

    if mes1 == "jan":
        mes1= 1
    if mes2 == "jan":
        mes2=1
    if mes1 == "feb":
        mes1= 2
    if mes2 == "feb":
        mes2= 2
    if mes1 == "mar":
        mes1= 3
    if mes2 == "mar":
        mes2= 3
    if mes1 == "apr":
        mes1= 4
    if mes2 == "apr":
        mes2= 4
    if mes1 == "maj":
        mes1= 5
    if mes2 == "maj":
        mes2= 5
    if mes1 == "jun":
        mes1= 6
    if mes2 == "jun":
        mes2= 6
    if mes1 == "jul":
        mes1= 7
    if mes2 == "jul":
        mes2= 7
    if mes1 == "aug":
        mes1= 8
    if mes2 == "aug":
        mes2= 8
    if mes1 == "sep":
        mes1= 9
    if mes2 == "sep":
        mes2= 9
    if mes1 == "okt":
        mes1= 10
    if mes2 == "okt":
        mes2= 10
    if mes1 == "nov":
        mes1= 11
    if mes2 == "nov":
        mes2= 11
    if mes1 == "dec":
        mes1= 12
    if mes2 == "dec":
        mes2= 12

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
            #print ("pripocitavam mesiac ", datum1 // 10000, "s poctom dni ", dni_v_mesiaci, "datum ", datum1, "a priebezne mam ", dni_spolu)

            datum1 += 1 * 10000
            if datum1 == datum2 :
                break

        if datum1 == datum2 :
                break
        datum1 -= 120000
        datum1 += 1
        #print (datum1)

    return (dni_spolu)