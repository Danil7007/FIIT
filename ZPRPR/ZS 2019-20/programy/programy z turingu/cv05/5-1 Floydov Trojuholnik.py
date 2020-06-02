vstup = int (input(""))
if vstup == 'x':
    exit();
else:
    rang = 6
    for i in range(1, rang+1):
        for j in range(1, i+1):
            print(vstup, end=" ")
            vstup += 1
        print()