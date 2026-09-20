import os

records = []

def addRec(name, grade1, grade2, grade3):

    average = (grade1 + grade2 + grade3) / 3

    record = {
        "name": name,
        "grade1": grade1,
        "grade2": grade2,
        "grade3": grade3,
        "average": average
    }

    records.append(record)

    print(f"Record of {name} successfully added.")

    return


def updateRec(name):

    for rec in records:

        if rec["name"] == name:

            print("Enter new grades:")

            rec["grade1"] = float(input("Input Grade 1: "))
            rec["grade2"] = float(input("Input Grade 2: "))
            rec["grade3"] = float(input("Input Grade 3: "))

            rec["average"] = (
                rec["grade1"] +
                rec["grade2"] +
                rec["grade3"]
            ) / 3

            print(f"Record of {name} successfully updated.")
            return

    print(f"Record of {name} not found.")


def delRec(name):

    for rec in records:

        if rec["name"] == name:

            records.remove(rec)

            print(f"Record of {name} successfully deleted.")

            return

    print(f"Record of {name} not found.")


def display():
    
    print("\n\n{:<15} {:<10} {:<10} {:<10} {:<10} {:<10}".format(
        "Name", "Grade1", "Grade2", "Grade3", "Average", "Status"
    ))

    print("*" * 70)

    for rec in records:

        status = "Passed" if rec["average"] >= 75 else "Failed"

        print("{:<15} {:<10} {:<10} {:<10} {:<10.2f} {:<10}".format(
            rec["name"],
            rec["grade1"],
            rec["grade2"],
            rec["grade3"],
            rec["average"],
            status
        ))

    print("*" * 70)


def save_records():

    with open("records.txt", "w") as file:

        for rec in records:

            file.write(
                f"{rec['name']},"
                f"{rec['grade1']},"
                f"{rec['grade2']},"
                f"{rec['grade3']}\n"
            )


def load_records():

    if os.path.exists("records.txt"):

        with open("records.txt", "r") as file:

            for line in file:

                name, grade1, grade2, grade3 = line.strip().split(",")

                average = (
                    float(grade1) +
                    float(grade2) +
                    float(grade3)
                ) / 3

                records.append({
                    "name": name,
                    "grade1": float(grade1),
                    "grade2": float(grade2),
                    "grade3": float(grade3),
                    "average": average
                })


def start():

    load_records()

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

                addRec(name, grade1, grade2, grade3)

            case 2:

                name = input("Input name to update: ")

                updateRec(name)

            case 3:

                name = input("Input name to delete: ")

                delRec(name)

            case 4:

                display()

            case 5:

                print("Saving and Exiting the program...")

                save_records()

                break

            case _:

                print("Invalid choice.")


if __name__ == "__main__":

    start()