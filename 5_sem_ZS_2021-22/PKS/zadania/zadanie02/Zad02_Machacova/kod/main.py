import server
import klient


class farby:
    B = '\u001b[34m'
    M = '\u001b[35m'
    Y = '\u001b[33m'
    C = '\u001b[36m'
    ENDC = '\u001b[0m'


def main():
    while True:

        print(farby.Y + "\n----------------- MENU -----------------"
              "\n-> pre funkciu KLIENT stlac ........ (a)"
              "\n-> pre funkciu SERVER stlac ........ (b)"
              "\n-> pre ukoncenie programu stlac .... (x)"
              "\n----------------------------------------"
              "\n... ", end='')

        swtch = input()

        if swtch == "a":
            print("\nSPUSTAM VERZIU KLIENT" + farby.ENDC)
            klient.klient()
            break

        elif swtch == "b":
            print("\nSPUSTAM VERZIU SERVER\n" + farby.ENDC)
            server.server()
            break

        elif swtch == "x":
            return

        else:
            print(farby.R + "-> Neplatny prikaz." + farby.ENDC)


if __name__ == '__main__':
    main()
