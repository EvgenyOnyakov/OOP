#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// ======================================================= CARD =======================================================

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

    int GetValue() const
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

    friend ostream& operator<<(ostream& os, const Card& aCard);
};

ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "c", "d", "h", "s" };

    if (aCard.m_IsFaceUp)
    {
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    }
    else
    {
        os << "XX";
    }

    return os;
}

// ======================================================= HAND =======================================================

class Hand
{
protected:
    vector<Card*> m_Cards;

public:
    Hand() { m_Cards.reserve(7); };

    // добавляет карту в руку
    void Add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }

    // очищает руку от карт
    void Clear()
    {
        // проходит по вектору, освобождая всю память в куче
        vector<Card*>::iterator iter = m_Cards.begin();

        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            delete* iter;
            *iter = 0;
        }
        // очищает вектор указателей
        m_Cards.clear();
    }

    // получает сумму очков карт в руке, присваивая тузу
    // значение 1 или 11 в зависимости от ситуации
    int GetTotal() const
    {
        // если карт в руке нет, возвращает значение 0
        if (m_Cards.empty())
        {
            return 0;
        }

        // если первая карта имеет значение 0, то она лежит рубашкой вверх:
        // вернуть значение 0
        if (m_Cards[0]->GetValue() == 0)
        {
            return 0;
        }

        // находит сумму очков всех карт, каждый туз дает 1 очко
        int total = 0;
        vector<Card*>::const_iterator iter;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            total += (*iter)->GetValue();
        }

        // определяет, держит ли рука туз
        bool containsAce = false;
        for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        {
            if ((*iter)->GetValue() == Card::RANK_ACE)
            {
                containsAce = true;
            }
        }

        // если рука держит туз и сумма довольно маленькая, туз дает 11 очков
        if (containsAce && total <= 11)
        {
            // добавляем только 10 очков, поскольку мы уже добавили
            // за каждый туз по одному очку
            total += 10;
        }

        return total;
    }

    virtual ~Hand() { Clear(); };
};

// ======================================================= GENERIC PLAYER =======================================================

class GenericPlayer : public Hand
{
protected:
    string m_Name;

public:
    GenericPlayer() {}
    GenericPlayer(const string& name) : m_Name(name) {}

    virtual bool IsHitting() const = 0;

    bool IsBusted() { return (GetTotal() > 21); }

    void Bust() const { cout << m_Name << " - перебор" << endl; }

    virtual ~GenericPlayer() {};

    friend ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer);
};

ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.m_Name << ":\t";

    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard)
        {
            os << *(*pCard) << "\t";
        }

        if (aGenericPlayer.GetTotal() != 0)
        {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }

    return os;
}

// ======================================================= PLAYER =======================================================

class Player : public GenericPlayer
{
public:
    
    Player(const string& name = "") : GenericPlayer(name) {}

    virtual ~Player() {}

    // показывает, хочет ли игрок продолжать брать карты
    virtual bool IsHitting() const
    {
        cout << m_Name << ", хотите взять еще карту? (Y/N): ";
        char response;
        cin >> response;
        return (response == 'y' || response == 'Y');
    }

    // объявляет, что игрок победил
    void Win() const
    {
        cout << m_Name << " победил.\n";
    }

    // объявляет, что игрок проиграл
    void Lose() const
    {
        cout << m_Name << " проиграл.\n";
    }

    // объявляет ничью
    void Push() const
    {
        cout << m_Name << " ничья.\n";
    }
};

// ======================================================= HOUSE =======================================================

class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) {}

    virtual ~House(){}

    // показывает, хочет ли дилер продолжать брать карты
    virtual bool IsHitting() const
    {
        return (GetTotal() <= 16);
    }

    // переворачивает первую карту
    void FlipFirstCard()
    {
        if (!(m_Cards.empty()))
        {
            m_Cards[0]->Flip();
        }
        else
        {
            cout << "Нет карты, чтобы перевернуть!\n";
        }
    }

};

