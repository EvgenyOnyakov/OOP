#include <iostream>

using namespace std;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создать класс Person(человек) с полями : имя, возраст, пол и вес.
// Определить методы переназначения имени, изменения возраста и веса.
// Создать производный класс Student(студент), имеющий поле года обучения.
// Определить методы переназначения и увеличения этого значения.
// Создать счетчик количества созданных студентов.
// В функции main() создать несколько(не больше трёх) студентов.Вывести информацию о них.

class Person 
{
protected:
    string       m_name   = "Alex";
    unsigned int m_age    = 18;
    string       m_gender = "мужской";
    unsigned int m_weight = 60;
public:
    Person(){}

    Person(string name, unsigned int age, string gender, unsigned int weight) : m_name(name), m_age(age), m_gender(gender), m_weight(weight) {}

    string getName()   const { return m_name;   }
    int    getAge()    const { return m_age;    }
    string getGender() const { return m_gender; }
    int    getWeight() const { return m_weight; }

    int setName(string name)           { this -> m_name   = name;   }
    int setAge(unsigned int age)       { this -> m_age    = age;    }
    int setGender(string gender)       { this -> m_gender = gender; }
    int setWeight(unsigned int weight) { this -> m_weight = weight; }

    ~Person(){}
};

class Student : public Person
{
private:
    unsigned int m_study_years = 1;
    static int counter;
public:
    Student() { counter++; }

    Student(string name, unsigned int age, string gender, unsigned int weight, unsigned int study_years) : Person(name, age, gender, weight), m_study_years(study_years) { counter++; }

    static int getCounter() { return counter; }

    int setStudyYears(unsigned int study_years) { this -> m_study_years = study_years; }
    int increaseStudyYears()                    { this -> m_study_years++; }

    void print() const 
    {
        cout << m_name << " " << m_age << " " << m_gender << " " << m_weight << " " << m_study_years << endl;
    }

    ~Student() { counter--; }
};

int Student::counter = 0;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Создать классы Apple(яблоко) и Banana(банан), которые наследуют класс Fruit(фрукт).
// У Fruit есть две переменные - члена: name(имя) и color(цвет).
// Добавить новый класс GrannySmith, который наследует класс Apple.

class Fruit
{
public:
    string m_name;
    string m_color;
public:      
    Fruit(const string name = "", const string color = ""): m_name(name), m_color(color) {}

    string getName()  const { return m_name;  }
    string getColor() const { return m_color; }    
};

class Apple : public Fruit
{
protected:
    Apple(string name, string color) : Fruit(name, color) {}
public:        
    Apple(string color = "red"):Fruit("apple", color) {}    
};

class Banana : public Fruit
{
public:
    Banana() : Fruit("banana", "yellow") {}
};

class GrannySmith : public Apple
{
public:
    GrannySmith():Apple("Granny Smith apple", "green") {}
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Изучить правила игры в Blackjack.Подумать, как написать данную игру на С++, используя объектно - ориентированное программирование.
// Сколько будет классов в программе ? Какие классы будут базовыми, а какие производными ? 
// Продумать реализацию игры с помощью классов и записать результаты в виде комментария в основном файле сдаваемой работы.

// Мне кажется необходимо будет 4 базовых класса: 1.Карты, 2. Доска для игры, 3. Игрок или компьютер, 4. Сама игра
// и 3 производных класса : 1.(Карты) ---> набор карт 2. (Игрок или компьютер) ---> Игрок , 3. (Игрок или компьютер) ---> Компьютер, 

int main()
{
    setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

    cout << "  ========== Домашнее задание № 1 ========== " << endl << endl;
    Student Alex;
    Alex.print();
    Student Maria("Maria", 21, "женский", 55, 4);
    Maria.print();
    Student Ivan("Ivan", 20, "мужской", 75, 3);
    Ivan.print();
    cout << "Создано обектов класса (Student): " << Student::getCounter() << endl << endl;

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

    cout << endl << "  ========== Домашнее задание № 2 ========== " << endl << endl;

    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n" << endl;

    system("pause");
}