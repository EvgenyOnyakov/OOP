#include <iostream>
#include <iomanip>
#include <numbers>
#include <cassert>

using namespace std;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создать абстрактный класс Figure(фигура).
// Его наследниками являются классы Parallelogram(параллелограмм) и Circle(круг).
// Класс Parallelogram — базовый для классов Rectangle(прямоугольник), Square(квадрат), Rhombus(ромб).
// Для всех классов создать конструкторы.Для класса Figure добавить чисто виртуальную функцию area() (площадь).
// Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.

class Figure  // фигура
{
public:
    virtual double area() = 0;
};

class Circle : public Figure // круг
{
private:
    double m_radius;
public:
    Circle(double rad): m_radius(rad) {}
    double area() { return numbers::pi * pow(m_radius,2); }
};

class Parallelogram : public Figure // параллелограмм
{
protected:
    double m_side;
    double m_height;
    Parallelogram (double side, double height) : m_side(side),m_height(height) {}
};

class Rectangle : public Parallelogram // прямоугольник
{
public:
    Rectangle(double side, double height) : Parallelogram(side,height){}
    double area() override { return m_side * m_height; }
};

class Square : public Parallelogram // квадрат
{
public:
    Square(double side) : Parallelogram(side, side) {}
    double area() override { return m_side * m_height; }
};

class Rhombus : public Parallelogram //ромб
{
public:
    Rhombus(double side, double height) : Parallelogram(side, height) {}
    double area() override { return m_side * m_height; }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Создать класс Car(автомобиль) с полями company(компания) и model(модель).
// Классы - наследники: PassengerCar(легковой автомобиль) и Bus(автобус).
// От этих классов наследует класс Minivan(минивэн).
// Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
// Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы.
// Обратить внимание на проблему «алмаз смерти».

class Car
{
protected:
    string m_company;
    string m_model;
public:
    Car(string company, string model): m_company(company), m_model(model) 
    { cout << "Автомобиль          компании: " << m_company << " | Модель: " << m_model << endl; }
};

class PassengerCar : virtual public Car
{
public:
    PassengerCar(string company, string model) : Car(company, model) 
    { cout << "Легковой автомобиль компании: " << m_company << " | Модель: " << m_model << endl; }
    //~PassengerCar() { cout << "~ PassengerCar" << endl; }
};

class Bus : virtual public Car
{
public:
    Bus(string company, string model) : Car(company, model) 
    { cout << "Автобус             компании: " << m_company << " | Модель: " << m_model << endl; }
    //~Bus() { cout << "~ Bus" << endl; }
};

class Minivan : public PassengerCar, public Bus
{
public:
    Minivan(string company, string model) : Car(company, model), PassengerCar(company, model), Bus(company, model) 
    { cout << "Минивен             компании: " << m_company << " | Модель: " << m_model << endl; }
    //~Minivan() { cout << "~ Minivan" << endl; }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Создать класс : Fraction(дробь).Дробь имеет числитель и знаменатель(например, 3 / 7 или 9 / 2).Предусмотреть, чтобы знаменатель не был равен 0. 
// Перегрузить : математические бинарные операторы(+, -, *, / ) для выполнения действий с дробями 
// унарный оператор(-) логические операторы сравнения двух дробей(== , != , <, >, <= , >= ).
// Примечание : Поскольку операторы < и >= , > и <= — это логические противоположности, попробуйте перегрузить один через другой.
// Продемонстрировать использование перегруженных операторов.

class Fraction
{
private:
    double m_numerator;
    double m_denominator;
public:
    Fraction(double numerator, double denominator) : m_numerator(numerator), m_denominator(denominator) { assert(denominator != 0); }
    void printFraction()
    {
        if (m_numerator == 0)
        {
            cout << "0" << endl;
        }
        else if (m_numerator == m_denominator)
        {
            cout << "1" << endl;
        }
        else
        {
            cout << m_numerator << "/" << m_denominator << endl;
        }
    }
    
