import os
import random
from dataclasses import dataclass, field
from enum import IntEnum
from typing import List

MAX = 50
PLAYERS_FILE = "players.txt"


class Operation(IntEnum):
    ADD = 0
    SUB = 1
    MUL = 2
    DIVI = 3


class Difficulty(IntEnum):
    EASY = 0
    MEDIUM = 1
    HARD = 2


@dataclass
class Player:
    user: str
    password: str
    score: List[float] = field(default_factory=lambda: [0.0, 0.0, 0.0, 0.0])


players: List[Player] = []
current_user = -1


def clear_screen() -> None:
    os.system("cls" if os.name == "nt" else "clear")


def pause() -> None:
    if os.name == "nt":
        os.system("pause")
    else:
        input("Press Enter to continue...")


def compute(op: Operation, x: int, y: int) -> int:
    if op == Operation.ADD:
        return x + y
    if op == Operation.SUB:
        if x < y:
            x, y = y, x
        return x - y
    if op == Operation.MUL:
        return x * y
    if op == Operation.DIVI:
        if y == 0:
            y = 1
        return x // y
    return 0


def generate(op: Operation, diff: Difficulty) -> tuple[int, int]:
    if diff == Difficulty.EASY:
        limit = 10
    elif diff == Difficulty.MEDIUM:
        limit = 100
    else:
        limit = 1000

    if op == Operation.DIVI:
        y = random.randint(1, limit)
        k = random.randint(1, limit)
        x = y * k
    else:
        x = random.randint(1, limit)
        y = random.randint(1, limit)

    if op == Operation.SUB and x < y:
        x, y = y, x

    return x, y


def get_score_value(player: Player, mode: int) -> float:
    if mode == -1:
        return sum(player.score) / 4.0
    return player.score[mode]


def leaderboard(mode: int) -> None:
    idx = list(range(len(players)))
    for i in range(1, len(idx)):
        key = idx[i]
        key_val = get_score_value(players[key], mode)
        j = i - 1
        while j >= 0 and get_score_value(players[idx[j]], mode) < key_val:
            idx[j + 1] = idx[j]
            j -= 1
        idx[j + 1] = key

    print("\n===================Leaderboard===================")
    if mode == -1:
        print("TOP 10 - OVERALL")
    elif mode == Operation.ADD:
        print("TOP 10 - ADDITION")
    elif mode == Operation.SUB:
        print("TOP 10 - SUBTRACTION")
    elif mode == Operation.MUL:
        print("TOP 10 - MULTIPLICATION")
    elif mode == Operation.DIVI:
        print("TOP 10 - DIVISION")

    for i, p_idx in enumerate(idx[:10], start=1):
        p = players[p_idx]
        print(f"{i}.) {p.user:<10} | {get_score_value(p, mode):.2f}%")


def play_game(op: Operation, diff: Difficulty) -> None:
    global current_user

    correct = 0
    symbols = {
        Operation.ADD: "+",
        Operation.SUB: "-",
        Operation.MUL: "*",
        Operation.DIVI: "/",
    }

    for i in range(5):
        x, y = generate(op, diff)
        print(f"Question {i + 1}")

        try:
            ans = int(input(f"{x} {symbols[op]} {y} = ").strip())
        except ValueError:
            ans = None

        correct_ans = compute(op, x, y)
        if ans == correct_ans:
            print("Correct!")
            correct += 1
        else:
            print(f"Wrong! The correct answer is {correct_ans}")

    score = (correct / 5) * 100
    if current_user != -1:
        players[current_user].score[op] = score

    print("\n--- GAME RESULT ---")
    print(f"Score: {score:.2f}%")

    print("\n--- OVERALL LEADERBOARD ---")
    leaderboard(-1)
    pause()


def locate_pos(username: str) -> int:
    for i, p in enumerate(players):
        if p.user == username:
            return i
    return -1


def create() -> None:
    clear_screen()
    if len(players) >= MAX:
        print("List is full")
        return

    username = input("Enter username: ").strip()
    if locate_pos(username) != -1:
        print("Username already exists")
        return

    password = input("Enter password: ").strip()
    players.append(Player(user=username, password=password))
    print("Account created successfully")


def login() -> None:
    global current_user

    clear_screen()
    username = input("\nEnter username: ").strip()
    pos = locate_pos(username)

    if pos == -1:
        print("Username not found")
        return

    error_tries = 5
    while error_tries != 0:
        password = input("Enter password: ").strip()
        if players[pos].password == password:
            print("Login successful")
            current_user = pos
            menu()
            return

        error_tries -= 1
        if error_tries != 0:
            print("\nIncorrect Password")
        else:
            print("Too many attempts!")


def save_file() -> bool:
    try:
        with open(PLAYERS_FILE, "w", encoding="utf-8") as fp:
            for p in players:
                fp.write(
                    f"{p.user} {p.password} {p.score[Operation.ADD]:.2f} {p.score[Operation.SUB]:.2f} "
                    f"{p.score[Operation.MUL]:.2f} {p.score[Operation.DIVI]:.2f}\n"
                )
        return True
    except OSError:
        print("File Not Found")
        return False


def load_file() -> bool:
    players.clear()
    try:
        with open(PLAYERS_FILE, "r", encoding="utf-8") as fp:
            for line in fp:
                parts = line.strip().split()
                if len(parts) == 6 and len(players) < MAX:
                    user, password, a, s, m, d = parts
                    players.append(Player(user=user, password=password, score=[float(a), float(s), float(m), float(d)]))
        return True
    except OSError:
        print("File Not Found")
        return False


def menu() -> None:
    while True:
        clear_screen()
        print("\nSELECT:")
        print("1. Play Game\n2. Leaderboard\n3. Exit")

        try:
            choice = int(input("Enter choice: ").strip())
        except ValueError:
            choice = 0

        if choice == 1:
            print("\nChoose Operation:")
            print("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division")
            try:
                op_choice = int(input("Enter choice: ").strip())
            except ValueError:
                op_choice = 0

            if op_choice < 1 or op_choice > 4:
                print("Invalid choice")
                return

            print("\nChoose Difficulty:")
            print("1. Easy\n2. Medium\n3. Hard")
            try:
                diff_choice = int(input("Enter choice: ").strip())
            except ValueError:
                diff_choice = 0

            if diff_choice < 1 or diff_choice > 3:
                print("Invalid choice")
                return

            play_game(Operation(op_choice - 1), Difficulty(diff_choice - 1))
            save_file()

        elif choice == 2:
            print("\nLeaderboard Type:")
            print("1. Overall\n2. Addition\n3. Subtraction\n4. Multiplication\n5. Division")
            try:
                type_choice = int(input("Enter choice: ").strip())
            except ValueError:
                type_choice = 0

            if type_choice == 1:
                leaderboard(-1)
            elif 2 <= type_choice <= 5:
                leaderboard(type_choice - 2)
            else:
                print("Invalid choice")

            pause()

        elif choice == 3:
            return
        else:
            print("Invalid choice")
            pause()


def main() -> None:
    random.seed()
    clear_screen()
    load_file()

    while True:
        print("\n1. Register\n2. Login\n3. Exit")
        try:
            choice = int(input("Enter choice: ").strip())
        except ValueError:
            choice = 0

        if choice == 1:
            create()
            save_file()
        elif choice == 2:
            login()
        elif choice == 3:
            break
        else:
            print("Invalid choice")

    pause()


if __name__ == "__main__":
    main()
 