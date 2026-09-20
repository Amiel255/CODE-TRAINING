import os
import json

records = []


def addRec(name, age):
    record = {"name": name, "age": age}
    records.append(record)
    print(f"Record of {name} successfully added.")


def updateRec(name):
    for rec in records:
        if rec["name"] == name:
            rec["age"] = int(input("Input new age: "))
            print(f"Record of {name} successfully updated.")
            return

    print(f"Record of {name} not found.")


def delRec(name):
    if not records:
        print("No records to delete.")
        return

    for rec in records:
        if rec["name"] == name:
            records.remove(rec)
            print(f"Record of {name} successfully deleted.")
            return

    print(f"Record of {name} not found.")


def display():
    if not records:
        print("No records to display.")
        return

    print("{:<20} {:<10} {:<10}".format("Name", "Age", "Remarks"))
    print("-" * 40)

    for rec in records:
        print("{:<20} {:<10} {:<10}".format(
            rec["name"],
            rec["age"],
            "Adult" if rec["age"] >= 18 else "Minor"
        ))

    print("-" * 40)


def save_records():
    with open("records.json", "w") as file:
        json.dump(records, file, indent=4)

    print("Records saved successfully.")


def load_records():
    global records

    if os.path.exists("records.json"):
        try:
            with open("records.json", "r") as file:
                records = json.load(file)

            print("Records loaded successfully.")

        except json.JSONDecodeError:
            records = []
            print("File corrupted or empty. Starting fresh.")
    else:
        records = []


def start():
    load_records()

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
                addRec(name, age)

            case 2:
                name = input("Input name to update: ")
                updateRec(name)

            case 3:
                name = input("Input name to delete: ")
                delRec(name)

            case 4:
                display()

            case 5:
                print("Saving and exiting the program...")
                save_records()
                break

            case _:
                print("Invalid choice.")


if __name__ == "__main__":
    start()