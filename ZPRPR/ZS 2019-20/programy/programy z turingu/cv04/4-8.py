vstup = int (input ("vstup "))

sucet = 0
priemer = 0
vstup2 = float (input ("cislo "))
priemer += vstup2
sucet += vstup2

i = 0

while i < vstup - 1 :
    vstup2 = float (input ("cislo "))
    print (vstup2)

    if vstup2 > priemer :
        sucet += vstup2

    priemer += vstup2
    priemer = priemer / (i + 1)

    i += 1

print (sucet)