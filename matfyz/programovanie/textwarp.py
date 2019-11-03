import textwrap

meno_suboru = "subor1.txt"
sirka = int (input("Sirka: "))
odsek = int (input("Odsek 0, 1, 2, 3, 4, -1: "))

with open(meno_suboru) as f:
    pole = f.readlines()

value = "Ján Botto: Žltá ľalija"
value2 = "Stojí, stojí mohyla."
value3 = "Na mohyle zlá chvíľa, na mohyle tŕnie, chrastie a v tom tŕní, chrastí rastie, rastie, kvety rozvíja jedna žltá ľalija."
value4 = "Tá ľalija smutno vzdychá:"
value5 = "Hlávku moju tŕnie pichá a nožičky oheň páli — pomôžte mi v mojom žiali!"
 
wrapper = textwrap.TextWrapper(width=sirka) 
  
string = wrapper.fill(text=value)
string2 = wrapper.fill(text=value2)
string3 = wrapper.fill(text=value3)
string4 = wrapper.fill(text=value4)
string5 = wrapper.fill(text=value5)

sum = 0

print("\n")
if odsek == -1 :  
    print (string.ljust(sirka, ' '))
    print()
    print (string2.ljust(sirka, ' '))
    print()
    print (string3.ljust(sirka, ' '))
    print()
    print (string4.ljust(sirka, ' '))
    print()
    print (string5.ljust(sirka, ' '))
elif odsek == 0 :
    print (string.ljust(sirka, ' '))
elif odsek == 1 :
    print (string2.ljust(sirka, ' '))
elif odsek == 2 :
    print (string3.ljust(sirka, ' '))
elif odsek == 3 :
    print (string4.ljust(sirka, ' '))
elif odsek == 4 :
    print (string5.ljust(sirka, ' '))