    friend Fraction operator +  (Fraction& fr_1, Fraction& fr_2);
    friend Fraction operator -  (Fraction& fr_1, Fraction& fr_2);
    friend Fraction operator *  (Fraction& fr_1, Fraction& fr_2);
    friend Fraction operator /  (Fraction& fr_1, Fraction& fr_2);
    friend bool     operator == (Fraction& fr_1, Fraction& fr_2);
    friend bool     operator != (Fraction& fr_1, Fraction& fr_2);
    friend bool     operator <  (Fraction& fr_1, Fraction& fr_2);
    friend bool     operator >  (Fraction& fr_1, Fraction& fr_2);
    friend bool     operator <= (Fraction& fr_1, Fraction& fr_2);
    friend bool     operator >= (Fraction& fr_1, Fraction& fr_2);
    Fraction        operator -  () const;
};

Fraction Fraction::operator - () const
{
    return Fraction(-m_numerator, m_denominator);
}

Fraction operator + (Fraction& fr_1, Fraction& fr_2)
{
    const double new_numerator   { fr_1.m_numerator * fr_2.m_denominator + fr_2.m_numerator * fr_1.m_denominator };
    const double new_denominator { fr_1.m_denominator * fr_2.m_denominator };
    return Fraction(new_numerator, new_denominator);
}

Fraction operator - (Fraction& fr_1, Fraction& fr_2)
{
    const double new_numerator   { fr_1.m_numerator * fr_2.m_denominator - fr_2.m_numerator * fr_1.m_denominator };
    const double new_denominator { fr_1.m_denominator * fr_2.m_denominator };
    return Fraction(new_numerator, new_denominator);
}

Fraction operator * (Fraction& fr_1, Fraction& fr_2)
{
    const double new_numerator   { fr_1.m_numerator * fr_2.m_numerator };
    const double new_denominator { fr_1.m_denominator * fr_2.m_denominator };
    return Fraction(new_numerator, new_denominator);
}

Fraction operator / (Fraction& fr_1, Fraction& fr_2)
{
    const double new_numerator   { fr_1.m_numerator * fr_2.m_denominator };
    const double new_denominator { fr_1.m_denominator * fr_2.m_numerator };
    return Fraction(new_numerator, new_denominator);
}

bool operator == (Fraction& fr_1, Fraction& fr_2)
{
    return fr_1.m_numerator / fr_1.m_denominator == fr_2.m_numerator / fr_2.m_denominator;
}

bool operator != (Fraction& fr_1, Fraction& fr_2)
{
    return !(fr_2 == fr_1);
}

bool operator < (Fraction& fr_1, Fraction& fr_2)
{
    return fr_1.m_numerator * fr_2.m_denominator < fr_2.m_numerator* fr_1.m_denominator;
}

bool operator > (Fraction& fr_1, Fraction& fr_2)
{
    return fr_1.m_numerator * fr_2.m_denominator > fr_2.m_numerator * fr_1.m_denominator;
}

bool operator <= (Fraction& fr_1, Fraction& fr_2)
{
    return !(fr_2 > fr_1);
}

bool operator >= (Fraction& fr_1, Fraction& fr_2)
{
    return !(fr_1 < fr_2);
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 4 ================================

// Создать класс Card, описывающий карту в игре БлэкДжек.У этого класса должно быть три поля : масть, значение карты и положение карты(вверх лицом или рубашкой).
// Сделать поля масть и значение карты типом перечисления(enum).
// Положение карты - тип bool.
// Также в этом классе должно быть два метода :метод Flip(), который переворачивает карту, т.е.если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
// метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.

class Card
{
protected:

    enum Card_Rank
    {
        RANK_2,
        RANK_3,
        RANK_4,
        RANK_5,
        RANK_6,
        RANK_7,
        RANK_8,
        RANK_9,
        RANK_10,
        RANK_JACK,
        RANK_QUEEN,
        RANK_KING,
        RANK_ACE        
    };

    enum Card_Suit
    {
        SUIT_CLUB,
        SUIT_DIAMOND,
        SUIT_HEART,
        SUIT_SPADE,
    };
    
    Card_Rank m_Rank;
    Card_Suit m_Suit;
    bool m_IsFaceUp = false;

public:

    Card(Card_Rank rank, Card_Suit suit, bool IsFaceUp) : m_Rank(rank), m_Suit(suit), m_IsFaceUp(IsFaceUp) {}

    void Flip()
    {
        if (m_IsFaceUp)
            m_IsFaceUp = true;
        else
            m_IsFaceUp = false;
    }

    int GetValue()
    {
        switch (m_Rank)
        {
        case RANK_2:	 return 2;
        case RANK_3:	 return 3;
        case RANK_4:	 return 4;
        case RANK_5:	 return 5;
        case RANK_6:	 return 6;
        case RANK_7:	 return 7;
        case RANK_8:	 return 8;
        case RANK_9:	 return 9;
        case RANK_10:	 return 10;
        case RANK_JACK:	 return 10;
        case RANK_QUEEN: return 10;
        case RANK_KING:	 return 10;
        case RANK_ACE:	 return 11;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

    cout << "  ========== Домашнее задание № 1 ========== " << endl << endl;

    Circle    sCircle    (3);
    Rectangle sRectangle (2, 4);
    Square    sSquare    (5);
    Rhombus   sRhombus   (5, 3);
    cout << "Площадь круга          = " << sCircle.area()    << endl
         << "Площадь прямоугольникa = " << sRectangle.area() << endl
         << "Площадь квадратa       = " << sSquare.area()    << endl
         << "Площадь ромбa          = " << sRhombus.area()   << endl;

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
    
    cout << endl << "  ========== Домашнее задание № 2 ========== " << endl << endl;

    Car          Car  ("Лада", "калина");
    PassengerCar pCar ("Лада", "гранта");
    Bus          bCar ("ПАЗ ", "аврора");
    Minivan      mCar ("Лада", "Ларгус");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

    cout << endl << "  ========== Домашнее задание № 3 ========== " << endl << endl;

    Fraction fr_1(2, 1);
    fr_1.printFraction();
    Fraction fr_2(3, 4);
    fr_2.printFraction();
    Fraction fr_3 = fr_1 + fr_2;
    fr_3.printFraction();
    fr_3 = fr_1 - fr_2;
    fr_3.printFraction();
    fr_3 = fr_1 * fr_2;
    fr_3.printFraction();
    fr_3 = fr_1 / fr_2;
    fr_3.printFraction();
    fr_3 = -fr_1;
    fr_3.printFraction();
    fr_3 = fr_1;
   
    if (fr_1 == fr_3)
    {
        cout << "Дроби равны" << endl;
    }
    if (fr_1 != fr_2)
    {
        cout << "Дроби не равны" << endl;
    }
    if (fr_1 > fr_2)
    {
        cout << "Первая дробь больше втрой" << endl;
    }
   
    cout << endl;
}