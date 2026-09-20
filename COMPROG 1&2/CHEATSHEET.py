# PYTHON FINAL REVIEWER CHEAT SHEET
# Records (Grades) + OOP + JSON + Recursion

import os, json, random

# =========================
# NON-OOP RECORD SYSTEM
# =========================

records = []

def addRec(name, age, g1, g2, g3):
    ave = (g1 + g2 + g3) / 3
    rec = {"name": name, "age": age, "g1": g1, "g2": g2, "g3": g3, "average": ave}
    records.append(rec)
    records.sort(key=lambda x: x["average"], reverse=True)

def updateRec(name, age, g1, g2, g3):
    for rec in records:
        if rec["name"] == name:
            rec["age"], rec["g1"], rec["g2"], rec["g3"] = age, g1, g2, g3
            rec["average"] = (g1 + g2 + g3) / 3
            records.sort(key=lambda x: x["average"], reverse=True)
            return
    print("Record not found.")

def delRec(name):
    for rec in records:
        if rec["name"] == name:
            records.remove(rec)
            return
    print("Record not found.")

def display():
    print("Name", "Age", "G1", "G2", "G3", "Average", "Status")
    for rec in records:
        status = "Passed" if rec["average"] >= 75 else "Failed"
        print(rec["name"], rec["age"], rec["g1"], rec["g2"], rec["g3"], rec["average"], status)

def save_records():
    with open("records.json", "w") as file:
        json.dump(records, file, indent=4)

def load_records():
    global records
    if os.path.exists("records.json"):
        try:
            with open("records.json", "r") as file:
                records = json.load(file)
        except json.JSONDecodeError:
            records = []
    else:
        records = []


# =========================
# OOP RECORD SYSTEM
# =========================

class Person:
    def __init__(self):
        self.records = []

    def addRec(self, name, age, g1, g2, g3):
        ave = (g1 + g2 + g3) / 3
        rec = {"name": name, "age": age, "g1": g1
               , "g2": g2, "g3": g3, "average": ave}
        self.records.append(rec)
        self.records.sort(key=lambda rec: 
            rec[""], reverse=True)
        

    def updateRec(self, name, age, g1, g2, g3):
        for rec in self.records:
            if rec["name"] == name:
                rec["age"], rec["g1"], rec["g2"], rec["g3"] = age, g1, g2, g3
                rec["average"] = (g1 + g2 + g3) / 3
                self.records.sort(key=lambda rec: rec["average"], 
                                  reverse=True)
                return
        print("Record not found.")

    def delRec(self, name):
        if not self.records:
            print("No records to delete.")
            return

        for rec in self.records:
            if rec["name"] == name:
                self.records.remove(rec)
                return

        print("Record not found.")

    def display(self):
        print("Name", "Age", "G1", "G2", "G3", "Average", "Status")
        for rec in self.records:
            status = "Passed" if rec["average"] >= 75 else "Failed"
            print(rec["name"], rec["age"], rec["g1"], rec["g2"], rec["g3"]
                  , rec["average"], status)

    def save_records(self):
        with open("records.json", "w") as file:
            json.dump(self.records, file, indent=4)

    def load_records(self):
        if os.path.exists("records.json"):
            try:
                with open("records.json", "r") as file:
                    self.records = json.load(file)
            except json.JSONDecodeError:
                self.records = []
        else:
            self.records = []


class Student(Person):
    pass


# SAMPLE USE, NO INPUT
s1 = Student()
s1.addRec("Mel Chor", 18, 85, 90, 88)
s1.addRec("Gas Chor", 19, 70, 75, 72)
s1.addRec("Mel Par", 20, 95, 92, 98)
s1.updateRec("Mel Chor", 18, 90, 92, 91)
s1.delRec("Gas Chor")
s1.display()


# =========================
# MENU PATTERN
# =========================

def menu():
    print("1 Add")
    print("2 Update")
    print("3 Delete")
    print("4 Display")
    print("5 Exit")
    return int(input("Select choice: "))

def start():
    s = Student()
    s.load_records()

    while True:
        choice = menu()

        match choice:
            case 1:
                n = input("Name: ")
                a = int(input("Age: "))
                g1 = float(input("Grade 1: "))
                g2 = float(input("Grade 2: "))
                g3 = float(input("Grade 3: "))
                s.addRec(n, a, g1, g2, g3)
            case 2:
                n = input("Name to update: ")
                a = int(input("New Age: "))
                g1 = float(input("New Grade 1: "))
                g2 = float(input("New Grade 2: "))
                g3 = float(input("New Grade 3: "))
                s.updateRec(n, a, g1, g2, g3)
            case 3:
                n = input("Name to delete: ")
                s.delRec(n)
            case 4:
                s.display()
            case 5:
                s.save_records()
                break
            case _:
                print("Invalid choice.")


# =========================
# MAIN GUARD
# =========================

if __name__ == "__main__":
    start()

# =========================
# MENU PATTERN
# =========================

def merge(l1, l2) :
    merged = list(set(l1+l2))
    merged.sort(reverse=False)
    return merged

# =========================
# RECURSION FUNCTIONS
# =========================

def factorial(n):
    if n == 0 or n == 1:
        return 1
    return n * factorial(n - 1)

def printn(n): #print numbers from 1 to n
    if n <= 0:
        return
    printn(n - 1)
    print(n)

def sumA(arr, i=0):
    if i == len(arr):
        return 0
    return arr[i] + sumA(arr, i + 1)

def largest_element(arr, i=0):
    if i == len(arr) - 1:
        return arr[i]
    rest = largest_element(arr, i + 1)
    return arr[i] if arr[i] > rest else rest

def countdigits(n):
    n = abs(n)
    if n < 10:
        return 1
    return 1 + countdigits(n // 10)

def sumofdigits(n):
    n = abs(n)
    if n < 10:
        return n
    return n % 10 + sumofdigits(n // 10)

def isSorted(arr, i=0):
    if i >= len(arr) - 1:
        return True
    if arr[i] > arr[i + 1]:
        return False
    return isSorted(arr, i + 1)

def isPalindromenum(n):
    s = str(abs(n))

    def check(s, left, right):
        if left >= right:
            return True
        if s[left] != s[right]:
            return False
        return check(s, left + 1, right - 1)

    return check(s, 0, len(s) - 1)

def isPalindromearr(arr, left=0, right=None):
    if right is None:
        right = len(arr) - 1
    if left >= right:
        return True
    if arr[left] != arr[right]:
        return False
    return isPalindromearr(arr, left + 1, right - 1)

def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

def isPrime(n, divisor=2):
    if n < 2:
        return False
    if divisor * divisor > n:
        return True
    if n % divisor == 0:
        return False
    return isPrime(n, divisor + 1)


# =========================
# ARITHMETIC PRACTICE
# =========================

records2 = []

def add():
    x, y = 10, 5
    ans = 15
    result = x + y
    status = "Correct" if ans == result else "Wrong"
    records2.append(["Addition", x, y, result, ans, status])

def minus():
    x, y = 10, 5
    ans = 5
    result = x - y
    status = "Correct" if ans == result else "Wrong"
    records2.append(["Subtraction", x, y, result, ans, status])

def mul():
    x, y = 10, 5
    ans = 50
    result = x * y
    status = "Correct" if ans == result else "Wrong"
    records2.append(["Multiplication", x, y, result, ans, status])

def div():
    x, y = 10, 5
    ans = 2
    result = x // y
    status = "Correct" if ans == result else "Wrong"
    records2.append(["Division", x, y, result, ans, status])

def show():
    for r in records2:
        print(r[0], r[1], r[2], r[3], r[4], r[5])
