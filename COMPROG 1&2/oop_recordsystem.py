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
                print(f"Record of {name} successfully removed.")
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


class Student(Person):  # child class of Person
    pass


p1 = Student()

p1.addRec("Mel Chor", 12)
p1.addRec("Gas Chor", 22)
p1.addRec("Mel Par", 32)
p1.addRec("Hes Chor", 121)

p1.display()

p1.updateRec("Mel Chor")

p1.display()