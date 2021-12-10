#include <iostream>
#include <vector>

using namespace std;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.

template <class T>
class Pair1
{
private:
	T m_foo;
	T m_bar;
public:
	Pair1(const T& f, const T& b) : m_foo(f), m_bar(b) {}

	T&       first()        { return m_foo; }
	const T& first() const  { return m_foo; }
	T&       second()       { return m_bar; }
	const T& second() const { return m_bar; }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.

template <class T1, class T2>
class Pair
{
private:
    T1 m_foo;
    T2 m_bar;
public:
    Pair(const T1& f, const T2& b) : m_foo(f), m_bar(b) {}

    T1&       first()        { return m_foo; }
    const T1& first() const  { return m_foo; }
    T2&       second()       { return m_bar; }
    const T2& second() const { return m_bar; }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа.
// Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, а второй — любого типа данных.

template <class T>
class StringValuePair : public Pair<string, T>
{
public:
    StringValuePair(const string& text, const T& value) : Pair<string, T>(text, value) {}
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 4 ================================

// Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс GenericPlayer, 
// который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.
// Создать класс GenericPlayer, в который добавить поле name - имя игрока.Также добавить 3 метода:
// IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
// IsBoosted() - возвращает bool значение, есть ли у игрока перебор
// Bust() - выводит на экран имя игрока и объявляет, что у него перебор.

class Card
{
public:
    enum Card_Rank
    {
        RANK_ACE = 1,
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
    };

    enum Card_Suit
    {
        SUIT_CLUB,
        SUIT_DIAMOND,
        SUIT_HEART,
        SUIT_SPADE,
    };
protected:
    Card_Rank m_Rank;
    Card_Suit m_Suit;
    bool m_IsFaceUp = false;

public:

    Card(Card_Rank rank, Card_Suit suit, bool IsFaceUp = true) : m_Rank(rank), m_Suit(suit), m_IsFaceUp(IsFaceUp) {}

    void Flip()
    {
        m_IsFaceUp = !(m_IsFaceUp);
    }

    int GetValue()
    {
        int value = 0;
        if (m_IsFaceUp)
        {
            value = m_Rank;
            if (value > 10)
            {
                value = 10;
            }
        }
        return value;
    }
};

class Hand
{
private:
    vector<Card*> m_Cards;

public:
    Hand() { m_Cards.reserve(7); };

    void Add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }

    void Clear()
    {
        vector<Card*>::iterator iter = m_Cards.begin();

        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            delete* iter;
            *iter = 0;
        }

        m_Cards.clear();
    }

    int GetTotal() 
    {
        if (m_Cards.empty())
        {
            return 0;
        }

        if (m_Cards[0]->GetValue() == 0)
        {
            return 0;
        }

        int total = 0;
        vector<Card*>::const_iterator iter;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            total += (*iter)->GetValue();
        }

        bool containsAce = false;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            if ((*iter)->GetValue() == Card::RANK_ACE)
            {
                containsAce = true;
            }
        }

        if (containsAce && total <= 11)
        {
            total += 10;
        }

        return total;
    }

    virtual ~Hand() { Clear(); };
};

class GenericPlayer : public Hand
{
protected:
    string m_Name;

public:
    GenericPlayer(const string& name = ""): m_Name(name) {}
   
    virtual bool IsHitting() const = 0;
    
    bool IsBusted() { return (GetTotal() > 21); }
   
    void Bust() const { cout << m_Name << " - перебор" << endl; }

    virtual ~GenericPlayer() {};
};


int main()
{
    setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================
    {
        cout << "  ========== Домашнее задание № 1 ========== " << endl << endl;

        Pair1<int> p1(6, 9);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << endl;

        const Pair1<double> p2(3.4, 7.8);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << endl;
    }

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================
    {
        cout << endl << "  ========== Домашнее задание № 2 ========== " << endl << endl;

        Pair<int, double> p1(6, 7.8);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << endl;

        const Pair<double, int> p2(3.4, 5);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << endl;
    }

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================
    {
        cout << endl << "  ========== Домашнее задание № 3 ========== " << endl << endl;

        StringValuePair<int> svp("Amazing", 7);
        std::cout << "Pair: " << svp.first() << ' ' << svp.second() << endl << endl;
    }
    return 0;
}