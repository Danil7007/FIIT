meno_suboru = "subor1.txt"

with open(meno_suboru) as f:
    pole = f.readlines()
    
#pole = ['Ján Botto:\n', '  Žltá ľalija\n', '\n', '\n', 'Stojí, stojí mohyla.\n']
pole2 = []
pole3 = []

for obsah in pole :
    obsah = obsah.replace("\n", "")
    obsah = obsah.replace("  ", " ")
    if obsah != "" :
        pole2.append (obsah)
        #print(obsah)
    if obsah != "" :
        for znak in obsah :
            pole3.append (znak)
    if obsah == "" :
        pole3.append("¤")

#print(pole2)
#print(pole3)

posledny = len(pole3) -1

pole4 = []
index = 0
try:
    while index <= posledny :
        #print (pole3[index])
        pole4.append(pole3[index])
        if (ord(pole3[index])) != 32 and (64 < (ord(pole3[index + 1])) <91) :
            #print("\n",end="")
            pole4.append(" ")
        elif ((pole3[index]) == "." or (pole3[index]) == "," or (pole3[index]) == "—") and (96 < (ord(pole3[index + 1])) <123) :
            pole4.append(" ")
        index += 1
except IndexError :
   pass


for znak in pole4 :
    if znak != ("¤"):
        print (znak,end="")

print("\n")

index = 0
odsek = 0
pole5=[]
try:
    while index <= posledny :
        if (pole3[index]) != ("¤") :
            pole5.append(pole3[index])
        if (pole3[index]) == ("¤") and (64 < (ord(pole3[index + 1])) <91) :
            odsek += 1
            cislovanie = "ODSEK", odsek
            pole5.append(cislovanie)
        if ((pole3[index]) == "." or (pole3[index]) == "," or (pole3[index]) == "—") and (96 < (ord(pole3[index + 1])) <123) :
            pole5.append(" ")
        if ((96 < (ord(pole3[index - 1])) <123) and (pole3[index]) == " ") and (96 < (ord(pole3[index + 1])) <123) :
            pole5.append(" ")
        index += 1
except IndexError :
    pass

for znak in pole5 :
    print (znak,end="")


