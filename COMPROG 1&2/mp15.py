import random
records = []

def add():
    x = random.randint(1,100)
    y = random.randint(1,100)
    print(f"{x} + {y} = ")
    ans = int(input("Enter Result: "))
    result = x + y
    
    status = "Correct" if ans == result else "Wrong"
    records.append(["Addition", x, y, result, ans, status])
    print(status)
    show()
    
def minus():
    x = random.randint(1,100)
    y = random.randint(1,100)
    print(f"{x} - {y} = ")
    ans = int(input("Enter Result: "))
    result = x - y
    status = "Correct" if ans == result else "Wrong"
    records.append(["Subtraction", x, y, result, ans, status])
    print(status)
    show()

def mul():
    x = random.randint(1,10)
    y = random.randint(1,10)
    print(f"{x} * {y} = ")
    ans = int(input("Enter Result: "))
    result = x * y
    status = "Correct" if ans == result else "Wrong"
    records.append(["Multiplication", x, y, result, ans, status])
    print(status)
    show()

def div():
    y = random.randint(1,10)
    result = random.randint(1,10)
    x = y * result
    print(f"{x} / {y} = ")
    ans = int(input("Enter Result: "))
    status = "Correct" if ans == result else "Wrong"
    records.append(["Division", x, y, result, ans, status])
    print(status)
    show()
    
def show():
    if records:
        print("\nArithmetic\tX\tY\tResult\tAnswer\tStatus")
        for r in records:
            print(f"{r[0]}\t{r[1]}\t{r[2]}\t{r[3]}\t{r[4]}\t{r[5]}")
    else:
        print("No records found.")

def menu():
    print("\nMENU")
    print("1. Addition")
    print("2. Subtraction")
    print("3. Multiplication")
    print("4. Division")
    print("5. Exit")
    return input("Enter choice: ")

def start():
    while True:
        choice = menu()
        if choice == '1':
            add()
        elif choice == '2':
            minus()
        elif choice == '3':
            mul()
        elif choice == '4':
            div()
        elif choice == '5':
            print("Bye")
            break
        else:
            print("Invalid choice")

if __name__ == "__main__":
    start()