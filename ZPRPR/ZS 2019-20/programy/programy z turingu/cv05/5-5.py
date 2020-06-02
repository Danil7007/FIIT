vstup = int (input (" "))

riadok = 1

a = 0
b = 1
# c = vstup - a - b - d - e - f - g
d = 1
# e = vstup - a - b - d - e - f - g
f = 1
g = 0

c = ((vstup - (a + b + d + f + g)) // 2)
e = ((vstup - (a + b + d + f + g)) // 2)

while riadok <= vstup // 2 :
    for i in range (0, a) :
        print ("-", end="")
    for j in range (0, b) :
        print ("*", end="")
    for k in range (0, c) :
        print ("-", end="")
    for l in range (0, d) :
        print ("*", end="")
    for m in range (0, e) :
        print ("-", end="")
    for n in range (0, f) :
        print ("*", end="")
    for o in range (0, g) :
        print ("-", end="")

    print ()
    a += 1
    g += 1
    c = ((vstup - (a + b + d + f + g)) // 2)
    e = ((vstup - (a + b + d + f + g)) // 2)

    riadok += 1

for p in range (0, vstup) :
    print ("*", end="")

print()

riadok = 1
a -= 1
g -= 1
c = ((vstup - (a + b + d + f + g)) // 2)
e = ((vstup - (a + b + d + f + g)) // 2)
while riadok <= vstup // 2 :
    for i in range (0, a) :
        print ("-", end="")
    for j in range (0, b) :
        print ("*", end="")
    for k in range (0, c) :
        print ("-", end="")
    for l in range (0, d) :
        print ("*", end="")
    for m in range (0, e) :
        print ("-", end="")
    for n in range (0, f) :
        print ("*", end="")
    for o in range (0, g) :
        print ("-", end="")

    print ()
    a -= 1
    g -= 1
    c = ((vstup - (a + b + d + f + g)) // 2)
    e = ((vstup - (a + b + d + f + g)) // 2)

    riadok += 1