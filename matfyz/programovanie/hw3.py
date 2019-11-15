from typing import List, Optional, Tuple
from random import randint


PlayGround = List[List[str]]
ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def new_playground(height: int, width: int) -> PlayGround:
    retplay = []
    cache = []
    for i in range(height):
        for j in range(width):
            cache.append(" ")
        retplay.append(cache)
        cache = []
    return retplay


def get(playground: PlayGround, row: int, col: int) -> str:
    if playground[row][col] == "*":
        return " "
    return playground[row][col]


def getsize(playground: PlayGround) -> Tuple[int, int]:
    return len(playground), len(playground[0])


def put(playground: PlayGround, row: int, col: int, symbol: str) -> bool:
    i = 0
    j = 0
    rows, cols = getsize(playground)
    spot = playground[row+i][col+j]
    if spot == "X" or spot == "O" or spot == "*":
        return False

    for i in range(-1, 2):
        for j in range(-1, 2):
            if row + i < rows and col + j < cols:
                if spot == " ":
                    playground[abs(row+i)][abs(col+j)] = "*"
    playground[row][col] = symbol
    return True


def header(cols: int) -> None:
    print(" "*3, end="")
    for i in range(cols):
        if i >= 10:
            print("  ", i, sep="", end="")
        else:
            print("  ", i, " ", sep="", end="")
    print()


def sepr_line(cols: int) -> None:
    print(" " * 3, end="")
    for _ in range(cols):
        print("+", "---", sep="", end="")
    print("+")


def game_line(playground: PlayGround, row: int, col: int) -> None:
    print(" ", ALPHABET[row], " |", sep="", end="")
    for i in range(col):
        print(" ", playground[row][i], " |", sep="", end="")
    print()


def draw(playground: PlayGround) -> None:
    rows, cols = getsize(playground)
    header(cols)
    for row in range(rows):
        sepr_line(cols)
        game_line(playground, row, cols)
    sepr_line(cols)


def game_over(playground: PlayGround) -> bool:
    rows, cols = getsize(playground)
    for i in range(rows):
        for j in range(cols):
            if playground[i][j] == " ":
                return False
    return True


def deepcopy(mylist: PlayGround) -> PlayGround:
    retlist = []
    cache = []
    for i in range(len(mylist)):
        for j in range(len(mylist[0])):
            cache.append(mylist[i][j])
        retlist.append(cache)
        cache = []
    return retlist


def hint(playground: PlayGround, symbol: str = "X")\
        -> Optional[Tuple[int, int]]:
    whitespaces = []
    play_copy = deepcopy(playground)
    rows, cols = getsize(playground)
    for i in range(rows):
        for j in range(cols):
            if playground[i][j] == " ":
                whitespaces.append((i, j))
    if len(whitespaces) > 9:
        return None

    for t in whitespaces:
        row, col = t
        put(play_copy, row, col, symbol)
        if game_over(play_copy):
            return t
        play_copy = deepcopy(playground)
    return None


def validinput_num(promt: str) -> int:
    finished = False
    while not finished:
        userstring = input(promt+": ")
        if userstring.isdigit():
            finished = True
        else:
            print("Not valid whole number.")

    ret = int(userstring)
    return ret


def validinput_put(playground: PlayGround) -> Tuple[int, int]:
    rows, cols = getsize(playground)
    play_copy = deepcopy(playground)
    letter_rows = set()
    for i in range(rows):
        letter_rows.add(ALPHABET[i])

    big_finish = False
    while not big_finish:
        finished = False
        while not finished:
            userstring = input("Row: ")
            if userstring in letter_rows:
                finished = True
            else:
                print("Not valid uppercase row letter.")
        row_num = ord(userstring.upper()) - ord("A")

        finished = False
        while not finished:
            usernum = validinput_num("Collumn")
            if 0 <= usernum <= cols:
                finished = True
            else:
                print("Not valid collumn number.")

        if put(play_copy, row_num, usernum, "X"):
            big_finish = True
        else:
            print("You cant play on obstructed places!")

    return row_num, usernum


def validinput_sym(promt: str) -> str:
    finished = False
    while not finished:
        userstring = input(promt+": ")
        if userstring.upper() == "X" or "O":
            finished = True
        else:
            print("Thats not valid symbol. Valid ones are X or O")
    return userstring.upper()


def cls() -> None:
    print("\n" * 30)


def symbolreverse(symbol: str) -> str:
    if symbol == "X":
        return "O"
    else:
        return "X"


def ai_play(playground: PlayGround, symbol: str) -> None:
    rows, cols = getsize(playground)
    finished = False

    while not finished:
        if put(playground, randint(0, rows - 1), randint(0, cols - 1),  # "AI"
               symbolreverse(symbol)):
            finished = True


def player_play(playground: PlayGround, symbol: str) -> None:
    row, col = validinput_put(playground)
    put(playground, row, col, symbol)


def draw_hint(playground: PlayGround) -> None:
    the_hint = hint(playground)
    if the_hint is not None:
        row, col = the_hint
        print("Pssst. Try playing {} {}"
              .format(ALPHABET[row], col))


def draw_game_info(playground: PlayGround, cur_round: int,
                   player: str, symbol: str, first_lap: bool = False) -> bool:
    cls()
    print("Round {}".format(cur_round))
    if first_lap:
        print("Player {} starts this round as X!".format(player))
    else:
        print("Player {} playing as {}!".format(player, symbol))

    draw(playground)
    draw_hint(playground)
    return False


def game(height: int, width: int) -> None:
    print("Wellcome to game Obstruction!",
          "In this multiplayer game you take turns\
 and try to defeat your oponent.",
          sep="\n")

    rounds = validinput_num("How many rounds you want to play?")
    player1 = input("Player 1 name: ")
    player2 = input("Player 2 name: ")
    players: List[Tuple[str, int]] = [(player1, 0), (player2, 0)]

    for cur_round in range(1, rounds + 1):
        playground = new_playground(height, width)
        finished = False
        first_lap = True
        zero_or_one = cur_round % 2
        while not finished:
            first_player = players[zero_or_one][0]
            second_player = players[abs(zero_or_one - 1)][0]

            first_lap = draw_game_info(playground, cur_round,  # first player
                                       first_player, "X", first_lap)
            player_play(playground, "X")
            if game_over(playground):
                who_won = first_player
                finished = True
            else:
                first_lap = draw_game_info(playground, cur_round,
                                           second_player, "O")  # second player
                player_play(playground, "O")  # second player
                if game_over(playground):
                    who_won = second_player
                    finished = True

        if who_won == players[zero_or_one][0]:
            index = zero_or_one
        else:
            index = abs(zero_or_one - 1)

        players[index] = (players[index][0], players[index][1] + 1)

        cls()
        print("End of round {} out of {}".format(cur_round, rounds),
              "Player {} won!".format(who_won),
              sep="\n")
        draw(playground)
        input("\n\nPress enter")                            # pasue

        if (players[zero_or_one][1] == players[abs(zero_or_one - 1)][1]) and\
                cur_round == rounds:
            cls()
            print("It's a tie!",
                  "Thanks for playing!",
                  sep="\n")

        elif players[zero_or_one][1] > rounds // 2:
            print("Player {} won the match!".format(players[zero_or_one][0]),
                  "Thanks for playing!",
                  sep="\n")
            cur_round = rounds + 1

        elif players[abs(zero_or_one - 1)][1] > rounds // 2:
            cls()
            print("Player {} won the match!\n\
Thanks for playing!".format(players[abs(zero_or_one - 1)][0]))
            cur_round = rounds + 1
