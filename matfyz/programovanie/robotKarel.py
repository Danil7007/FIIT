class RobotKarel:
    def __init__(self, meno_suboru):
        self.tab = []
        pomocny = []
        self.r = [-1, -1, -1]
        self.ruksak = []
        with open(meno_suboru, 'r') as subor:
            for riadok in subor:
                riadok = riadok.split()
                if len(riadok) == 2:
                    for a in range(int(riadok[0])):
                        for b in range(int(riadok[1])):
                            pomocny.append([])
                        self.tab.append(pomocny)
                        pomocny = []
                else:
                    self.tab[int(riadok[1])][int(riadok[2])] += list(riadok[0])
    def __str__(self):
        vysl = ''
        for i,riadok in enumerate(self.tab):
            for j,prvok in enumerate(riadok):
                if (i,j) == (self.r[0], self.r[1]):
                    if self.r[2] == 0:
                        vysl+= '>'
                    elif self.r[2] == 1:
                        vysl+='v'
                    elif self.r[2] == 2:
                        vysl+='<'
                    elif self.r[2] == 3:
                        vysl+='^'
                elif prvok == []:
                    vysl+='.'
                else:
                    vysl+= prvok[-1]
            vysl += '\n'
        return vysl[:-1]
    def robot(self, riadok, stlpec, smer):
        self.r = [int(riadok), int(stlpec), int(smer)]
    def rob(self, prikaz):
        pocet = 0
        prikazy = prikaz.split()
        prikaz = None
        ulohy = []
        for n, prvok in enumerate(prikazy):
            try:
                for i in range(int(prvok)-1):
                    ulohy.append(prikazy[n+1])
            except:
                ulohy.append(prvok)
        for prikaz in ulohy:
            if prikaz == 'vlavo':
                self.r[2] -= 1
                if self.r[2] < 0:
                    self.r[2] = 3
                pocet += 1
            elif prikaz == 'vpravo':
                self.r[2] += 1
                if self.r[2] > 3:
                    self.r[2] = 0
                pocet+=1
            elif prikaz == 'krok':
                if self.r[2] == 0:
                    if self.r[1] + 1 < len(self.tab[0]):
                        self.r[1] += 1
                        pocet+=1
                elif self.r[2] == 1:
                    if self.r[0] + 1 < len(self.tab):
                        self.r[0] += 1
                        pocet+=1
                elif self.r[2] == 2:
                    if self.r[1] - 1 >= 0:
                        self.r[1] -= 1
                        pocet += 1
                elif self.r[2] == 3:
                    if self.r[0] - 1 >= 0:
                        self.r[0] -= 1
                        pocet += 1
            elif prikaz == 'zdvihni':
                if self.tab[self.r[0]][self.r[1]] != []:
                    self.ruksak.append(self.tab[self.r[0]][self.r[1]].pop())
                    pocet += 1
            elif prikaz == 'poloz':
                if self.batoh() != []:
                    self.tab[self.r[0]][self.r[1]].append(self.ruksak.pop())
                    pocet += 1
        return pocet
    def batoh(self):
        return self.ruksak

if __name__ == '__main__':
    k = RobotKarel('subor1.txt')
    k.robot(0, 0, 0)
    print(k)
    print(k.rob('krok'))
    print(k.rob('2 zdvihni'))
    k.rob('krok')
    k.rob('vpravo')
    k.rob('krok')
    k.rob('2 zdvihni')
    k.rob('2 krok')
    print(k)
    print('batoh =', k.batoh())
    k.rob('poloz vlavo')
    k.rob('krok 6 vlavo')
    print(k)
    print('batoh =', k.batoh())