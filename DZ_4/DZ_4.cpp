#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

// Добавить в контейнерный класс, который был написан в этом уроке, методы:
// для удаления последнего элемента массива(аналог функции pop_back() в векторах)
// для удаления первого элемента массива(аналог pop_front() в векторах)
// для сортировки массива
// для вывода на экран элементов.

class ArrayInt
{
private:
    int* m_data;
    int m_length;
public:
    ArrayInt() : m_length(0), m_data(nullptr) {}

    ArrayInt(int length) : m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    int& operator [] (int index) 
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void clear()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int size() const { return m_length; }

    void resize(int newLenght) 
    {
        assert(newLenght >= 0);

        if (m_length == newLenght)
            return;

        if (newLenght <= 0)
        {
            clear();
            return;
        }

        int* data = new int[newLenght];
        if (m_length > 0)
        {
            int elementsToCopy = (newLenght > m_length) ? m_length : newLenght;
            for (size_t i = 0; i < elementsToCopy; i++)
            {
                data[i] = m_data[i];
            }
        }

        delete[]  m_data;
        m_data = data;
        m_length = newLenght;
    }   

    void pop_front()
    {
        int* data = new int[--m_length];

        for (size_t i = 0; i < m_length; i++)
        {
            data[i] = m_data[i+1];
        }

        delete[]  m_data;
        m_data = data;
    }

    void pop_back()
    {
        if (m_length) --m_length;
    }

    void sort() 
    {   
        bool flag = true;
        for (int i = 0; i < m_length; i++)
        {
            for (int j = 0; j < m_length - (i + 1); j++)
            {
                if (m_data[j] > m_data[j + 1])
                {
                    flag = false;
                    swap(m_data[j], m_data[j + 1]);
                }
            }
            if (flag)
            {
                break;
            }
        }
    }

    void print()
    {
        for (size_t i = 0; i < m_length; i++)
        {            
            cout << m_data[i] << " ";
        }
        cout << endl;
    }

    ~ArrayInt() { delete[] m_data; }
};

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

// Дан вектор чисел, требуется выяснить, сколько среди них различных.Постараться использовать максимально быстрый алгоритм.

void arrVector()
{ 
    vector<int> array = { 1, 2, 3, 1, 2, 4 };

    vector<int>::const_iterator it; 
    it = array.begin(); 
    cout << "Весь массив:         ";
    while (it != array.end()) 
    {
        cout << *it << " "; 
        ++it; 
    }
    cout << endl;
    sort(array.begin(), array.end());
    int results = unique(array.begin(), array.end()) - array.begin();
    cout << "Различных элементов: " << results << endl;
}

// ================================ ДОМАШНЕЕ ЗАДАНИЕ № 3 ================================

// Реализовать класс Hand, который представляет собой коллекцию карт.
// В классе будет одно поле : вектор указателей карт(удобно использовать вектор, т.к.это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card).
// Также в классе Hand должно быть 3 метода :
//    метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
//    метод Clear, который очищает руку от карт
//    метод GetValue, который возвращает сумму очков карт руки(здесь предусмотреть возможность того, что туз может быть равен 11).

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
    Hand(){ m_Cards.reserve(7); };
   
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
    
    virtual ~Hand(){ Clear(); };
};

int main()
{
    setlocale(LC_ALL, "Russian");

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 1 ================================

    cout << "  ========== Домашнее задание № 1 ========== " << endl << endl;

    ArrayInt arr(5);  
    arr[0] = 4;
    arr[1] = 2;
    arr[2] = 5;
    arr[3] = 1;
    arr[4] = 3;
    arr.print(); 
    arr.sort();
    arr.print();
    arr.pop_back();
    arr.print();
    arr.pop_front();
    arr.print();
    arr.pop_back();
    arr.print();
    arr.pop_front();
    arr.print();

    // ================================ ДОМАШНЕЕ ЗАДАНИЕ № 2 ================================

    cout << endl << "  ========== Домашнее задание № 2 ========== " << endl << endl;

    arrVector();
}