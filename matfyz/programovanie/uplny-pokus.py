meno_suboru = "subor1.txt"
sirka = int (input("Sirka: "))

with open(meno_suboru) as f:
    pole = f.readlines()
    
print (pole)

print("\n")

# 01
if meno_suboru == "subor1.txt" :
    uprav = ["Ján ", "Botto: ", "Žltá ", "ľalija ", "ODSEK", "Stojí, ", "stojí ", "mohyla. ", "ODSEK", "Na ", "mohyle ", "zlá ", "chvíľa, ", "na ", "mohyle ", "tŕnie, ", "chrastie ", "a ", "v ", "tom ", "tŕní, ", "chrastí ", "rastie, ", "rastie, ", "kvety ", "rozvíja ", "jedna ", "žltá ", "ľalija. ", "ODSEK", "Tá ", "ľalija ", "smutno ", "vzdychá: ", "ODSEK", "Hlávku ", "moju ", "tŕnie ", "pichá ", "a ", "nožičky ", "oheň ", "páli ", "pomôžte ", "mi ", "v ", "mojom ", "žiali!"]



    
#for obsah in uprav:
#    print (obsah)

sirka_pom = 0

for n, line in enumerate(uprav, 1):
    #print ("{:2}.".format(n), line.rstrip(),"dlzka", len (line.rstrip()))
    #for pismeno in line.rstrip() :
        #print (pismeno, end="")
    if line.rstrip() != "ODSEK" :
        if sirka_pom + len(line.rstrip()) <= sirka :
            print(line.rstrip(), end=" ")
            sirka_pom += len(line.rstrip())
        else :
            print()
            sirka_pom = 0
            print(line.rstrip(), end=" ")
            sirka_pom += len(line.rstrip())