// ======================================================= DECK =======================================================

class Deck : public Hand
{
public:
    Deck()
    {
        m_Cards.reserve(52);
        Populate();
    }
    virtual ~Deck(){}

    // создает стандартную колоду из 52 карт
    void Populate()
    {
        Clear();
        // создает стандартную колоду
        for (int s = Card::SUIT_CLUB; s <= Card::SUIT_SPADE; ++s)
        {
            for (int r = Card::RANK_ACE; r <= Card::RANK_KING; ++r)
            {
                Add(new Card(static_cast<Card::Card_Rank>(r),
                    static_cast<Card::Card_Suit>(s)));
            }
        }
    }

    // тасует карты
    void Shuffle()
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(m_Cards.begin(), m_Cards.end(), g);        
    }

    // раздает одну карту в руку
    void Deal(Hand& aHand)
    {
        if (!m_Cards.empty())
        {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else
        {
            cout << "Нет карт, раздавать нечего.";
        }
    }

    // дает дополнительные карты игроку
    void AdditionalCards(GenericPlayer& aGenericPlayer)
    {
        cout << endl;
        // продолжает раздавать карты до тех пор, пока у игрока не случается
        // перебор или пока он хочет взять еще одну карту
        while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting())
        {
            Deal(aGenericPlayer);
            cout << aGenericPlayer << endl;
            if (aGenericPlayer.IsBusted())
            {
                aGenericPlayer.Bust();
            }
        }
    }

};

// ======================================================= GAME =======================================================

class Game
{
public:
    Game(const vector<string>& names)
    {
        // создает вектор игроков из вектора с именами
        vector<string>::const_iterator pName;
        for (pName = names.begin(); pName != names.end(); ++pName)
        {
            m_Players.push_back(Player(*pName));
        }
        // запускает генератор случайных чисел
        srand(static_cast<unsigned int>(time(0)));
        m_Deck.Populate();
        m_Deck.Shuffle();
    }

    ~Game(){}

    // проводит игру в Blackjack
    void Play()
    {
        // раздает каждому по две стартовые карты
        vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i)
        {
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                m_Deck.Deal(*pPlayer);
            }
            m_Deck.Deal(m_House);
        }

        // прячет первую карту дилера
        m_House.FlipFirstCard();

        // открывает руки всех игроков
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            cout << *pPlayer << endl;
        }
        cout << m_House << endl;

        // раздает игрокам дополнительные карты
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            m_Deck.AdditionalCards(*pPlayer);
        }

        // показывает первую карту дилера
        m_House.FlipFirstCard();
        cout << endl << m_House;

        // раздает дилеру дополнительные карты
        m_Deck.AdditionalCards(m_House);
        if (m_House.IsBusted())
        {
            // все, кто остался в игре, побеждают
            for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
            {
                if (!(pPlayer->IsBusted()))
                {
                    pPlayer->Win();
                }
            }
        }
        else
        {
            // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера

                for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
                    ++pPlayer)
                {
                    if (!(pPlayer->IsBusted()))
                    {
                            if (pPlayer->GetTotal() > m_House.GetTotal())
                            {
                                 pPlayer->Win();
                            }
                        else if (pPlayer->GetTotal() < m_House.GetTotal())
                        {
                            pPlayer->Lose();
                        }
                        else
                        {
                            pPlayer->Push();
                        }
                    }
                }
        }

        // очищает руки всех игроков
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
        {
            pPlayer->Clear();
        }
        m_House.Clear();
    }

private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "\t\tДобро пожаловать в игру Blackjack!\n\n";

    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "Введите количество игроков (1 - 7): ";
        cin >> numPlayers;
    }

    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Введите имя игрока: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

    // игровой цикл
    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        aGame.Play();
        cout << "\nХотите сыграть снова? (Y/N): ";
        cin >> again;
    }

    return 0;
}