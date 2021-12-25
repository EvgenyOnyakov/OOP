#include <iostream>
#include <string>
#include <regex>

using namespace std;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создать программу, которая считывает целое число типа int.
// И поставить «защиту от дурака»: если пользователь вводит что-то кроме одного целочисленного значения, 
// нужно вывести сообщение об ошибке и предложить ввести число еще раз. 
// Пример неправильных введенных строк: rbtrb nj34njkn 1n

void aFoolproofSecuritySystem()
{
    regex reg("^-{0,1}\\d{1,}$");
    smatch match;
    string value;
    
    do
    {
        cout << "Введите целое число типа int:";
        getline(cin, value);
        if (regex_match(value, match, reg))
            cout << "Введено число: " << value << endl;
        else
            cerr << "Ошибка, введено не целое число!" << endl << endl;
    } while (!regex_match(value, match, reg));
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
 
// Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки и сбрасывает буфер.

template< class CharT, class Traits >
basic_ostream<CharT, Traits>& endll(basic_ostream<CharT, Traits>& os)
{
    os.put(os.widen('\n'));
    os.put(os.widen('\n'));
    os.flush();
    return os;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================
    {
        cout << endl << "  ========== Домашнее задание № 1 ========== " << endl << endl;

        aFoolproofSecuritySystem();     
    }
     
    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
    {
        cout << endl << "  ========== Домашнее задание № 2 ========== " << endl << endl;

        cout << "Первая строка" << endll << "Вторая строка" << endl;
        return 0;
    }
}
