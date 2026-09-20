#include <iostream>
#include <string>
using namespace std;

class Animal
{
private:
    string name;

public:
    Animal(string animalName)
    {
        setName(animalName);
    }

    // Setter
    void setName(string animalName)
    {
        if (!animalName.empty())
        {
            name = animalName;
        }
        else
        {
            name = "Unknown";
        }
    }

    // Getter
    string getName() const
    {
        return name;
    }

    // Virtual function
    virtual void animalSound() const
    {
        cout << "The animal makes a sound.\n";
    }

    void display() const
    {
        cout << "Name: " << getName() << '\n';
        animalSound();
    }

    virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
    Dog(string name) : Animal(name)
    {
    }

    void animalSound() const override
    {
        cout << "The dog says Woof!\n";
    }
};

class Cat : public Animal
{
public:
    Cat(string name) : Animal(name)
    {
    }

    void animalSound() const override
    {
        cout << "The cat says Meow!\n";
    }
};

int main()
{
    Dog dog("Chewi");
    Cat cat("Pusa");

    dog.display();

    cout << '\n';

    cat.display();

    return 0;
}