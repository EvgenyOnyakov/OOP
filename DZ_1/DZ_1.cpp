#include <iostream>
#include <cmath>
#include <cstdint>
using namespace std;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создать класс Power, который содержит два вещественных числа.
// Этот класс должен иметь две переменные - члена для хранения этих вещественных чисел.
// Еще создать два метода : один с именем set, который позволит присваивать значения переменным, 
// второй — calculate, который будет выводить результат возведения первого числа в степень второго числа.
// Задать значения этих двух чисел по умолчанию.

class Power 
{
private:
    double foo;
    double bar;
public:
    Power() : foo(1.1), bar(2.2) {};
    void setPower(double first, double second)
    {
        foo = first;
        bar = second;
    }
    void calculatePower()
    {            
        cout << "Pезультат возведения первого числа в степень второго числа: " << pow(foo, bar) << endl;
    }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Написать класс с именем RGBA, который содержит 4 переменные - члена типа std::uint8_t: m_red, m_green, m_blue и m_alpha(#include cstdint для доступа к этому типу).
// Задать 0 в качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha.
// Создать конструктор со списком инициализации членов, который позволит пользователю передавать значения для m_red, m_blue, m_green и m_alpha.
// Написать функцию print(), которая будет выводить значения переменных - членов.

class RGBA
{
private:
    uint8_t m_red, m_green, m_blue, m_alpha;
public:
    RGBA() :m_red(0), m_green(0), m_blue(0), m_alpha(0) {};
    RGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {};
    void print()
    {
        cout << "RGBA(" << m_red << "," << m_green << "," << m_blue << "," << m_alpha << ")" << endl;
    }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Написать класс, который реализует функциональность стека. Класс Stack должен иметь:
// private-массив целых чисел длиной 10;
// private целочисленное значение для отслеживания длины стека;
// public-метод с именем reset(), который будет сбрасывать длину и все значения элементов на 0;
// public-метод с именем push(), который будет добавлять значение в стек. push() должен возвращать значение false, если массив уже заполнен, и true в противном случае;
// public-метод с именем pop() для вытягивания и возврата значения из стека. Если в стеке нет значений, то должно выводиться предупреждение;
// public-метод с именем print(), который будет выводить все значения стека.

class Stack
{
private: 
    static const int SIZE = 10;
    int arr[SIZE];    
    int index;
public:
    void reset() 
    {
        index = 0;
        for (size_t i = 0; i < SIZE; i++)
        {
            arr[i] = 0;
        }
    }
    bool push(int val)
    {
        if (index == 0)
        {
            arr[0] = val;
            index++;
        }
        else if (index > 0)
        {
            arr[index] = val;
            index++;
        }
        if (index == 10)
            return false;
        else
            return true;
    }
    void pop()
    {
        if (index == 0)
            cout << "Ошибка: стек пустой" << endl;
        else 
        {
            arr[index - 1] = 0;
            index--;
        }
    }
    void print()
    {
        cout << "( ";
        for (size_t i = 0; i < index; i++)
        {            
            cout << arr[i] << " ";
        }
        cout << ")" << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

    cout << "  ========== Домашнее задание № 1 ========== " << endl << endl;
    cout << "Введите первое вещественное число: ";
    double first, second;
    cin >> first;
    cout << "Введите второе вещественное число: ";
    cin >> second;
    Power FOO;
    FOO.setPower(first, second);
    FOO.calculatePower();

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

    cout << endl << "  ========== Домашнее задание № 2 ========== " << endl << endl;
    uint8_t red, green, blue, alpha;
    cout << "Введите значение переменной red:   ";
    cin >> red;
    cout << "Введите значение переменной green: ";
    cin >> green;
    cout << "Введите значение переменной blue:  ";
    cin >> blue;
    cout << "Введите значение переменной alpha: ";
    cin >> alpha;

    RGBA mycolor(red, green, blue, alpha);
    mycolor.print(); 

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

    cout << endl << "  ========== Домашнее задание № 3 ========== " << endl << endl;
    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();
    cout << endl;

    system("pause");
    return 0;
}