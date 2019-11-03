def zarovnavacka(odsek, sirka, zarovnat) :
    pocitadlo = 0
    vysledok = ""
    pocet_medzier = 0
    poloha = 0
    slova = 0
    line = ""
    c = 0
    odsek = odsek.replace("  "," ")

    if len(odsek) <= sirka :
        print (odsek, end="")

    else :
        while len(odsek) > sirka :
            line += odsek[c]
            c += 1
            if (line.find(" ") == -1) and (odsek.find(" ") != -1):
                pass
            else:
                if len(line) > sirka :
                    if (line[-1] == " " ):
                        line = line[:-1]
                        line = line.strip()
                        print (line)
                        odsek = odsek[len(line):]
                        odsek = odsek.strip(" ")
                        line = ""
                        c = 0
                    else :
                        line = line.strip()
                        if line.count(" ") == 0 :
                            odsek = odsek[len(line):]
                        else:
                            while line[-1] != " ":
                                line = line[:-1]
                            line = line.strip()
                            odsek = odsek[len(line):]
                            slova = line.count(" ")
                            pocet_medzier = sirka - len(line)
                            if slova == 0:
                                modulo = 0
                                pridat = 0
                            else:
                                modulo = pocet_medzier % slova
                                pridat = pocet_medzier // slova

                            if zarovnat == True:

                                while pocet_medzier != 0 :

                                    if slova != 0 :
                                        poloha = line.find(" ")
                                    else:
                                        pocet_medzier -= pocet_medzier

                                        break
                                    if pocitadlo < (modulo):
                                        vysledok += (line[:poloha+1]+ (pridat + 1)*" ")
                                        pocet_medzier -= (pridat +1)
                                    else:
                                        vysledok += (line[:poloha+1]+ (pridat)*" ")
                                        pocet_medzier -= (pridat)
                                    line = line[poloha + 1:]
                                    pocitadlo += 1

                        vysledok += line
                        print(vysledok, end= "")
                        vysledok =""
                        #
                        if (odsek != "") and (odsek.count(" ") == 0) :
                            print(odsek, end="")
                            odsek = ""
                        odsek = odsek.strip(" ")
                        if odsek == "":
                            pass
                        else:
                            print ()
                        line=""
                        c = 0
                        pocitadlo = 0

            odsek = odsek.strip()

            print (odsek, end="")


def vypis(meno_suboru, sirka, zarovnat=True, odsek=-1):
    with open(meno_suboru, "r",encoding='utf-8') as subor:
        paragraf = odsek
        pocitacka = -1
        odsek = ""
        for riadok in subor :
            riadok = riadok.replace("  ", " ")
            riadok = riadok.replace("  ", " ")
            riadok = riadok.strip(" ")
            odsek += riadok

            if odsek == "\n" :
                odsek = ""
            elif (riadok == "\n") :
                if paragraf == -1:
                    odsek = odsek[:-2]
                    odsek = odsek.replace("\n", " ")
                    zarovnavacka(odsek, sirka, zarovnat)
                    print ("\n")
                    odsek =""
                else:
                    pocitacka += 1
                    if pocitacka == paragraf:
                        break
                    odsek = ""
        odsek = odsek[:-1]
        odsek = odsek.replace("\n", " ")

        zarovnavacka(odsek, sirka, zarovnat)



