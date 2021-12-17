#include <iostream>
#include <chrono>

using namespace std;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. 
// Перегрузите оператор вывода для данного класса. Создайте два "умных" указателя today и date. 
// Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа к полям класса Date, 
// а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода. 
// Затем переместите ресурс, которым владеет указатель today в указатель date. 
// Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.

class Date
{
private:
	int m_day = 01;
	int m_month = 01;
	int m_year = 1900;
public:
	Date(){}
	Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

	const int& getDay() const
	{
		return m_day;
	}

	const int& getMonth() const
	{
		return m_month;
	}

	const int& getYear() const
	{
		return m_year;
	}

	friend ostream& operator<< (ostream& out, const Date& date)
	{
		out << date.m_day << "." << date.m_month << "." << date.m_year << "\n";
		return out;
	}

	void check_NULL(Date& ptr)
	{
		bool NorN = (bool)&ptr;
		if (NorN)
			cout << "NOT_NULL" << endl;
		else
			cout << "__NULL__" << endl;
	}

	Date more_or_less(Date& ptr1, Date& ptr2)
	{
		if (ptr1.getDay() > ptr2.getDay() || ptr1.getMonth() > ptr2.getMonth() || ptr1.getYear() > ptr2.getYear() )
			return ptr1;
		else
			return ptr2;
	}

	void SWAP(Date& ptr1, Date& ptr2)
	{
		unique_ptr<Date> tmp = make_unique<Date>();
		*tmp = ptr2;
		ptr2 = move(ptr1);
		ptr1 = *tmp;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================
	
		cout << endl << "  ========== Домашнее задание № 1 ========== " << endl << endl;
		unique_ptr<Date> today = make_unique<Date>(17,12,2021);
		unique_ptr<Date> date  = make_unique<Date>();		
		
		cout << today->getDay() << "/" << today->getMonth() << "/" << today->getYear() << endl;
		cout << *today << endl;

		date = move(today);
		today->check_NULL(*today);		
		date ->check_NULL(*date);	

	// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
		
	// По условию предыдущей задачи создайте два умных указателя date1 и date2.
	// Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой(сравнение происходит по датам).
	// Функция должна вернуть более позднюю дату.
	// Создайте функцию, которая обменивает ресурсами(датами) два умных указателя, переданных в функцию в качестве параметров.
	// Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.
	
		cout << endl << "  ========== Домашнее задание № 2 ========== " << endl << endl;
		unique_ptr<Date> date1 = make_unique<Date>(1,12,2000);
		unique_ptr<Date> date2 = make_unique<Date>(31,12,2020);
		cout << "Наибольшая дата: " << date->more_or_less(*date1, *date2) << endl;

		cout << "До обмена значениями:    " << endl << *date1 << *date2 << endl;
		date->SWAP(*date1, *date2);
		cout << "После обмена значениями: " << endl << *date1 << *date2 << endl;

		// Зачем изобретать велосипед, если можно сделать так?
		date2.swap(date1);
		cout << "Просто SWAP: " << endl << *date1 << *date2 << endl;	
}