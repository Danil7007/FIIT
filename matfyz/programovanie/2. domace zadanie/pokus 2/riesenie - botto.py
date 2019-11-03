tab = []
def ano(meno_suboru):
    r = " "
    t = open(meno_suboru, 'r')
    for riadok in t :
        for slovo in riadok.split():
            word = (slovo, 0)
            for index in range (len(tab)):
                if tab[index][0]==slovo:
                    word = tab.pop(index)
                    break

            tab.append((word[0], word[1] + 1 ))
            return [tab]