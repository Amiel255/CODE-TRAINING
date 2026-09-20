import random, json, os
records = []

class Person:
    def __init__(self):
        self.records = []

    def addRec(self,name, age, g1, g2, g3):
        rec = {"name": name, "age": age, "Grade 1": g1, "Grade 2": g2, "Grade 3": g3, "average": (g1+g2+g3)/3}
        self.records.append(rec)
        self.records.sort(key=lambda x: x["average"], reverse= True)

    def updateRec(self, name, age, g1, g2, g3):
        for rec in self.records:
            if rec["name"] == name:
                rec["age"], rec["g1"], rec["g2"], rec["g3"] = age, g1, g2, g3
                rec["average"] = ((g1+g2+g3)/3)
                self.records.sort(key=lambda rec: rec["average"], reverse= True)
                return
        return("No record found")    
    
    def deleteRec(self, name):
        if not self.records:
            print("No record to delete")
            return
        
        for rec in self.records:
            if rec["name"] == name:
                self.records.remove(rec)
                return
            
        print("Record not found")
               
    def display(records):
        print("{:<15} {:<5} {:<8} {:<8} {:<8} {:<8} {:<8}".format("Name", "Age", "G1", "G2", "G3", "AVE", "Status"))
        for rec in records:
                print("{:<15} {:<5} {:<8} {:<8} {:<8} {:<8} {:<8}".format( 
                                                                          rec["name"], rec["age"], rec["Grade 1"], rec["Grade 2"], rec["Grade 3"], rec["average"], "PASSED" if rec["average"] >= 75 else "FAILED"))
        
    def saveRec(self):
        with open("records2.json", "w") as file:
            json.dump(self.records, file, indent = 4)
            
    def loadRec(self):
        if os.path.exists("records2.json"):
            try:
                with open("recordstwo.json", "r") as file:
                    self.records = json.load(file)
            except json.JSONDecodeError:
                self.records = []
        else:
            self.records = []
            
class Student(Person):
    pass

def menu():
    print("1 Add")
    print("2 Update")
    print("3 Delete")
    print("4 Display")
    print("5 Exit")
    return int(input("Select choice: "))

def start():
    s = Student()
    s.loadRec
    
    while True:
        choice = menu()
        
        match choice:
            case 1: 
                n = input("Name: ")
                a = int(input("Age:"))
                g1 =float(input("Grade 1:"))
                g2 =float(input("Grade 2:"))
                g3 =float(input("Grade 3:"))
                s.addRec(n, a, g1, g2, g3)
            case 2:
                n = input("Name to update: ")
                a = int(input("New Age:"))
                g1 =float(input("New Grade 1:"))
                g2 =float(input("New Grade 2:"))
                g3 =float(input("New Grade 3:"))
                s.updateRec(n, a, g1, g2, g3)
            case 3: 
                n = input("Input name to delete:")
                s.deleteRec(n)
            case 4:
                s.display()
            case 5:
                s.saveRec
                break
            case _:
                print("Invalid Choice")
                
if __name__ == "__main__":
    start()