mes1 = int (input ("Zadaj mesiac 1: "))
rok1 = int (input ("Zadaj rok 1: "))

mes2 = int (input ("Zadaj mesiac 2: "))
rok2 = int (input ("Zadaj rok 2: "))

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
        print ("pripocitavam mesiac ", datum1 // 10000, "s poctom dni ", dni_v_mesiaci, "datum ", datum1, "a priebezne mam ", dni_spolu)

        datum1 += 1 * 10000
        if datum1 == datum2 :
            break

    if datum1 == datum2 :
            break
    datum1 -= 120000
    datum1 += 1
    print (datum1)
