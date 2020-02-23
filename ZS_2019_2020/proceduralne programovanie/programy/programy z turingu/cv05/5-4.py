vstup = int (input (" "))

pocet_a = 1
pocet_b = vstup - pocet_a

for i in range (0, vstup) :

    for j in range (0, pocet_a) :
        print ("*", end="")

    for k in range (0, pocet_b) :
        print (" ", end="")

    pocet_a += 1
    pocet_b = vstup - pocet_a

    print ()

pocet_b = 1
pocet_a = vstup - pocet_b
for l in range (0, vstup - 1) :

    for m in range (0, pocet_a) :
        print ("*", end="")

    for n in range (0, pocet_b) :
        print (" ", end="")

    pocet_b += 1
    pocet_a = vstup - pocet_b

    print ()