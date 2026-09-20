import os
import json


class Person:
    def __init__(self):
        self.records = []  # list of dictionaries

    def addRec(self, name, age):
        rec = {"name": name, "age": age}
        self.records.append(rec)

        self.records.sort(key=lambda rec: rec["age"], reverse=True)

        print(f"Record of {name} successfully added.")

    def updateRec(self, name):
        for rec in self.records:
            if rec["name"] == name:
                rec["age"] = int(input("Input new age: "))

                self.records.sort(key=lambda rec: rec["age"], reverse=True)

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

        print("{:<20} {:<10} {:<10}".format("Name", "Age", "Remarks"))
        print("-" * 40)

        for rec in self.records:
            print("{:<20} {:<10} {:<10}".format(
                rec["name"],
                rec["age"],
                "Adult" if rec["age"] >= 18 else "Minor"
            ))

        print("-" * 40)

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
        print("\nMenu")
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
                age = int(input("Input age: "))
                s1.addRec(name, age)

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