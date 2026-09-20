import os
import json


class Person:
    def __init__(self):
        self.records = []  # list of dictionaries

    def addRec(self, name, grade1, grade2, grade3):
        average = (grade1 + grade2 + grade3) / 3

        rec = {
            "name": name,
            "grade1": grade1,
            "grade2": grade2,
            "grade3": grade3,
            "average": average
        }

        self.records.append(rec)
        print(f"Record of {name} successfully added.")

    def updateRec(self, name):
        for rec in self.records:
            if rec["name"] == name:
                print("Enter new grades:")

                rec["grade1"] = float(input("Input Grade 1: "))
                rec["grade2"] = float(input("Input Grade 2: "))
                rec["grade3"] = float(input("Input Grade 3: "))

                rec["average"] = (
                    rec["grade1"] + rec["grade2"] + rec["grade3"]
                ) / 3

                print(f"Record of {name} successfully updated.")
                return

        print(f"Record of {name} not found.")

    def delRec(self, name):
        if not self.records:
            print("No records to delete.")
            return

        for rec in self.records:
            if rec["name"] == name:
                self.records.remove(rec)
                print(f"Record of {name} successfully deleted.")
                return

        print(f"Record of {name} not found.")

    def display(self):
        if not self.records:
            print("No records to display.")
            return

        print("-" * 75)
        print("{:<15} {:<10} {:<10} {:<10} {:<10} {:<10}".format(
            "Name", "Grade1", "Grade2", "Grade3", "Average", "Remarks"
        ))
        print("-" * 75)

        for rec in self.records:
            remarks = "Passed" if rec["average"] >= 75 else "Failed"

            print("{:<15} {:<10} {:<10} {:<10} {:<10.2f} {:<10}".format(
                rec["name"],
                rec["grade1"],
                rec["grade2"],
                rec["grade3"],
                rec["average"],
                remarks
            ))

        print("-" * 75)

    def save_records(self):
        with open("records.json", "w") as file:
            json.dump(self.records, file, indent=4)

        print("Records saved successfully.")

    def load_records(self):
        if os.path.exists("records.json"):
            try:
                with open("records.json", "r") as file:
                    self.records = json.load(file)

                print("Records loaded successfully.")

            except json.JSONDecodeError:
                self.records = []
                print("File corrupted or empty. Starting fresh.")
        else:
            self.records = []


class Student(Person):
    pass


def start():
    s1 = Student()
    s1.load_records()

    def menu():
        print("\nMENU")
        print("1. Add Record")
        print("2. Update Record")
        print("3. Delete Record")
        print("4. Display")
        print("5. Exit")

        return int(input("Select (1-5): "))

    while True:
        match menu():
            case 1:
                name = input("Input name: ")
                grade1 = float(input("Input Grade 1: "))
                grade2 = float(input("Input Grade 2: "))
                grade3 = float(input("Input Grade 3: "))

                s1.addRec(name, grade1, grade2, grade3)

            case 2:
                name = input("Input name to update: ")
                s1.updateRec(name)

            case 3:
                name = input("Input name to delete: ")
                s1.delRec(name)

            case 4:
                s1.display()

            case 5:
                print("Saving and exiting the program...")
                s1.save_records()
                break

            case _:
                print("Invalid choice.")


if __name__ == "__main__":
    start()